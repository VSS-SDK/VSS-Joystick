CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT(vss-joystick)
set(CMAKE_BUILD_TYPE Release)

include_directories(src src/joystick)

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


ADD_LIBRARY(vss-joystick-core ${SRCS_CPP} ${SRCS_CC} ${H} ${HH})
TARGET_LINK_LIBRARIES(vss-joystick-core ${VSS_CORE} ${PROTOBUF_LIBRARY})
TARGET_LINK_LIBRARIES(vss-joystick-core LINK_PUBLIC ${Boost_LIBRARIES})
target_include_directories(vss-joystick-core PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(vss-joystick-core PUBLIC ${ZeroMQ_LIBRARY})

ADD_EXECUTABLE(vss-joystick src/Main.cpp)
TARGET_LINK_LIBRARIES(vss-joystick vss-joystick-core)

IF(RELEASE)
    SET(CMAKE_CXX_FLAGS "-Wall -Werror -o2 -std=c++11 -pthread")

    INCLUDE(CPack)

    INSTALL(TARGETS vss-joystick DESTINATION bin)

    SET(CPACK_GENERATOR "DEB")
    SET(CPACK_DEBIAN_PACKAGE_NAME "vss-joystick")
    SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A simple way to send commands for robots on VSS-Simulator or real robots. You can use ANY Joystick via USB.")
    SET(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://sirlab.github.io/VSS-SDK/")
    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
    SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Johnathan Fercher")
    SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
ELSE()
    INCLUDE_DIRECTORIES(third-party)

    enable_testing()

    add_subdirectory(third-party/googletest)

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

    file(GLOB_RECURSE TEST test/*.cpp)

    ADD_EXECUTABLE(tests ${TEST})

    target_link_libraries(tests
            pthread
            gtest
            gtest_main
            vss-joystick-core)

    SET(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11 -pthread")
ENDIF()