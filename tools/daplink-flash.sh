#!/usr/bin/env bash
set -euo pipefail

project_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
check_only=false
user_name="${USER:-$(id -un)}"

if [[ "${1:-}" == "--check" ]]; then
    check_only=true
elif [[ $# -ne 0 ]]; then
    echo "用法: $0 [--check]" >&2
    exit 2
fi

find_daplink_mount() {
    local candidate
    for candidate in "/media/${user_name}"/* "/run/media/${user_name}"/*; do
        [[ -d "$candidate" ]] || continue
        if [[ -f "$candidate/README.TXT" ]] && grep -aFq "Horco CMSIS-DAP" "$candidate/README.TXT"; then
            printf '%s\n' "$candidate"
            return 0
        fi
    done
    return 1
}

build_dir="${DAPLINK_BUILD_DIR:-$project_dir/cmake-build-debug}"
if [[ ! -f "$build_dir/CMakeCache.txt" ]]; then
    echo "CLion Debug 构建目录不存在，改用 CMake Debug preset。"
    cmake --preset Debug -S "$project_dir"
    build_dir="$project_dir/build/Debug"
fi

echo "[1/3] 编译 MSPM0 固件"
cmake --build "$build_dir" --target compile_firmware

image="$build_dir/print_Eight_model_IO.hex"
if [[ ! -s "$image" ]]; then
    echo "未找到可烧录的 HEX: $image" >&2
    exit 1
fi

echo "[2/3] 检查 DAPLink"
mount_point="$(find_daplink_mount || true)"
if [[ -z "$mount_point" ]]; then
    echo "未找到已挂载的 Horco CMSIS-DAP，请检查 USB 连接。" >&2
    exit 1
fi
if [[ ! -w "$mount_point" ]]; then
    echo "DAPLink 挂载点不可写: $mount_point" >&2
    exit 1
fi

if $check_only; then
    echo "检查通过：$(basename "$image") -> $mount_point/"
    echo "--check 模式未执行烧录。"
    exit 0
fi

echo "[3/3] 烧录 $(basename "$image")"
cp -- "$image" "$mount_point/$(basename "$image")"
sync -f "$mount_point"

# DAPLink 完成编程后可能会短暂重连。
sleep 2
mount_point="$(find_daplink_mount || true)"
if [[ -n "$mount_point" && -s "$mount_point/FAIL.TXT" ]]; then
    echo "DAPLink 报告烧录失败：" >&2
    sed -n '1,80p' "$mount_point/FAIL.TXT" >&2
    exit 1
fi

echo "DAPLink 烧录完成。"
