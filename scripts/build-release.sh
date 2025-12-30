#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
project_root="$(cd "${script_dir}/.." && pwd)"

cd "$project_root"

echo "CMake configuring build files..."
cmake --preset release

echo "CMake building project..."
cmake --build --preset release
