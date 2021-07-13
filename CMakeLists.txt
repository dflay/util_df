#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(utildf LANGUAGES CXX)

#----------------------------------------------------------------------------
# Implement user-defined items here
# The generated shared library will be named lib$(PACKAGE).so/dylib 
set(PACKAGE UtilDF)

# sources 
set(src 
  ABA.cpp
  Blinder.cpp
  CSVManager.cpp
  FourierTransform.cpp
  MovingAverage.cpp
  TemperatureSensor.cpp
  UtilDFCrossSection.cpp
  UtilDFEnergyLoss.cpp
  UtilDFFunc.cpp
  UtilDFGraph.cpp
  UtilDFHistogram.cpp
  UtilDFImport.cpp
  UtilDFMath.cpp
  )

# headers
string(REPLACE .cpp .hh headers "${src}")

# additional headers
set(allheaders ${headers} UtilDFConstants.hh UtilDFUnits.hh Material.hh rootData.hh json.hh)

# Sources live in dedicated src directory
list(TRANSFORM src PREPEND "${CMAKE_CURRENT_LIST_DIR}/src/")

# Headers live in dedicated include directory
list(TRANSFORM allheaders PREPEND "${CMAKE_CURRENT_LIST_DIR}/include/")

# # checks 
# MESSAGE(${src})
# MESSAGE(${allheaders}) 

#----------------------------------------------------------------------------
# Find ROOT 
set(ROOT_VER 6.22) 
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT ${ROOT_VER} REQUIRED)
# Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

#----------------------------------------------------------------------------
# Library
# add_library(${PACKAGE} SHARED ${src} ${allheaders} ${PACKAGE}Dict.cxx)
add_library(${PACKAGE} SHARED ${src} ${allheaders})

target_compile_options(${PACKAGE} PRIVATE ${${PROJECT_NAME_UC}_DIAG_FLAGS_LIST})

target_include_directories(${PACKAGE}
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  )
target_link_libraries(${PACKAGE} PUBLIC ${ROOT_LIBRARIES})

include(GNUInstallDirs)

install(TARGETS ${PACKAGE}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
install(FILES ${allheaders} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#----------------------------------------------------------------------------
# ROOT dictionary
root_generate_dictionary(
 ${PACKAGE}Dict
 ${allheaders} 
 LINKDEF ${CMAKE_CURRENT_LIST_DIR}/include/${PACKAGE}_LinkDef.hh  
 MODULE UtilDF
 )
