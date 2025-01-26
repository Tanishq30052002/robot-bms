#include <signal.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

bool flg_run = true;
void signal_callback_handler(int signal) {
  flg_run = true;
  if (signal == SIGINT)
    std::cout << "[main] Exiting on SIGINT";
  else {
    std::cout << "[main] Exiting on Abort or Seg-Fault";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

typedef struct Robot {
  int id;
  float battery;
  bool status;

  Robot(int id, float battery, bool status) {
    this->id = id;
    this->battery = battery;
    this->status = status;
  }
} Robot;

void printRobotBatteries(std::vector<Robot> &robots) {
  // Sort the bots in increasing order based on the id
  sort(robots.begin(), robots.end(),
       [](Robot &robot1, Robot &robot2) { return robot1.id < robot2.id; });

  for (int i = 0; i < robots.size(); i++) {
    std::cout << "Robot " << std::setw(2) << robots[i].id << ": ("
              << std::setw(6) << robots[i].battery << ", " << std::setw(1)
              << robots[i].status << ")";

    if (i != robots.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
}

class BMS {
 public:
  BMS() {}

  void run(std::vector<Robot> &robots) {
    // Sort the bots in increasing order based on the battery
    sort(robots.begin(), robots.end(), [](Robot &robot1, Robot &robot2) {
      return robot1.battery < robot2.battery;
    });

    // set bots with min charge to charging
    if (currBotsCharging < numSlotsCharging) {
      for (int i = 0; i < numSlotsCharging; i++) {
        robots[i].status = true;
        currBotsCharging++;
      }
    } else {
      for (int i = robots.size() - 1; i >= 0; i--) {
        //   until the bot which is getting charged reaches min of 20 percent
        //   battery, keep it charging

        // currently the bot is charging but it is more than min charge so it
        // can be replaced if wish so
        if (robots[i].status && robots[i].battery > 20) {
          for (int j = 0; j < robots.size(); j++) {
            // check for bots which are not charging and needs to be swap
            if (!robots[j].status && robots[j].battery < 20) {
              robots[j].status = true;
              robots[i].status = false;
              std::swap(robots[i], robots[j]);
            }
          }
        }
      }
    }

    for (auto &robot : robots) {
      if (robot.status)
        chargingRobot(robot);
      else
        dischargingRobot(robot);
    }
  }

  ~BMS() {}

 private:
  int currBotsCharging = 0;
  int numSlotsCharging = 2;

  void chargingRobot(Robot &robot) { robot.battery = robot.battery + 1.5; }
  void dischargingRobot(Robot &robot) { robot.battery = robot.battery - 1; }
};

int main() {
  std::vector<Robot> robots;
  robots.emplace_back(Robot(1, 10, false));
  robots.emplace_back(Robot(2, 20, false));
  robots.emplace_back(Robot(3, 20, false));
  robots.emplace_back(Robot(4, 40, false));
  robots.emplace_back(Robot(5, 40, false));

  BMS robotBMS;

  while (flg_run) {
    printRobotBatteries(robots);
    robotBMS.run(robots);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  robotBMS.~BMS();

  return 0;
}