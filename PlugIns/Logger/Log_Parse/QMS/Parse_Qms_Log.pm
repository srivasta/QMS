#                              -*- Mode: CPerl -*- 
# Parse_Qms_Log.pm --- 
# Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
# Created On       : Wed Nov 15 16:40:16 2000
# Created On Node  : glaurung.stdc.com
# Last Modified By : Manoj Srivastava
# Last Modified On : Mon Jan  1 14:51:55 2001
# Last Machine Used: glaurung.stdc.com
# Update Count     : 28
# Status           : Unknown, Use with caution!
# HISTORY          : 
# Description      : 
# $Id: Parse_Qms_Log.pm,v 1.4 2001/12/02 03:30:27 srivasta Exp $
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



require 5.001;
use strict;
use Carp;


=head1 NAME

  QMS::Parse_Qms_Log - Parses QMS log files

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
parser of a B<QMS_EVENT>, and constructs a native perl data structure
populated with the documents contents.  This is library handles the
application independent parts of the Event, and needs a handler
routine to parse the aplication specific data payload.

=cut


package QMS::Parse_Qms_Log;

use strict;

use Carp;
use FileHandle;
use XML::DOM;
use Data::Dumper;

my $VERSION = '$Version$';

# Preloaded methods go here.

# Autoload methods go after =cut, and are processed by the autosplit program.


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

This call creates an object that handles the B<QMS_Event> dtd. It
takes a required argument that is a reference to an object that can
handle the event specific transforms. It takes in various optional
arguments

=over

=item Delimiter

In the log file, we have multiple log item documents. This delimiter
is what enables us to chop them apart 

=item Out Put

The function that is called for dealing with the out put. The default
is to just dump the perl data structures created.

=item Out Args

Arguments to feed the output function, besides the reference to the
perl data structures

=item Use Format

Instead of outputting the event as a comma or tab separated line, it
uses the Perl format and report creating facilities to write out the
event log. This is not fully impolemented yet. 

=item Debug

This argument sets the debug level

=back

=cut

sub new {
  my $this = shift;
  my %params = @_;
  my $class = ref($this) || $this;
  my $self = {};

  bless $self => $class;

  $self->{' _Delimiter'} = "</QMSLOG>";
  die ("Need a parser object for  QMS event payload data ")
    unless (defined $params{'Call Back'} && $params{'Call Back'});

  # The object that helps parse the payload
  $self->{' _call_back'}  = $params{'Call Back'};

  # In the log file, we have multiple log item documents. This
  # delimiter is what enables us to chop them apart
  if (defined $params{'Delimiter'} && $params{'Delimiter'}) {
    $self->{' _Delimiter'} = $params{'Delimiter'};
  }

  # The function that is called for dealing with the out 
  if (defined ($params{'Out Put'}) && $params{'Out Put'}) {
    $self->{' _Output'} = $params{'Out Put'};
  }
  if (defined ($params{'Out Args'}) && $params{'Out Args'}) {
    $self->{' _Outargs'} = $params{'Out Args'};
  }

  # The function that is called for dealing with the out used format
  if (defined ($params{'Use Format'}) && $params{'Use Format'}) {
    $self->{' _Useformat'} = $params{'Use Format'};
  }

  if (defined ($params{'Debug'}) && $params{'Debug'}) {
    $self->{' _Debug'} = $params{'Debug'};
  }
  else {
    $self->{' _Debug'} = 15;
  }

  return $self;
}


=head2 parse_log_headers

This routine handles the transformations required for the headers or
meta information associated with the B<QMS Log>.  .  It takes in a
reference to a B<Node> in a DOM tree, and an output B<Log Item> object
to populate.

=cut

sub parse_log_headers {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};

  for my $node ($params{'Node'}->getChildNodes()) {
    if ($node->getNodeType() == TEXT_NODE()) {
      print "parse_log_headers $1 (",
	$node_types{$node->getNodeType()}, ") = ",
	  $node->getNodeValue(), "\n"
	    if $self->{' _Debug'} < 4;

      # Skip all empty text nodes
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      $params{'Log Item'}{"$1"} = $node->getNodeValue();
    }
    else {
      die ("Error: Unknown node type", $node->getNodeType());
    }
  }
}

=head2 parse_qms_headers

This routine handles the transformations required for the headers or
meta information associated with the B<QMS Event>.  It takes in a
reference to a B<Node> in a DOM tree, and an output B<Log Item> object
to populate.

=cut

sub parse_qms_headers {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};

  my $name = $params{'Node'}->getNodeName();
  for my $node ($params{'Node'}->getChildNodes()) {
    if ($node->getNodeType() == TEXT_NODE()) {
      print "parse_qms_headers $name $1 (",
	$node_types{$node->getNodeType()}, ") = ",
	  $node->getNodeValue(), "\n"
	    if $self->{' _Debug'} < 8;

      # Skip all empty text nodes
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      $params{'Log Item'}{"$name"} = $value;
    }
    else {
      die ("Error: Unknown node type", $node->getNodeType());
    }
  }
}

=head2 parse_qms_event

This routine handles the transformations required for the individual
B<QMS Event>.  It takes in a reference to a B<Node> in a DOM tree, and
an output B<Log Item> object to populate. This routine iterates over
the children of the root of the B<QMS Event>, and calls methods to
parse the QMS headers, or the call back function registered to handle
the payload, as appropriate.

=cut

sub parse_qms_event {
  my $self = shift;
  my %params = @_;
  die ("internal Error: Need an node")
    unless defined $params{'Node'} && $params{'Node'};
  die ("internal Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};

  my $valid_event = 0;
  $params{'Log Item'}{"QMS Event"} = {};

  for my $node ($params{'Node'}->getChildNodes()) {
    print STDERR "parse_qms_event (", $node_types{$node->getNodeType()},
      ") = ", $node->getNodeName(), "\n"
	if defined ($self->{' _Debug'}) && $self->{' _Debug'} < 6;
    if ($node->getNodeType() == TEXT_NODE()) {
      my $value = $node->getNodeValue();
      next if ($value =~ /^\s*$/ms);
      die("Unexpected Text (", $node->getNodeValue());
    }
    elsif ($node->getNodeType() == ELEMENT_NODE()) {
      my $node_name = $node->getNodeName();
      if ($node_name =~ 
	  m/(SequenceNo|SenderID|EventDate|EventTime|EventType)/og) {
	$self->parse_qms_headers('Node' => $node,
				 'Log Item' => $params{'Log Item'}{"QMS Event"});
      }
      elsif ($node->getNodeName() eq "EventData") {
	my $ret = $self->{' _call_back'}->parse_qms_data
	  ('Node' => $node,
	   'Log Item' => $params{'Log Item'}{"QMS Event"});
	if ($ret) {
	  $valid_event++;
	}
      }
      else {
	die ("Uknown element in QMS Event,", $node->getNodeName());
      }
    }
    else {
      die ("Uknown element type QMS Event,", $node->getNodeType());
    }
  }
  return $valid_event;
}

=head2 parse_log_item

This routine handles the transformations required for the individual
Log Items.  It takes in a reference to a B<Node> in a DOM tree, and an
output B<Log Item> object to populate. This strips out the version and
doctype tags, normalizes the document, extracts the root element of
the DOM tree, and iterates over the childre, calling the log header
parsing method or the B<QMS_Event> parser as appropriate.

=cut

sub parse_log_item {
  my $self = shift;
  my %params = @_;
  my $parser = new XML::DOM::Parser;

  die ("Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};
  die ("Error: Need a XML Document")
    unless defined $params{'XML Doc'} && $params{'XML Doc'};

  my $valid_log = 0;

  # We now have a log item
  $params{'XML Doc'} =~ s/<\?xml version.*?>\s*$//ms;
  $params{'XML Doc'} =~ s/^\s*<!DOCTYPE.*?>\s*$//ms;
  return $valid_log if (m/^\s*$/s);

  # Parse the string
  my $doc = $parser->parse($params{'XML Doc'});

  # Puts all Text nodes into a "normal" form
  $doc->normalize();

  # This should be the QMSLOG element
  my $root = $doc->getDocumentElement();

  # Look for children of the log element
  for my $node ($root->getChildNodes){
    print "parse ", $node_types{$node->getNodeType()}, "\t" if
      $self->{' _Debug'} <2; 
    print "parse ", $node->getNodeName(), "\n" 
      if $self->{' _Debug'} <2;

    if ($node->getNodeType() == TEXT_NODE()) {
      # Skip all empty text nodes
      my $value = $node->getNodeValue();

      next if ($value =~ /^\s*$/ms);
      die("Unexpected Text (", $node->getNodeValue());
    }
    elsif ($node->getNodeType() == ELEMENT_NODE()) {
      my $node_name = $node->getNodeName();
      if ($node_name =~ m/(SequenceNo|LoggerID|LogDate|LogTime)/og)
	{
	  $self->parse_log_headers('Node' => $node,
				   'Log Item' => $params{'Log Item'});
	}
      elsif ($node->getNodeName() eq "QMS_Event") {
	my $ret = $self->parse_qms_event('Node' => $node,
					 'Log Item' => $params{'Log Item'});
	if ($ret) {
	  $valid_log++;
	}
      }
      else {
	die ("Uknown element in QMS_Log ", $node->getNodeName());
      }
    }
    else {
      die ("Uknown element type", $node->getNodeType());
    }
  }
  $params{'Log Item'} = {} unless $valid_log;
  return $valid_log;
}

=head2 parse

This routine is the entry point for the library. This routine is used
by the calling program to handles the transformations required for the
full log file, which may contain multiple B<QMS_Event>s.  It takes in
a reference to an output B<Log Item> object to populate, and the Debug
level. This routine reads in the data orivided on the standard inpout,
cuts it into chunks divided at the B<Delimiter>, and calls the
C<parse_log_item> method on each chunk. It then calls the output
method on the results of the parsing operation.

=cut

sub parse {
  my $self = shift;
  my %params = @_;

  die ("Error: Need an Output Log Item")
    unless defined $params{'Log Item'} && $params{'Log Item'};
  print "parse with delimiter = $self->{' _Delimiter'}\n" 
      if $self->{' _Debug'} <2;

  # Slurp one event at a  time
  $/=$self->{' _Delimiter'};

  while (<>) {
    next if m/^\s*$/og;
    next unless m|$/|;

    my $ret = $self->parse_log_item('Log Item' => $params{'Log Item'},
				    'XML Doc'  => $_);
    # Handle the log item
    if ($self->{' _Useformat'}) {
      write if $ret;
    }
    else {
      if (defined($self->{' _Output'}) && $self->{' _Output'}) {
	print $self->{' _Output'}->($params{'Log Item'}, 
				    $self->{' _Outargs'})
	  if $ret;
      }
      else {
	print Dumper($params{'Log Item'})  if $ret;
      }
    }
  }
}


=head1 CAVEATS

This is very inchoate, at the moment, and needs testing.

=cut

=head1 BUGS

None Known so far.

=cut

=head1 AUTHOR

Manoj Srivastava <srivasta@debian.org>

=cut

# { # Execute simple test if run as a script
#   package main; no strict;
#   if (! caller()) {
#     eval join('', <main::DATA>);
#     die "$@ $main::DATA" if $@;
#   }
#   ##eval join('', <main::DATA>) || die "$@ $main::DATA" unless caller();
# }

1;
__END__
# Test code. Execute this module 
use Data::Dumper;
use QMS::Desi_Remos;
my $event_type =  'desi_app_data';

my %log_item;		# create a new log item

my $handler = QMS::Desi_Remos->new('EventType' => $event_type,
				   'Debug' => 19);
my $log = 
  QMS::Parse_Qms_Log->new('Call Back' => $handler,
			  'Debug'     => 19);
$log->parse('Log Item' => \%log_item);

