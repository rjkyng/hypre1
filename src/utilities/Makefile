#BHEADER**********************************************************************
# Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
# Produced at the Lawrence Livermore National Laboratory.
# This file is part of HYPRE.  See file COPYRIGHT for details.
#
# HYPRE is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License (as published by the Free
# Software Foundation) version 2.1 dated February 1999.
#
# $Revision$
#EHEADER**********************************************************************

include ../config/Makefile.config

CINCLUDES = ${INCLUDES} ${MPIINCLUDE}
CDEFS = ${TIMERDEFS}

C_COMPILE_FLAGS =\
   -I..\
   -I$(srcdir)/..\
   -I$(srcdir)\
   ${CINCLUDES}\
   ${CDEFS}
CXX_COMPILE_FLAGS = ${C_COMPILE_FLAGS}

HEADERS =\
 amg_linklist.h\
 exchange_data.h\
 fortran.h\
 fortran_matrix.h\
 general.h\
 hypre_memory.h\
 HYPRE_utilities.h\
 mpistubs.h\
 threading.h\
 timing.h\
 _hypre_utilities.h\
 lap_utils.h

FILES =\
 HYPRE_version.c\
 amg_linklist.c\
 binsearch.c\
 exchange_data.c\
 fortran_matrix.c\
 hypre_ap.c\
 hypre_complex.c\
 hypre_memory.c\
 hypre_printf.c\
 hypre_qsort.c\
 mpistubs.c\
 qsplit.c\
 random.c\
 threading.c\
 timer.c\
 timing.c\
 hypre_mpi_comm_f2c.c\
 hypre_error.c\
 F90_HYPRE_error.c\
 hypre_prefix_sum.c\
 hypre_merge_sort.c\
 hypre_hopscotch_hash.c\
 gpuErrorCheck.c\
 gpuMem.c\
 hypre_general.c\
 hypre_reducesum.c\
 lap_utils.c

OBJS = ${FILES:.c=.o}

SONAME = libHYPRE_utilities-${HYPRE_RELEASE_VERSION}${HYPRE_LIB_SUFFIX}

##################################################################
# Targets
##################################################################

all: libHYPRE_utilities${HYPRE_LIB_SUFFIX}
	cp -fR $(srcdir)/HYPRE_*.h $(HYPRE_BUILD_DIR)/include
	cp -fR $(srcdir)/_hypre_utilities.h $(HYPRE_BUILD_DIR)/include
	cp -fR $(srcdir)/hypre_hopscotch_hash.h $(HYPRE_BUILD_DIR)/include
	cp -fR $(srcdir)/fortran*.h $(HYPRE_BUILD_DIR)/include
	cp -fR $(srcdir)/lap_utils.h $(HYPRE_INC_INSTALL)
	# RK 2019 (lap_utils)
#	cp -fR libHYPRE* $(HYPRE_BUILD_DIR)/lib

install: libHYPRE_utilities${HYPRE_LIB_SUFFIX}
	cp -fR $(srcdir)/HYPRE_*.h $(HYPRE_INC_INSTALL)
	cp -fR $(srcdir)/_hypre_utilities.h $(HYPRE_INC_INSTALL)
	cp -fR $(srcdir)/fortran*.h $(HYPRE_INC_INSTALL)
	cp -fR $(srcdir)/lap_utils.h $(HYPRE_INC_INSTALL)
	# RK 2019 (lap_utils)
#	cp -fR libHYPRE* $(HYPRE_LIB_INSTALL)

clean:
	rm -f *.o libHYPRE*
	rm -rf pchdir tca.map *inslog*

distclean: clean

##################################################################
# Rules
##################################################################

libHYPRE_utilities.a: ${OBJS}
	@echo  "Building $@ ... "
	${AR} $@ *.o
	${RANLIB} $@

libHYPRE_utilities.so libHYPRE_utilities.dylib: ${OBJS}
	@echo  "Building $@ ... "
	${BUILD_CC_SHARED} -o ${SONAME} ${OBJS} ${SHARED_SET_SONAME}${SONAME}
	ln -s ${SONAME} $@

${OBJS}: ${HEADERS}
