#!/bin/sh
set -eu

PROJECT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
BUILD_DIR="${PROJECT_DIR}/build"

# Always start from a clean build tree.
rm -rf -- "${BUILD_DIR}"

# Keep ccache writes inside this exercise for restricted sandboxes.
export CCACHE_DIR="${BUILD_DIR}/.ccache"
export CCACHE_TEMPDIR="${BUILD_DIR}/.ccache-tmp"
mkdir -p "${CCACHE_DIR}" "${CCACHE_TEMPDIR}"

cmake -S "${PROJECT_DIR}" -B "${BUILD_DIR}" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "${BUILD_DIR}" --parallel
