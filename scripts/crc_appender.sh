#!/bin/sh

set -eu

REQUIRED_COMMANDS="
    [
    command
    echo
    exit
    getopts
    gzip
    hexdump
    printf
    tail
    test
    truncate
    xxd
"

CRC_SIZE_BYTES="4"

checksum_tmp_file=""

e_err() {
    echo >&2 "ERROR: ${*}"
}

e_warn() {
    echo "WARN: ${*}"
}

cleanup()
{
    if [ -f "${checksum_tmp_file}" ]; then
        unlink "${checksum_tmp_file}"
    fi

    trap - EXIT INT
}

usage() {
    echo "Usage: ${0} FILE OUTPUT_FILE"
    echo
    echo "Helper script to generate a file with its crc32 appended"
    echo
    echo "    -h  Print this help text and exit"
    echo
}

check_requirements() {
    for _cmd in ${REQUIRED_COMMANDS}; do
        if ! _test_result="$(command -V "${_cmd}")"; then
            _test_result_fail="${_test_result_fail:-}${_test_result}\n"
        else
            _test_result_pass="${_test_result_pass:-}${_test_result}\n"
        fi
    done

    if [ -n "${_test_result_fail:-}" ]; then
        e_err "Self-test failed, missing dependencies."
        echo "======================================="
        echo "Passed tests:"
        # shellcheck disable=SC2059  # Interpret \n from variable
        printf "${_test_result_pass:-none\n}"
        echo "---------------------------------------"
        echo "Failed tests:"
        # shellcheck disable=SC2059  # Interpret \n from variable
        printf "${_test_result_fail:-none\n}"
        echo "======================================="
        exit 1
    fi
}

init()
{
    trap cleanup EXIT INT
    check_requirements
    checksum_tmp_file="$(mktemp -t "checksum_XXXXXX")"
}

main()
{
    cp "${1:?}" "${2:?}"

    filesize="$(stat -c %s ${2:?})"
    truncate "${2:?}" -s "$((filesize - CRC_SIZE_BYTES))"

    gzip -c "${2:?}" \
        | tail -c8 \
        | hexdump -n4 -e '"%08x"' \
        | xxd -p -r > "${checksum_tmp_file}"

    cat "${checksum_tmp_file}" >> "${2:?}"
}

init
main "${@}"
cleanup
