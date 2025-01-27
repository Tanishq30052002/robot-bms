#include <params.h>

#include <algorithm>
#include <thread>
#include <vector>

namespace bms {

class BMS {
 public:
  BMS(std::string config_path) {
    params::Params params_obj(config_path);
    chargingPercentage = params_obj.getChargingRate();
    dischargingPercentage = params_obj.getDischargingRate();
    minOperationalBattery = params_obj.getMinOperationalBattery();
    maxOperationalBattery = params_obj.getMaxOperationalBattery();
    numSlotsCharging = params_obj.getChargingSpots();
  }

  void run(std::vector<utils::Robot> &robots);

  void stop();

  ~BMS() { stop(); }

 private:
  float chargingPercentage;     // per second
  float dischargingPercentage;  // per second
  int numSlotsCharging;         // charging slots
  float minOperationalBattery;
  float maxOperationalBattery;

  int currBotsCharging = 0;
  bool flg_run_ = true;

  inline void chargingRobot(utils::Robot &robot);

  inline void dischargingRobot(utils::Robot &robot);
};

}  // namespace bms