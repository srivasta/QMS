############################ -*- Mode: Makefile -*- ###########################
## Makefile --- 
## Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
## Created On       : Thu Aug  9 19:23:11 2001
## Created On Node  : ember.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Wed Dec  5 19:50:33 2001
## Last Machine Used: glaurung.green-gryphon.com
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
SRCTOP := $(shell cd $(THIS_DIR)/../../;  pwd)
PROJECTPRECONF=$(SRCTOP)/Config/qms.preconf

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
#CPPFLAGS += -DDEBUG=1L 
SRC     = EC_Adapter.cpp  Push_Consumer.cpp  Push_Supplier.cpp \
          EC_Adapter.h    Push_Consumer.h    Push_Supplier.h   \
	  Makefile        

C++LDFLAGS += -L$(ACE_ROOT)/ace  
C++LIBS += -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading \
           -lTAO_CosEvent -lTAO  -lACE
CPPFLAGS += -I../ 
#SUBDIRS = test
LIBRARIES = $(OBJDIR)/../../libQMS.a
#SHARED_LIBRARIES = $(OBJDIR)/../../libQMS.so.1
#SHARED_OBJECTS = $(OBJDIR)/$(VSHDIR)/Push_Supplier.o \
#                 $(OBJDIR)/$(VSHDIR)/Push_Consumer.o \
#                 $(OBJDIR)/$(VSHDIR)/EC_Adapter.o

include_INSTALL = EC_Adapter.h    Push_Consumer.h    Push_Supplier.h
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
$(OBJDIR)/../../libQMS.a: $(OBJDIR)/../../libQMS.a($(OBJDIR)/Push_Supplier.o) \
                          $(OBJDIR)/../../libQMS.a($(OBJDIR)/Push_Consumer.o) \
                          $(OBJDIR)/../../libQMS.a($(OBJDIR)/EC_Adapter.o) 

#$(OBJDIR)/../../libQMS.so.1_SHLIB: $(SHARED_OBJECTS)

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
