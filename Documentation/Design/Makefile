############################ -*- Mode: Makefile -*- ###########################
## Makefile ---
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
## Created On       : Mon Oct 30 15:20:21 2000
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Tue Oct 16 13:41:30 2001
## Last Machine Used: ember.stdc.com
## Update Count     : 25
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
SRC     = Makefile ChangeLog QMS_Design.mdl c-bindings.html \
          desi-remos.png design.html

FilesToClean = QMS_Api.html tmp.html QMS_Consumer.h.html \
	QMS_Supplier.h.html QMS_Remos_Msg.h.html Remos_Datastructs.h.html
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
#       Local macros
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------
all:QMS_Api.h.html QMS_Consumer.h.html QMS_Supplier.h.html \
           QMS_Remos_Msg.h.html Remos_Datastructs.h.html

$(OBJDIR)/QMS_Remos_Msg.h.html: $(SRCTOP)/Desi_Remos/QMS_Remos_Msg.h
	code2html -n -T '$@' -l c++ $^ > $(OBJDIR)/tmp.html
	tidy -i -c -latin1 $(OBJDIR)/tmp.html 2>/dev/null | \
                    perl -ple 's/#444444/#cc4444/go' > $@
	$(RM) $(OBJDIR)/tmp.html

$(OBJDIR)/Remos_Datastructs.h.html: $(SRCTOP)/Desi_Remos/Remos_Datastructs.h
	code2html -n -T '$@' -l c++ $^ > $(OBJDIR)/tmp.html
	tidy -i -c -latin1 $(OBJDIR)/tmp.html 2>/dev/null | \
                    perl -ple 's/#444444/#cc4444/go' > $@
	$(RM) $(OBJDIR)/tmp.html

%.h.html: $(SRCTOP)/QMS_Api/%.h
	code2html -n -T '$@' -l c++ $^ > $(OBJDIR)/tmp.html
	tidy -i -c -latin1 $(OBJDIR)/tmp.html  2>/dev/null | \
                     perl -ple	's/#444444/#cc4444/go' > $(OBJDIR)/$@
	$(RM) $(OBJDIR)/tmp.html



#----------------------------------------------------------------------------
#       Dependencies
#----------------------------------------------------------------------------


# Local Variables:
# mode: makefile
# comment-start: "#"
# End:

