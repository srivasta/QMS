############################ -*- Mode: Makefile -*- ###########################
## Makefile ---
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
## Created On       : Wed Nov  1 10:04:09 2000
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Mon Oct  8 21:55:53 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 70
## Status           : Unknown, Use with caution!
## HISTORY          :
## Description      :
## $Id: Makefile,v 1.7 2002/05/16 16:48:31 srivasta Exp $
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
SRC     = corba_svc config.guess gethostname Makefile
script_INSTALL = corba_svc 
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------

# Local Variables:
# mode: makefile
# comment-start: "#"
# End:
