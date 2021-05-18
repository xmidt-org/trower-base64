# SPDX-FileCopyrightText: 2010-2021 Comcast Cable Communications Management, LLC
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

project(trower-base64 VERSION 1.1.4)

include(BitwiseVersion)
include(CTest)
include(LicenseLinterTarget)
include(Coverage)

add_definitions(-std=c99)
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Werror -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")



add_subdirectory(src)
if (BUILD_TESTING)
    include(FindCunit)
    add_subdirectory(tests)
endif (BUILD_TESTING)
