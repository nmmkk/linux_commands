#!/bin/bash

# SCRIPT_NAME="$(basename "${BASH_SOURCE:-${(%):-%N}}")"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE:-${(%):-%N}}")" || exit 1; pwd)"

BIN_DIR="${SCRIPT_DIR}/../build/mv"

#============================================================
# Sub routines
#============================================================
err() {
    msg="$*"
    echo "${msg}" 1>&2
}

test_this() {
    local exp_exit=$1
    shift
    local args=( "$@" )
    local act_exit=

    ./mv "${args[@]}"
    act_exit=$?
    if [ ${act_exit} -ne "${exp_exit}" ]; then
        err "FAIL: Unexpected exit code result=<${act_exit}> exp=<${exp_exit}>"
        exit 1
    fi
}

cleanup() {
    rm -rf dummy_dir
    rm -f dummy_file1 dummy_file2
}

prep() {
    mkdir -p dummy_dir
    touch dummy_file1
    touch dummy_file2
}

#============================================================
# Main routine
#============================================================
cd "${BIN_DIR}" || exit 1

make || exit 2

trap cleanup EXIT
prep
ls -lid dummy_file1 dummy_file2 dummy_dir

echo "========================================"
echo "INFO: Case 1"
test_this 0 dummy_file1 moved_file1
ls -lid dummy_file1 moved_file1

echo "========================================"
echo "INFO: Case 2"
test_this 0 moved_file1 dummy_dir
ls -lid dummy_dir/moved_file1

echo "========================================"
echo "INFO: Case 3"
mv dummy_dir/moved_file1 moved_file1
test_this 0 moved_file1 dummy_dir///
ls -lid dummy_dir/moved_file1

echo "========================================"
echo "Done!"

