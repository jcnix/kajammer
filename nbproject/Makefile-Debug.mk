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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/${CND_PLATFORM}

# Object Files
OBJECTFILES=

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

nbproject/qt-${CONF}.mk: nbproject/qt-${CONF}.pro FORCE
	qmake VPATH=. -spec linux-g++ -o qttmp-${CONF}.mk nbproject/qt-${CONF}.pro
	mv -f qttmp-${CONF}.mk nbproject/qt-${CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CONF}.mk
	${MAKE} -f nbproject/qt-${CONF}.mk dist/kajammer

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: nbproject/qt-Debug.mk
	$(MAKE) -f nbproject/qt-Debug.mk distclean

# Subprojects
.clean-subprojects:
