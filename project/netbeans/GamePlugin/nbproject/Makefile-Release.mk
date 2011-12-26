#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/504080735/PH_GamePlugin.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../bin -lPH_Kernel -lPH_Input -lPH_EgineCore -lPH_Dictionary -lPG_GameEngine

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk ../../../bin/libPH_GamePlugin.so

../../../bin/libPH_GamePlugin.so: ${OBJECTFILES}
	${MKDIR} -p ../../../bin
	${LINK.cc} -shared -o ../../../bin/libPH_GamePlugin.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/504080735/PH_GamePlugin.o: ../../../src/gamePlugin/PH_GamePlugin.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/504080735
	${RM} $@.d
	$(COMPILE.cc) -O2 -DPH_LINUX -DPH_GCC -DPH_SDL -DPH_RELEASE -DPH_IGNORE_ASSERT -I../../../include/gamePlugin -I../../../include/kernel -I../../../include/input -I../../../include/dictionary -I../../../include/engineCore -I../../../include/gameEngine -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/504080735/PH_GamePlugin.o ../../../src/gamePlugin/PH_GamePlugin.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} ../../../bin/libPH_GamePlugin.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc