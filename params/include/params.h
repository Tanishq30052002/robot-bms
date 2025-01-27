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
  inline float getChargingRate() const { return chargingRate; }
  inline float getDischargingRate() const { return dischargingRate; }
  inline int getChargingSpots() const { return chargingSpots; }

 private:
  std::string config_path;
  std::vector<utils::Robot> robots;

  float chargingRate = 1;
  float dischargingRate = 1.5;
  float minOperationalBattery = 20;
  int chargingSpots = 2;
};
}  // namespace params