##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=GimpLibraries
ConfigurationName      :=Debug
WorkspacePath          := "C:\Documents and Settings\Derby Russell\My Documents\CodeLite\Projects\GimpLibraries"
ProjectPath            := "C:\Documents and Settings\Derby Russell\My Documents\CodeLite\Projects\GimpLibraries"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Derby Russell
Date                   :=11/7/2013
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="C:\Documents and Settings\Derby Russell\My Documents\CodeLite\Projects\GimpLibraries\GimpLibraries.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects=

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:
	@echo Executing Pre Build commands ...
	mkdir c:\gtk\lib\gimp-2.0
	copy libgimp-2.0-0.def c:\gtk\lib\gimp-2.0
	copy libgimpbase-2.0-0.def c:\gtk\lib\gimp-2.0
	copy libgimpcolor-2.0-0.def c:\gtk\lib\gimp-2.0
	copy libgimpconfig-2.0-0.def c:\gtk\lib\gimp-2.0
	copy libgimpmath-2.0-0.def c:\gtk\lib\gimp-2.0
	copy libgimpmodule-2.0-0.def c:\gtk\lib\gimp-2.0
	copy libgimpthumb-2.0-0.def c:\gtk\lib\gimp-2.0
	copy libgimpui-2.0-0.def c:\gtk\lib\gimp-2.0
	copy libgimpwidgets-2.0-0.def c:\gtk\lib\gimp-2.0
	dlltool -d libgimp-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimp-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimp.dll.a"
	dlltool -d libgimpbase-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimpbase-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimpbase.dll.a"
	dlltool -d libgimpcolor-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimpcolor-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimpcolor.dll.a"
	dlltool -d libgimpconfig-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimpconfig-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimpconfig.dll.a"
	dlltool -d libgimpmath-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimpmath-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimpmath.dll.a"
	dlltool -d libgimpmodule-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimpmodule-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimpmodule.dll.a"
	dlltool -d libgimpthumb-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimpthumb-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimpthumb.dll.a"
	dlltool -d libgimpui-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimpui-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimpui.dll.a"
	dlltool -d libgimpwidgets-2.0-0.def -D "C:\Program Files\GIMP-2.0\bin\libgimpwidgets-2.0-0.dll" -l "C:\gtk\lib\gimp-2.0\libgimpwidgets.dll.a"
	@echo Done


##
## Objects
##

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) "C:\Documents and Settings\Derby Russell\My Documents\CodeLite\Projects\GimpLibraries\.build-debug\GimpLibraries"


