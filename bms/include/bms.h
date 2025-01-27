#include <params.h>

#include <algorithm>
#include <thread>
#include <vector>

namespace bms {

class BMS {
 public:
  BMS(float chargingPercentage, float dischargingPercentage,
      int numSlotsCharging)
      : chargingPercentage(chargingPercentage),
        dischargingPercentage(dischargingPercentage),
        numSlotsCharging(numSlotsCharging) {}

  void run(std::vector<utils::Robot> &robots);

  void stop();

  ~BMS() { stop(); }

 private:
  float chargingPercentage;     // per second
  float dischargingPercentage;  // per second
  int numSlotsCharging;         // charging slots

  int currBotsCharging = 0;
  bool flg_run_ = true;

  inline void chargingRobot(utils::Robot &robot);

  inline void dischargingRobot(utils::Robot &robot);
};

}  // namespace bms