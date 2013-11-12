##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CXX01_Final_Assignment
ConfigurationName      :=Debug
WorkspacePath          := "C:\Users\Chinwei\Documents\GitHub\CXX01_Final_Assignment"
ProjectPath            := "C:\Users\Chinwei\Documents\GitHub\CXX01_Final_Assignment"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Chinwei
Date                   :=11/12/13
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
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
ObjectsFileList        :="CXX01_Final_Assignment.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/memory$(ObjectSuffix) $(IntermediateDirectory)/ReadWriteFile$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.c $(IntermediateDirectory)/main$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Chinwei/Documents/GitHub/CXX01_Final_Assignment/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/memory$(ObjectSuffix): memory.c $(IntermediateDirectory)/memory$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Chinwei/Documents/GitHub/CXX01_Final_Assignment/memory.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/memory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/memory$(DependSuffix): memory.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/memory$(ObjectSuffix) -MF$(IntermediateDirectory)/memory$(DependSuffix) -MM "memory.c"

$(IntermediateDirectory)/memory$(PreprocessSuffix): memory.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/memory$(PreprocessSuffix) "memory.c"

$(IntermediateDirectory)/ReadWriteFile$(ObjectSuffix): ReadWriteFile.c $(IntermediateDirectory)/ReadWriteFile$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/Chinwei/Documents/GitHub/CXX01_Final_Assignment/ReadWriteFile.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ReadWriteFile$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ReadWriteFile$(DependSuffix): ReadWriteFile.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ReadWriteFile$(ObjectSuffix) -MF$(IntermediateDirectory)/ReadWriteFile$(DependSuffix) -MM "ReadWriteFile.c"

$(IntermediateDirectory)/ReadWriteFile$(PreprocessSuffix): ReadWriteFile.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ReadWriteFile$(PreprocessSuffix) "ReadWriteFile.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/memory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/memory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/memory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ReadWriteFile$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ReadWriteFile$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ReadWriteFile$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) ".build-debug/CXX01_Final_Assignment"


