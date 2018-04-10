CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)

if(WIN32 AND NOT MINGW)
  if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "d")
  endif()
endif()

IF(NOT DEFINED CMAKE_BUILD_TYPE)
  # No effect for multi-configuration generators (e.g. for Visual Studio)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose: RelWithDebInfo Release Debug MinSizeRel None")
ENDIF()

PROJECT(oi.client.rgbd.libfreenect)
SET(CMAKE_CXX_STANDARD 11)

SET(MY_DIR ${PROJECT_SOURCE_DIR})

SET(freenect_ROOT_DIR "${MY_DIR}/../../dependencies/libfreenect" CACHE STRING "Root folder of libfreenect source.")

#SET(DEPENDS_DIR "${freenect2_ROOT_DIR}/depends" CACHE STRING "libfreenect2 Dependency directory")
SET(DEPENDS_DIR "${MY_DIR}/../../dependencies" CACHE STRING "OpenIMPRESS dependency directory")
SET(SHARED_OI_DIR "${MY_DIR}/../oi.client.rgbd.libfreenect2" CACHE STRING "OpenIMPRESS Shared")


FIND_PACKAGE(PkgConfig)
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ) # oi.client.rgbd.libfreenect Modules
LIST(APPEND CMAKE_MODULE_PATH "${SHARED_OI_DIR}/cmake_modules" ) # oi.client.rgbd.libfreenect2 Modules
#LIST(APPEND CMAKE_MODULE_PATH "${freenect_ROOT_DIR}/cmake_modules" ) # freenect2 Modules

FIND_PACKAGE(Freenect REQUIRED)
FIND_PACKAGE(ASIO REQUIRED)
FIND_PACKAGE(TurboJPEG REQUIRED)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE=YES" )

INCLUDE_DIRECTORIES(${FREENECT_INCLUDE_DIR})    
INCLUDE_DIRECTORIES(${ASIO_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/headers)      
INCLUDE_DIRECTORIES(${TurboJPEG_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${SHARED_OI_DIR}/headers)

SET(application_src ${PROJECT_SOURCE_DIR}/src/main.cpp)

LIST(APPEND application_LIBRARIES ${TurboJPEG_LIBRARIES})
LIST(APPEND application_LIBRARIES ${FREENECT_LIBRARIES})
LIST(APPEND application_headers
  ${PROJECT_SOURCE_DIR}/headers/config.h
  ${PROJECT_SOURCE_DIR}/headers/json.hpp
  ${PROJECT_SOURCE_DIR}/headers/stb_dxt.h
  ${SHARED_OI_DIR}/headers/UDPBase.hpp
  ${SHARED_OI_DIR}/headers/UDPConnector.hpp
  ${SHARED_OI_DIR}/headers/RGBDStreamer.hpp
  ${SHARED_OI_DIR}/headers/RecordState.hpp
  ${PROJECT_SOURCE_DIR}/headers/LibFreenectStreamer.hpp
)
LIST(APPEND application_DLLS)
LIST(APPEND application_src
  ${SHARED_OI_DIR}/src/UDPBase.cpp
  ${SHARED_OI_DIR}/src/UDPConnector.cpp
  ${SHARED_OI_DIR}/src/RGBDStreamer.cpp
  ${SHARED_OI_DIR}/src/RecordState.cpp
  ${PROJECT_SOURCE_DIR}/src/LibFreenectStreamer.cpp
#  ${PROJECT_SOURCE_DIR}/src/AVEncodeTest.cpp
)
LIST(APPEND application_LIBRARIES
)

SOURCE_GROUP("Header Files" FILES ${application_headers})

ADD_EXECUTABLE(oi.client.rgbd.libfreenect
  ${application_src}
  ${application_headers}
)

TARGET_LINK_LIBRARIES(oi.client.rgbd.libfreenect
  ${application_LIBRARIES}
)

