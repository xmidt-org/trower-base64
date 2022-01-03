/* SPDX-FileCopyrightText: 2021-2022 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                            File Scoped Variables                           */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
static void encode(const char *map, const uint8_t *in, size_t len, uint8_t *out);
static size_t decode(const int8_t *map, const uint8_t *in, size_t len, uint8_t *out);
static uint8_t *decode_w_alloc(size_t(size_fn)(const size_t),
                               size_t(decode_fn)(const uint8_t *, const size_t, uint8_t *),
                               const uint8_t *enc, size_t len, size_t *out_len);
static char *encode_w_alloc(size_t(size_fn)(const size_t),
                            void(encode_fn)(const uint8_t *, const size_t, uint8_t *),
                            const uint8_t *enc, size_t len, size_t *out_len);

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
size_t b64_get_encoded_buffer_size(const size_t decoded_size)
{
    return ((decoded_size + 2) / 3) * 4;
}


size_t b64_get_decoded_buffer_size(const size_t encoded_size)
{
    size_t rv = (encoded_size / 4) * 3;

    /* Check that the input is valid. */
    if (b64_get_encoded_buffer_size(rv) != encoded_size) {
        rv = 0;
    }

    return rv;
}


size_t b64url_get_encoded_buffer_size(const size_t decoded_size)
{
    size_t remainder = decoded_size % 3;

    if (remainder) {
        remainder++;
    }

    return (decoded_size / 3) * 4 + remainder;
}


size_t b64url_get_decoded_buffer_size(const size_t encoded_size)
{
    size_t remainder = 0x03 & encoded_size;
    size_t rv        = 0;

    if (remainder) {
        remainder--;
    }

    rv = (encoded_size / 4) * 3 + remainder;

    /* Check that the input is valid. */
    if (b64url_get_encoded_buffer_size(rv) != encoded_size) {
        rv = 0;
    }

    return rv;
}


void b64_encode(const uint8_t *raw, const size_t len, uint8_t *out)
{
    static const char map[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

    encode(map, raw, len, out);
}


void b64url_encode(const uint8_t *raw, const size_t len, uint8_t *out)
{
    static const char map[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_\0";

    encode(map, raw, len, out);
}


size_t b64_decode(const uint8_t *enc, const size_t len, uint8_t *out)
{
    // -1 = invalid
    // -2 = padding
    // clang-format off
    static const int8_t map[256] = {
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0x00-0x0f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0x10-0x1f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,62, -1,-1,-1,63,    /* 0x20-0x2f */
        52,53,54,55, 56,57,58,59, 60,61,-1,-1, -1,-2,-1,-1,    /* 0x30-0x3f */
        -1, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,    /* 0x40-0x4f */
        15,16,17,18, 19,20,21,22, 23,24,25,-1, -1,-1,-1,-1,    /* 0x50-0x5f */
        -1,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,    /* 0x60-0x6f */
        41,42,43,44, 45,46,47,48, 49,50,51,-1, -1,-1,-1,-1,    /* 0x70-0x7f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0x80-0x8f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0x90-0x9f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xa0-0xaf */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xb0-0xbf */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xc0-0xcf */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xd0-0xdf */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xe0-0xef */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xf0-0xff */
    };
    // clang-format off
    size_t max = b64_get_decoded_buffer_size( len );

    if( (0 == max) || !enc || !out ) {
        return 0;
    }

    return decode( map, enc, len, out );
}


size_t b64url_decode( const uint8_t *enc, const size_t len, uint8_t *out )
{
    // -1 = invalid
    // -2 = padding
    // clang-format off
    static const int8_t map[256] = {
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0x00-0x0f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0x10-0x1f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,62,-1,-1,    /* 0x20-0x2f */
        52,53,54,55, 56,57,58,59, 60,61,-1,-1, -1,-2,-1,-1,    /* 0x30-0x3f */
        -1, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,    /* 0x40-0x4f */
        15,16,17,18, 19,20,21,22, 23,24,25,-1, -1,-1,-1,63,    /* 0x50-0x5f */
        -1,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,    /* 0x60-0x6f */
        41,42,43,44, 45,46,47,48, 49,50,51,-1, -1,-1,-1,-1,    /* 0x70-0x7f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0x80-0x8f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0x90-0x9f */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xa0-0xaf */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xb0-0xbf */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xc0-0xcf */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xd0-0xdf */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xe0-0xef */
        -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,    /* 0xf0-0xff */
    };
    // clang-format on
    size_t max = b64url_get_decoded_buffer_size(len);

    if ((0 == max) || !enc || !out) {
        return 0;
    }

    return decode(map, enc, len, out);
}


uint8_t *b64_decode_with_alloc(const uint8_t *enc, size_t len, size_t *out_len)
{
    return decode_w_alloc(b64_get_decoded_buffer_size, b64_decode, enc, len, out_len);
}


char *b64_encode_with_alloc(const uint8_t *raw, size_t len, size_t *out_len)
{
    return encode_w_alloc(b64_get_encoded_buffer_size, b64_encode, raw, len, out_len);
}


uint8_t *b64url_decode_with_alloc(const uint8_t *enc, size_t len, size_t *out_len)
{
    return decode_w_alloc(b64url_get_decoded_buffer_size, b64url_decode, enc, len, out_len);
}


char *b64url_encode_with_alloc(const uint8_t *raw, size_t len, size_t *out_len)
{
    return encode_w_alloc(b64url_get_encoded_buffer_size, b64url_encode, raw, len, out_len);
}


/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
static void encode(const char *map, const uint8_t *in, size_t len, uint8_t *out)
{
    uint32_t bits = 0;
    int bit_count = 0;
    size_t j      = 0;

    for (size_t i = 0; i < len; i++) {
        bits = (bits << 8) | in[i];
        bit_count += 8;

        while (6 <= bit_count) {
            bit_count -= 6;
            out[j++] = (uint8_t) map[0x3f & (bits >> bit_count)];
        }
    }

    /* Handle the extra bits. */
    if (bit_count) {
        bits <<= 8;
        bit_count += 8;
        bit_count -= 6;
        out[j++] = (uint8_t) map[0x3f & (bits >> bit_count)];
    }

    /* Pad */
    while (('\0' != map[64]) && (0x03 & j)) {
        out[j++] = (uint8_t) map[64];
    }
}


static size_t decode(const int8_t *map, const uint8_t *in, size_t len, uint8_t *out)
{

    uint32_t bits  = 0;
    int bit_count  = 0;
    size_t padding = 0;
    size_t j       = 0;

    if ('=' == in[len - 1]) {
        padding++;
        if ('=' == in[len - 2]) {
            padding++;
        }

        /* If there is padding then it should only pad to ensure the string
         * has a multiple of 4.  Anything else is an error. */
        if (0 != (0x03 & len)) {
            return 0;
        }
    }

    len -= padding;

    for (size_t i = 0; i < len; i++) {
        int8_t val;

        val = map[in[i]];
        if (val < 0) {
            return 0;
        }
        bits = (bits << 6) | val;
        bit_count += 6;

        if (8 <= bit_count) {
            out[j++] = (uint8_t) (0x0ff & (bits >> (bit_count - 8)));
            bit_count -= 8;
        }
    }

    return j;
}

static uint8_t *decode_w_alloc(size_t(size_fn)(const size_t),
                               size_t(decode_fn)(const uint8_t *, const size_t, uint8_t *),
                               const uint8_t *enc, size_t len, size_t *out_len)
{
    size_t raw_len = size_fn(len);
    uint8_t *buf   = NULL;

    if (out_len) {
        *out_len = 0;
    }
    if (!raw_len || !enc || !out_len) {
        return NULL;
    }

    buf = malloc(raw_len * sizeof(uint8_t));
    if (buf) {
        *out_len = decode_fn(enc, len, buf);
        if (0 == *out_len) {
            free(buf);
            buf = NULL;
        }
    }

    return buf;
}

static char *encode_w_alloc(size_t(size_fn)(const size_t),
                            void(encode_fn)(const uint8_t *, const size_t, uint8_t *),
                            const uint8_t *raw, size_t len, size_t *out_len)
{
    size_t enc_len = size_fn(len);
    char *buf      = NULL;

    if (out_len) {
        *out_len = 0;
    }

    if (!enc_len || !raw) {
        return NULL;
    }

    buf = malloc((enc_len + 1) * sizeof(char));
    if (buf) {
        encode_fn(raw, len, (uint8_t *) buf);
        buf[enc_len] = '\0';
        if (out_len) {
            *out_len = enc_len;
        }
    }

    return buf;
}
