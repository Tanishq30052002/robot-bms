#include <utils.h>

void utils::printRobotBatteries(std::vector<utils::Robot> &robots) {
  // Sort the bots in increasing order based on the id
  sort(robots.begin(), robots.end(), [](Robot &robot1, Robot &robot2) {
    return robot1.getRobotId() < robot2.getRobotId();
  });

  std::cout << "[printRobotBatteries] ";
  for (std::size_t i = 0; i < robots.size(); i++) {
    std::cout << "Robot " << std::setw(2) << robots[i].getRobotId() << ": ("
              << std::setw(4) << robots[i].getRobotBattery() << ", "
              << std::setw(1) << robots[i].getChargingStatus() << ")";

    if (i != robots.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
}
