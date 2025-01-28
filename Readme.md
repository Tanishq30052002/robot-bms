# Robot Battery Management System

## Introduction

This project maintains a fleet of 5 robots with varying battery levels in such a manner than no robot falls below a minimum battery level.

## Table of Contents

- [Introduction](#introduction)
- [Table of Contents](#table-of-contents)
- [Setup](#setup)
- [Usage](#usage)
- [Explanation of Code and Algorithm](#explanation-of-code-and-algorithm)

## Setup

### Building the Project

- Follow the steps to build the project
  ```bash
  cd
  git clone https://github.com/Tanishq30052002/robot-bms.git
  cd robot-bms
  mkdir build && cd build
  cmake .. && make -j`nproc`
  ```

## Usage

### Running the Project

- Follow the steps to run the project
  ```bash
  cd ~/robot-bms/build
  ./robot_bms config/bms.yaml
  ```

## Explanation of Code and Algorithm

### Code Structure

The project is organized into several directories:

- `bms` Contains the Battery Management System (BMS) implementation.
  - `include` Header files for the BMS.
  - `src` Source files for the BMS.
- `params` Contains parameter handling code.
  - `include` Header files for parameters.
  - `src` Source files for parameters.
- `utils` Contains utility functions and classes.
  - `include` Header files for utilities.
  - `src` Source files for utilities.
- `src` Contains the main entry point for the application.

### Algorithm

The main algorithm is implemented in the BMS::run method in the bms.cpp file. The algorithm performs the following steps:

1. **Sort Robots by Battery Level:** The robots are sorted in ascending order based on their battery levels.
2. **Allocate Charging Slots:** Available charging slots are allocated to robots with battery levels below the maximum operational battery threshold.
3. **Swap Robots if Charging Slots are Full:** If all charging slots are occupied, robots with low battery levels that are not charging are swapped with robots that are charging and have higher battery levels.
4. **Stop Charging Robots Near Maximum Battery:** Charging is stopped for robots whose battery levels are close to the maximum operational threshold to free up slots.
5. **Charge or Discharge Robots:** Robots are charged or discharged based on their charging status.

### Key Classes and Functions

- `bms::BMS:` Manages the charging and discharging of robots.

  - `BMS::run(std::vector<utils::Robot>& robots)utils::Robot& robots):` Main method that implements the algorithm.
  - `BMS::chargingRobot(utils::Robot& robot):` Charges a robot.
  - `BMS::dischargingRobot(utils::Robot& robot):` Discharges a robot.

- `params::Params:` Handles parameters from the configuration file.

  - `Params::getRobots(std::vector<utils::Robot>& robots)utils::Robot& robots):` Retrieves the list of robots from the configuration file.

- `utils::Robot:` Represents a robot with properties such as battery level and charging status.

  - `Robot::getRobotId() const:` Returns the robot's ID.
  - `Robot::getRobotBattery() const:` Returns the robot's battery level.
  - `Robot::getChargingStatus() const:` Returns the robot's charging status.

- `utils::printRobotBatteries(std::vector<utils::Robot>& robots):` Prints the battery levels of all robots.

#### Main Function

This main function sets up a signal handler, reads the configuration file, initializes the BMS and parameters, and runs the BMS algorithm in a loop, printing the battery levels of the robots at each iteration.

#### Special Note

In this project, there is a special case where the charging rate is 1% per robot and the discharging rate is 1.5% per robot. Given that 3 robots are discharging and 2 robots are charging at all times, no robot will reach its maximum battery level. This ensures a continuous cycle of charging and discharging, maintaining the battery levels within operational thresholds.
