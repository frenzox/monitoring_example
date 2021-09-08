#!/bin/sh

set -eu

BASE_BUILD_DIR="build"

REQUIRED_COMMANDS="
    [
    command
    echo
    exit
    getopts
    printf
    test
    meson
    ninja
"

e_err() {
    echo >&2 "ERROR: ${*}"
}

e_warn() {
    echo "WARN: ${*}"
}

usage() {
    echo "Usage: ${0} [OPTIONS]"
    echo
    echo "Helper script to build the Safety Controller software"
    echo
    echo "    -h  Print this help text and exit"
    echo
    echo "Optional arguments:"
    echo "    -b <board>        Board to compile the software to, can be given"
    echo "                      multiple times to compile for multiple boards"
    echo "    -c                Clean before building"
    echo "    -t <buildtype>    Build type: {plain, debug, debugoptimized, release, minsize, custom}"
    echo "                      See http://mesonbuild.com/"
    echo
    echo "If you don't pass any argument, then all boards are built using the 'debugoptimized' build type"
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

clean()
{
    boards="${1}"

    if [ "${boards}" = "all" ]; then
        rm -rf "${BASE_BUILD_DIR:?}"
    else
        for board in ${boards}; do
            rm -rf "${BASE_BUILD_DIR}/${board}"
        done
    fi
}

meson_build()
{
    builddir="${1?Build directory is required}"
    buildtype="${2?Build type is required}"

    meson --cross-file="boards/${builddir#${BASE_BUILD_DIR}}/meson.ini" \
          --buildtype="${buildtype}" \
          "${builddir}"

    ninja -C "${builddir}"
}

build()
{
    boards="${1}"
    buildtype="${2}"

    if [ "${boards}" = "all" ]; then
        boards="$(find "boards" \
                                -maxdepth 1 \
                                -type d \
                                \( ! -iname "boards" \) \
                                -exec basename {} \;)"
    fi

    for board in ${boards}; do
        if [ -f "boards/${board}/meson.ini" ]; then
            meson_build "${BASE_BUILD_DIR}/${board}" "${buildtype}"
        fi
    done
}

main()
{
    check_requirements

    while getopts ":bcht:" options; do
        case "${options}" in
        b)
            chosen_boards="${chosen_boards:-} ${OPTARG}"
            ;;
        c)
            clean="true"
            ;;
        h)
            usage
            exit 0
            ;;
        t)
            buildtype="${OPTARG}"
            ;;
        :)
            e_err "Option -${OPTARG} requires an argument."
            exit 1
            ;;
        ?)
            e_err "Invalid option: -${OPTARG}"
            exit 1
            ;;
        esac
    done

    if [ -n "${clean:-}" ]; then
        clean "${chosen_boards:-all}"
    fi

    build "${chosen_boards:-all}" "${buildtype:-debugoptimized}"
}

main "${@}"
