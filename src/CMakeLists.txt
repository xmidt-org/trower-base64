#   Copyright 2016 Comcast Cable Communications Management, LLC
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

set(CMAKE_MACOSX_RPATH 1)

add_library(trower-base64 SHARED b64.c b64-decode.c)

install (FILES
         ${CMAKE_CURRENT_SOURCE_DIR}/base64.h
         DESTINATION include/trower-base64)

set_target_properties(trower-base64 PROPERTIES
        OUTPUT_NAME trower-base64
        SOVERSION "1.0.0")

install(TARGETS trower-base64
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
       )

