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

    ATT_ASSERT(phc_send_request(PHC_API_USERS, PHC_NET_POST, NULL, &client), PHC_ERROR_INVALID_METHOD, "POST users list");

    phc_cleanup(&client);

    return NULL;
}
