

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

use ExtUtils::MakeMaker;
# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile(
	      'NAME'		=> 'QMS_Log_Parse',
	      'DISTNAME'        => 'QMS_Log_Parse',
	      'PMLIBDIRS'    => ['QMS/'],
	      'EXE_FILES'    => ['logger_sample'],
	      'VERSION_FROM'	=> 'patchlevel', # finds $VERSION
	      'PREREQ_PM'		=> {}, # e.g., Module::Name => 1.1
              linkext        => { LINKTYPE => '' },
              dist           => {COMPRESS=>'gzip -9f', SUFFIX => 'gz'},
	     );
