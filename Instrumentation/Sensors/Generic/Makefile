############################ -*- Mode: Makefile -*- ###########################
## Makefile --- 
## Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
## Created On       : Tue May 15 12:46:36 2001
## Created On Node  : ember.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Wed Jan  9 15:27:14 2002
## Last Machine Used: glaurung.green-gryphon.com
## Update Count     : 59
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


SUBDIRS=test
#VPATH += $(SRCTOP)/Core/:$(OBJTOP)/Core/
CPPFLAGS += -I$(SRCTOP)/Core/        -I$(SRCTOP)/Core/Trader/          \
            -I$(OBJTOP)/Core/        -I$(OBJTOP)/Core/Trader/          \
            -I$(SRCTOP)/Utilities    -I$(SRCTOP)/Utilities/EC_Adapter  \
            -I$(SRCTOP)/Instrumentation                                \
            -I$(XERCESCROOT)/include -I$(XALANCROOT)/src               \
            -I/usr/include/xercesc   -I/usr/include/xalan/
#CPPFLAGS += -DDEBUG=0xFFFFFFFFL -DQMS_DO_TRACE=1
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
#CPPFLAGS += -DSILENT_MODE=1

SRC= Continuous_Pipe_Proxy.cpp   Continuous_Pipe_Proxy.h              \
     Generic_Sensor_Impl.cpp     Generic_Sensor_Impl.h                \
     Generic_Sensor.idl          List_Data.h                          \
     Probe_Proxy.h               Makefile                             \
     Meta_Data.cpp               Meta_Data.h                          \
     One_Shot_Pipe_Proxy.cpp     One_Shot_Pipe_Proxy.h                \
     Pipe_Proxy.cpp              Pipe_Proxy.h                         \
     generic_sensor.cpp          CallBack.cpp                         

C++PROGRAMS = qms_sensor
LIBRARIES = $(OBJDIR)/../../../libQMS.a

idl_INSTALL = Generic_Sensor.idl
bin_INSTALL = $(OBJDIR)/qms_sensor
include_INSTALL=$(OBJDIR)/Generic_SensorC.h    $(OBJDIR)/Generic_SensorC.i    \
                $(OBJDIR)/Generic_SensorS.h    $(OBJDIR)/Generic_SensorS.i    \
                $(OBJDIR)/Generic_SensorS_T.h  $(OBJDIR)/Generic_SensorS_T.i 
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl

NEWSTUFF= $(patsubst %.o,%.d,$(OBJECTS))

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------
$(OBJDIR)/../../../libQMS.a: \
          $(OBJDIR)/../../../libQMS.a($(OBJDIR)/Generic_SensorC.o)
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJTOP) -L$(OBJTOP)/Core/Trader \
              -L$(XALANCROOT)/lib -L$(XERCESCROOT)/lib
C++LIBS += -lQMS                -lTAO_RTEvent          -lTAO_RTSched      \
           -lTAO_CosTrading     -lTAO_CosNaming        -lTAO_CosEvent     \
           -lTAO_PortableServer -lTAO_RTPortableServer -lTAO_RTSchedEvent \
           -lTAO_IORManip       -lTAO                  -lACE              \
           -lxalan-c              -lxerces-c               -lpthread          \
           -lrt
C++IDL_FLAGS += -I$(SRCTOP)/Core/    -I$(OBJTOP)/Core/  
qms_sensor_BINC++: \
	   $(OBJDIR)/Continuous_Pipe_Proxy.o $(OBJDIR)/Generic_Sensor_Impl.o \
           $(OBJDIR)/Meta_Data.o             $(OBJDIR)/One_Shot_Pipe_Proxy.o \
	   $(OBJDIR)/Pipe_Proxy.o            $(OBJDIR)/generic_sensor.o      \
           $(OBJDIR)/CallBack.o                                              \
           $(OBJTOP)/Core/CommandC.o         $(OBJTOP)/Core/CommandS.o       \
           $(OBJTOP)/Core/CommandS_T.o       $(OBJTOP)/Core/ControlC.o       \
           $(OBJTOP)/Core/ControlS.o         $(OBJTOP)/Core/ControlS_T.o     \
           $(OBJDIR)/Generic_SensorS.o       $(OBJDIR)/Generic_SensorS_T.o     

flags:
	@echo LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)
	@echo OBJECTS=$(OBJECTS)
	@echo DEFAULT_OBJECTS=$(DEFAULT_OBJECTS)
	@echo C++FILES=$(C++FILES)
	@echo C++_IDLFILES=$(C++_IDLFILES)
	@echo IDL_TARGETS=$(IDL_TARGETS)
	@echo NEWSTUFF=$(NEWSTUFF)


# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
