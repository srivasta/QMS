############################ -*- Mode: Makefile -*- ###########################
## Makefile --- 
## Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
## Created On       : Tue May 15 12:46:36 2001
## Created On Node  : ember.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Thu Dec  6 01:41:01 2001
## Last Machine Used: glaurung.green-gryphon.com
## Update Count     : 63
## Status           : Unknown, Use with caution!
## HISTORY          : 
## Description      : 
## 
###############################################################################

# $Id: Makefile,v 1.22 2002/02/10 06:06:48 srivasta Exp $

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


SUBDIRS= test
VPATH += $(SRCTOP)/Core/:$(OBJTOP)/Core/

#CPPFLAGS += -DDEBUG=1L              -DQMS_DO_TRACE=1
#CPPFLAGS += -DDEBUG=1L
CPPFLAGS += -DINTRODUCE_ERROR

CPPFLAGS += -I$(SRCTOP)/Core/        -I$(SRCTOP)/Core/Trader/          \
            -I$(OBJTOP)/Core/        -I$(OBJTOP)/Core/Trader/          \
            -I$(SRCTOP)/Utilities    -I$(SRCTOP)/Utilities/EC_Adapter  \
            -I$(XERCESCROOT)/include -I/usr/include/xercesc  

SRC= Hello_World.idl   Hello_World_Impl.cpp  Hello_World_Impl.h       \
     Makefile          hello_world.cpp       CallBack_HW.cpp          \
     List_Data_HW.h    Meta_Data_HW.h        Meta_Data_HW.cpp         \
     Hello_World.h     Message_Format_HW.h   README.hello_world       

C++PROGRAMS = qms_sensor_hw
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
          $(OBJDIR)/../../../libQMS.a($(OBJDIR)/Hello_WorldC.o)
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJTOP) -L$(OBJTOP)/Core/Trader \
              -L$(XERCESCROOT)/lib
C++LIBS += -lQMS  -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading \
           -lTAO_CosNaming -lTAO_CosEvent \
	   -lTAO_PortableServer -lTAO_RTPortableServer \
	   -lTAO_RTSchedEvent -lTAO_IORManip \
           -lTAO -lACE -lxerces-c -lpthread -lrt

qms_sensor_hw_BINC++: \
	   $(OBJDIR)/Hello_World_Impl.o      $(OBJDIR)/hello_world.o        \
           $(OBJDIR)/CallBack_HW.o                                          \
           $(OBJTOP)/Core/CommandC.o         $(OBJTOP)/Core/CommandS.o      \
           $(OBJTOP)/Core/CommandS_T.o       $(OBJTOP)/Core/ControlC.o      \
           $(OBJTOP)/Core/ControlS.o         $(OBJTOP)/Core/ControlS_T.o    \
           $(OBJDIR)/Hello_WorldS.o          $(OBJDIR)/Hello_WorldS_T.o     \
           $(OBJDIR)/Meta_Data_HW.o  

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
