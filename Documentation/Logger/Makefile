############################ -*- Mode: Makefile -*- ###########################
## Makefile ---
## Author           : Manoj Srivastava ( srivasta@ember )
## Created On       : Wed Oct 18 09:28:34 2000
## Created On Node  : ember
## Last Modified By : Manoj Srivastava
## Last Modified On : Tue Oct 16 13:41:20 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 171
## Status           : Unknown, Use with caution!
## HISTORY          :
## Description      :
##  $Id: Makefile,v 1.7 2001/10/21 08:54:04 srivasta Exp $
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
SRC     = Makefile ChangeLog QMS_Logger.argo QMS_Logger.xmi            \
          QMS_Logger_Registerwithtraderstates1.pgml                    \
          QMS_Logger_StartLoggerstates1.pgml                           \
	  QMS_Logger_StartnewLogstates1.pgml                           \
	  QMS_Logger_classdiagram1.pgml QMS_Logger_usecasediagram1.pgml\
	  QMS_Logger_usecasediagram2.pgml                              \
	  QMS_Logger_usecasediagram3.pgml                              \
	  Registerwithtraderstates1.pgml  StartLoggerstates1.pgml      \
	  StartnewLogstates1.pgml  use-case.sgml  usecasediagram2.pgml \
	  usecasediagram3.pgml

#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------
