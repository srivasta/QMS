############################ -*- Mode: Makefile -*- ###########################
## Makefile --- 
## Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
## Created On       : Tue May 15 12:46:36 2001
## Created On Node  : ember.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Sat Dec  1 01:12:33 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 75
## Status           : Unknown, Use with caution!
## HISTORY          : 
## Description      : 
## 
###############################################################################

# $Id: Makefile,v 1.30 2002/01/03 20:33:30 srivasta Exp $

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
SUBDIRS= test
VPATH += $(SRCTOP)/Core/:$(OBJTOP)/Core/

#CPPFLAGS += -DDEBUG=3L              -DQMS_DO_TRACE=1
#CPPFLAGS += -DDEBUG=5L

CPPFLAGS += -I$(SRCTOP)/Core/       -I$(SRCTOP)/Core/Trader/          \
            -I$(OBJTOP)/Core/       -I$(OBJTOP)/Core/Trader/          \
            -I$(SRCTOP)/Utilities   -I$(SRCTOP)/Utilities/EC_Adapter  \
            -I$(SRCTOP)/Instrumentation                               \
            -I$(XERCESCROOT)/include -I$(XALANCROOT)/src              \
            -I/usr/include/xercesc   -I/usr/include/xalan/

SRC= Remos_Sensor.idl    Remos_Sensor_Impl.cpp Remos_Sensor_Impl.h       \
     Makefile            remos_sensor.cpp      CallBack_Remos.cpp        \
     List_Data_Remos.h   Meta_Data_Remos.h     Meta_Data_Remos.cpp       \
     Probe_Proxy_Remos.h Pipe_Proxy_Remos.h    Pipe_Proxy_Remos.cpp      \
     Continuous_Pipe_Proxy_Remos.h             Continuous_Pipe_Proxy_Remos.cpp\
     One_Shot_Pipe_Proxy_Remos.h               One_Shot_Pipe_Proxy_Remos.cpp   

C++PROGRAMS = qms_sensor_remos
LIBRARIES = $(OBJDIR)/../../../libQMS.a
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl

NEWSTUFF= $(patsubst %.o,%.d,$(OBJECTS))

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------
$(OBJDIR)/../../../libQMS.a: \
          $(OBJDIR)/../../../libQMS.a($(OBJDIR)/Remos_SensorC.o)
C++LDFLAGS += -L$(ACE_ROOT)/ace   -L$(OBJTOP) -L$(OBJTOP)/Core/Trader \
              -L$(XALANCROOT)/lib -L$(XERCESCROOT)/lib
C++LIBS += -lQMS                -lTAO_RTEvent          -lTAO_RTSched      \
           -lTAO_CosTrading     -lTAO_CosNaming        -lTAO_CosEvent     \
           -lTAO_PortableServer -lTAO_RTPortableServer -lTAO_RTSchedEvent \
           -lTAO_IORManip       -lTAO                  -lACE              \
           -lxalan-c              -lxerces-c               -lpthread          \
           -lrt

qms_sensor_remos_BINC++: \
	   $(OBJDIR)/Remos_Sensor_Impl.o     $(OBJDIR)/remos_sensor.o       \
           $(OBJDIR)/CallBack_Remos.o                                       \
           $(OBJTOP)/Core/CommandC.o         $(OBJTOP)/Core/CommandS.o      \
           $(OBJTOP)/Core/CommandS_T.o       $(OBJTOP)/Core/ControlC.o      \
           $(OBJTOP)/Core/ControlS.o         $(OBJTOP)/Core/ControlS_T.o    \
           $(OBJDIR)/Remos_SensorS.o         $(OBJDIR)/Remos_SensorS_T.o    \
           $(OBJDIR)/Meta_Data_Remos.o       $(OBJDIR)/Pipe_Proxy_Remos.o   \
           $(OBJDIR)/Continuous_Pipe_Proxy_Remos.o                          \
           $(OBJDIR)/One_Shot_Pipe_Proxy_Remos.o

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
