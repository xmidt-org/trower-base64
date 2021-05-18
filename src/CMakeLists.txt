# SPDX-FileCopyrightText: 2016-2021 Comcast Cable Communications Management, LLC
# SPDX-License-Identifier: Apache-2.0

add_library(trower-base64 SHARED b64.c b64-decode.c)

configure_file(ver.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/ver.h)

install (FILES
         ${CMAKE_CURRENT_BINARY_DIR}/ver.h
         ${CMAKE_CURRENT_SOURCE_DIR}/base64.h
         DESTINATION include/trower-base64)

set_target_properties(trower-base64 PROPERTIES
        OUTPUT_NAME trower-base64)

install(TARGETS trower-base64
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
       )

