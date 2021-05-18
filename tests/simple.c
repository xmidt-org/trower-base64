/* SPDX-FileCopyrightText: 2016-2021 Comcast Cable Communications Management, LLC */
/* SPDX-License-Identifier: Apache-2.0 */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../src/base64.h"

struct test_vector {
    const char *in;
    size_t in_len;
    const char *out;
    size_t out_len;
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

#if 0
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
#endif
        /* Protect against a bogus empty string */
        {   .in = "==",
            .in_len = 2,
            .out = NULL,
            .out_len = 0,
        },

#if 0
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
        {   .in = "as\x00d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x01d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x02d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x03d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x04d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x05d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x06d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x07d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x08d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x09d=", .in_len = 4, .out = NULL, .out_len = 0, },
        {   .in = "as\x0ad=", .in_len = 4, .out = NULL, .out_len = 0, },

        /* A remainder of 1 is never valid */
        {   .in = "TWFub",
            .in_len = 5,
            .out = NULL,
            .out_len = 0,
        },
#endif
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

#if 0
        /* The padding '=' is optional for the URL variant. */
        {   .in = "TWE",
            .in_len = 3,
            .out = "Ma",
            .out_len = 2,
        },
        {   .in = "TQ",
            .in_len = 2,
            .out = "M",
            .out_len = 1,
        },
#endif

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
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(0), 0);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(1), 0);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(2), 1);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(3), 2);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(4), 3);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(8), 6);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(51), 38);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(52), 39);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(53), 39);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(54), 40);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(55), 41);
    CU_ASSERT_EQUAL(b64url_get_decoded_buffer_size(56), 42);
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
    uint8_t *workspace = malloc(workspace_size);
    uint8_t *tmp = dup( raw, raw_size );

    // Copy the data into a malloc'ed buffer so valgrind can help us find problems
    // Use it, then free it.
    b64_encode(tmp, raw_size, workspace);
    free(tmp);

    CU_ASSERT_EQUAL( expected_size, workspace_size );
    for( i = 0; i < expected_size; i++ ) {
        CU_ASSERT_EQUAL(workspace[i], (uint8_t) expected[i]);
        if( workspace[i] != (uint8_t) expected[i] ) {
            printf("Expected[%zd:%c] %*s ::Actual[%zd:%c] %*s\n",
                    i, expected[i], (int) expected_size, expected,
                    i, workspace[i], (int) workspace_size, workspace);
        }
    }
    free(workspace);
}

void test_decode() {
    struct test_vector *t = common_decoder_tests;

    for( size_t i = 0; i < sizeof(common_decoder_tests)/sizeof(struct test_vector); i++ ) {
        test_decoded_stuff( b64_decode, t[i].in, t[i].in_len, t[i].out, t[i].out_len );
    }

    test_decoded_stuff( b64_decode, "bGVhc3VyZS4=", 12, "leasure.",     8 );
    test_decoded_stuff( b64_decode, "ZWFzdXJlLg==", 12, "easure.",      7 );
    test_decoded_stuff( b64_decode, "YXN1cmUu",      8, "asure.",       6 );
    test_decoded_stuff( b64_decode, "c3VyZS4=",      8, "sure.",        5 );
    test_decoded_stuff( b64_decode, "+/+/",          4, "\xfb\xff\xbf", 3 );
    test_decoded_stuff( b64_decode, "Y",             1, NULL,           0 );
    test_decoded_stuff( b64_decode, "==",            2, NULL,           0 );
    test_decoded_stuff( b64_decode, "b==",           3, NULL,           0 );

    //test_decoded_stuff( b64_decode, "bad4=",         5, NULL,           0 );
    //test_decoded_stuff( b64_decode, "bad4==",        6, NULL,           0 );
    //test_decoded_stuff( b64_decode, "bad==",         5, NULL,           0 );
    //test_decoded_stuff( b64_decode, "ba=",           3, NULL,           0 );
    //test_decoded_stuff( b64_decode, "YXN=cmUu",      8, NULL,           0 );
    //test_decoded_stuff( b64_decode, "YXN\xffmcUu",   8, NULL,           0 );
}

void test_url_decode() {
    struct test_vector *t = common_decoder_tests;

    for( size_t i = 0; i < sizeof(common_decoder_tests)/sizeof(struct test_vector); i++ ) {
        test_decoded_stuff( b64url_decode, t[i].in, t[i].in_len, t[i].out, t[i].out_len );
    }

    test_decoded_stuff( b64url_decode, "bGVhc3VyZS4",  11, "leasure.",     8 );
    test_decoded_stuff( b64url_decode, "ZWFzdXJlLg",   10, "easure.",      7 );
    test_decoded_stuff( b64url_decode, "YXN1cmUu",      8, "asure.",       6 );
    test_decoded_stuff( b64url_decode, "c3VyZS4",       7, "sure.",        5 );
    test_decoded_stuff( b64url_decode, "-_-_",          4, "\xfb\xff\xbf", 3 );
    test_decoded_stuff( b64url_decode, "Y",             1, NULL,           0 );
    test_decoded_stuff( b64url_decode, "==",            2, NULL,           0 );
    test_decoded_stuff( b64url_decode, "b==",           3, NULL,           0 );
    test_decoded_stuff( b64url_decode, "ZWFzdXJlLg==", 12, "easure.",      7 );

    //test_decoded_stuff( b64url_decode, "bad4=",         5, NULL,           0 );
    //test_decoded_stuff( b64url_decode, "bad4==",        6, NULL,           0 );
    //test_decoded_stuff( b64url_decode, "bad==",         5, NULL,           0 );
    //test_decoded_stuff( b64url_decode, "ba=",           3, NULL,           0 );
    //test_decoded_stuff( b64url_decode, "YXN=cmUu",      8, NULL,           0 );
    //test_decoded_stuff( b64url_decode, "YXN\xffmcUu",   8, NULL,           0 );
}

void test_decoded_stuff( size_t (*fn)(const uint8_t*, const size_t, uint8_t*),
                         const char *raw, size_t raw_size, const char *expected, size_t expected_size )
{
    size_t i;

    size_t workspace_size = b64_get_decoded_buffer_size(raw_size);
    uint8_t *workspace = malloc(workspace_size);
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
            printf("Expected[%d:%c] %*s ::Actual[%d:%c] %*s\n",
                    (int)i, expected[i], (int)expected_size, expected,
                    (int)i, workspace[i], (int)num_chars, workspace);
        }
    }
    free(workspace);
}

void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "Base64 encoding tests", NULL, NULL );
    CU_add_test( *suite, "Get the Encoded Size     ", test_encoded_size );
    CU_add_test( *suite, "Get the Decoded Size     ", test_decoded_size );
    CU_add_test( *suite, "Get the base64url Decoded Size", test_b64url_decoded_size );
    CU_add_test( *suite, "Get the Encode           ", test_encode );
    CU_add_test( *suite, "Get the Decode           ", test_decode );
    CU_add_test( *suite, "Get the URL Decode       ", test_url_decode );
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
