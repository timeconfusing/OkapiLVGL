////////////////////////////////////////////////////////////////////////
//! @file: robot.h
//! @brief defines and prototypes for the robot
//
//  TODO:
//
//! @author RPM
//
//! @copyright Copyright 2019 RPM
//
//! @license MIT
//
////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory> // required for smart pointers
#include "main.h" // robot.h needs main for forwad declarations

#define LEFT_DRIVE_MOTOR1_PORT 11
#define LEFT_DRIVE_MOTOR2_PORT 20

#define RIGHT_DRIVE_MOTOR1_PORT 1
#define RIGHT_DRIVE_MOTOR2_PORT 10

#define DRIVE_GEARSET okapi::AbstractMotor::gearset::green
#define DRIVE_TPR okapi::imev5GreenTPR
#define DRIVE_GEARMOTOR 36.0
#define DRIVE_GEARWHEEL 36.0

#define CHASSIS_TRACK 10.5_in
#define CHASSIS_WHEELS 4.0_in
#define JOYSTICK_THRESHOLD 0.1  // okapi control uses 1,-1 range

// #define INTAKE_MOTOR0_PORT 13
// #define INTAKE_MOTOR1_PORT 3
// #define LIFT_MOTOR_PORT 5
// #define ARM_MOTOR_PORT 6

// Joystick drive control modes
#define TANK 0
#define ARCADE 1
#define SPLIT_ARCADE 2

extern int drive_control;

extern std::shared_ptr<okapi::Controller> joy1;
extern std::shared_ptr<okapi::ChassisController> chassis;
extern okapi::MotorGroup left_drive_motors;
extern okapi::MotorGroup right_drive_motors;
extern std::shared_ptr<okapi::AsyncMotionProfileController> profileControllerF;
extern std::shared_ptr<okapi::AsyncMotionProfileController> profileControllerM;
extern std::shared_ptr<okapi::AsyncMotionProfileController> profileControllerS;
