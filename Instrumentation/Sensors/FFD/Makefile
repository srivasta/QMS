############################ -*- Mode: Makefile -*- ###########################
## Makefile<Trader> --- 
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
## Created On       : Mon Sep  3 22:50:48 2001
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Mon Oct  8 21:57:08 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 173
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

#include $(SRCTOP)/qms.mk

ifeq (,$(findstring $(LD_LIBRARY_PATH),$(SRCTOP)))
export LD_LIBRARY_PATH:=$(SRCTOP)/API/:$(LD_LIBRARY_PATH)
endif

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------

SRC     = QMS_Test_Client.cpp \
	  QMS_Generic_Sensor.cpp \
	  STDC_i.cpp              STDC_i.h \
          ping.idl \
          Makefile                   
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
include_install=$(OBJDIR)/pingC.h    $(OBJDIR)/pingC.i    \
                $(OBJDIR)/pingS.h    $(OBJDIR)/pingS.i    \
                $(OBJDIR)/pingS_T.h $(OBJDIR)/pingS_T.i

VPATH += $(SRCTOP)/Instrumentation/Sensors/FFD/:$(OBJTOP)/Instrumentation/Sensors/FFD/
CPPFLAGS += -I./  -I$(SRCTOP)/Utilities  -I$(SRCTOP)/Utilities/EC_Adapter  -I$(OBJDIR)/ \
-I$(OBJTOP)/Core/Trader/ -I$(OBJTOP)/Core/

LIBRARIES = $(OBJDIR)/../../libQMS.a
idl_INSTALL = ping.idl
C++PROGRAMS = QMS_Generic_Sensor QMS_Test_Client
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJDIR)/ -L$(OBJDIR)/../../../ 
C++LIBS += -lQMS -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading \
           -lTAO_CosEvent -lTAO  -lACE -lTAO_PortableServer
$(OBJDIR)/../../libQMS.a: $(OBJDIR)/../../libQMS.a($(OBJDIR)/pingC.o) \
                           $(OBJDIR)/../../libQMS.a($(OBJDIR)/pingS.o) \
                           $(OBJDIR)/../../libQMS.a($(OBJDIR)/pingS_T.o) \
			   $(OBJDIR)/../../libQMS.a($(OBJDIR)/STDC_i.o)

QMS_Test_Client_BINC++: $(OBJDIR)/QMS_Test_Client.o \
			   $(OBJDIR)/pingC.o 

QMS_Generic_Sensor_BINC++: $(OBJDIR)/QMS_Generic_Sensor.o \
                           $(OBJDIR)/STDC_i.o \
			   $(OBJDIR)/pingC.o \
			   $(OBJDIR)/pingS.o \
			   $(OBJDIR)/pingS_T.o 
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
