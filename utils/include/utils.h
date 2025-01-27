#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

namespace utils {

class Robot {
 public:
  Robot() : id(0), battery(0), charging_status(0) {}
  Robot(int id, float battery, bool charging_status)
      : id(id), battery(battery), charging_status(charging_status) {}

  ~Robot() = default;

  inline int getRobotId() const { return id; }
  inline float getRobotBattery() const { return battery; }
  inline bool getChargingStatus() const { return charging_status; }

  inline void setRobotBattery(float robot_battery) { battery = robot_battery; }
  inline void setChargingStatus(bool robot_charging_status) {
    charging_status = robot_charging_status;
  }

 private:
  int id = 0;
  float battery = 0;
  bool charging_status = 0;
};

void printRobotBatteries(std::vector<utils::Robot>& robots);
}  // namespace utils