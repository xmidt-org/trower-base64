/* SPDX-FileCopyrightText: 2010-2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */
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
 *  @note: The size returned does not account for any trailing '\0'.
 *
 *  @param decoded_size size of the decoded date
 *
 *  @return size of the buffer required to hold the encoded data
 */
size_t b64_get_encoded_buffer_size( const size_t decoded_size );

/**
 *
 *  Get the size of the buffer required to hold the decoded data when base64
 *  url encoded.
 *
 *  @note: The size returned does not account for any trailing '\0'.
 *
 *  @param decoded_size size of the decoded date
 *
 *  @return size of the buffer required to hold the encoded data
 */
size_t b64url_get_encoded_buffer_size( const size_t decoded_size );


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
 * Get the size of the buffer needed to hold the output decoded from
 * base64url encoded data.
 *
 * @note: The size MAY be larger the the resulting decoded output.
 *
 * @param encoded_size size of the base64url encoded data
 *
 * @return size of the raw data
 */
size_t b64url_get_decoded_buffer_size( const size_t encoded_size );

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
 * @return total number of bytes in the decoded array, or 0 if there was a
 *         decoding error
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
 * @return total number of bytes in the decoded array, or 0 if there was a
 *         decoding error
 */
size_t b64url_decode( const uint8_t *input, const size_t input_size, uint8_t *output );


#ifdef __cplusplus
}
#endif

#endif /* __BASE64_LIB__ */
