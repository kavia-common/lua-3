#ifndef DRASIM_ROBOT_EMULATOR__MOTION_ENGINE_HPP_
#define DRASIM_ROBOT_EMULATOR__MOTION_ENGINE_HPP_

#include <array>
#include <atomic>
#include <mutex>
#include <string>

namespace drasim_robot_emulator
{

/** @brief Robot motion status. */
enum class MotionStatus { IDLE, MOVING, STOPPED, ERROR };

/**
 * @brief MotionEngine — minimal 6-axis motion emulator using linear interpolation.
 *
 * Supports MovJ (single joint), MovL (linear Cartesian), MovP (PTP Cartesian).
 */
class MotionEngine
{
public:
  static constexpr int NUM_JOINTS = 6;

  // PUBLIC_INTERFACE
  MotionEngine();

  // PUBLIC_INTERFACE
  bool mov_j(int joint, double degree,
             double spd_pct = 10.0, double acc_pct = 10.0, double dec_pct = 10.0);

  // PUBLIC_INTERFACE
  bool mov_l(const std::string & point, const std::array<double, 6> & offset,
             double spd_mms = 100.0, double acc = 10.0, double dec = 10.0,
             bool use_pass = false);

  // PUBLIC_INTERFACE
  bool mov_p(const std::string & point, const std::array<double, 6> & offset,
             double spd_pct = 10.0, double acc_pct = 10.0, double dec_pct = 10.0,
             bool use_pass = false);

  // PUBLIC_INTERFACE
  std::array<double, NUM_JOINTS> get_joint_angles() const;

  // PUBLIC_INTERFACE
  std::array<double, 6> get_cartesian_pose() const;

  // PUBLIC_INTERFACE
  std::string get_status_string() const;

  // PUBLIC_INTERFACE
  MotionStatus get_status() const;

private:
  mutable std::mutex mutex_;
  std::array<double, NUM_JOINTS> joint_angles_{};
  std::array<double, 6>          cart_pose_{};
  std::atomic<MotionStatus>      status_{MotionStatus::IDLE};

  void interpolate_joint(int joint_idx, double target_deg, double spd_pct);
  void interpolate_cart(const std::array<double, 6> & target, double spd_mms);
};

}  // namespace drasim_robot_emulator

#endif  // DRASIM_ROBOT_EMULATOR__MOTION_ENGINE_HPP_
