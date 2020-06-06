# Microsoft Developer Studio Project File - Name="loriFucker" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=loriFucker - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "loriFucker.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "loriFucker.mak" CFG="loriFucker - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "loriFucker - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "loriFucker - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "loriFucker - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /incremental:yes /debug /machine:I386

!ELSEIF  "$(CFG)" == "loriFucker - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "loriFucker - Win32 Release"
# Name "loriFucker - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\LoriFucker.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap\add.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\add_active.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\add_passive.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\add_pressed.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\delete_active.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\delete_passive.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\down_active.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\down_passive.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\lori.ico
# End Source File
# Begin Source File

SOURCE=.\lori.rc
# End Source File
# Begin Source File

SOURCE=.\bitmap\pause_active.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\pause_passive.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\start_active.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\start_passive.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\stop_active.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\stop_passive.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\up_active.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap\up_passive.bmp
# End Source File
# End Group
# Begin Group "loriproject"

# PROP Default_Filter ""
# Begin Group "mytypes"

# PROP Default_Filter ""
# Begin Group "gfl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lorifuck\mytypes\gfl\libgfl.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\gfl\stdint.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\gfl\libgfl.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\lorifuck\mytypes\BitmapContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\BitmapContainer.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\Color.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\Color.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\StringList.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\StringList.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\mytypes\Utils.h
# End Source File
# End Group
# Begin Group "imageproportion"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lorifuck\imageproportion\ImageProportion.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\imageproportion\ImageProportion.h
# End Source File
# End Group
# Begin Group "tasksmanager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lorifuck\tasksmanager\Task.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\tasksmanager\Task.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\tasksmanager\TaskManager.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\tasksmanager\TaskManager.h
# End Source File
# End Group
# Begin Group "userinterface"

# PROP Default_Filter ""
# Begin Group "components"

# PROP Default_Filter "*.cpp *.h"
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\Button.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\Button.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\ComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\ComboBox.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\EditBox.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\EditBox.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\LabelText.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\LabelText.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\ListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\ListBox.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\ProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\ProgressBar.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\RectangleProportions.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\components\RectangleProportions.h
# End Source File
# End Group
# Begin Group "taskselector"

# PROP Default_Filter ""
# Begin Group "lastpatch"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lorifuck\userinterface\taskselector\lastpatch\LastPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\taskselector\lastpatch\LastPatch.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\lorifuck\userinterface\taskselector\TaskSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\taskselector\TaskSelector.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\lorifuck\userinterface\TaskConfiguratorWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\TaskConfiguratorWindow.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\TaskWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\userinterface\TaskWindow.h
# End Source File
# End Group
# Begin Group "framesmanager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lorifuck\framesmanager\FramesManager.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\framesmanager\FramesManager.h
# End Source File
# End Group
# Begin Group "taskworker"

# PROP Default_Filter ""
# Begin Group "logocleaner"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lorifuck\taskworker\logocleaner\LogoCleaner.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\taskworker\logocleaner\LogoCleaner.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\lorifuck\taskworker\TaskWorker.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\taskworker\TaskWorker.h
# End Source File
# End Group
# Begin Group "piecegluer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lorifuck\piecegluer\Area.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\Area.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\AreaSequenceCreator.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\AreaSequenceCreator.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\AreaSequenceDebugBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\AreaSequenceDebugBitmap.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\AreaShiftCalculator.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\AreaShiftCalculator.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\AreasLinker.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\AreasLinker.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\BadChainsCleaner.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\BadChainsCleaner.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\BitmapIterator.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\BitmapIterator.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\BitmapShifter.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\BitmapShifter.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\FlatAreaAccumulator.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\FlatAreaAccumulator.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\Gluer.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\Gluer.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\Orientation.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\PieceGluer.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\PieceGluer.h
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\TrashAreaCleaner.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\piecegluer\TrashAreaCleaner.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\lorifuck\ProgramDirection.cpp
# End Source File
# Begin Source File

SOURCE=.\lorifuck\ProgramDirection.h
# End Source File
# End Group
# End Target
# End Project
