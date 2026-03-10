// drasim_robot_emulator/src/motion_engine.cpp
#include "drasim_robot_emulator/motion_engine.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

namespace drasim_robot_emulator
{

MotionEngine::MotionEngine()
{
  joint_angles_.fill(0.0);
  cart_pose_.fill(0.0);
  status_.store(MotionStatus::IDLE);
}

bool MotionEngine::mov_j(int joint, double degree, double spd_pct,
                          double acc_pct, double dec_pct)
{
  (void)acc_pct; (void)dec_pct;
  if (joint < 1 || joint > NUM_JOINTS) {
    std::cerr << "[MotionEngine] MovJ: invalid joint " << joint << "\n";
    return false;
  }
  std::cout << "[MotionEngine] MovJ joint=" << joint << " target=" << degree << " deg\n";
  status_.store(MotionStatus::MOVING);
  interpolate_joint(joint - 1, degree, spd_pct);
  status_.store(MotionStatus::IDLE);
  return true;
}

bool MotionEngine::mov_l(const std::string & point,
                          const std::array<double, 6> & offset,
                          double spd_mms, double acc, double dec, bool use_pass)
{
  (void)acc; (void)dec; (void)use_pass;
  std::cout << "[MotionEngine] MovL point=" << point << " spd=" << spd_mms << "mm/s\n";
  std::array<double, 6> target{};
  {
    std::lock_guard<std::mutex> lock(mutex_);
    for (int i = 0; i < 6; ++i) { target[i] = cart_pose_[i] + offset[i]; }
  }
  status_.store(MotionStatus::MOVING);
  interpolate_cart(target, spd_mms);
  status_.store(MotionStatus::IDLE);
  return true;
}

bool MotionEngine::mov_p(const std::string & point,
                          const std::array<double, 6> & offset,
                          double spd_pct, double acc_pct, double dec_pct, bool use_pass)
{
  (void)acc_pct; (void)dec_pct; (void)use_pass;
  double spd_mms = spd_pct * 20.0;
  std::cout << "[MotionEngine] MovP point=" << point << " spd=" << spd_pct << "%\n";
  std::array<double, 6> target{};
  {
    std::lock_guard<std::mutex> lock(mutex_);
    for (int i = 0; i < 6; ++i) { target[i] = cart_pose_[i] + offset[i]; }
  }
  status_.store(MotionStatus::MOVING);
  interpolate_cart(target, spd_mms);
  status_.store(MotionStatus::IDLE);
  return true;
}

std::array<double, MotionEngine::NUM_JOINTS> MotionEngine::get_joint_angles() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return joint_angles_;
}

std::array<double, 6> MotionEngine::get_cartesian_pose() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return cart_pose_;
}

MotionStatus MotionEngine::get_status() const { return status_.load(); }

std::string MotionEngine::get_status_string() const
{
  switch (status_.load()) {
    case MotionStatus::IDLE:    return "IDLE";
    case MotionStatus::MOVING:  return "MOVING";
    case MotionStatus::STOPPED: return "STOPPED";
    case MotionStatus::ERROR:   return "ERROR";
    default:                    return "UNKNOWN";
  }
}

void MotionEngine::interpolate_joint(int jidx, double target, double spd_pct)
{
  spd_pct = std::max(0.001, std::min(100.0, spd_pct));
  double max_dps = 180.0 * (spd_pct / 100.0);
  double cur = 0.0;
  { std::lock_guard<std::mutex> lock(mutex_); cur = joint_angles_[jidx]; }
  double delta = target - cur;
  double dist  = std::abs(delta);
  double dur   = (max_dps > 0.0) ? (dist / max_dps) : 0.0;
  constexpr double step_ms = 10.0;
  int steps = (int)std::ceil(dur * 1000.0 / step_ms);
  if (steps < 1) {
    std::lock_guard<std::mutex> lock(mutex_); joint_angles_[jidx] = target; return;
  }
  for (int s = 1; s <= steps; ++s) {
    double t = (double)s / (double)steps;
    { std::lock_guard<std::mutex> lock(mutex_); joint_angles_[jidx] = cur + delta * t; }
    std::this_thread::sleep_for(std::chrono::milliseconds((int)step_ms));
  }
}

void MotionEngine::interpolate_cart(const std::array<double, 6> & target, double spd_mms)
{
  spd_mms = std::max(1.0, std::min(2000.0, spd_mms));
  std::array<double, 6> start{};
  { std::lock_guard<std::mutex> lock(mutex_); start = cart_pose_; }
  double dist = 0.0;
  for (int i = 0; i < 3; ++i) { double d = target[i] - start[i]; dist += d * d; }
  dist = std::sqrt(dist);
  double dur = (spd_mms > 0.0) ? (dist / spd_mms) : 0.0;
  constexpr double step_ms = 10.0;
  int steps = (int)std::ceil(dur * 1000.0 / step_ms);
  if (steps < 1) {
    std::lock_guard<std::mutex> lock(mutex_); cart_pose_ = target; return;
  }
  for (int s = 1; s <= steps; ++s) {
    double t = (double)s / (double)steps;
    std::array<double, 6> interp{};
    for (int i = 0; i < 6; ++i) { interp[i] = start[i] + (target[i] - start[i]) * t; }
    { std::lock_guard<std::mutex> lock(mutex_); cart_pose_ = interp; }
    std::this_thread::sleep_for(std::chrono::milliseconds((int)step_ms));
  }
}

}  // namespace drasim_robot_emulator
