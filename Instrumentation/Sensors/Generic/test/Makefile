############################ -*- Mode: Makefile -*- ###########################
## Makefile --- 
## Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
## Created On       : Tue May 15 12:46:36 2001
## Created On Node  : ember.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Fri Dec 14 14:14:23 2001
## Last Machine Used: ember.green-gryphon.com
## Update Count     : 43
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
SRCTOP := $(shell cd $(THIS_DIR)/../../../../;  pwd)
PROJECTPRECONF=$(SRCTOP)/Config/qms.preconf

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
SRC= Benchmark_Client.cpp    Capability.cpp      Client.cpp             \
     Client.h                Makefile            Payload.cpp            \
     Payload.h               test_Capability.cpp test_XML.cpp           \
     generic_client.cpp      test_list_data.cpp  test_trading.cpp       \
     Receiver.h              Receiver.cpp        receiver_client.cpp

#test_meta_data.cpp 
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
CPPFLAGS += -I$(SRCTOP)/Utilities       -I$(SRCTOP)/Utilities/EC_Adapter     \
            -I$(OBJTOP)/Core/Trader/    -I$(OBJTOP)/Core                     \
            -I$(OBJDIR)/..              -I$(SRCTOP)/Instrumentation -I../    \
            -I$(XERCESCROOT)/include -I$(XALANCROOT)/src                     \
            -I/usr/include/xercesc   -I/usr/include/xalan/

VPATH += $(SRCTOP)/Core/:$(OBJTOP)/Core/
VPATH += $(SRCTOP)/Core/Trader:$(OBJTOP)/Core/Trader

C++PROGRAMS = test_list_data test_XML test_trading test_Capability Capability \
              benchmark_client generic_client receiver_client
#              test_meta_data 
test_XML_C++LIBS=$(C++LIBS) -lxerces-c
test_XML_C++LDFLAGS = $(C++LDFLAGS) -L$(XERCESCROOT)/lib
test_Capability_C++LIBS=$(C++LIBS) -lxerces-c
test_Capability_C++LDFLAGS = $(C++LDFLAGS) -L$(XERCESCROOT)/lib
Capability_C++LIBS=$(C++LIBS) -lxerces-c
Capability_C++LDFLAGS = $(C++LDFLAGS) -L$(XERCESCROOT)/lib

#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJDIR)/ -L$(OBJTOP) \
              -L$(OBJTOP)/Core/Trader -L$(XERCESCROOT)/lib
C++LIBS += -lQMS -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading        \
           -lTAO_CosEvent -lTAO  -lACE -lTAO_PortableServer -lxerces-c \
           -lpthread -lrt

test_list_data_BINC++: $(OBJDIR)/test_list_data.o
test_XML_BINC++: $(OBJDIR)/test_XML.o
test_trading_BINC++: $(OBJDIR)/test_trading.o
test_Capability_BINC++: $(OBJDIR)/test_Capability.o
Capability_BINC++: $(OBJDIR)/Capability.o
benchmark_client_BINC++: $(OBJDIR)/Benchmark_Client.o   \
                         $(OBJDIR)/Payload.o      \
                         $(OBJDIR)/generic_client.o 

generic_client_BINC++: $(OBJDIR)/Client.o             \
                    $(OBJDIR)/Payload.o      \
                    $(OBJDIR)/generic_client.o 
receiver_client_BINC++: $(OBJDIR)/Receiver.o             \
                 $(OBJDIR)/receiver_client.o 
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------

flags:
	@echo LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)
	@echo LDFLAGS=$(LDFLAGS)
	@echo CCFLAGS=$(CCFLAGS)
	@echo C++CPPFLAGS=$(C++CPPFLAGS)
	@echo CFLAGS=$(CFLAGS)
	@echo CPPFLAGS=$(CPPFLAGS)
	@echo VPATH=$(VPATH)
	@echo LIBS=$(LIBS)
	@echo INCPATHS=$(INCPATHS)
	@echo C++INCPATHS=$(C++INCPATHS)
	@echo LIBRARIES=$(LIBRARIES)
	@echo ARCHIVES=$(ARCHIVES)
	@echo SRC=$(SRC)
	@echo OBJECTS=$(OBJECTS)
	@echo XERCESCROOT=$(XERCESCROOT)

# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
