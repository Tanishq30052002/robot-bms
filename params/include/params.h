#include <utils.h>
#include <yaml-cpp/yaml.h>
// #include <yaml.h>

namespace params {
class Params {
 public:
  /**
   * @brief Construct a new Params object
   *
   * @param config_path location of the config file
   */
  Params(const std::string &config_path) : config_path(config_path) {
    readConfigFile(config_path);
  }

  /**
   * @brief read the parameters from the config file
   *
   * @param config_path
   */
  void readConfigFile(std::string config_path);

  /**
   * @brief Get the Robots from the config file
   *
   * @param robots
   */
  inline void getRobots(std::vector<utils::Robot> &robots) {
    robots = this->robots;
  }

  /**
   * @brief Get the Charging Rate from the config file
   *
   * @return float
   */
  inline float getChargingRate() const { return chargingRate_; }

  /**
   * @brief Get the Discharging Rate from the config file
   *
   * @return float
   */
  inline float getDischargingRate() const { return dischargingRate_; }

  /**
   * @brief Get the Min Operational Battery from the config file
   *
   * @return float
   */
  inline float getMinOperationalBattery() const {
    return minOperationalBattery_;
  }

  /**
   * @brief Get the Max Operational Battery from the config file
   *
   * @return float
   */
  inline float getMaxOperationalBattery() const {
    return maxOperationalBattery_;
  }

  /**
   * @brief Get the Charging Spots from the config file
   *
   * @return int
   */
  inline int getChargingSpots() const { return chargingSpots_; }

 private:
  std::string config_path;
  std::vector<utils::Robot> robots;

  float chargingRate_ = 1;
  float dischargingRate_ = 1.5;
  float minOperationalBattery_ = 20;
  float maxOperationalBattery_ = 100;
  int chargingSpots_ = 2;
};
}  // namespace params