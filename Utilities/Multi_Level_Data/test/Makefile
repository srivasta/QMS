############################ -*- Mode: Makefile -*- ###########################
## Makefile<3> ---
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
## Created On       : Wed Nov  1 10:04:09 2000
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Mon Oct  8 21:56:15 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 39
## Status           : Unknown, Use with caution!
## HISTORY          :
## Description      :
## $Id: Makefile,v 1.6 2001/10/21 08:54:13 srivasta Exp $
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
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
CPPFLAGS += -I../ -I../../
SRC     = instantiate.cpp testLinkedList.cpp ChangeLog Makefile 
C++PROGRAMS = testLinkedList
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJDIR)/../../.. 
C++LIBS += -lQMS -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading \
           -lTAO_CosEvent -lTAO  -lACE
testLinkedList_BINC++: $(OBJDIR)/instantiate.o $(OBJDIR)/testLinkedList.o

#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------

flags:
	@echo LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)
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



# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
