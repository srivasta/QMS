############################ -*- Mode: Makefile -*- ###########################
## Makefile<Core> --- 
## Author           : Manoj Srivastava ( srivasta@ember.stdc.com ) 
## Created On       : Tue Aug 14 10:34:02 2001
## Created On Node  : ember.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Tue Oct 16 13:42:09 2001
## Last Machine Used: ember.stdc.com
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
SRCTOP := $(shell cd $(THIS_DIR)/../;  pwd)
PROJECTPRECONF=$(SRCTOP)/Config/qms.preconf

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
SUBDIRS = Trader
SRC     = Command.idl Control.idl Makefile
idl_INSTALL = Command.idl Control.idl
include_INSTALL=$(OBJDIR)/CommandC.h    $(OBJDIR)/CommandC.i    \
                $(OBJDIR)/CommandS.h    $(OBJDIR)/CommandS.i    \
                $(OBJDIR)/CommandS_T.h  $(OBJDIR)/CommandS_T.i  \
                $(OBJDIR)/ControlC.h    $(OBJDIR)/ControlC.i    \
                $(OBJDIR)/ControlS.h    $(OBJDIR)/ControlS.i    \
                $(OBJDIR)/ControlS_T.h  $(OBJDIR)/ControlS_T.i

LIBRARIES = $(OBJDIR)/../libQMS.a
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
$(OBJDIR)/../libQMS.a: $(OBJDIR)/../libQMS.a(CommandC.o) \
                       $(OBJDIR)/../libQMS.a(CommandS.o) \
                       $(OBJDIR)/../libQMS.a(CommandS_T.o) \
                       $(OBJDIR)/../libQMS.a(ControlC.o) \
                       $(OBJDIR)/../libQMS.a(ControlS.o) \
                       $(OBJDIR)/../libQMS.a(ControlS_T.o)
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
	@echo ARCHIVES=$(ARCHIVES)
	@echo SRC=$(SRC)
	@echo OBJECTS=$(OBJECTS)

# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
