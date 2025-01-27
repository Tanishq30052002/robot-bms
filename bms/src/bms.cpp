#include <bms.h>
namespace bms {

void BMS::chargingRobot(utils::Robot &robot) {
  robot.setRobotBattery(robot.getRobotBattery() + chargingPercentage);
}

void BMS::dischargingRobot(utils::Robot &robot) {
  robot.setRobotBattery(robot.getRobotBattery() - dischargingPercentage);
}

void BMS::run(std::vector<utils::Robot> &robots) {
  sort(robots.begin(), robots.end(),
       [](utils::Robot &robot1, utils::Robot &robot2) {
         return robot1.getRobotBattery() < robot2.getRobotBattery();
       });

  int numRobots = robots.size();
  if (currBotsCharging < numSlotsCharging) {
    for (int i = 0; i < numSlotsCharging; i++) {
      robots[i].setChargingStatus(true);
      currBotsCharging++;
    }
  } else {
    for (int i = numRobots - 1; i >= 0; i--) {
      if (robots[i].getChargingStatus() && robots[i].getRobotBattery() > 20) {
        for (int j = 0; j < numRobots; j++) {
          if (!robots[j].getChargingStatus() &&
              robots[j].getRobotBattery() < 20) {
            robots[j].setChargingStatus(true);
            robots[i].setChargingStatus(false);
            std::swap(robots[i], robots[j]);
          }
        }
      }
    }
  }

  for (auto &robot : robots) {
    if (robot.getChargingStatus())
      chargingRobot(robot);
    else
      dischargingRobot(robot);
  }
}

void BMS::stop() { std::cout << "[BMS::stop] Exiting the Robot BMS\n"; }
}  // namespace bms