############################ -*- Mode: Makefile -*- ###########################
## Makefile<Gateway> --- 
## Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
## Created On       : Fri Dec  7 15:14:34 2001
## Created On Node  : glaurung.green-gryphon.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Tue Dec 11 14:39:58 2001
## Last Machine Used: glaurung.green-gryphon.com
## Update Count     : 8
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
SRCTOP := $(shell cd $(THIS_DIR)/../../../;  pwd)
PROJECTPRECONF=$(SRCTOP)/Config/qms.preconf

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
#CPPFLAGS += -DDEBUG=1L 
SRC     = Makefile             dummy_gui.cpp    test_request.cpp       \
          test_discovery.cpp

C++LIBS += -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading -lTAO_CosEvent \
           -lTAO  -lACE
CPPFLAGS += -I$(SRCTOP)/Core/        -I$(SRCTOP)/Core/Trader/     -I.. \
            -I$(OBJTOP)/Core/        -I$(OBJTOP)/Core/Trader/          \
            -I$(SRCTOP)/Utilities    -I$(SRCTOP)/Utilities/EC_Adapter  \
            -I$(SRCTOP)/Instrumentation                                \
            -I$(XERCESCROOT)/include -I$(XALANCROOT)/src               \
            -I/usr/include/xercesc   -I/usr/include/xalan/
include_INSTALL = 
C++PROGRAMS = dummy_gui test_discovery test_request
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJTOP) -L$(OBJTOP)/Core/Trader \
              -L$(XALANCROOT)/lib -L$(XERCESCROOT)/lib
C++LIBS += -lQMS                -lTAO_RTEvent          -lTAO_RTSched      \
           -lTAO_CosTrading     -lTAO_CosNaming        -lTAO_CosEvent     \
           -lTAO_PortableServer -lTAO_RTPortableServer -lTAO_RTSchedEvent \
           -lTAO_IORManip       -lTAO                  -lACE              \
           -lxalan-c              -lxerces-c               -lpthread          \
           -lrt
dummy_gui_BINC++: $(OBJDIR)/dummy_gui.o
test_request_BINC++: $(OBJDIR)/test_request.o
test_discovery_BINC++: $(OBJDIR)/test_discovery.o

flags:
	@echo LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)
	@echo LDFLAGS=$(LDFLAGS)
	@echo CFLAGS=$(CFLAGS)
	@echo CCFLAGS=$(CCFLAGS)
	@echo C++FLAGS=$(C++FLAGS)
	@echo CPPFLAGS=$(CPPFLAGS)
	@echo OBJDIR=$(OBJDIR)
	@echo C++FILES=$(C++FILES)
	@echo DEFAULT_OBJECTS=$(DEFAULT_OBJECTS)


# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
