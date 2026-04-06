/**
 * The Posthog C library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#include <stdlib.h>
#include <string.h>

#include "posthog.h"

static CURLU *phc_url(const char *path, phc_client *client) {
    CURLUcode rc;
    CURLU *url = curl_url();

    rc = curl_url_set(url, CURLUPART_URL, client->host, 0);

    if(rc == CURLUE_OK) {
        rc = curl_url_set(url, CURLUPART_PATH, path, 0);

        if(rc == CURLUE_OK) {
            return url;
        }
    }

    curl_url_cleanup(url);

    return NULL;
}

// Initialize the client.
PHC_EXPORT phc_status phc_send_request(const char *path, const char *payload, phc_client *client) {
    CURLU *url = phc_url(path, client);

    if(!url) {
        return PHC_ERROR;
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    if(!headers) {
        curl_url_cleanup(url);

        return PHC_ERROR;
    }

    headers = curl_slist_append(headers, client->api_key);

    if(!headers) {
        curl_url_cleanup(url);

        return PHC_ERROR;
    }

    curl_easy_setopt(client->curl, CURLOPT_URL, url);
    curl_easy_setopt(client->curl, CURLOPT_POST, 1);
    curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, payload);
    curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(client->curl);

    curl_slist_free_all(headers);
    curl_url_cleanup(url);

    if(res != CURLE_OK) {
        return PHC_ERROR_CURL;
    }

    return PHC_OK;
}
