#! /usr/bin/perl


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

my $ret1 = 0;

print "1..3\n";

my $output = `perl  logger_sample --event bandwidth_request t/test_log > t/output1 `;
if ($output || $?) {
  print "not ok 1\n";
  $ret1 =  $?;
}
else {
  $output = `cmp t/basic.remos_request.out t/output1 >& /dev/null`;
  
  if ($output || $?) {
    print "not ok 1\n";
    $ret1 =  $?;
  }
  else {
    print "ok 1\n";
    unlink "t/output1";
  }
}


$output = `perl logger_sample --event bandwidth_data t/test_log > t/output2 2>/dev/null`;
my $ret2 = 0;

if ($output || $?) {
  print "not ok 2\n";
  $ret2 =  $?;
}
else {
  $output = `cmp t/basic.remos_data.out t/output2 >& /dev/null`;
  
  if ($output || $?) {
    print "not ok 2\n";
    $ret2 =  $?;
  }
  else {
    print "ok 2\n";
    unlink "t/output2";
  }
}


$output = `perl logger_sample --event desi_app_data t/test_log > t/output3 2>/dev/null`;
my $ret3 = 0;

if ($output || $?) {
  print "not ok 3\n";
  $ret3 =  $?;
}
else {
  $output = `cmp t/basic.desi_data.out t/output3 >& /dev/null`;
  
  if ($output || $?) {
    print "not ok 3\n";
    $ret3 =  $?;
  }
  else {
    print "ok 3\n";
    unlink "t/output3";
  }
}

exit $ret1 + $ret2 + $ret3;
