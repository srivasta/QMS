############################ -*- Mode: Makefile -*- ###########################
## Makefile ---
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
## Created On       : Wed Nov  1 10:04:09 2000
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Tue Dec 11 12:06:13 2001
## Last Machine Used: glaurung.green-gryphon.com
## Update Count     : 81
## Status           : Unknown, Use with caution!
## HISTORY          :
## Description      :
## $Id: Makefile,v 1.27 2002/05/16 17:35:19 srivasta Exp $
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
SRCTOP := $(shell cd $(THIS_DIR)/../;  pwd)
PROJECTPRECONF=$(SRCTOP)/Config/qms.preconf

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
CPPFLAGS += -I$(XERCESCROOT)/include -I/usr/include/xercesc
SUBDIRS = Scripts Backend test EC_Adapter Multi_Level_Data 
C++LDFLAGS += -L$(ACE_ROOT)/ace  
C++LIBS += -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading -lTAO_CosEvent -lTAO  \
            -lACE
SRC     = CORBA_Handles.cpp CORBA_Handles.h     Debug.h     Makefile          \
	  YP_Offer.h        YP_Offer.cpp        Parse_XML.h Parse_XML.cpp     \
          Parse_Duration.h  Parse_Duration.cpp
LIBRARIES = $(OBJDIR)/../libQMS.a
#SHARED_LIBRARIES = $(OBJDIR)/../libQMS.so.1
#SHARED_OBJECTS = $(OBJDIR)/$(VSHDIR)/CORBA_Handles.o                         \
#                 $(OBJDIR)/$(VSHDIR)/Parse_XML.o
include_INSTALL = CORBA_Handles.h Debug.h YP_Offer.h Parse_XML.h              \
                  Parse_Duration.h
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
$(OBJDIR)/../libQMS.a: $(OBJDIR)/../libQMS.a($(OBJDIR)/CORBA_Handles.o)    \
                       $(OBJDIR)/../libQMS.a($(OBJDIR)/YP_Offer.o)         \
                       $(OBJDIR)/../libQMS.a($(OBJDIR)/Parse_XML.o)        \
                       $(OBJDIR)/../libQMS.a($(OBJDIR)/Parse_Duration.o) 
#$(OBJDIR)/../libQMS.so.1_SHLIB: $(SHARED_OBJECTS)

#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
flags:
	@echo LDFLAGS=$(LDFLAGS)
	@echo VLDLIBS=$(VLDLIBS)
	@echo CCFLAGS=$(CCFLAGS)
	@echo C++CPPFLAGS=$(C++CPPFLAGS)
	@echo CFLAGS=$(CFLAGS)
	@echo CPPFLAGS=$(CPPFLAGS)
	@echo VPATH=$(VPATH)
	@echo LIBS=$(LIBS)
	@echo INCPATHS=$(INCPATHS)
	@echo C++INCPATHS=$(C++INCPATHS)
	@echo LIBRARIES=$(LIBRARIES)
	@echo SHARED_LIBRARIES=$(SHARED_LIBRARIES)
	@echo ARCHIVES=$(ARCHIVES)
	@echo SHARED_ARCHIVES=$(SHARED_ARCHIVES)
	@echo SRC=$(SRC)
	@echo OBJECTS=$(OBJECTS)
	@echo SHARED_OBJECTS=$(SHARED_OBJECTS)
	@echo LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)

# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
