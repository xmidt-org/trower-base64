/* SPDX-FileCopyrightText: 2010-2022 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */
#ifndef __BASE64_LIB__
#define __BASE64_LIB__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/*----------------------------------------------------------------------------*/
/*                             Standard Base64                                */
/*----------------------------------------------------------------------------*/

/**
 *  Get the size of the buffer required to hold the decoded data when encoded.
 *
 *  @note: The size returned does not account for any trailing '\0'.
 *
 *  @param decoded_size size of the decoded date
 *
 *  @return size of the buffer required to hold the encoded data
 */
size_t b64_get_encoded_buffer_size(const size_t decoded_size);


/**
 * Get the size of the buffer needed to hold the decoded output.
 *
 * @note: The size MAY be larger the the resulting decoded output.
 *
 * @param encoded_size size of the encoded data
 *
 * @return size of the raw data
 */
size_t b64_get_decoded_buffer_size(const size_t encoded_size);


/**
 *  Encodes the input into base64.  The base 64 produced string will be placed
 *  into the output param.  Consumers of this function are responsible for
 *  making sure the output buffer is able to hold all of the data once it is
 *  encoded.
 *
 *  @note: The output buffer must be large enough to handle the encoded payload.
 *
 *  @param raw  pointer to the raw data
 *  @param len  size of the raw data in bytes
 *  @param out  pointer to where the encoded data should be placed
 */
void b64_encode(const uint8_t *raw, const size_t len, uint8_t *out);


/**
 * Decodes the base64 encoded buffer.  The produced raw buffer will be placed
 * into the output array.  Consumers of this function are responsible for making
 * sure the output buffer is large enough to hold all of the decoded data.
 *
 * @note: The output buffer must be large enough to handle the decoded payload.
 *
 * @param enc  pointer to the encoded data
 * @param len  size of the raw data
 * @param out  pointer to where the decoded data should be placed
 *
 * @return total number of bytes in the decoded array, or 0 if there was a
 *         decoding error
 */
size_t b64_decode(const uint8_t *enc, const size_t len, uint8_t *out);


/**
 * Decodes the base64 buffer into a new buffer with the size specified in
 * out_len.
 *
 * @note: The returned buffer must have free() called to prevent a memory
 *        leak.
 *
 * @param enc      pointer to the encoded data
 * @param len      size of the raw data
 * @param out_len  pointer to where the resulting buffer length is placed
 *
 * @return the buffer containing the raw bytes or NULL on error
 */
uint8_t *b64_decode_with_alloc(const uint8_t *enc, size_t len, size_t *out_len);


/**
 * Encodes the raw bytes using standard base64 into a new buffer with the size
 * specified in out_len.
 *
 * @note: The returned buffer must have free() called to prevent a memory
 *        leak.
 * @note: The returned buffer is '\0' terminated.
 * @note: The out_len value is equivalent to strlen() of the returned buffer.
 *
 * @param raw      pointer to the encoded data
 * @param len      size of the raw data
 * @param out_len  pointer to where the resulting buffer length is placed
 *
 * @return the buffer containing the raw bytes or NULL on error
 */
char *b64_encode_with_alloc(const uint8_t *raw, size_t len, size_t *out_len);


/*----------------------------------------------------------------------------*/
/*                                 URL Base64                                 */
/*----------------------------------------------------------------------------*/


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
size_t b64url_get_encoded_buffer_size(const size_t decoded_size);


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
size_t b64url_get_decoded_buffer_size(const size_t encoded_size);


/**
 *  Encodes the input into base64url.  The base 64 produced string will be placed
 *  into the output param.  Consumers of this function are responsible for
 *  making sure the output buffer is able to hold all of the data once it is
 *  encoded.
 *
 *  @note: The output buffer must be large enough to handle the encoded payload.
 *
 *  @param raw pointer to the raw data
 *  @param len size of the raw data in bytes
 *  @param output pointer to where the encoded data should be placed
 */
void b64url_encode(const uint8_t *raw, const size_t len, uint8_t *output);


/**
 * Decodes the base64url encoded stream.  The produced raw buffer will be
 * placed into the output array.  Consumers of this function are responsible for
 * making sure the output buffer is large enough to hold all of the decoded data.
 *
 * @note: The output buffer must be large enough to handle the decoded payload.
 *
 * @param enc pointer to the encoded data
 * @param len size of the raw data
 * @param output pointer to where the decoded data should be placed
 *
 * @return total number of bytes in the decoded array, or 0 if there was a
 *         decoding error
 */
size_t b64url_decode(const uint8_t *enc, const size_t len, uint8_t *output);


/**
 * Decodes the base64url buffer into a new buffer with the size specified in
 * out_len.
 *
 * @note: The returned buffer must have free() called to prevent a memory
 *        leak.
 *
 * @param enc      pointer to the encoded data
 * @param len      size of the raw data
 * @param out_len  pointer to where the resulting buffer length is placed
 *
 * @return the buffer containing the raw bytes or NULL on error
 */
uint8_t *b64url_decode_with_alloc(const uint8_t *enc, size_t len, size_t *out_len);


/**
 * Encodes the raw bytes using base64url into a new buffer with the size
 * specified in out_len.
 *
 * @note: The returned buffer must have free() called to prevent a memory
 *        leak.
 * @note: The returned buffer is '\0' terminated.
 * @note: The out_len value is equivalent to strlen() of the returned buffer.
 *
 * @param raw      pointer to the encoded data
 * @param len      size of the raw data
 * @param out_len  pointer to where the resulting buffer length is placed
 *
 * @return the buffer containing the raw bytes or NULL on error
 */
char *b64url_encode_with_alloc(const uint8_t *raw, size_t len, size_t *out_len);


#ifdef __cplusplus
}
#endif

#endif /* __BASE64_LIB__ */
