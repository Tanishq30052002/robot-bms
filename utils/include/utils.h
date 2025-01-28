#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

namespace utils {

class Robot {
 public:
  /**
   * @brief Construct a new Robot object with default values
   *
   */
  Robot() : id_(0), battery_(0), charging_status_(0) {}

  /**
   * @brief Construct a new Robot object based on the values
   *
   * @param id
   * @param battery
   * @param charging_status
   */
  Robot(int id, float battery, bool charging_status)
      : id_(id), battery_(battery), charging_status_(charging_status) {}

  /**
   * @brief Destroy the Robot object
   *
   */
  ~Robot() = default;

  /**
   * @brief Get the Robot Id object
   *
   * @return int
   */
  inline int getRobotId() const { return id_; }

  /**
   * @brief Get the Robot Battery object
   *
   * @return float
   */
  inline float getRobotBattery() const { return battery_; }

  /**
   * @brief Get the Charging Status object
   *
   * @return true
   * @return false
   */
  inline bool getChargingStatus() const { return charging_status_; }

  /**
   * @brief Set the Robot Battery object
   *
   * @param robot_battery
   */
  inline void setRobotBattery(float robot_battery) { battery_ = robot_battery; }

  /**
   * @brief Set the Charging Status object
   *
   * @param robot_charging_status
   */
  inline void setChargingStatus(bool robot_charging_status) {
    charging_status_ = robot_charging_status;
  }

 private:
  int id_ = 0;
  float battery_ = 0;
  bool charging_status_ = 0;
};

/**
 * @brief prints the robot batteries
 *
 * Step 1: It sorts the robots based on the id
 * Step 2: It prints the robot id and battery level
 *
 * @param robots
 */
void printRobotBatteries(std::vector<utils::Robot>& robots);
}  // namespace utils