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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/vendor/EBBLibrary/gpio/GPIO.o \
	${OBJECTDIR}/vendor/EBBLibrary/gpio/PWM.o \
	${OBJECTDIR}/vendor/EBBLibrary/gpio/util.o


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
LDLIBSOPTIONS=-static

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stepdriver

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stepdriver: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/stepdriver ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/vendor/EBBLibrary/gpio/GPIO.o: vendor/EBBLibrary/gpio/GPIO.cpp
	${MKDIR} -p ${OBJECTDIR}/vendor/EBBLibrary/gpio
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vendor/EBBLibrary/gpio/GPIO.o vendor/EBBLibrary/gpio/GPIO.cpp

${OBJECTDIR}/vendor/EBBLibrary/gpio/PWM.o: vendor/EBBLibrary/gpio/PWM.cpp
	${MKDIR} -p ${OBJECTDIR}/vendor/EBBLibrary/gpio
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vendor/EBBLibrary/gpio/PWM.o vendor/EBBLibrary/gpio/PWM.cpp

${OBJECTDIR}/vendor/EBBLibrary/gpio/util.o: vendor/EBBLibrary/gpio/util.cpp
	${MKDIR} -p ${OBJECTDIR}/vendor/EBBLibrary/gpio
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vendor/EBBLibrary/gpio/util.o vendor/EBBLibrary/gpio/util.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
