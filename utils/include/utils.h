#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

namespace utils {

class Robot {
 public:
  Robot() : id_(0), battery_(0), charging_status_(0) {}
  Robot(int id, float battery, bool charging_status)
      : id_(id), battery_(battery), charging_status_(charging_status) {}

  ~Robot() = default;

  inline int getRobotId() const { return id_; }
  inline float getRobotBattery() const { return battery_; }
  inline bool getChargingStatus() const { return charging_status_; }

  inline void setRobotBattery(float robot_battery) { battery_ = robot_battery; }
  inline void setChargingStatus(bool robot_charging_status) {
    charging_status_ = robot_charging_status;
  }

 private:
  int id_ = 0;
  float battery_ = 0;
  bool charging_status_ = 0;
};

void printRobotBatteries(std::vector<utils::Robot>& robots);
}  // namespace utils