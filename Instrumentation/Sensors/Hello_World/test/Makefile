############################ -*- Mode: Makefile -*- ###########################
## Makefile<Trader> ---
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
## Created On       : Mon Sep  3 22:50:48 2001
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Thu Dec  6 11:44:42 2001
## Last Machine Used: glaurung.green-gryphon.com
## Update Count     : 192
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

VPATH += $(OBJTOP)/Instrumentation/Sensors/Hello_World/test

CPPFLAGS += -DINTRODUCE_ERROR
#CPPFLAGS += -DDEBUG=5L -DQMS_DO_TRACE=1
CPPFLAGS += -I$(SRCTOP)/Utilities      -I$(SRCTOP)/Utilities/EC_Adapter     \
            -I$(OBJTOP)/Core/Trader/   -I$(OBJTOP)/Core                     \
            -I$(OBJTOP)/Instrumentation/Sensors/Hello_World                 \
            -I$(XERCESCROOT)/include   -I/usr/include/xercesc

SRC     = Makefile     Client_HW.h      Client_HW.cpp                   \
          Payload_HW.h Payload_HW.cpp   hello_world_client.cpp          \
          QMSMessage_helloWorld.xml     helloWorld_request_modify.xml   \
          helloWorld_request_new.xml    helloWorld_response.xml         \
          README                        test_helloWorld.dsp


C++PROGRAMS = hello_world_client 
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl

NEWSTUFF= $(patsubst %.o,%.d,$(OBJECTS))

#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJDIR)/ -L$(OBJTOP) \
              -L$(OBJTOP)/Core/Trader -L$(XERCESCROOT)/lib
C++LIBS += -lQMS -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading \
           -lTAO_CosEvent -lTAO  -lACE -lTAO_PortableServer -lxerces-c \
           -lpthread -lrt

hello_world_client_BINC++: $(OBJDIR)/Client_HW.o $(OBJDIR)/Payload_HW.o \
                    $(OBJDIR)/hello_world_client.o 
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
