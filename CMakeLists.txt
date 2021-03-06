#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(util_df)
set (LIB_NAME "util_df") 

#----------------------------------------------------------------------------
# Setup GNUInstallDirs for installation
include(GNUInstallDirs)

#----------------------------------------------------------------------------
# The following lines are required so that the executable can dynamically locate 
# the library dependencies independent of use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_FULL_LIBDIR}" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
ENDIF("${isSystemDir}" STREQUAL "-1")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

#----------------------------------------------------------------------------
# Force use of c++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------------------------------------------------------------------------
# ROOT path
# commented out the following line so that this procedure will evolve with ROOT:
# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
# - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
# - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)

# Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

#----------------------------------------------------------------------------
# Directories relevant for this project 
include_directories(${PROJECT_SOURCE_DIR}/include ${ROOT_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/include)

#----------------------------------------------------------------------------
# sources and headers for the project 
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp) 
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh) 

#----------------------------------------------------------------------------
# # generate ROOT dictionary (for items that derive from TObject)  
# ROOT_GENERATE_DICTIONARY(
# G__UtilDF
# UtilDFGraph.hh
# UtilDFImport.hh 
# OPTIONS -I${PROJECT_SOURCE_DIR}/include 
# MODULE UtilDF
# LINKDEF UtilDF_LinkDef.hh
# )
# generate the shared library from sources 
add_library (${LIB_NAME} SHARED ${SOURCES})
target_link_libraries (${LIB_NAME} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Install items 
install (TARGETS ${LIB_NAME} DESTINATION ${INSTALL_DIR})
install (FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/examples DESTINATION ${CMAKE_INSTALL_PREFIX})

