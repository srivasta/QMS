############################ -*- Mode: Makefile -*- ###########################
## Makefile<Trader> --- 
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com ) 
## Created On       : Mon Sep  3 22:50:48 2001
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Tue Oct 16 13:42:24 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 13
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

SUBDIRS= test


#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------
#CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
SRC     = ECInfo.cpp		ECInfo.h		ListOffers.cpp	    \
	  ListOffers.dsp	ListOffers.h		Makefile	    \
	  QMS_Trader_ECInfo.cpp QMS_Trader_ECInfo.dsp	QMS_Trader_ECInfo.h \
	  QMS_Trader_ECInfo_Impl.cpp	QMS_Trader_ECInfo_Impl.h            \
	  README.trader		Trader.config		Trader.idl          

include_INSTALL=$(OBJDIR)/TraderC.h    $(OBJDIR)/TraderC.i    \
                $(OBJDIR)/TraderS.h    $(OBJDIR)/TraderS.i    \
                $(OBJDIR)/TraderS_T.h  $(OBJDIR)/TraderS_T.i 
VPATH += $(SRCTOP)/Core/:$(OBJTOP)/Core/
CPPFLAGS += -I../ -I$(SRCTOP)/API -I$(SRCTOP)/Utilities -I../ -I$(OBJDIR)/..
LIBRARIES = $(OBJDIR)/../../libQMS.a
idl_INSTALL = Trader.idl
C++PROGRAMS = qms_trader  qms_ls_offers
bin_INSTALL = $(OBJDIR)/qms_ls_offers     $(OBJDIR)/qms_trader
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJDIR)/.. -L$(OBJDIR)/../.. 
C++LIBS += -lQMS -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading \
           -lTAO_CosEvent -lTAO  -lACE
$(OBJDIR)/../../libQMS.a: $(OBJDIR)/../../libQMS.a($(OBJDIR)/TraderC.o) \
                           $(OBJDIR)/../../libQMS.a($(OBJDIR)/TraderS.o) \
                           $(OBJDIR)/../../libQMS.a($(OBJDIR)/TraderS_T.o)
qms_trader_BINC++: $(OBJDIR)/QMS_Trader_ECInfo.o \
                            $(OBJDIR)/QMS_Trader_ECInfo_Impl.o \
                            $(OBJDIR)/ECInfo.o

qms_ls_offers_BINC++: $(OBJDIR)/ListOffers.o


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
