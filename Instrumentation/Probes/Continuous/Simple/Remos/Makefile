############################ -*- Mode: Makefile -*- ###########################
## Makefile<Remos> --- 
## Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
## Created On       : Tue Oct 16 13:40:06 2001
## Created On Node  : ember.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Thu Dec  6 15:21:14 2001
## Last Machine Used: glaurung.green-gryphon.com
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



####################################################################################
THIS_DIR:= $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
SRCTOP := $(shell cd $(THIS_DIR)/../../../../../;  pwd)
PROJECTPRECONF=$(SRCTOP)/Config/qms.preconf

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
CPPFLAGS += -I$(SRCTOP)/Utilities -I$(SRCTOP)/Instrumentation

SRC     = Remos_Graph_Probe.cpp         Remos_Graph_Probe.h \
          Remos_Flow_Probe.cpp          Remos_Flow_Probe.h  \
          get_data_graph.cpp            get_data_graph.h  \
          get_data_flow.cpp             get_data_flow.h   \
          Makefile
CPPFLAGS += -I$(REMOS_ROOT)/modeler/include
C++PROGRAMS = Remos_Graph_Probe Remos_Flow_Probe
bin_INSTALL = $(OBJDIR)/Remos_Graph_Probe $(OBJDIR)/Remos_Flow_Probe
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
ifneq ($(strip $(REMOS_ROOT)),)
ifeq (,$(findstring $(DEFAULT_LD_LIBRARY_PATH),$(REMOS_ROOT)))
ifneq (,$(findstring 86,$(MACHINE)))
ifeq ($(strip $(SYSTEM)),linux)
C++LDFLAGS +=-L$(REMOS_ROOT)/modeler/lib/I386/LINUX
endif
endif
endif
endif

C++LDFLAGS += -L$(ACE_ROOT)/ace
C++LIBS +=  -lremos -lACE
Remos_Graph_Probe_BINC++: $(OBJDIR)/Remos_Graph_Probe.o \
                          $(OBJDIR)/get_data_graph.o

Remos_Flow_Probe_BINC++: $(OBJDIR)/Remos_Flow_Probe.o   \
                         $(OBJDIR)/get_data_flow.o
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------

# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
