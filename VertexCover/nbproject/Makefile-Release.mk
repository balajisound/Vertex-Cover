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
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/_ext/957739886/Edge.o \
	${OBJECTDIR}/_ext/957739886/Graph.o \
	${OBJECTDIR}/_ext/957739886/VertexCover.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vertexcover

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vertexcover: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vertexcover ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/_ext/957739886/Edge.o: /Users/balajisoundrarajan/Vertex-Cover/VertexCover/Edge.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957739886
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/957739886/Edge.o /Users/balajisoundrarajan/Vertex-Cover/VertexCover/Edge.cpp

${OBJECTDIR}/_ext/957739886/Graph.o: /Users/balajisoundrarajan/Vertex-Cover/VertexCover/Graph.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957739886
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/957739886/Graph.o /Users/balajisoundrarajan/Vertex-Cover/VertexCover/Graph.cpp

${OBJECTDIR}/_ext/957739886/VertexCover.o: /Users/balajisoundrarajan/Vertex-Cover/VertexCover/VertexCover.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/957739886
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/957739886/VertexCover.o /Users/balajisoundrarajan/Vertex-Cover/VertexCover/VertexCover.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vertexcover

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
