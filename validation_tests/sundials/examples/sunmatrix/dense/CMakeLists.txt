# -*- mode: cmake -*-
# -----------------------------------------------------------------
# Programmer(s): Radu Serban @ LLNL
#                David J. Gardner @ LLNL
# -----------------------------------------------------------------
# SUNDIALS Copyright Start
# Copyright (c) 2002-2019, Lawrence Livermore National Security
# and Southern Methodist University.
# All rights reserved.
#
# See the top-level LICENSE and NOTICE files for details.
#
# SPDX-License-Identifier: BSD-3-Clause
# SUNDIALS Copyright End
# -----------------------------------------------------------------
# CMakeLists.txt for  serial examples
#
# This file is generated from a template using variables
# set at configuration time. It can be used as a template for
# other user CMakeLists configuration files.
# -----------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)

# Specify project name
PROJECT(_serial_examples C)

MARK_AS_ADVANCED(EXECUTABLE_OUTPUT_PATH LIBRARY_OUTPUT_PATH)

# Examples using SUNDIALS linear solvers
SET(examples  test_sunmatrix_dense)
SET(examples_dependencies  test_sunmatrix sundials_nvector sundials_matrix)

# Examples using LAPACK linear solvers
SET(examples_bl )
SET(examples_dependencies_bl )

# Examples using KLU linear solvers
SET(examples_klu )
SET(examples_dependencies_klu )

# Examples using SuperLU_MT linear solvers
SET(examples_slumt )
SET(examples_dependencies_slumt )

# Specify path to SUNDIALS header files
SET(SUNDIALS_INC_DIR
  /spack/opt/spack/linux-rhel7-x86_64/gcc-7.3.0/sundials-4.1.0-zcot6t4hb6hbkydothsxlbfh5gbbbprp/include
  CACHE STRING
  "Location of SUNDIALS header files")

# Add path to SUNDIALS header files
INCLUDE_DIRECTORIES(${SUNDIALS_INC_DIR})

# Set search path for SUNDIALS libraries 
SET(SUNDIALS_LIB_DIR /spack/opt/spack/linux-rhel7-x86_64/gcc-7.3.0/sundials-4.1.0-zcot6t4hb6hbkydothsxlbfh5gbbbprp/lib64)

# Find the SUNDIALS solver's library
FIND_LIBRARY(SUNDIALS_SOLVER_LIB
  sundials_sunmatrixdense ${SUNDIALS_LIB_DIR}
  DOC " library")

# Find the NVECTOR library
FIND_LIBRARY(SUNDIALS_NVEC_LIB
  sundials_nvecserial ${SUNDIALS_LIB_DIR}
  DOC "NVECTOR library")

# Set an extra link directory if necessary (false if empty)
IF(EXISTS )
  LINK_DIRECTORIES()
ENDIF()

# Set additional libraries
SET(SUNDIALS_EXTRA_LIB  -lm /usr/lib64/librt.so CACHE STRING "Additional libraries")

# Set other libraries libraries
SET(BLAS_LIBRARIES  CACHE STRING "Blas libraries")
SET(LAPACK_LIBRARIES  CACHE STRING "Lapack libraries")

INCLUDE_DIRECTORIES()
SET(SUPERLUMT_LIBRARIES  CACHE STRING "SuperLUMT libraries")

INCLUDE_DIRECTORIES()
SET(KLU_LIBRARIES  CACHE STRING "KLU libraries")

# List of Sundials libraries shared across all examples
SET(SUNDIALS_LIBS ${SUNDIALS_SOLVER_LIB} ${SUNDIALS_NVEC_LIB} ${SUNDIALS_EXTRA_LIB})

# Enable testing
INCLUDE(CTest)

# Build examples with SUNDIALS linear solvers one by one
FOREACH(example ${examples})

  # example source files
  ADD_EXECUTABLE(${example} ${example}.c ${examples_dependencies})

  # libraries to link against
  TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_LIBS})

ENDFOREACH(example ${examples})

# add the first example to ctest
LIST(GET examples 0 TEST)
ADD_TEST(NAME ${TEST} COMMAND ${TEST})

# Build each example with LAPACK linear solvers one by one
IF(LAPACK_LIBRARIES)
  FOREACH(example ${examples_bl})

    # Find the Sundials linear solver libraries
    FIND_LIBRARY(SUNDIALS_SUNLINSOLLAPACKBAND_LIB
      sundials_sunlinsollapackband ${SUNDIALS_LIB_DIR}
      DOC "Sundials banded LAPACK linear solver library")

    FIND_LIBRARY(SUNDIALS_SUNLINSOLLAPACKDENSE_LIB
      sundials_sunlinsollapackdense ${SUNDIALS_LIB_DIR}
      DOC "Sundials dense LAPACK linear solver library")

    # example source files
    ADD_EXECUTABLE(${example} ${example}.c ${examples_dependencies_bl})
  
    # libraries to link against
    TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_LIBS})
    TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_SUNLINSOLLAPACKBAND_LIB})
    TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_SUNLINSOLLAPACKDENSE_LIB})
    TARGET_LINK_LIBRARIES(${example} ${LAPACK_LIBRARIES})

    IF(BLAS_LIBRARIES)
      TARGET_LINK_LIBRARIES(${example} ${BLAS_LIBRARIES})
    ENDIF()

  ENDFOREACH(example ${examples_bl})
ENDIF()


# Build each example with KLU linear solvers one by one
IF(KLU_LIBRARIES)
  FOREACH(example ${examples_klu})

    # Find the Sundials linear solver libraries
    FIND_LIBRARY(SUNDIALS_SUNLINSOLKLU_LIB
      sundials_sunlinsolklu ${SUNDIALS_LIB_DIR}
      DOC "Sundials KLU linear solver library")

    # example source files
    ADD_EXECUTABLE(${example} ${example}.c ${examples_dependencies_klu})
  
    # libraries to link against
    TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_LIBS})
    TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_SUNLINSOLKLU_LIB})
    TARGET_LINK_LIBRARIES(${example} ${KLU_LIBRARIES})

  ENDFOREACH(example ${examples_klu})
ENDIF()


# Build each example with SuperLU_MT linear solvers one by one
IF(SUPERLUMT_LIBRARIES)
  FOREACH(example ${examples_slumt})

    # Find the Sundials linear solver libraries
    FIND_LIBRARY(SUNDIALS_SUNLINSOLSLUMT_LIB
      sundials_sunlinsolsuperlumt ${SUNDIALS_LIB_DIR}
      DOC "Sundials KLU linear solver library")

    # example source files
    ADD_EXECUTABLE(${example} ${example}.c ${examples_dependencies_slumt})
  
    # libraries to link against
    TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_LIBS})
    TARGET_LINK_LIBRARIES(${example} ${SUNDIALS_SUNLINSOLSLUMT_LIB})
    TARGET_LINK_LIBRARIES(${example} ${SUPERLUMT_LIBRARIES})

    IF(BLAS_LIBRARIES)
      TARGET_LINK_LIBRARIES(${example} ${BLAS_LIBRARIES})
    ENDIF()

  ENDFOREACH(example ${examples_slumt})
ENDIF()
