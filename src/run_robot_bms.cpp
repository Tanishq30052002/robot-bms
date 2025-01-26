#include <signal.h>

#include <bms.cpp>

bool flg_run = true;
void signal_callback_handler(int signal) {
  flg_run = false;
  if (signal == SIGINT)
    std::cout << "[main] Exiting on SIGINT\n";
  else {
    std::cout << "[main] Exiting on Abort or Seg-Fault\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main() {
  signal(SIGINT, signal_callback_handler);

  std::vector<utils::Robot> robots;
  robots.emplace_back(utils::Robot(1, 10, false));
  robots.emplace_back(utils::Robot(2, 20, false));
  robots.emplace_back(utils::Robot(3, 20, false));
  robots.emplace_back(utils::Robot(4, 40, false));
  robots.emplace_back(utils::Robot(5, 40, false));

  float chargingPercentage = 1.5;   // %/sec
  float dischargingPercentage = 1;  // %/sec
  int SlotsCharging = 2;

  bms::BMS robotBMS(chargingPercentage, dischargingPercentage, SlotsCharging);

  while (flg_run) {
    utils::printRobotBatteries(robots);
    robotBMS.run(robots);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}