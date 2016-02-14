/**
 *  Copyright 2010-2016 Comcast Cable Communications Management, LLC
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <stdbool.h>

#include "../src/base64.h"

bool test_encoded_stuff( uint8_t *raw, size_t raw_size, uint8_t *expected, size_t expected_size );
bool test_decoded_stuff( size_t (*fn)(const uint8_t*, const size_t, uint8_t*),
                         uint8_t *raw, size_t raw_size, uint8_t *expected, size_t expected_size );

void test_encoded_size() {
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(0), 0);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(1), 4);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(2), 4);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(3), 4);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(4), 8);
    CU_ASSERT_EQUAL(b64_get_encoded_buffer_size(300), 400);
}

void test_decoded_size() {
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(0), 0);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(1), 0);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(2), 0);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(3), 0);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(4), 3);
    CU_ASSERT_EQUAL(b64_get_decoded_buffer_size(8), 6);
}

void test_encode() {
    CU_ASSERT_FALSE(test_encoded_stuff( (uint8_t*)"leasure.", 8, (uint8_t*)"bGVhc3VyZS4=", 12 ));
    CU_ASSERT_FALSE(test_encoded_stuff( (uint8_t*)"easure.", 7, (uint8_t*)"ZWFzdXJlLg==", 12 ));
    CU_ASSERT_FALSE(test_encoded_stuff( (uint8_t*)"asure.", 6, (uint8_t*)"YXN1cmUu", 8 ));
    CU_ASSERT_FALSE(test_encoded_stuff( (uint8_t*)"sure.", 5, (uint8_t*)"c3VyZS4=", 8 ));
}


bool test_encoded_stuff( uint8_t *raw, size_t raw_size, uint8_t *expected, size_t expected_size )
{
    size_t i;
    bool rv = false;

    size_t workspace_size = b64_get_encoded_buffer_size(raw_size);
    uint8_t *workspace = malloc(workspace_size);
    b64_encode(raw, raw_size, workspace);
    CU_ASSERT_EQUAL( expected_size, workspace_size );
    rv |= (expected_size != workspace_size );
    for( i = 0; i < expected_size; i++ ) {
        CU_ASSERT_EQUAL(workspace[i], expected[i]);
        if( workspace[i] != expected[i] ) {
            rv = true;
            printf("Expected[%zd:%c] %*s ::Actual[%zd:%c] %*s\n",
                    i, expected[i], (int) expected_size, expected,
                    i, workspace[i], (int) workspace_size, workspace);
        }
    }
    free(workspace);
    return rv;
}

void test_decode() {
    uint8_t involved[] = { 0xfb, 0xff, 0xbf };

    CU_ASSERT_FALSE(test_decoded_stuff( b64_decode, (uint8_t*)"bGVhc3VyZS4=", 12, (uint8_t*)"leasure.", 8 ));
    CU_ASSERT_FALSE(test_decoded_stuff( b64_decode, (uint8_t*)"ZWFzdXJlLg==", 12, (uint8_t*)"easure.", 7 ));
    CU_ASSERT_FALSE(test_decoded_stuff( b64_decode, (uint8_t*)"YXN1cmUu", 8, (uint8_t*)"asure.", 6 ));
    CU_ASSERT_FALSE(test_decoded_stuff( b64_decode, (uint8_t*)"c3VyZS4=", 8, (uint8_t*)"sure.", 5 ));
    CU_ASSERT_FALSE(test_decoded_stuff( b64_decode, (uint8_t*)"+/+/", 4, involved, 3 ));
}

void test_url_decode() {
    uint8_t involved[] = { 0xfb, 0xff, 0xbf };

    CU_ASSERT_FALSE(test_decoded_stuff( b64url_decode, (uint8_t*)"bGVhc3VyZS4", 11, (uint8_t*)"leasure.", 8 ));
    CU_ASSERT_FALSE(test_decoded_stuff( b64url_decode, (uint8_t*)"ZWFzdXJlLg", 10, (uint8_t*)"easure.", 7 ));
    CU_ASSERT_FALSE(test_decoded_stuff( b64url_decode, (uint8_t*)"YXN1cmUu", 8, (uint8_t*)"asure.", 6 ));
    CU_ASSERT_FALSE(test_decoded_stuff( b64url_decode, (uint8_t*)"c3VyZS4", 7, (uint8_t*)"sure.", 5 ));
    CU_ASSERT_FALSE(test_decoded_stuff( b64url_decode, (uint8_t*)"-_-_", 4, involved, 3 ));
}

bool test_decoded_stuff( size_t (*fn)(const uint8_t*, const size_t, uint8_t*),
                         uint8_t *raw, size_t raw_size, uint8_t *expected, size_t expected_size )
{
    size_t i;
    bool rv = false;

    size_t workspace_size = b64_get_decoded_buffer_size(raw_size);
    uint8_t *workspace = malloc(workspace_size);
    size_t num_chars = (fn)(raw, raw_size, workspace);
    CU_ASSERT_EQUAL( expected_size, num_chars );
    rv |= ( expected_size != num_chars );
    if( rv ) {
        printf("Size fail: %s :: %d %d\n", expected, (int)expected_size, (int)num_chars);
    }

    for( i = 0; i < expected_size; i++ ) {
        CU_ASSERT_EQUAL(workspace[i], expected[i]);
        if( workspace[i] != expected[i] ) {
            rv = true;
            printf("Expected[%d:%c] %*s ::Actual[%d:%c] %*s\n",
                    (int)i, expected[i], (int)expected_size, expected,
                    (int)i, workspace[i], (int)num_chars, workspace);
        }
    }
    free(workspace);
    return rv;
}

void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "Base64 encoding tests", NULL, NULL );
    CU_add_test( *suite, "Get the Encoded Size     ", test_encoded_size );
    CU_add_test( *suite, "Get the Decoded Size     ", test_decoded_size );
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
