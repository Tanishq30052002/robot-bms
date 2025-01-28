#include <params.h>

#include <algorithm>
#include <thread>
#include <vector>

namespace bms {

class BMS {
 public:
  /**
   * @brief Construct a new BMS object
   *
   * @param config_path location for the configuration file
   */
  BMS(std::string config_path) {
    params::Params params_obj(config_path);
    chargingPercentage_ = params_obj.getChargingRate();
    dischargingPercentage_ = params_obj.getDischargingRate();
    minOperationalBattery_ = params_obj.getMinOperationalBattery();
    maxOperationalBattery_ = params_obj.getMaxOperationalBattery();
    numSlotsCharging_ = params_obj.getChargingSpots();
  }

  /**
   * @brief Manages the charging and discharging of robots based on their
   * battery levels, charging status, and available charging slots.
   *
   * This function performs the following steps:
   * 1. Sorts the robots by their battery levels in ascending order.
   * 2. Allocates available charging slots to robots with battery levels below
   * the maximum operational battery threshold.
   * 3. If all charging slots are occupied, swaps robots with low battery levels
   * that are not charging with robots that are charging and have higher battery
   * levels.
   * 4. Stops charging robots whose battery levels are close to the maximum
   * operational threshold to free up slots.
   * 5. Charges or discharges robots based on their charging status.
   *
   * @param robots A reference to a vector of `utils::Robot` objects. Each robot
   * has properties such as battery level, charging status, and methods to
   * modify these properties.
   */

  void run(std::vector<utils::Robot> &robots);

  /**
   * @brief Destroy the BMS object
   *
   */
  ~BMS() { std::cout << "[BMS::~BMS] Exiting the Robot BMS\n"; }

 private:
  float chargingPercentage_;     // per second
  float dischargingPercentage_;  // per second
  int numSlotsCharging_;         // charging slots
  float minOperationalBattery_;
  float maxOperationalBattery_;

  int currBotsCharging_ = 0;

  /**
   * @brief charges the robot
   *
   * @param robot
   */
  inline void chargingRobot(utils::Robot &robot);

  /**
   * @brief discharges the robot
   *
   * @param robot
   */
  inline void dischargingRobot(utils::Robot &robot);
};

}  // namespace bms