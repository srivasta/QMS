############################ -*- Mode: Makefile -*- ###########################
## Makefile ---
## Author           : Manoj Srivastava ( srivasta@ember )
## Created On       : Wed Oct 18 09:28:34 2000
## Created On Node  : ember
## Last Modified By : Manoj Srivastava
## Last Modified On : Mon Oct  8 21:56:37 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 174
## Status           : Unknown, Use with caution!
## HISTORY          :
## Description      :
##  $Id: Makefile,v 1.7 2001/10/21 08:54:09 srivasta Exp $
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

include $(SRCTOP)/qms.mk

ifeq (,$(findstring $(LD_LIBRARY_PATH),$(SRCTOP)))
export LD_LIBRARY_PATH:=$(SRCTOP)/API/:$(LD_LIBRARY_PATH)
endif

#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
CCFLAGS += -I$(TAO_ROOT) -I$(TAO_ROOT)/orbsvcs/ -I$(SRCTOP)/Utilities

# Warnings etc
CFLAGS += -Wall -W -Dgets=DONT_USE_GETS -Dlint
CFLAGS += -Wmissing-prototypes -Wmissing-declarations
CFLAGS += -fshort-enums -fno-common -Wstrict-prototypes
CFLAGS += -Woverloaded-virtual -Wnested-externs -Wwrite-strings
CFLAGS += -Wpointer-arith -Wbad-function-cast -Wcast-align
CFLAGS += -pedantic -Wno-long-long -Wtraditional

# Can't use these since these trigger vast quantties of diagnostics
# from ACE+TAO. That's a pity, really, for these are useful checks
# CFLAGS += -Wshadow -Winline -Wredundant-decls -Wundef

# I am not sure these should be warnings, really
# CFLAGS += -Wcast-qual -Wconversion -Waggregate-return

# All informational stuff is dumped here.
INFO    = README

FILES=Remos_Instrumentation.cpp
BIN=Remos_Instrumentation

#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------

# Use one or the other of these two
# This file sets up the rules for VDIR/*.o files, shared libs, install
# targets, and more.
include $(ACE_ROOT)/include/makeinclude/rules.local.GNU
# Makefile for directories with no local build targets
# include $(ACE_ROOT)/include/makeinclude/rules.nolocal.GNU


# Use one or the other of these two
# Include this to descend subdirs
# include $(ACE_ROOT)/include/makeinclude/rules.nested.GNU
#       Null nested targets
include $(ACE_ROOT)/include/makeinclude/rules.nonested.GNU


# Include this if you are building libraries (shall create shared and
# non-shared versions), Uses internal macros VSHOBJS and VSHOBJS1,
# derived from LSRC.
# include  $(ACE_ROOT)/include/makeinclude/rules.lib.GNU
include  $(ACE_ROOT)/include/makeinclude/rules.bin.GNU

include $(SRCTOP)/project.mk

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------
LDLIBS  =  -lTAO -lTAO_CosEvent -lTAO_RTEvent -lTAO_RTSched  -lQMS_Api -lQMS_Remos -lremos -lACE
VLDLIBS = $(LDLIBS:%=%$(VAR))

BUILD = $(VLIB) $(VSHLIB) $(VSHLIBA) $(VBIN)

LDFLAGS += -L$(ACE_ROOT)/ace -L$(SRCTOP)/API -Lutility -L$(REMOS_ROOT)/modeler/lib/I386/LINUX -L$(TAO_ROOT)/orbsvcs/orbsvcs -L$(TAO_ROOT)/tao -L$(TAO_ROOT)/orbsvcs/Naming_Service
CPPFLAGS += -I$(SRCTOP)/API -Iutility\
            -I$(REMOS_ROOT)/modeler/include/ \
            -I$(REMOS_ROOT)/listpack/include/ \
            -I$(SRCTOP)/Utilities \
            -I$(TAO_ROOT) -I$(TAO_ROOT)/orbsvcs

CCFLAGS := $(sort $(CCFLAGS))
CPPFLAGS := $(sort $(CPPFLAGS))
LDFLAGS := $(sort $(LDFLAGS))

flags:
	@echo LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)
	@echo LDFLAGS=$(LDFLAGS)
	@echo VLDLIBS=$(VLDLIBS)
	@echo CCFLAGS=$(CCFLAGS)
	@echo CPPFLAGS=$(CPPFLAGS)
	@echo PRELIB=$(PRELIB)
	@echo VLIB=$(VLIB)
	@echo VSHLIB=$(VSHLIB)
	@echo VSHLIB_TWO=$(VSHLIB_TWO)
	@echo VSHOBJS1=$(VSHOBJS1)
	@echo VSHOBJS1_TWO=$(VSHOBJS1_TWO)
	@echo VSHOBJS=$(VSHOBJS)
	@echo VSHOBJS_TWO=$(VSHOBJS_TWO)
	@echo SHLIBA=$(SHLIBA)
	@echo SHLIBA_TWO=$(SHLIBA_TWO)

#### To disable installs, just add "INSTALL=" to your "make" invocation.

build.local: Depend utility/libQMS_Remos.a utility/libQMS_Remos.$(SOEXT) $(VLIB) $(VSHLIB) $(VSHLIBA) $(LIB) $(BIN)
	@echo local build done

Depends Depend : depend
	perl $(SRCTOP)/fix.Makefile

utility/libQMS_Remos.a utility/libQMS_Remos.$(SOEXT):
	$(MAKE) -C utility $(subst utility/,,$@)

CLEAN: realclean
	rm -f .depend

tar: CLEAN
	@echo $(THIS_DIR) ready for packing

#----------------------------------------------------------------------------
#       Dependencies
#----------------------------------------------------------------------------


# Local Variables:
# mode: makefile
# comment-start: "#"
# End:

# Don't put anything below here.  Between the "depend" target and
# fix.Makefile it's guaranteed to be lost!

# This is inserted by the fix.Makefile script
-include .depend
