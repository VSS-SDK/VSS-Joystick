PROJECT(vss-joystick)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11")

ADD_SUBDIRECTORY(VSS-Interface)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
find_package(PkgConfig)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

include_directories(${Boost_INCLUDE_DIR})

file(GLOB_RECURSE SRCS_CPP src/*.cpp)
file(GLOB_RECURSE SRCS_CC src/*.cc)
file(GLOB_RECURSE INTERFACE_CPP VSS-Interface/*.cpp)

ADD_EXECUTABLE(vss-joystick ${SRCS_CPP} ${SRCS_CC} ${INTERFACE_CPP})

target_include_directories(vss-joystick PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(vss-joystick PUBLIC ${ZeroMQ_LIBRARY})

TARGET_LINK_LIBRARIES(vss-joystick VSS-Interface ${PROTOBUF_LIBRARY})
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
