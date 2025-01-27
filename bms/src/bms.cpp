#include <bms.h>
namespace bms {

void BMS::chargingRobot(utils::Robot &robot) {
  robot.setRobotBattery(robot.getRobotBattery() + chargingPercentage_);
}

void BMS::dischargingRobot(utils::Robot &robot) {
  robot.setRobotBattery(robot.getRobotBattery() - dischargingPercentage_);
}

void BMS::run(std::vector<utils::Robot> &robots) {
  sort(robots.begin(), robots.end(),
       [](utils::Robot &robot1, utils::Robot &robot2) {
         return robot1.getRobotBattery() < robot2.getRobotBattery();
       });

  int numRobots = robots.size();
  for (int i = 0; i < numRobots; i++) {
    if (currBotsCharging_ < numSlotsCharging_ &&
        !robots[i].getChargingStatus() &&
        robots[i].getRobotBattery() <
            (maxOperationalBattery_ - chargingPercentage_)) {
      robots[i].setChargingStatus(true);
      currBotsCharging_++;
    }
  }
  if (currBotsCharging_ == numSlotsCharging_) {
    for (int i = numRobots - 1; i >= 0; i--) {
      if (robots[i].getChargingStatus() &&
          robots[i].getRobotBattery() > minOperationalBattery_) {
        for (int j = 0; j < numRobots; j++) {
          if (!robots[j].getChargingStatus() &&
              robots[j].getRobotBattery() < minOperationalBattery_) {
            robots[j].setChargingStatus(true);
            robots[i].setChargingStatus(false);
            std::swap(robots[i], robots[j]);
          } else if (robots[i].getChargingStatus() &&
                     robots[i].getRobotBattery() >
                         maxOperationalBattery_ - chargingPercentage_) {
            currBotsCharging_--;
            robots[i].setChargingStatus(false);
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