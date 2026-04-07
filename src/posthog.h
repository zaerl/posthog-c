/**
 * The Posthog C library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#pragma once

#ifndef PHC_POSTHOG_H
#define PHC_POSTHOG_H

#include <curl/curl.h>

#define PHC_VERSION "0.1.0"
#define PHC_ENV_API_KEY "POSTHOG_API_KEY"
#define PHC_ENV_HOST "POSTHOG_HOST"

#define PHC_HOST_EU "https://eu.i.posthog.com"
#define PHC_HOST_US "https://us.i.posthog.com"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PHC_EXPORT
    #if defined(_WIN32) || defined(_WIN64)
        #define PHC_EXPORT
    #elif defined(__GNUC__) || defined(__clang__)
        #define PHC_EXPORT __attribute__((visibility("default")))
    #else
        #define PHC_EXPORT
    #endif
#endif

// Modern compiler attributes with fallbacks
#if defined(__GNUC__) || defined(__clang__)
    #define PHC_NODISCARD __attribute__((warn_unused_result))
    #define PHC_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
    #define PHC_PURE __attribute__((pure))
    #define PHC_CONST __attribute__((const))
#elif defined(__cplusplus) && __cplusplus >= 201703L
    #define PHC_NODISCARD [[nodiscard]]
    #define PHC_NONNULL(...)
    #define PHC_PURE
    #define PHC_CONST
#else
    #define PHC_NODISCARD
    #define PHC_NONNULL(...)
    #define PHC_PURE
    #define PHC_CONST
#endif

typedef enum {
    PHC_OK = 0,
    PHC_ERROR = -1,
    PHC_ERROR_NO_API_KEY = -2,
    PHC_ERROR_CURL = -3,
} phc_status;

typedef enum {
    PHC_NET_GET = 0x0,
    PHC_NET_POST = 0x1,
    PHC_NET_PUT = 0x2,
    PHC_NET_PATCH = 0x4,
    PHC_NET_DELETE = 0x8,
} phc_net_method;

enum {
    // Start of endpoints list, automatically generated. Do not modify.
    // End of endpoints list.
};

typedef struct phc_client {
    char *api_key;
    char *host;
    CURL *curl;
} phc_client;

// Initialize the client.
PHC_NONNULL(3) phc_status phc_init(const char *api_key, const char *host, phc_client *client);
// Clean up the client.
PHC_NONNULL(1) void phc_cleanup(phc_client *client);
PHC_NONNULL(1, 2, 3) phc_status phc_send_request(const char *path, const char *payload, phc_client *client);

#ifdef __cplusplus
}
#endif

#endif // PHC_POSTHOG_H
