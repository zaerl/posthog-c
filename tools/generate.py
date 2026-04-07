#!/usr/bin/env python3

import os
import re
import sys
import yaml

# Function to generate a new content.
def generate_content(
    content: str, start: str, end: str, replacement: str, start_pos=0
) -> dict[str, int | str]:
    start_pos = content.find(start, start_pos)

    if start_pos == -1:
        print(f"Could not find start marker: {repr(start)}")
        sys.exit(1)

    end_pos = content.find(end, start_pos + len(start))

    if end_pos == -1:
        print(f"Could not find end marker: {repr(end)} after position {start_pos}")
        sys.exit(1)

    start_pos += len(start) + 1

    new_file_start = content[:start_pos]
    new_file_end = content[end_pos:]
    new_file = new_file_start + replacement + new_file_end

    return {
        "start_pos": start_pos,
        "text": new_file,
    }

schema_path = os.path.join(os.path.dirname(__file__), "schema.yaml")

with open(schema_path, "r") as f:
    data = yaml.safe_load(f)

if not isinstance(data, dict) or "paths" not in data:
    print("Error: missing 'paths' in schema", file=sys.stderr)
    sys.exit(1)

METHOD_BITS = {
    "get": 0x1,
    "post": 0x2,
    "put": 0x4,
    "patch": 0x8,
    "delete": 0x10,
}

paths = data["paths"]
endpoints: list[dict] = []
enums: list[str] = []

for path in paths:
    current_path = path
    methods = 0
    required_fields = 0
    print(path)
    enum_name = '    PHC_' + path.strip("/").replace("/", "_").replace("-", "_").replace(".", "_")
    # /api/projects/{project_id}/... -> /api/projects/{id}/...
    enum_name = re.sub(r'\{[a-zA-Z0-9_]+_id', '{id', enum_name)
    enum_name = enum_name.replace("{", "").replace("}", "").upper()
    enums.append(enum_name.upper())

    for method in paths[path]:
        methods |= METHOD_BITS.get(method.lower(), 0)
        params = paths[path][method].get('parameters', [])
        for param in params:
            if param.get('in') == 'path' and param.get('required', False):
                required_fields += 1
                current_path = current_path.replace(f"{{{param['name']}}}", "%s")
    endpoints.append(f"    {{\"{current_path}\", {methods}, {required_fields}}}")

generated_endpoints = ",\n".join(endpoints)
generated_endpoints += "\n    "

http_client_path = os.path.join(os.path.dirname(__file__), "..", "src", "http-client.c")

with open(http_client_path, "r") as file:
    content = file.read()

res = generate_content(
    content,
    "// List of endpoints, automatically generated. Do not modify.",
    "// End of endpoints list.",
    generated_endpoints
)

with open(http_client_path, "w") as file:
    file.write(res["text"])

print("Generated src/http-client.h successfully.")

header_path = os.path.join(os.path.dirname(__file__), "..", "src", "posthog.h")

with open(header_path, "r") as file:
    content = file.read()

generated_enums = ",\n".join(enums)
generated_enums += "\n    "

res = generate_content(
    content,
    "// List of endpoints, automatically generated. Do not modify.",
    "// End of endpoints list.",
    generated_enums
)

with open(header_path, "w") as file:
    file.write(res["text"])

print("Generated src/posthog.h successfully.")
