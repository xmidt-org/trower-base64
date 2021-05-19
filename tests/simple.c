/* SPDX-FileCopyrightText: 2016-2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../src/base64.h"

struct test_vector {
    size_t in_len;
    const char *in;
    size_t out_len;
    const char *out;
};

struct test_vector common_decoder_tests[] = {
        /* Simple NULL, string length tests */
        {   .in = NULL,
            .in_len = 0,
            .out = NULL,
            .out_len = 0,
        },
        {   .in = "asdf123",
            .in_len = 0,
            .out = NULL,
            .out_len = 0,
        },

        /* The length must be at least 2 */
        {   .in = "a",
            .in_len = 1,
            .out = NULL,
            .out_len = 0,
        },

        /* Every character must be valid */
        {   .in = "asdf1\xffjj",
            .in_len = 8,
            .out = NULL,
            .out_len = 0,
        },
        {   .in = "asdf1=jj",
            .in_len = 8,
            .out = NULL,
            .out_len = 0,
        },

        /* Protect against a bogus empty string */
        {   .in = "==",
            .in_len = 2,
            .out = NULL,
            .out_len = 0,
        },

        /* Invalid, safely fail. */
        {   .in = "b==",
            .in_len = 3,
            .out = NULL,
            .out_len = 0,
        },

        /* Invalid, padding. */
        {   .in = "ba=",
            .in_len = 3,
            .out = NULL,
            .out_len = 0,
        },
        {   .in = "bad==",
            .in_len = 5,
            .out = NULL,
            .out_len = 0,
        },
        {   .in = "bad4==",
            .in_len = 6,
            .out = NULL,
            .out_len = 0,
        },
        {   .in = "bad4=",
            .in_len = 5,
            .out = NULL,
            .out_len = 0,
        },

        /* Disallow other printable charcters. */
        {   .in = "as d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as!d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\"d",.in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as#d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as$d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as%d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as&d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as'd", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as(d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as)d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as*d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as.d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as:d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as;d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as<d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as>d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as?d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as@d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as[d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\\d",.in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as]d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as^d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as`d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as{d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as|d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as}d", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as~d", .in_len = 4, .out = NULL, .out_len = 0, },

        /* Disallow other non-printable charcters. */
        {   .in = "bs\x00p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x01p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x02p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x03p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x04p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x05p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x06p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x07p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x08p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x09p", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "bs\x0ap", .in_len = 4, .out = NULL, .out_len = 0, },

        /* A remainder of 1 is never valid */
        {   .in = "TWFub",
            .in_len = 5,
            .out = NULL,
            .out_len = 0,
        },

        /* Simple valid examples */
        {   .in = "TWFu",
            .in_len = 4,
            .out = "Man",
            .out_len = 3,
        },
        {   .in = "TWE=",
            .in_len = 4,
            .out = "Ma",
            .out_len = 2,
        },
        {   .in = "TQ==",
            .in_len = 4,
            .out = "M",
            .out_len = 1,
        },

        /* A longer sample text. */
        {   .in = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24s"
                  "IGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmlt"
                  "YWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBw"
                  "ZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBp"
                  "bmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRz"
                  "IHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=",
            .in_len = 360,
            .out = "Man is distinguished, not only by his reason, but by this "
                   "singular passion from other animals, which is a lust of "
                   "the mind, that by a perseverance of delight in the "
                   "continued and indefatigable generation of knowledge, "
                   "exceeds the short vehemence of any carnal pleasure.",
            .out_len = 269,
        },
    };


void test_encoded_stuff( const char *raw, size_t raw_size, const char *expected, size_t expected_size );
void test_decoded_stuff( size_t (*fn)(const uint8_t*, const size_t, uint8_t*),
                         const char *raw, size_t raw_size, const char *expected, size_t expected_size );

void test_encoded_size() {
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(0), 0);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(1), 4);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(2), 4);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(3), 4);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(4), 8);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(300), 400);
}

void test_b64url_encoded_size() {
    CU_ASSERT_EQUAL(b64url_get_encoded_buffer_size(0), 0);
}

void test_decoded_size() {
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(0), 0);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(1), 0);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(2), 0);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(3), 0);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(4), 3);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(8), 6);
}

void test_b64url_decoded_size() {
    struct test {
        size_t expect;
        size_t in;
    } tests[] = {
        {  0,  0 },   { 15, 20 },   { 29, 39 },   { 43, 58 },   {  0, 77 },
        {  1,  2 },   {  0, 21 },   { 30, 40 },   { 44, 59 },   { 58, 78 },
        {  2,  3 },   { 16, 22 },   {  0, 41 },   { 45, 60 },   { 59, 79 },
        {  3,  4 },   { 17, 23 },   { 31, 42 },   {  0, 61 },   { 60, 80 },
        {  4,  6 },   { 18, 24 },   { 32, 43 },   { 46, 62 },   {  0, 81 },
        {  0,  5 },   {  0, 25 },   { 33, 44 },   { 47, 63 },   { 61, 82 },
        {  5,  7 },   { 19, 26 },   {  0, 45 },   { 48, 64 },   { 62, 83 },
        {  6,  8 },   { 20, 27 },   { 34, 46 },   {  0, 65 },   { 63, 84 },
        {  0,  9 },   { 21, 28 },   { 35, 47 },   { 49, 66 },   {  0, 85 },
        {  7, 10 },   {  0, 29 },   { 36, 48 },   { 50, 67 },   { 64, 86 },
        {  8, 11 },   { 22, 30 },   {  0, 49 },   { 51, 68 },   { 65, 87 },
        {  9, 12 },   { 23, 31 },   { 37, 50 },   {  0, 69 },   { 66, 88 },
        {  0, 13 },   { 24, 32 },   { 38, 51 },   { 52, 70 },   {  0, 89 },
        { 10, 14 },   {  0, 33 },   { 39, 52 },   { 53, 71 },   { 67, 90 },
        { 11, 15 },   { 25, 34 },   {  0, 53 },   { 54, 72 },
        { 12, 16 },   { 26, 35 },   { 40, 54 },   {  0, 73 },
        {  0, 17 },   { 27, 36 },   { 41, 55 },   { 55, 74 },
        { 13, 18 },   {  0, 37 },   { 42, 56 },   { 56, 75 },
        { 14, 19 },   { 28, 38 },   {  0, 57 },   { 57, 76 },
    };

    for( size_t i = 0; i < sizeof(tests)/sizeof(struct test); i++ ) {
        size_t rv = b64url_get_decoded_buffer_size( tests[i].in );

        if( rv != tests[i].expect ) {
            printf( "Expected: %zd, got: %zd\n", tests[i].expect, rv );
        }
        CU_ASSERT( rv == tests[i].expect );
    }
}

void test_encode() {
    test_encoded_stuff( "leasure.", 8, "bGVhc3VyZS4=", 12 );
    test_encoded_stuff( "easure.",  7, "ZWFzdXJlLg==", 12 );
    test_encoded_stuff( "asure.",   6, "YXN1cmUu",      8 );
    test_encoded_stuff( "sure.",    5, "c3VyZS4=",      8 );
    test_encoded_stuff( "ure.",     4, "dXJlLg==",      8 );
    test_encoded_stuff( "re.",      3, "cmUu",          4 );
    test_encoded_stuff( "e.",       2, "ZS4=",          4 );
    test_encoded_stuff( ".",        1, "Lg==",          4 );
    test_encoded_stuff( "",         0, "",              0 );
}

uint8_t* dup( const char *raw, size_t size )
{
    uint8_t *tmp;
    tmp = malloc( sizeof(char) * size );
    memcpy( tmp, raw, size );
    return tmp;
}

void test_encoded_stuff( const char *raw, size_t raw_size, const char *expected, size_t expected_size )
{
    size_t i;

    size_t workspace_size = b64_get_encoded_buffer_size(raw_size);
    uint8_t *workspace = calloc(1, workspace_size);
    uint8_t *tmp = dup( raw, raw_size );

    // Copy the data into a malloc'ed buffer so valgrind can help us find problems
    // Use it, then free it.
    b64_encode(tmp, raw_size, workspace);
    free(tmp);

    CU_ASSERT_EQUAL( expected_size, workspace_size );
    for( i = 0; i < expected_size; i++ ) {
        CU_ASSERT_EQUAL(workspace[i], (uint8_t) expected[i]);
        if( workspace[i] != (uint8_t) expected[i] ) {
            printf("Encoding Error: Expected[%zd:%c] '%*s' ::Actual[%zd:%c] '%*s'\n",
                    i, expected[i], (int) expected_size, expected,
                    i, workspace[i], (int) workspace_size, workspace);
        }
    }
    free(workspace);
}

void test_decode() {
    struct test_vector *t = common_decoder_tests;
    struct test_vector local[] = {
        /* len, input         len, expected */
        {  12, "bGVhc3VyZS4=", 8, "leasure."     },
        {  12, "ZWFzdXJlLg==", 7, "easure."      },
        {  8,  "YXN1cmUu",     6, "asure."       },
        {  8,  "c3VyZS4=",     5, "sure."        },
        {  4,  "+/+/",         3, "\xfb\xff\xbf" },
        {  1,  "Y",            0, NULL           },
        {  2,  "==",           0, NULL           },
        {  3,  "b==",          0, NULL           },
        {  5,  "bad4=",        0, NULL           },
        {  6,  "bad4==",       0, NULL           },
        {  5,  "bad==",        0, NULL           },
        {  3,  "ba=",          0, NULL           },
        {  8,  "YXN=cmUu",     0, NULL           },
        {  8,  "YXN\xffmcUu",  0, NULL           },

        /* Use every character to ensure they all map properly */
        {   .in = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  "abcdefghijklmnopqrstuvwxyz"
                  "0123456789+/",
            .in_len = 64,
            .out = "\x00\x10\x83\x10\x51\x87\x20\x92\x8b\x30"
                   "\xd3\x8f\x41\x14\x93\x51\x55\x97\x61\x96"
                   "\x9b\x71\xd7\x9f\x82\x18\xa3\x92\x59\xa7"
                   "\xa2\x9a\xab\xb2\xdb\xaf\xc3\x1c\xb3\xd3"
                   "\x5d\xb7\xe3\x9e\xbb\xf3\xdf\xbf",
            .out_len = 48,
        },
    };
    uint8_t fake_buf;

    for( size_t i = 0; i < sizeof(common_decoder_tests)/sizeof(struct test_vector); i++ ) {
        test_decoded_stuff( b64_decode, t[i].in, t[i].in_len, t[i].out, t[i].out_len );
    }

    t = local;
    for( size_t i = 0; i < sizeof(local)/sizeof(struct test_vector); i++ ) {
        test_decoded_stuff( b64_decode, t[i].in, t[i].in_len, t[i].out, t[i].out_len );
    }

    CU_ASSERT( 0 == b64_decode(NULL, 8, &fake_buf) );
    CU_ASSERT( 0 == b64_decode(&fake_buf, 0, &fake_buf) );
    CU_ASSERT( 0 == b64_decode(&fake_buf, 8, NULL) );
}

void test_url_decode() {
    struct test_vector *t = common_decoder_tests;
    struct test_vector local[] = {
        /* len, input       len, expected */
        {  3, "TWE",          2, "Ma"           },
        {  2, "TQ",           1, "M"            },
        { 11, "bGVhc3VyZS4",  8, "leasure."     },
        { 10, "ZWFzdXJlLg",   7, "easure."      },
        {  8, "YXN1cmUu",     6, "asure."       },
        {  7, "c3VyZS4",      5, "sure."        },
        {  4, "-_-_",         3, "\xfb\xff\xbf" },
        {  1, "Y",            0, NULL           },
        {  2, "==",           0, NULL           },
        {  3, "b==",          0, NULL           },
        { 12, "ZWFzdXJlLg==", 7, "easure."      },
        {  5, "bad4=",        0, NULL           },
        {  6, "bad4==",       0, NULL           },
        {  5, "bad==",        0, NULL           },
        {  3, "ba=",          0, NULL           },
        {  8, "YXN=cmUu",     0, NULL           },
        {  8, "YXN\xffmcUu",  0, NULL           },

        /* Use every character to ensure they all map properly */
        {   .in = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  "abcdefghijklmnopqrstuvwxyz"
                  "0123456789-_",
            .in_len = 64,
            .out = "\x00\x10\x83\x10\x51\x87\x20\x92\x8b\x30"
                   "\xd3\x8f\x41\x14\x93\x51\x55\x97\x61\x96"
                   "\x9b\x71\xd7\x9f\x82\x18\xa3\x92\x59\xa7"
                   "\xa2\x9a\xab\xb2\xdb\xaf\xc3\x1c\xb3\xd3"
                   "\x5d\xb7\xe3\x9e\xbb\xf3\xdf\xbf",
            .out_len = 48,
        },
    };
    uint8_t fake_buf;

    for( size_t i = 0; i < sizeof(common_decoder_tests)/sizeof(struct test_vector); i++ ) {
        test_decoded_stuff( b64url_decode, t[i].in, t[i].in_len, t[i].out, t[i].out_len );
    }

    t = local;
    for( size_t i = 0; i < sizeof(local)/sizeof(struct test_vector); i++ ) {
        test_decoded_stuff( b64url_decode, t[i].in, t[i].in_len, t[i].out, t[i].out_len );
    }

    CU_ASSERT( 0 == b64url_decode(NULL, 8, &fake_buf) );
    CU_ASSERT( 0 == b64url_decode(&fake_buf, 0, &fake_buf) );
    CU_ASSERT( 0 == b64url_decode(&fake_buf, 8, NULL) );
}

void test_decoded_stuff( size_t (*fn)(const uint8_t*, const size_t, uint8_t*),
                         const char *raw, size_t raw_size, const char *expected, size_t expected_size )
{
    size_t i;

    size_t workspace_size = (b64_decode == fn) ? b64_get_decoded_buffer_size(raw_size) :
                                                 b64url_get_decoded_buffer_size(raw_size);
    uint8_t *workspace = calloc(1, workspace_size);
    uint8_t *tmp = dup( raw, raw_size );
    size_t num_chars;

    // Copy the data into a malloc'ed buffer so valgrind can help us find problems
    // Use it, then free it.
    num_chars = (fn)(tmp, raw_size, workspace);
    free(tmp);

    CU_ASSERT_EQUAL( expected_size, num_chars );
    if( expected_size != num_chars ) {
        printf("Size fail: raw='%.*s' expected='%.*s' :: %zd %zd\n",
               (int) raw_size, raw, (int) expected_size, expected,
               expected_size, num_chars);
    }

    for( i = 0; i < expected_size; i++ ) {
        CU_ASSERT_EQUAL(workspace[i], (uint8_t) expected[i]);
        if( workspace[i] != (uint8_t) expected[i] ) {
            printf("Decoding Error: Expected[%zd:%c] '%*s' ::Actual[%zd:%c] '%*s'\n",
                    i, expected[i], (int)expected_size, expected,
                    i, workspace[i], (int)num_chars, workspace);
        }
    }
    free(workspace);
}

void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "Base64 encoding tests", NULL, NULL );
    CU_add_test( *suite, "Test the Encoded Size     ", test_encoded_size );
    CU_add_test( *suite, "Test the Decoded Size     ", test_decoded_size );
    CU_add_test( *suite, "Test the url Decoded Size ", test_b64url_decoded_size );
    CU_add_test( *suite, "Test Encoding             ", test_encode );
    CU_add_test( *suite, "Test Decoding             ", test_decode );
    CU_add_test( *suite, "Test URL Decoding         ", test_url_decode );
}

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main( void )
{
    unsigned rv = 1;
    CU_pSuite suite = NULL;

    if( CUE_SUCCESS == CU_initialize_registry() ) {
        add_suites( &suite );

        if( NULL != suite ) {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();
    }

    if( 0 != rv ) {
        return 1;
    }
    return 0;
}
