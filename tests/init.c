/**
 * The Posthog C library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include <stdio.h>
#include <string.h>

#include "test.h"

void *test_init(void *arg) {
    phc_client client;

    ATT_ASSERT(phc_init(NULL, NULL, &client), PHC_ERROR_NO_API_KEY, "No API key is provided");

    return NULL;
}
