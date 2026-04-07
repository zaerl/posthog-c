#!/bin/sh

# The Mojibake library
# This file is distributed under the MIT License. See LICENSE for details.

UNICODE_VERSION="17.0.0"

if [ ! -f "schema.yaml" ] ; then
    curl -o schema.yaml "https://app.posthog.com/api/schema/"
fi

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
"$SCRIPT_DIR/../.venv/bin/python3" "$SCRIPT_DIR/generate.py"
