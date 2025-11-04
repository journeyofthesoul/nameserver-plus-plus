#!/bin/sh
set -e # Exit on failure

cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
cmake --build ./build
gcc -Wall -Wextra -std=c11 -I./src -o test_dns_parser src/*.c tests/test_dns_parser.c -lcunit
