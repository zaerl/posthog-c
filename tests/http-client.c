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
    char url[2056];

    phc_init("test_api_key", "https://localhost", &client);

    // Format URL without arguments.
    ATT_ASSERT(phc_format_url(PHC_API_USERS, &client, url, sizeof(url)), PHC_OK, "Format users URL");
    ATT_ASSERT((const char *)url, "https://localhost/api/users/", "Users URL value");

    // Format URL without arguments but with an argument provided (should be ignored).
    ATT_ASSERT(phc_format_url(PHC_API_CODE_INVITES_REDEEM, &client, url, sizeof(url), "extra_arg"), PHC_OK, "Format URL with extra argument");
    ATT_ASSERT((const char *)url, "https://localhost/api/code/invites/redeem/", "Check-access URL value with extra argument");

    // Format URL with one argument.
    ATT_ASSERT(phc_format_url(PHC_API_USERS_UUID, &client, url, sizeof(url), "abc123"), PHC_OK, "Format users UUID URL");
    ATT_ASSERT((const char *)url, "https://localhost/api/users/abc123/", "Users UUID URL value");

    ATT_ASSERT(phc_endpoint_accept(PHC_API_USERS, PHC_NET_POST), PHC_ERROR_INVALID_METHOD, "POST users list");
    ATT_ASSERT(phc_endpoint_accept(PHC_API_USERS, PHC_NET_GET), PHC_OK, "GET users list");

    const char *api_key = getenv("ATT_API_KEY");

    if(!api_key) {
        printf("Skipping request test since ATT_API_KEY is not set\n");

        return NULL;
    }

    phc_cleanup(&client);
    ATT_ASSERT(phc_init(api_key, PHC_HOST_EU, &client), PHC_OK, "Initialize client");

    ATT_ASSERT(phc_format_url(PHC_API_USERS, &client, url, sizeof(url)), PHC_OK, "Format URL");
    ATT_ASSERT(phc_send_request(url, PHC_NET_GET, NULL, &client), PHC_OK, "GET users list");

    phc_cleanup(&client);

    return NULL;
}
