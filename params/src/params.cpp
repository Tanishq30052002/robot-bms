#include <params.h>
namespace params {

void params::Params::readConfigFile(std::string config_path) {
  YAML::Node configFile;

  try {
    YAML::Node config = YAML::LoadFile(config_path);

    // Read robots
    const auto& robot_list = config["robots"];
    for (const auto& robot : robot_list) {
      robots.emplace_back(utils::Robot(
          robot["id"].as<int>(), robot["battery_level"].as<float>(), false));
    }

    // Read constraints
    dischargingRate = config["constraints"]["discharging_rate"].as<float>();
    chargingRate = config["constraints"]["charging_rate"].as<float>();
    chargingSpots = config["constraints"]["charging_spots"].as<int>();
    minOperationalBattery =
        config["constraints"]["min_operational_battery"].as<float>();

  } catch (const YAML::Exception& e) {
    std::cerr << "Error reading config file: " << e.what() << std::endl;
  }
}
}  // namespace params