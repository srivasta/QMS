############################ -*- Mode: Makefile -*- ###########################
## Makefile<Continuous/Simple/FFD> --- 
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
## Created On       : Fri Aug 17 14:53:33 2001
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Mon Oct 22 14:45:10 2001
## Last Machine Used: glaurung.stdc.com
## Update Count     : 5
## Status           : Unknown, Use with caution!
## HISTORY          : 
## Description      : 
## 
###############################################################################


#  Copyright (C) 2001 System/Technology Development Corporation
#  This file is part of QoS Metrics Services (QMS)
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


THIS_DIR:= $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
SRCTOP := $(shell cd $(THIS_DIR)/../../../../../;  pwd)
PROJECTPRECONF=$(SRCTOP)/Config/qms.preconf

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------

#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
CPPFLAGS += -I$(SRCTOP)/Utilities -I$(SRCTOP)/Instrumentation

SRC     = FFD_Probe.cpp  get_data_ffd.cpp  \
          FFD_Probe.h    get_data_ffd.h    \
	  Makefile pseudoFFD.cpp
C++PROGRAMS = FFD_Probe pseudoFFD
bin_INSTALL = $(OBJDIR)/FFD_Probe
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
C++LDFLAGS += -L$(ACE_ROOT)/ace 
C++LIBS +=  -lACE
FFD_Probe_BINC++: $(OBJDIR)/FFD_Probe.o $(OBJDIR)/get_data_ffd.o
pseudoFFD_BINC++: $(OBJDIR)/pseudoFFD.o
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------

# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
