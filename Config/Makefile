############################ -*- Mode: Makefile -*- ###########################
## Makefile --- 
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
## Created On       : Sat Sep 15 22:03:37 2001
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Tue Oct 16 13:41:44 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 5
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
SRC     = Makefile i586-pc-linux-gnu.cf i686-pc-linux-gnu.cf site.cf \
          project.defaults project.rules project.targets project.tmpl

#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
#       Dependencies
#----------------------------------------------------------------------------


# Local Variables:
# mode: makefile
# comment-start: "#"
# End:

