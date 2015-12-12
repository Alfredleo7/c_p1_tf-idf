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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1591637995/stem.o \
	${OBJECTDIR}/_ext/1122234286/documento.o \
	${OBJECTDIR}/_ext/1122234286/generic.o \
	${OBJECTDIR}/_ext/1122234286/list.o \
	${OBJECTDIR}/_ext/1122234286/nodelist.o \
	${OBJECTDIR}/_ext/1122234286/nodoTermino.o \
	${OBJECTDIR}/directorio.o \
	${OBJECTDIR}/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/c_p1_tf-idf

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/c_p1_tf-idf: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/c_p1_tf-idf ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/1591637995/stem.o: /home/stalyn/Documentos/ProyectoLenguajes/c_p1_tf-idf/stem.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1591637995
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1591637995/stem.o /home/stalyn/Documentos/ProyectoLenguajes/c_p1_tf-idf/stem.c

${OBJECTDIR}/_ext/1122234286/documento.o: /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/documento.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1122234286
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1122234286/documento.o /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/documento.c

${OBJECTDIR}/_ext/1122234286/generic.o: /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/generic.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1122234286
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1122234286/generic.o /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/generic.c

${OBJECTDIR}/_ext/1122234286/list.o: /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/list.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1122234286
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1122234286/list.o /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/list.c

${OBJECTDIR}/_ext/1122234286/nodelist.o: /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/nodelist.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1122234286
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1122234286/nodelist.o /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/nodelist.c

${OBJECTDIR}/_ext/1122234286/nodoTermino.o: /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/nodoTermino.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1122234286
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1122234286/nodoTermino.o /windows/Dropbox/Lenguajes/proyectos/proyecto1Lenguajes/nodoTermino.c

${OBJECTDIR}/directorio.o: directorio.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/directorio.o directorio.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/c_p1_tf-idf

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
