/**
 * The Posthog C library
 *
 * This file is distributed under the MIT License. See LICENSE for details.
 */

#pragma once

#ifndef PHC_TEST_H
#define PHC_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/posthog.h"
#include "./attractor/attractor.h"

#ifdef __cplusplus
extern "C" {
#endif

// Start tests declarations.
void *test_http_client(void *arg);
void *test_init(void *arg);

void set_error_callback(att_test_callback callback);
bool is_exit_on_error(void);

#ifdef _WIN32
// Windows-compatible strsep declaration
char *strsep(char **stringp, const char *delim);
#endif

#ifdef __cplusplus
}
#endif

#endif // PHC_TEST_H
