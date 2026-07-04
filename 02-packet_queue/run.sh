#!/bin/sh
set -eu

PROJECT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

"${PROJECT_DIR}/build/test_packet_queue"
