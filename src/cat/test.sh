#!/bin/bash

SCRIPT_NAME="$(basename "${BASH_SOURCE:-${(%):-%N}}")"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE:-${(%):-%N}}")"; pwd)"

BIN_DIR="${SCRIPT_DIR}/../build/cat"

cd "${BIN_DIR}" || exit 1

make

test_this_stdout() {
    diff -u <(echo -e "$*" | cat) <(echo -e "$*" | ./cat) || exit $?
}

test_this() {
    diff -u <(eval cat $*) <(eval ./cat $*) || exit $?
}

echo "INFO: Case 1"
test_this_stdout "abc\ndef\n123 456\n\tindented\n"

echo "INFO: Case 2"
test_this_stdout "!@#$%^&*()-=_+[]\{}|;':\",./<>?"

echo "INFO: Case 3"
test_this "${SCRIPT_DIR}/${SCRIPT_NAME}"

echo "INFO: Case 4"
test_this "${SCRIPT_DIR}/${SCRIPT_NAME}" "${SCRIPT_DIR}/cat.c"

echo "INFO: Case 5"
test_this "/dev/null"

echo "Done!"

