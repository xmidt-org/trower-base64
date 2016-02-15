/**
 * Copyright 2010-2016 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __BASE64_LIB__
#define __BASE64_LIB__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>


/**
 *  Get the size of the buffer required to hold the decoded data when encoded.
 *
 *  @param decoded_size size of the decoded date
 *
 *  @return size of the buffer required to hold the encoded data
 */
size_t b64_get_encoded_buffer_size( const size_t decoded_size );


/**
 *  Encodes the input into base 64.  The base 64 produced string will be placed
 *  into the output param.  Consumers of this function are responsible for
 *  making sure the output buffer is able to hold all of the data once it is
 *  encoded.
 *
 *  @note: The output buffer must be large enough to handle the encoded payload.
 *
 *  @param input pointer to the raw data
 *  @param input_size size of the raw data in bytes
 *  @param output pointer to where the encoded data should be placed
 */
void b64_encode( const uint8_t *input, const size_t input_size, uint8_t *output );


/**
 * Get the size of the buffer needed to hold the decoded output.
 *
 * @note: The size MAY be larger the the resulting decoded output.
 *
 * @param encoded_size size of the encoded data
 *
 * @return size of the raw data
 */
size_t b64_get_decoded_buffer_size( const size_t encoded_size );


/**
 * Decodes the base 64 stream.  The produced raw buffer will be placed into the
 * output array.  Consumers of this function are responsible for making sure the
 * output buffer is large enough to hold all of the decoded data.
 *
 * @note: The output buffer must be large enough to handle the decoded payload.
 *
 * @param input pointer to the encoded data
 * @param input_size size of the raw data
 * @param output pointer to where the decoded data should be placed
 *
 * @return total number of bytes in the decoded array
 */
size_t b64_decode( const uint8_t *input, const size_t input_size, uint8_t *output );


/**
 * Decodes the base 64 url encoded stream.  The produced raw buffer will be
 * placed into the output array.  Consumers of this function are responsible for
 * making sure the output buffer is large enough to hold all of the decoded data.
 *
 * @note: The output buffer must be large enough to handle the decoded payload.
 * @note: Base64url uses '-' and '_' instead of '+' and '\'.  It also contains
 *        no padding.
 *
 * @param input pointer to the encoded data
 * @param input_size size of the raw data
 * @param output pointer to where the decoded data should be placed
 *
 * @return total number of bytes in the decoded array
 */
size_t b64url_decode( const uint8_t *input, const size_t input_size, uint8_t *output );


#ifdef __cplusplus
}
#endif

#endif /* __BASE64_LIB__ */
