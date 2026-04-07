/**
 * The Posthog C library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include <stdio.h>
#include <string.h>

#include "test.h"

void *test_http_client(void *arg) {
    phc_client client;
    phc_init("test_api_key", "https://localhost", &client);

    phc_cleanup(&client);

    return NULL;
}
