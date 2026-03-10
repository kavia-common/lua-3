#!/usr/bin/env bash
# DRASim ROS2 workspace build helper.
# Usage: ./build.sh [--clean]
#
# Supports ROS2 Humble and Jazzy distributions.
# Falls back to Jazzy automatically when Humble is not installed.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${SCRIPT_DIR}"

# --- ROS2 distribution discovery (Humble preferred, Jazzy fallback) ---
if [[ -f /opt/ros/humble/setup.bash ]]; then
  ROS_DISTRO_PATH="/opt/ros/humble/setup.bash"
  ROS_DISTRO="humble"
elif [[ -f /opt/ros/jazzy/setup.bash ]]; then
  ROS_DISTRO_PATH="/opt/ros/jazzy/setup.bash"
  ROS_DISTRO="jazzy"
else
  echo "ERROR: Neither ROS2 Humble nor Jazzy found under /opt/ros/" >&2
  exit 1
fi

echo "Using ROS2 distribution: ${ROS_DISTRO} (${ROS_DISTRO_PATH})"
# shellcheck disable=SC1090
source "${ROS_DISTRO_PATH}"

# --- Optional clean build ---
if [[ "${1:-}" == "--clean" ]]; then
  echo "Cleaning previous build artifacts..."
  rm -rf build install log
fi

# --- Build ---
colcon build --symlink-install \
  --cmake-args -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  --event-handlers console_cohesion+

echo "Build complete. Source install with:"
echo "  source ${SCRIPT_DIR}/install/setup.bash"
