#! /usr/bin/perl -w
#                              -*- Mode: Perl -*- 
# Desi_Remos.pm --- 
# Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
# Created On       : Mon Nov 13 08:05:32 2000
# Created On Node  : glaurung.stdc.com
# Last Modified By : Manoj Srivastava
# Last Modified On : Mon Jan  1 14:11:58 2001
# Last Machine Used: glaurung.stdc.com
# Update Count     : 146
# Status           : Unknown, Use with caution!
# HISTORY          : 
# Description      : 
#  $Id: Desi_Remos.pm,v 1.4 2001/12/02 03:30:27 srivasta Exp $
#


#  Copyright (C) 2001 System/Technology Development Corporation
#  This file is part of QoS Metric Services
#  
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of the
#  License, or (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
#  02111-1307 USA
# 
#  You may contact System/Technology Development Corporation at
# 
#      System/Technology Development Corporation
#      Suite 500, Center for Innovative Technology,
#      2214 Rock Hill Road,
#      Herndon, VA 20170    
#      (703) 476-0687


use strict;
use Carp;
require 5.001;


package QMS::Desi_Remos;
use strict;

use Carp;
use FileHandle;
use XML::DOM;
use QMS::Parse_Qms_Log;

my $VERSION = '$Version$';

=head1 NAME

QMS::Desi_Remos - Parsees application specific B<QMS_EVENT> data payload

=cut

=head1 SYNOPSIS

B<use QMS::Parse_Qms_Log;>

B<use QMS::Desi_Remos;>

  my $handler = QMS::Desi_Remos->new('EventType' => 'bandwidth_data',
                                     'Debug' => 15);
  # Create the parser
  my $log     = QMS::Parse_Qms_Log->new('Call Back' => $handler,
                                        'Out Put'   => \&print_separated,
                                        'Out Args'  => \%write_opts,
                                        'Debug'     => $Debug);

  # Slurp one event at a  time
  $/=$delimiter;
  $log->parse('Log Item' => \%log_item);

=head1 DESCRIPTION

This library takes in a reference to a (sub)tree returned by a DOM XML
parser of the tree representation of the application specific
B<QMS_EVENT> data payload, and constructs a native perl data structure
populated with the documents contents.  This is fairly dependent on
the DTD.

=head2 KNOWN EVENT TYPES

This library contains support for the following event types:

=over 4

=item bandwidth_request

=item bandwidth_data

=item desi_app_data

=back

=cut


my %known_event_type =
  (
   'bandwidth_request' => 1,
   'bandwidth_data'    => 1,
   'desi_app_data'     => 1
  );


#
# Lists of constants used for node types. We use this array to print
# out human readable node type names. Look into AML::DOM for the
# definitions.
#
my %node_types =
  (
   XML::DOM::UNKNOWN_NODE()                => "UNKNOWN_NODE",
   XML::DOM::ELEMENT_NODE()                => "ELEMENT_NODE",
   XML::DOM::ATTRIBUTE_NODE()              => "ATTRIBUTE_NODE",
   XML::DOM::TEXT_NODE()                   => "TEXT_NODE",
   XML::DOM::CDATA_SECTION_NODE()          => "CDATA_SECTION_NODE",
   XML::DOM::ENTITY_REFERENCE_NODE()       => "ENTITY_REFERENCE_NODE",
   XML::DOM::ENTITY_NODE()                 => "ENTITY_NODE",
   XML::DOM::PROCESSING_INSTRUCTION_NODE() => "PROCESSING_INSTRUCTION_NODE",
   XML::DOM::COMMENT_NODE()                => "COMMENT_NODE",
   XML::DOM::DOCUMENT_NODE()               => "DOCUMENT_NODE",
   XML::DOM::DOCUMENT_TYPE_NODE()          => "DOCUMENT_TYPE_NODE",
   XML::DOM::DOCUMENT_FRAGMENT_NODE()      => "DOCUMENT_FRAGMENT_NODE",
   XML::DOM::NOTATION_NODE()               => "NOTATION_NODE",
   XML::DOM::ELEMENT_DECL_NODE()           => "ELEMENT_DECL_NODE",
   XML::DOM::ATT_DEF_NODE()                => "ATT_DEF_NODE",
   XML::DOM::XML_DECL_NODE ()              => "XML_DECL_NODE",
   XML::DOM::ATTLIST_DECL_NODE ()          => "ATTLIST_DECL_NODE",
  );

=head1 METHOD CALLS

This section shall detail the method calls available

=head2 new

This call creates an object that handles the payload data in the
B<QMS_Event> dtd, and which can be passed in to the B<QMS_Log+Parser>
object to handle event specific transforms. It takes in a required
argument, B<EventType>, which must be a known event type, and an
optional argument, B<Debug>.

=cut

sub new {
  my $this = shift;
  my %params = @_;
  my $class = ref($this) || $this;
  my $self = {};

  bless $self => $class;

  die("Uknown Event type $params{'EventType'}")
    unless (defined $params{'EventType'} && $params{'EventType'} &&
	    $known_event_type{$params{'EventType'}}) ;
  $self->{' _event_type'} = $params{'EventType'};

  if (defined ($params{'Debug'}) && $params{'Debug'}) {
    $self->{' _Debug'} = $params{'Debug'};
  }
  else {
    $self->{' _Debug'} = 15;
  }
  return $self;
}

=head2 parse_bandwidth_request

This routine handles the transformations required for the B<Remos>
bandwidth request query document. It takes in a reference to a B<Node>
in a DOM tree, and an output B<Log Item> object to populate.

=cut

sub parse_bandwidth_request {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};

  my $host_num = 0;

  # Get attributes now
  my $attr_list = $params{'Node'}->getAttributes();
  if (defined($attr_list)) {
    print STDERR "DEBUG: parse_bandwidth_request we have ",
      $attr_list->getLength(), " attribute\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 10;

    for (my $i = 0; $i < $attr_list->getLength(); $i++) {
      my $attribute = $attr_list->item($i);

      print STDERR "DEBUG: parse_bandwidth_request ",
	$attribute->getName(), " = ", $attribute->getValue(), "\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 10;

      $params{'Log Item'}{"bandwidth_request " . $attribute->getName()} =
	$attribute->getValue();
    }
  }

  for my $node ($params{'Node'}->getChildNodes()) {
    print STDERR "parse_bandwidth_request (",
      $node_types{$node->getNodeType()},
	") = ", $node->getNodeName(), "\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 10;

    $params{'Log Item'}{"Event Type"} = "bandwidth_request";
    if ($node->getNodeType() == TEXT_NODE()) {

      # Skip all empty text nodes
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      die("Unexpected Text (", $node->getNodeValue());
    }
    elsif ($node->getNodeType() == ELEMENT_NODE()) {
      my $node_name = $node->getNodeName();
      if ($node_name =~ m/(requestid|refreshrate|repeatcount)/og) {
	if ($node_name =~ m/(refreshrate)/og) {
	  my $attr_list = $node->getAttributes();
	  if (defined($attr_list)) {
	    for (my $i = 0; $i < $attr_list->getLength(); $i++) {
	      my $attribute = $attr_list->item($i);
	      $params{'Log Item'}{"$node_name " . $attribute->getName()} = 
		$attribute->getValue();
	    }
	  }
	}

	for my $kid ($node->getChildNodes()) {
	  if ($kid->getNodeType() == TEXT_NODE()) {
	    # Skip all empty text nodes
	    my $value = $kid->getNodeValue();
	    next if ($value =~ /^\s*$/ms);
	    $params{'Log Item'}{"$node_name"} = $kid->getNodeValue();
	  }
	  else {
	    die ("Error: Unknown node type", $kid->getNodeType());
	  }
	}
      }
      elsif ($node_name =~ m/(hostname)/og) {
	for my $kid ($node->getChildNodes()) {
	  if ($kid->getNodeType() == TEXT_NODE()) {
	    # Skip all empty text nodes
	    my $value = $kid->getNodeValue();
	    next if ($value =~ /^\s*$/ms);

	    $params{'Log Item'}{"Hostnames"}[$host_num++] ="$value";
	  }
	  else {
	    die ("Error: Unknown node type", $kid->getNodeType());
	  }
	}
      }
      else {
	die ("Error: Unknown element", $node->getNodeName());
      }
    }
    else {
      die ("Error: Unknown node type", $node->getNodeType());
    }
  }
}


=head2 parse_bandwidth_data

This routine handles the transformations required for the B<Remos>
bandwidth data document. It takes in a reference to a B<Node>
in a DOM tree, and an output B<Log Item> object to populate.

=cut

sub parse_bandwidth_data {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};

  # Get attributes now
  my $attr_list = $params{'Node'}->getAttributes();
  if (defined($attr_list)) {
    print STDERR "DEBUG: parse_bandwidth_data we have ",
      $attr_list->getLength(), "attribute\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 10;

    for (my $i = 0; $i < $attr_list->getLength(); $i++) {
      my $attribute = $attr_list->item($i);

      print STDERR "DEBUG: parse_bandwidth_data ",
	$attribute->getName(), " = ", $attribute->getValue(), "\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 10;

      $params{'Log Item'}{"bandwidth_data " . $attribute->getName()} =
	$attribute->getValue();
    }
  }


  for my $node ($params{'Node'}->getChildNodes()) {
    print STDERR "parse_bandwidth_data (",
      $node_types{$node->getNodeType()},
	") = ", $node->getNodeName(), "\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 10;
    if ($node->getNodeType() == TEXT_NODE()) {
      # Skip all empty text nodes
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      die("Unexpected Text (", $node->getNodeValue());
    }
    elsif ($node->getNodeType() == ELEMENT_NODE()) {
      my $node_name = $node->getNodeName();
      if ($node_name =~ 
	  m/(requestid|dataid|source|destination|latency|available|maximum|collectrate)/og) {
	
	if ($node_name =~ m/(available|maximum|collectrate)/og) {
	  my $attr_list = $node->getAttributes();
	  if (defined($attr_list)) {
	    for (my $i = 0; $i < $attr_list->getLength(); $i++) {
	      my $attribute = $attr_list->item($i);
	      $params{'Log Item'}{"$node_name " . $attribute->getName()} = 
		$attribute->getValue();
	    }
	  }
	}
	for my $kid ($node->getChildNodes()) {
	  if ($kid->getNodeType() == TEXT_NODE()) {
	    # Skip all empty text nodes
	    my $value = $kid->getNodeValue();
	    next if ($value =~ /^\s*$/ms);
	    $params{'Log Item'}{"$node_name"} = $kid->getNodeValue();
	  }
	  else {
	    die ("Error: Unknown node type", $kid->getNodeType());
	  }
	}
      }
      else {
	die ("Error: Unknown element", $node->getNodeName());
      }
    }
    else {
      die ("Error: Unknown node type", $node->getNodeType());
    }
  }
}


=head2 parse_desi_app_message_info

This routine handles the transformations required for the message meta
information for the B<Desi> test application data document. It takes
in a reference to a B<Node> in a DOM tree, and an output B<Log Item>
object to populate.

=cut

sub parse_desi_app_message_info {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};
  for my $node ($params{'Node'}->getChildNodes()) {
    print STDERR "parse_desi_app_message_info (",
      $node_types{$node->getNodeType()},
	") = ", $node->getNodeName(), "\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 12;
    if ($node->getNodeType() == TEXT_NODE()) {

      # Skip all empty text nodes
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      die("Unexpected Text (", $node->getNodeValue());
    }
    elsif ($node->getNodeType() == ELEMENT_NODE()) {
      my $node_name = $node->getNodeName();
      if ($node_name =~ m/(sender|receiver|length|frequency|total)/og) {
	for my $kid ($node->getChildNodes()) {
	  if ($kid->getNodeType() == TEXT_NODE()) {
	    # Skip all empty text nodes
	    my $value = $kid->getNodeValue();
	    next if ($value =~ /^\s*$/ms);
	    $params{'Log Item'}{"$node_name"} = $kid->getNodeValue();
	  }
	  else {
	    die ("Error: Unknown node type", $kid->getNodeType());
	  }
	}
      }
      else {
	die ("Error: Unknown element", $node->getNodeName());
      }
    }
    else {
      die ("Error: Unknown node type", $node->getNodeType());
    }
  }
}

=head2 parse_desi_app_load

This routine handles the transformations required for the data content
portion of the B<Desi> test application data document. It takes in a
reference to a B<Node> in a DOM tree, and an output B<Log Item> object
to populate.

=cut


sub parse_desi_app_load {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};
  for my $node ($params{'Node'}->getChildNodes()) {
    print STDERR "parse_desi_app_load (",
      $node_types{$node->getNodeType()},
	") = ", $node->getNodeName(), "\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 12;
    if ($node->getNodeType() == TEXT_NODE()) {

      # Skip all empty text nodes
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      die("Unexpected Text (", $node->getNodeValue());
    }
    elsif ($node->getNodeType() == ELEMENT_NODE()) {
      my $node_name = $node->getNodeName();
      if ($node_name =~ m/(iterations|data_size|name)/og) {
	for my $kid ($node->getChildNodes()) {
	  if ($kid->getNodeType() == TEXT_NODE()) {
	    # Skip all empty text nodes
	    my $value = $kid->getNodeValue();
	    next if ($value =~ /^\s*$/ms);
	    $params{'Log Item'}{"$node_name"} = $kid->getNodeValue();
	  }
	  else {
	    die ("Error: Unknown node type", $kid->getNodeType());
	  }
	}
      }
      else {
	die ("Error: Unknown element ", $node->getNodeName());
      }
    }
    else {
      die ("Error: Unknown node type", $node->getNodeType());
    }
  }
}


=head2 parse_desi_app_data

This routine handles the transformations required for the B<Desi> test
application data document. This routine transforms the common
elements, and then calls the appropriate routines to handle the meta
information as well as the actual data payloads. It takes in a
reference to a B<Node> in a DOM tree, and an output B<Log Item> object
to populate.

=cut


sub parse_desi_app_data {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};
  for my $node ($params{'Node'}->getChildNodes()) {
    print STDERR "parse_desi_app_data (",
      $node_types{$node->getNodeType()},
	") = ", $node->getNodeName(), "\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 10;
    if ($node->getNodeType() == TEXT_NODE()) {

      # Skip all empty text nodes
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      die("Unexpected Text (", $node->getNodeValue());
    }
    elsif ($node->getNodeType() == ELEMENT_NODE()) {
      my $node_name = $node->getNodeName();
      if ($node_name =~ m/(dataid|data_timestamp)/og) {
	for my $kid ($node->getChildNodes()) {
	  if ($kid->getNodeType() == TEXT_NODE()) {
	    # Skip all empty text nodes
	    my $value = $kid->getNodeValue();
	    next if ($value =~ /^\s*$/ms);
	    $params{'Log Item'}{"$node_name"} = $kid->getNodeValue();
	  }
	  else {
	    die ("Error: Unknown node type", $kid->getNodeType());
	  }
	}
      }
      elsif ($node_name =~ m/(desi_app_load)/og) {
	$params{'Log Item'}{"desi_app_load"} = {};
	$self->parse_desi_app_load
	  ('Node' => $node,
	   'Log Item' => $params{'Log Item'}{"desi_app_load"});
      }
      elsif ($node_name =~ m/(desi_app_message_info)/og) {
	$params{'Log Item'}{"desi_app_message_info"} = {};
	$self->parse_desi_app_message_info
	  ('Node' => $node,
	   'Log Item' => $params{'Log Item'}{"desi_app_message_info"});
      }
      else {
	die ("Error: Unknown element", $node->getNodeName());
      }
    }
    else {
      die ("Error: Unknown node type", $node->getNodeType());
    }
  }
}


=head2 parse_desi_app_data

This routine is the entry point for the library. This is the routine
that is invoked by the B<QMS Log Parser> library to handle the event
payload.  This routine decides which of the underlying routines to
invoke depending on the document type presented. It takes in a
reference to a B<Node> in a DOM tree, and an output B<Log Item> object
to populate.

=cut

sub parse_qms_data {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};

  my $valid_data = 0;
  my $data_element_num = 0;
  $params{'Log Item'}{"QMS Data"} = [];

  for my $node ($params{'Node'}->getChildNodes()) {
    print STDERR "parse_qms_data (", $node->getNodeType(), 
      $node_types{$node->getNodeType()},
	") = ", $node->getNodeName(), "\n"
	  if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 8;


    if ($node->getNodeType() == TEXT_NODE()) {
      # Skip all empty text nodes
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      die("Unexpected Text (", $node->getNodeValue());
    }
    elsif ($node->getNodeType() == ELEMENT_NODE()) {
      my $node_name = $node->getNodeName();
      next unless ($node_name eq $self->{' _event_type'});

      if ($node->getNodeName() eq "bandwidth_request") {
	$params{'Log Item'}{"QMS Data"}[$data_element_num] = {};
	$self->parse_bandwidth_request
	  ('Node' => $node,
	   'Log Item' => $params{'Log Item'}{"QMS Data"}[$data_element_num]);
	$data_element_num++;
	$valid_data++;
      }
      elsif ($node->getNodeName() eq "bandwidth_data") {
	$params{'Log Item'}{"QMS Data"}[$data_element_num] = {};
	$self->parse_bandwidth_data
	  ('Node' => $node,
	   'Log Item' => $params{'Log Item'}{"QMS Data"}[$data_element_num]);
	$data_element_num++;
	$valid_data++;
      }
      elsif ($node->getNodeName() eq "desi_app_data") {
	$params{'Log Item'}{"QMS Data"}[$data_element_num] = {};
	$self->parse_desi_app_data
	  ('Node' => $node,
	   'Log Item' => $params{'Log Item'}{"QMS Data"}[$data_element_num]);
	$data_element_num++;
	$valid_data++;
      }
      else {
	die ("Uknown element in QMS data,", $node->getNodeName());
      }
    }
    else {
      die ("Uknown element type QMS data,", $node->getNodeType());
    }
  }
  return $valid_data;
}



1;




=head1 SEE ALSO

B<logger_sample>, B<QMS::Parse_Qms_Log>


=head1 RESTRICTIONS

None at this time.

=head1 BUGS

None known at this time.

=head1 AUTHORS

Manoj Srivastava <manoj.srivastava@stdc.com>

=cut
