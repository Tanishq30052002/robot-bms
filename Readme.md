# Robot Battery Management System

## Introduction

This project maintains a fleet of 5 robots with varying battery levels in such a manner than no robot falls below a minimum battery level.

## Table of Contents

- [Introduction](#introduction)
- [Table of Contents](#table-of-contents)
- [Setup](#setup)
- [Usage](#usage)

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
