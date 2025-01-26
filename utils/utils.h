#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

namespace utils {

class Robot {
 public:
  int id;
  float battery;
  bool charging_status;

  Robot() : id(0), battery(0), charging_status(0) {}
  Robot(int id, float battery, bool charging_status)
      : id(id), battery(battery), charging_status(charging_status) {}

  ~Robot() = default;
};

void printRobotBatteries(std::vector<utils::Robot>& robots);
}  // namespace utils