##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=InsaneBump
ConfigurationName      :=Release
WorkspacePath          := "C:\Documents and Settings\Derby Russell\My Documents\CodeLite\Projects\gimp-plugin-insanebump\windows\InsaneBump"
ProjectPath            := "C:\Documents and Settings\Derby Russell\My Documents\CodeLite\Projects\gimp-plugin-insanebump\windows\InsaneBump"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Derby Russell
Date                   :=11/24/2013
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
ObjectsFileList        :="C:\Documents and Settings\Derby Russell\My Documents\CodeLite\Projects\gimp-plugin-insanebump\windows\InsaneBump\InsaneBump.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
LinkOptions            :=  -lgimp.dll -lglib-2.0.dll -lgdk-win32-2.0.dll -lgtk-win32-2.0.dll -lgobject-2.0.dll -lgimpui.dll -lgimpbase.dll -lgimpwidgets.dll -lintl.dll -mwindows
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:/gtk/include/cairo $(IncludeSwitch)C:/gtk/lib/gtk-2.0/include $(IncludeSwitch)C:/gtk/include/glib-2.0 $(IncludeSwitch)C:/gtk/include/atk-1.0 $(IncludeSwitch)C:/gtk/include/gtk-2.0 $(IncludeSwitch)C:/gtk/include $(IncludeSwitch)C:/gtk/include/gdk-pixbuf-2.0 $(IncludeSwitch)C:/gtk/include/pango-1.0 $(IncludeSwitch)C:/gtk/lib/glib-2.0/include $(IncludeSwitch)C:/gtk/include/freetype2 $(IncludeSwitch)C:/gtk/include/libpng14 $(IncludeSwitch)C:/gtk/include/gtkglext-1.0 $(IncludeSwitch)C:/gtk/lib/gtkglext-1.0/include $(IncludeSwitch)C:/gtk/include/gimp-2.0 $(IncludeSwitch)C:/GtkGLExt/1.0/lib/gtkglext-1.0/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)C:/gtk/lib/gimp-2.0 $(LibraryPathSwitch)C:/gtk/lib $(LibraryPathSwitch)C:/glew-1.10.0/lib 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects=$(IntermediateDirectory)/scale$(ObjectSuffix) $(IntermediateDirectory)/gimp-insanebump$(ObjectSuffix) $(IntermediateDirectory)/InsaneBump$(ObjectSuffix) $(IntermediateDirectory)/normalmap$(ObjectSuffix) $(IntermediateDirectory)/PluginConnectors$(ObjectSuffix) $(IntermediateDirectory)/InsaneBumpDialog$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects) > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	copy Release\InsaneBump.exe "C:\Documents and Settings\Derby Russell\.gimp-2.6\plug-ins"
	@echo Done

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/scale$(ObjectSuffix): scale.c $(IntermediateDirectory)/scale$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/scale.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/scale$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/scale$(DependSuffix): scale.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/scale$(ObjectSuffix) -MF$(IntermediateDirectory)/scale$(DependSuffix) -MM "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/scale.c"

$(IntermediateDirectory)/scale$(PreprocessSuffix): scale.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/scale$(PreprocessSuffix) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/scale.c"

$(IntermediateDirectory)/gimp-insanebump$(ObjectSuffix): gimp-insanebump.c $(IntermediateDirectory)/gimp-insanebump$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/gimp-insanebump.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/gimp-insanebump$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/gimp-insanebump$(DependSuffix): gimp-insanebump.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/gimp-insanebump$(ObjectSuffix) -MF$(IntermediateDirectory)/gimp-insanebump$(DependSuffix) -MM "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/gimp-insanebump.c"

$(IntermediateDirectory)/gimp-insanebump$(PreprocessSuffix): gimp-insanebump.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/gimp-insanebump$(PreprocessSuffix) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/gimp-insanebump.c"

$(IntermediateDirectory)/InsaneBump$(ObjectSuffix): InsaneBump.c $(IntermediateDirectory)/InsaneBump$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/InsaneBump.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/InsaneBump$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/InsaneBump$(DependSuffix): InsaneBump.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/InsaneBump$(ObjectSuffix) -MF$(IntermediateDirectory)/InsaneBump$(DependSuffix) -MM "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/InsaneBump.c"

$(IntermediateDirectory)/InsaneBump$(PreprocessSuffix): InsaneBump.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/InsaneBump$(PreprocessSuffix) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/InsaneBump.c"

$(IntermediateDirectory)/normalmap$(ObjectSuffix): normalmap.c $(IntermediateDirectory)/normalmap$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/normalmap.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/normalmap$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/normalmap$(DependSuffix): normalmap.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/normalmap$(ObjectSuffix) -MF$(IntermediateDirectory)/normalmap$(DependSuffix) -MM "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/normalmap.c"

$(IntermediateDirectory)/normalmap$(PreprocessSuffix): normalmap.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/normalmap$(PreprocessSuffix) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/normalmap.c"

$(IntermediateDirectory)/PluginConnectors$(ObjectSuffix): PluginConnectors.c $(IntermediateDirectory)/PluginConnectors$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/PluginConnectors.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PluginConnectors$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PluginConnectors$(DependSuffix): PluginConnectors.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PluginConnectors$(ObjectSuffix) -MF$(IntermediateDirectory)/PluginConnectors$(DependSuffix) -MM "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/PluginConnectors.c"

$(IntermediateDirectory)/PluginConnectors$(PreprocessSuffix): PluginConnectors.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PluginConnectors$(PreprocessSuffix) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/PluginConnectors.c"

$(IntermediateDirectory)/InsaneBumpDialog$(ObjectSuffix): InsaneBumpDialog.c $(IntermediateDirectory)/InsaneBumpDialog$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/InsaneBumpDialog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/InsaneBumpDialog$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/InsaneBumpDialog$(DependSuffix): InsaneBumpDialog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/InsaneBumpDialog$(ObjectSuffix) -MF$(IntermediateDirectory)/InsaneBumpDialog$(DependSuffix) -MM "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/InsaneBumpDialog.c"

$(IntermediateDirectory)/InsaneBumpDialog$(PreprocessSuffix): InsaneBumpDialog.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/InsaneBumpDialog$(PreprocessSuffix) "C:/Documents and Settings/Derby Russell/My Documents/CodeLite/Projects/gimp-plugin-insanebump/windows/InsaneBump/InsaneBumpDialog.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/scale$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/scale$(DependSuffix)
	$(RM) $(IntermediateDirectory)/scale$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/gimp-insanebump$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/gimp-insanebump$(DependSuffix)
	$(RM) $(IntermediateDirectory)/gimp-insanebump$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/InsaneBump$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/InsaneBump$(DependSuffix)
	$(RM) $(IntermediateDirectory)/InsaneBump$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/normalmap$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/normalmap$(DependSuffix)
	$(RM) $(IntermediateDirectory)/normalmap$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/PluginConnectors$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/PluginConnectors$(DependSuffix)
	$(RM) $(IntermediateDirectory)/PluginConnectors$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/InsaneBumpDialog$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/InsaneBumpDialog$(DependSuffix)
	$(RM) $(IntermediateDirectory)/InsaneBumpDialog$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) "C:\Documents and Settings\Derby Russell\My Documents\CodeLite\Projects\gimp-plugin-insanebump\windows\InsaneBump\.build-release\InsaneBump"


