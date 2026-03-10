#!/usr/bin/env bash
# DRASim ROS2 workspace build helper.
# Usage: ./build.sh [--clean]
set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${SCRIPT_DIR}"
if [[ -f /opt/ros/humble/setup.bash ]]; then
  source /opt/ros/humble/setup.bash
else
  echo "ERROR: ROS2 Humble not found" >&2; exit 1
fi
if [[ "${1:-}" == "--clean" ]]; then rm -rf build install log; fi
colcon build --symlink-install \
  --cmake-args -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  --event-handlers console_cohesion+
echo "Build complete. Source: source ${SCRIPT_DIR}/install/setup.bash"
