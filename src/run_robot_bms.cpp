#include <signal.h>

#include <bms.cpp>

bool flg_run = true;
void signal_callback_handler(int signal) {
  flg_run = false;
  if (signal == SIGINT)
    std::cout << "[run_robot_bms] Exiting on SIGINT\n";
  else {
    std::cout << "[run_robot_bms] Exiting on Abort or Seg-Fault\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main(int argc, char** argv) {
  signal(SIGINT, signal_callback_handler);

  if (argc < 2) {
    std::cout << "[run_robot_bms] Usage:\n"
              << argv[0] << " <path to config file>";
    return 1;
  }

  params::Params params_obj(argv[1]);
  bms::BMS robotBMS(params_obj.getChargingRate(),
                    params_obj.getDischargingRate(),
                    params_obj.getChargingSpots());

  std::vector<utils::Robot> robots;
  params_obj.getRobots(robots);

  while (flg_run) {
    utils::printRobotBatteries(robots);
    robotBMS.run(robots);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}