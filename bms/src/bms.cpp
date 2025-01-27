#include <bms.h>

void bms::BMS::chargingRobot(utils::Robot &robot) {
  robot.setRobotBattery(robot.getRobotBattery() + chargingPercentage);
}

void bms::BMS::dischargingRobot(utils::Robot &robot) {
  robot.setRobotBattery(robot.getRobotBattery() - dischargingPercentage);
}

void bms::BMS::run(std::vector<utils::Robot> &robots) {
  sort(robots.begin(), robots.end(),
       [](utils::Robot &robot1, utils::Robot &robot2) {
         return robot1.getRobotBattery() < robot2.getRobotBattery();
       });

  if (currBotsCharging < numSlotsCharging) {
    for (int i = 0; i < numSlotsCharging; i++) {
      robots[i].setChargingStatus(true);
      currBotsCharging++;
    }
  } else {
    for (int i = robots.size() - 1; i >= 0; i--) {
      if (robots[i].getChargingStatus() && robots[i].getRobotBattery() > 20) {
        for (std::size_t j = 0; j < robots.size(); j++) {
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

void bms::BMS::stop() { std::cout << "[BMS::stop] Exiting the Robot BMS\n"; }