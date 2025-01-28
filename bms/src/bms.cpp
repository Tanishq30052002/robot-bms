#include <bms.h>
namespace bms {

void BMS::chargingRobot(utils::Robot &robot) {
  robot.setRobotBattery(robot.getRobotBattery() + chargingPercentage_);
}

void BMS::dischargingRobot(utils::Robot &robot) {
  robot.setRobotBattery(robot.getRobotBattery() - dischargingPercentage_);
}

void BMS::run(std::vector<utils::Robot> &robots) {
  // Sort the robots based on their battery levels
  sort(robots.begin(), robots.end(),
       [](utils::Robot &robot1, utils::Robot &robot2) {
         return robot1.getRobotBattery() < robot2.getRobotBattery();
       });

  int numRobots = robots.size();  // Number of robots

  // if charging slots are available, charge the robots which are below the max
  // operational battery
  for (int i = 0; i < numRobots; i++) {
    if (currBotsCharging_ < numSlotsCharging_ &&
        !robots[i].getChargingStatus() &&
        robots[i].getRobotBattery() <
            (maxOperationalBattery_ - chargingPercentage_)) {
      robots[i].setChargingStatus(true);
      currBotsCharging_++;  // Increment the number of robots charging
    }
  }

  // If all the charging slots are occupied, then swap the robots based on the
  // battery levels
  if (currBotsCharging_ == numSlotsCharging_) {
    // Iterate through the robots in reverse order to find the robot which is
    // being charged and has a battery level above the minimum. also since we
    // iterate in reverse order the robot with the high battery level amongst
    // charging robots will be used for swapping
    for (int i = numRobots - 1; i >= 0; i--) {
      if (robots[i].getChargingStatus() &&
          robots[i].getRobotBattery() > minOperationalBattery_) {
        // Iterate through the robots to find the robot which is not charging in
        // increasing order so that the robot with minimum battery level can be
        // swapped with the robot who is being charged and has high battery
        // level
        for (int j = 0; j < numRobots; j++) {
          if (!robots[j].getChargingStatus() &&
              robots[j].getRobotBattery() < minOperationalBattery_) {
            robots[j].setChargingStatus(true);
            robots[i].setChargingStatus(false);
            // Swap the charging robot with the robot which is not charging
            std::swap(robots[i], robots[j]);
          }
          // If the robot is being charged and has a battery level which can be
          // reached to max in a next iteration then stop charging and empty the
          // slot
          else if (robots[i].getChargingStatus() &&
                   robots[i].getRobotBattery() >
                       maxOperationalBattery_ - chargingPercentage_) {
            currBotsCharging_--;  // empty the slot
            robots[i].setChargingStatus(false);
          }
        }
      }
    }
  }

  // Charge or discharge the robots based on their charging status
  for (auto &robot : robots) {
    if (robot.getChargingStatus())
      chargingRobot(robot);  // Charge the robot
    else
      dischargingRobot(robot);  // Discharge the robot
  }
}

}  // namespace bms