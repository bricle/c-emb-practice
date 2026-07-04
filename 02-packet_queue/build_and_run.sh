#!/bin/sh
set -eu

PROJECT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

"${PROJECT_DIR}/build.sh"
ctest --test-dir "${PROJECT_DIR}/build" --output-on-failure
"${PROJECT_DIR}/run.sh"
