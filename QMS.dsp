# Microsoft Developer Studio Project File - Name="QMS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=QMS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QMS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QMS.mak" CFG="QMS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QMS - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "QMS - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QMS - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "QMS - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(ACE_ROOT)" /I "$(QMS_ROOT)\Core" /I "$(QMS_ROOT)\Utilities" /I "$(QMS_ROOT)\build\winnt\Core\Trader" /I "$(XERCESCROOT)\src" /I "$(QMS_ROOT)\build\winnt\Instrumentaion\Sensors\Remos" /I "$(QMS_ROOT)\build\winnt\Instrumentation\Sensors\Hello_World" /I "$(QMS_ROOT)\build\winnt\Instrumentation\Sensors\Generic" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"build\winnt\Debug/QMS.pch" /YX /Fo"build\winnt\Debug/" /Fd"build\winnt\Debug/" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"build\winnt\QMS.lib"

!ENDIF 

# Begin Target

# Name "QMS - Win32 Release"
# Name "QMS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat"
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\CommandC.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\CommandS.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\CommandS_T.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\ControlC.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\ControlS.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\ControlS_T.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\CORBA_Handles.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\EC_Adapter\EC_Adapter.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Generic\Generic_SensorC.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Generic\Generic_SensorS.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Generic\Generic_SensorS_T.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Hello_World\Hello_WorldC.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Hello_World\Hello_WorldS.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Hello_World\Hello_WorldS_T.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\Parse_Duration.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\Parse_XML.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\EC_Adapter\Push_Consumer.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\EC_Adapter\Push_Supplier.cpp
# End Source File
# Begin Source File

SOURCE=.\Core\Trader\QMS_Trader_ECInfo_Impl.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Remos\Remos_SensorC.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Remos\Remos_SensorS.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Instrumentation\Sensors\Remos\Remos_SensorS_T.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\TraderC.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\TraderS.cpp
# End Source File
# Begin Source File

SOURCE=.\build\winnt\Core\Trader\TraderS_T.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilities\YP_Offer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "IDL"

# PROP Default_Filter "idl"
# Begin Source File

SOURCE=.\Core\Command.idl

!IF  "$(CFG)" == "QMS - Win32 Release"

!ELSEIF  "$(CFG)" == "QMS - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__COMMA="$(ACE_ROOT)\bin\tao_idl.exe"	
# Begin Custom Build - Invoking TAO_IDL compiler on $(InputName)
InputPath=.\Core\Command.idl
InputName=Command

BuildCmds= \
	$(ACE_ROOT)\bin\tao_idl -o $(QMS_ROOT)\build\winnt\Core\Trader -Ge 0 Core\$(InputName).idl

"$(InputName)C.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Core\Control.idl

!IF  "$(CFG)" == "QMS - Win32 Release"

!ELSEIF  "$(CFG)" == "QMS - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__CONTR="$(ACE_ROOT)\bin\tao_idl.exe"	
# Begin Custom Build - Invoking TAO_IDL compiler on $(InputName)
InputPath=.\Core\Control.idl
InputName=Control

BuildCmds= \
	$(ACE_ROOT)\bin\tao_idl -o $(QMS_ROOT)\build\winnt\Core\Trader -Ge 0 Core\$(InputName).idl

"$(InputName)C.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Instrumentation\Sensors\Generic\Generic_Sensor.idl

!IF  "$(CFG)" == "QMS - Win32 Release"

!ELSEIF  "$(CFG)" == "QMS - Win32 Debug"

USERDEP__GENER="$(ACE_ROOT)\bin\tao_idl.exe"	
# Begin Custom Build - Invoking TAO_IDL compiler on $(InputName)
InputPath=.\Instrumentation\Sensors\Generic\Generic_Sensor.idl
InputName=Generic_Sensor

BuildCmds= \
	mkdir $(QMS_ROOT)\build\winnt\Instrumentation\Sensors\Generic \
	$(ACE_ROOT)\bin\tao_idl -o $(QMS_ROOT)\build\winnt\Instrumentation\Sensors\Generic -Ge 0 Instrumentation\Sensors\Generic\$(InputName).idl \
	

"$(InputName)C.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Instrumentation\Sensors\Hello_World\Hello_World.idl

!IF  "$(CFG)" == "QMS - Win32 Release"

!ELSEIF  "$(CFG)" == "QMS - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__HELLO="$(ACE_ROOT)\bin\tao_idl.exe"	
# Begin Custom Build - Invoking TAO_IDL compiler on $(InputName)
InputPath=.\Instrumentation\Sensors\Hello_World\Hello_World.idl
InputName=Hello_World

BuildCmds= \
	mkdir $(QMS_ROOT)\build\winnt\Instrumentation\Sensors\Hello_World \
	$(ACE_ROOT)\bin\tao_idl -o $(QMS_ROOT)\build\winnt\Instrumentation\Sensors\Hello_World -Ge 0 Instrumentation\Sensors\Hello_World\$(InputName).idl \
	

"$(InputName)C.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Instrumentation\Sensors\Remos\Remos_Sensor.idl

!IF  "$(CFG)" == "QMS - Win32 Release"

!ELSEIF  "$(CFG)" == "QMS - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__REMOS="$(ACE_ROOT)\bin\tao_idl.exe"	
# Begin Custom Build - Invoking TAO_IDL compiler on $(InputName)
InputPath=.\Instrumentation\Sensors\Remos\Remos_Sensor.idl
InputName=Remos_Sensor

BuildCmds= \
	mkdir $(QMS_ROOT)\build\winnt\Instrumentation\Sensors\Remos \
	$(ACE_ROOT)\bin\tao_idl -o $(QMS_ROOT)\build\winnt\Instrumentation\Sensors\Remos -Ge 0 Instrumentation\Sensors\Remos\$(InputName).idl \
	

"$(InputName)C.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Core\Trader\Trader.idl

!IF  "$(CFG)" == "QMS - Win32 Release"

!ELSEIF  "$(CFG)" == "QMS - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__TRADE="$(ACE_ROOT)\bin\tao_idl.exe"	
# Begin Custom Build - Invoking TAO_IDL compiler on $(InputName)
InputPath=.\Core\Trader\Trader.idl
InputName=Trader

BuildCmds= \
	mkdir $(QMS_ROOT)\build\winnt\Core\Trader \
	$(ACE_ROOT)\bin\tao_idl -o $(QMS_ROOT)\build\winnt\Core\Trader -Ge 0 Core\Trader\$(InputName).idl \
	

"$(InputName)C.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)C.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.i" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)S_T.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
