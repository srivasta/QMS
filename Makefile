############################ -*- Mode: Makefile -*- ###########################
## Makefile ---
## Author           : Manoj Srivastava ( srivasta@ember )
## Created On       : Wed Oct 18 09:28:34 2000
## Created On Node  : ember
## Last Modified By : Manoj Srivastava
## Last Modified On : Wed Oct 24 11:45:25 2001
## Last Machine Used: glaurung.stdc.com
## Update Count     : 190
## Status           : Unknown, Use with caution!
## HISTORY          :
## Description      :
##  $Id: Makefile,v 1.26 2001/12/02 03:30:21 srivasta Exp $
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
SRCTOP := $(THIS_DIR)
PROJECTPRECONF=$(SRCTOP)/Config/qms.preconf
#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
SUBDIRS = Config Contrib Documentation Utilities Core Instrumentation PlugIns
SRC     = COPYING		COPYRIGHT		ChangeLog          \
          MANIFEST		MANIFEST.new		Makefile           \
	  QMS.doxygen		QMS.h			README

LIBRARIES = $(OBJDIR)/libQMS.a
lib_INSTALL = $(OBJDIR)/libQMS.a
FilesToClean=build/QMS.tag build/doxygen.log
DIRS_TO_CLEAN=build/html build/latex build/man build/rtf .shobj 

HAVE_DOXYGEN = $(shell command -v doxygen 2>/dev/null)
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------
.PHONY: documentation
build: documentation
documentation: QMS.doxygen
	(cd build; for i in include images stylesheets; do    \
            test -e $$i || ln -s ../Documentation/Output/$$i; \
        done)
ifneq ($(strip $(HAVE_DOXYGEN)),)
	mkdir -p build/man/man3/Hello_World
	mkdir -p build/man/man3/Generic
	mkdir -p build/man/man3/Continuous/Simple/Remos
	mkdir -p build/man/man3/OneShot/Simple/Remos
	doxygen QMS.doxygen
endif

realclean: 
	@echo "Cleaning out the documentation files"
	rm -r $(DIRS_TO_CLEAN)
flags:
	@echo $(OBJDIR)
#----------------------------------------------------------------------------
#       Dependencies
#----------------------------------------------------------------------------


# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
