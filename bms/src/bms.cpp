#include <bms.h>

void bms::BMS::chargingRobot(utils::Robot &robot) {
  robot.battery = robot.battery + chargingPercentage;
}

void bms::BMS::dischargingRobot(utils::Robot &robot) {
  robot.battery = robot.battery - dischargingPercentage;
}

void bms::BMS::run(std::vector<utils::Robot> &robots) {
  sort(robots.begin(), robots.end(),
       [](utils::Robot &robot1, utils::Robot &robot2) {
         return robot1.battery < robot2.battery;
       });

  if (currBotsCharging < numSlotsCharging) {
    for (int i = 0; i < numSlotsCharging; i++) {
      robots[i].charging_status = true;
      currBotsCharging++;
    }
  } else {
    for (int i = robots.size() - 1; i >= 0; i--) {
      if (robots[i].charging_status && robots[i].battery > 20) {
        for (std::size_t j = 0; j < robots.size(); j++) {
          if (!robots[j].charging_status && robots[j].battery < 20) {
            robots[j].charging_status = true;
            robots[i].charging_status = false;
            std::swap(robots[i], robots[j]);
          }
        }
      }
    }
  }

  for (auto &robot : robots) {
    if (robot.charging_status)
      chargingRobot(robot);
    else
      dischargingRobot(robot);
  }
}

void bms::BMS::stop() { std::cout << "[BMS::stop] Exiting the Robot BMS\n"; }