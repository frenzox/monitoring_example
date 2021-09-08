#!/bin/sh

# Wrapper around cmock.rb to allow passing output dir as argument cmock.rb
# takes a configuration files where the output path is configured, to properly
# use meson generators, we need to have the output path as a command line
# argument.

set -eu
echo "${@}"

if [ "${#}" -lt 3 ]; then
    exit 1
fi

script_path="$(dirname ${0})"
cmock_cli="${1}"
output_dir="${2}"

shift 2

input_headers="${@}"


if [ ! -f "${output_dir}/mock_cfg.yml" ]; then
    sed "s'@MOCKPATH@'${output_dir}'g" "${script_path}/mock_cfg.yml.in" > "${output_dir}/mock_cfg.yml"
fi

ruby "${cmock_cli}" -o"${output_dir}/mock_cfg.yml" "${input_headers}"
