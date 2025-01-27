#include <utils.h>
#include <yaml-cpp/yaml.h>
// #include <yaml.h>

namespace params {
class Params {
 public:
  Params(const std::string &config_path) : config_path(config_path) {
    readConfigFile(config_path);
  }

  void readConfigFile(std::string config_path);

  inline void getRobots(std::vector<utils::Robot> &robots) {
    robots = this->robots;
  }
  inline float getChargingRate() const { return chargingRate_; }
  inline float getDischargingRate() const { return dischargingRate_; }
  inline float getMinOperationalBattery() const {
    return minOperationalBattery_;
  }
  inline float getMaxOperationalBattery() const {
    return maxOperationalBattery_;
  }
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