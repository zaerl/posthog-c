/**
 * The Posthog C library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include <stdlib.h>
#include <string.h>

#include "posthog.h"

static const char *phc_env(const char *name) {
    return getenv(name);
}

// Initialize the client.
PHC_EXPORT phc_status phc_init(const char *api_key, const char *host, phc_client *client) {
    client->curl = NULL;
    client->api_key = NULL;
    client->host = NULL;

    CURL *curl = curl_easy_init();

    if(!curl) {
        return PHC_ERROR;
    }

    client->curl = curl;

    if(!api_key) {
        // Try the environment variable if no API key was provided.
        api_key = phc_env(PHC_ENV_API_KEY);

        if(!api_key) {
            phc_cleanup(client);

            return PHC_ERROR_NO_API_KEY;
        }
    }

    if(!host) {
        // Try the environment variable if no host was provided.
        host = phc_env(PHC_ENV_HOST);

        if(!host) {
            // Default to US host.
            host = strdup(PHC_HOST_US);
        }
    }

    client->api_key = malloc(8 + strlen(api_key));
    sprintf(client->api_key, "Bearer %s", api_key);

    client->host = strdup(host);

    return PHC_OK;
}

// Clean up the client.
PHC_EXPORT void phc_cleanup(phc_client *client) {
    if(client->api_key) {
        free(client->api_key);
        client->api_key = NULL;
    }

    if(client->host) {
        free(client->host);
        client->host = NULL;
    }

    if(client->curl) {
        curl_easy_cleanup(client->curl);
        client->curl = NULL;
    }
}
