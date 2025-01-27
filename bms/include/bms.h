#include <params.h>

#include <algorithm>
#include <thread>
#include <vector>

namespace bms {

class BMS {
 public:
  BMS(std::string config_path) {
    params::Params params_obj(config_path);
    chargingPercentage_ = params_obj.getChargingRate();
    dischargingPercentage_ = params_obj.getDischargingRate();
    minOperationalBattery_ = params_obj.getMinOperationalBattery();
    maxOperationalBattery_ = params_obj.getMaxOperationalBattery();
    numSlotsCharging_ = params_obj.getChargingSpots();
  }

  void run(std::vector<utils::Robot> &robots);

  void stop();

  ~BMS() { stop(); }

 private:
  float chargingPercentage_;     // per second
  float dischargingPercentage_;  // per second
  int numSlotsCharging_;         // charging slots
  float minOperationalBattery_;
  float maxOperationalBattery_;

  int currBotsCharging_ = 0;

  inline void chargingRobot(utils::Robot &robot);

  inline void dischargingRobot(utils::Robot &robot);
};

}  // namespace bms