############################ -*- Mode: Makefile -*- ###########################
## Makefile<3> ---
## Author           : Manoj Srivastava ( srivasta@glaurung.stdc.com )
## Created On       : Wed Nov  1 10:04:09 2000
## Created On Node  : glaurung.stdc.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Wed Dec  5 20:35:12 2001
## Last Machine Used: glaurung.green-gryphon.com
## Update Count     : 111
## Status           : Unknown, Use with caution!
## HISTORY          :
## Description      :
## $Id: Makefile,v 1.14 2002/01/03 20:33:30 srivasta Exp $
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
CPPFLAGS += -DDEBUG=1L -DQMS_DO_TRACE=1
CPPFLAGS += -I$(XERCESCROOT)/include -I$(XALANCROOT)/src      \
            -I/usr/include/xercesc   -I/usr/include/xalan/    \
            -I../
SRC     = test_CORBA_Handles.cpp Makefile          test_parse_xml.cpp  \
          test_capability.cpp    test_message.cpp  test_xslt.cpp       \
          bench_capability.cpp   bench_message.cpp bench_parse_xml.cpp \
          bench_xslt.cpp         test_duration.cpp
C++PROGRAMS = test_CORBA_Handles test_parse_xml   test_capability      \
              test_message       test_xslt        bench_capability     \
              bench_message      bench_parse_xml  bench_xslt           \
              test_duration


test_parse_xml_C++LIBS=$(C++LIBS) -lxerces-c
test_parse_xml_C++LDFLAGS = $(C++LDFLAGS) -L$(XERCESCROOT)/lib
test_capability_C++LIBS=$(C++LIBS) -lxerces-c
test_capability_C++LDFLAGS = $(C++LDFLAGS) -L$(XERCESCROOT)/lib
test_message_C++LIBS=$(C++LIBS) -lxerces-c
test_message_C++LDFLAGS = $(C++LDFLAGS) -L$(XERCESCROOT)/lib
test_xslt_C++LIBS=$(C++LIBS) -lxalan-c -lxerces-c
test_xslt_C++LDFLAGS = $(C++LDFLAGS) -L$(XALANCROOT)/lib -L$(XERCESCROOT)/lib
bench_capability_C++LIBS=$(C++LIBS) -lxalan-c -lxerces-c
bench_capability_C++LDFLAGS = $(C++LDFLAGS) -L$(XALANCROOT)/lib \
                              -L$(XERCESCROOT)/lib
bench_message_C++LIBS=$(C++LIBS) -lxalan-c -lxerces-c
bench_message_C++LDFLAGS = $(C++LDFLAGS) -L$(XALANCROOT)/lib \
                           -L$(XERCESCROOT)/lib
bench_parse_xml_C++LIBS=$(C++LIBS) -lxalan-c -lxerces-c
bench_parse_xml_C++LDFLAGS = $(C++LDFLAGS) -L$(XALANCROOT)/lib \
                           -L$(XERCESCROOT)/lib
bench_xslt_C++LIBS=$(C++LIBS) -lxalan-c -lxerces-c
bench_xslt_C++LDFLAGS = $(C++LDFLAGS) -L$(XALANCROOT)/lib \
                           -L$(XERCESCROOT)/lib
#----------------------------------------------------------------------------
#       Include macros and targets
#----------------------------------------------------------------------------
include $(SRCTOP)/Config/project.tmpl
#----------------------------------------------------------------------------
#       Local targets
#-------------------------------------------------------------------------
C++LDFLAGS += -L$(ACE_ROOT)/ace -L$(OBJDIR)/../.. 
C++LIBS += -lQMS -lTAO_RTEvent -lTAO_RTSched -lTAO_CosTrading \
           -lTAO_CosEvent -lTAO  -lACE
test_CORBA_Handles_BINC++: $(OBJDIR)/test_CORBA_Handles.o
test_parse_xml_BINC++: $(OBJDIR)/test_parse_xml.o
test_capability_BINC++: $(OBJDIR)/test_capability.o
test_message_BINC++: $(OBJDIR)/../Parse_XML.o $(OBJDIR)/test_message.o
test_xslt_BINC++: $(OBJDIR)/test_xslt.o
bench_capability_BINC++: $(OBJDIR)/bench_capability.o
bench_message_BINC++: $(OBJDIR)/bench_message.o
bench_parse_xml_BINC++: $(OBJDIR)/bench_parse_xml.o
bench_xslt_BINC++: $(OBJDIR)/bench_xslt.o
test_duration_BINC++: $(OBJDIR)/test_duration.o
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
