PROJECT(vss-joystick)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -pthread")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
find_package(PkgConfig)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)
INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

file(GLOB_RECURSE SRCS_CPP src/*.cpp)
file(GLOB_RECURSE SRCS_CC src/*.cc)
file(GLOB_RECURSE H src/*.h)
file(GLOB_RECURSE HH src/*.hh)

set (VSS_CORE libvss-core.so)
link_directories(usr/lib)
include_directories(usr/local/include)

ADD_EXECUTABLE(vss-joystick ${SRCS_CPP} ${SRCS_CC} ${H} ${HH})

target_include_directories(vss-joystick PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(vss-joystick PUBLIC ${ZeroMQ_LIBRARY})

TARGET_LINK_LIBRARIES(vss-joystick ${VSS_CORE} ${PROTOBUF_LIBRARY})
TARGET_LINK_LIBRARIES(vss-joystick LINK_PUBLIC ${Boost_LIBRARIES})

INSTALL(TARGETS vss-joystick DESTINATION bin)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "vss-joystick")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A simple way to send commands for robots on VSS-Simulator or real robots. You can use ANY Joystick via USB.")
SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://sirlab.github.io/VSS-SDK/")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johnathan Fercher")
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

INCLUDE(CPack)
