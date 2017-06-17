#!/bin/bash

SCRIPT_NAME="$(basename "${BASH_SOURCE:-${(%):-%N}}")"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE:-${(%):-%N}}")"; pwd)"

BIN_DIR="${SCRIPT_DIR}/../build/wc"

cd "${BIN_DIR}" || exit 1

make

test_this() {
    local args="$*"

    # wc on Linux adjusts amount of spaces with some smart way.
    # It is out of interest to imprement the fundamental logic of wc, so
    # ignoring the amount of spaces.
    diff --ignore-space-change -u <(eval wc ${args}) <(eval ./wc ${args}) || exit $?
}

echo "INFO: Case 1"
test_this "<${SCRIPT_DIR}/${SCRIPT_NAME}"

echo "INFO: Case 2"
test_this "${SCRIPT_DIR}/${SCRIPT_NAME}"

echo "INFO: Case 3"
test_this "${SCRIPT_DIR}/${SCRIPT_NAME}" "${SCRIPT_DIR}/wc.c"

echo "INFO: Case 4"
test_this "/dev/null"

echo "Done!"

