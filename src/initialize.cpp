////////////////////////////////////////////////////////////////////////
//! @file: initialize.c
//! @brief Initialize the robot
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
#include "robot.h"
#include "robot_gui.h"

int drive_control;

// live_telemetry; a function intended to run as a task to display live value of sensor pedantically
// param: required by pros::Task but not used
void live_telemetry(void* param) {
  while (1) {
    telm_printf(1,"  LDPos=%f, RDPos=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
    telm_printf(2,"  LDVel=%f, RDVel=%f",left_drive_motors.getActualVelocity(),right_drive_motors.getActualVelocity());
    telm_printf(3,"  LDCur=%d, RDCur=%d",left_drive_motors.getCurrentDraw(),right_drive_motors.getCurrentDraw());
    telm_printf(4,"  BMode=%s",right_drive_motors.getBrakeMode() == okapi::AbstractMotor::brakeMode::hold ? "Hold" : "Coast");
    telm_printf(5,"  Left Vel=%3.0f, Right Vel=%3.0f",left_drive_motors.getActualVelocity(),right_drive_motors.getActualVelocity());

    pros::Task::delay(50);
  }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::delay(50); // sometimes LVGL won't draw the screen if there is no delay or it is not inverted on the brain
  robot_gui();
	auton_ptr = &auton_non;
  auton_go = 0;

  drive_control = TANK;

  // intialize drive motor encoder positions and set default brake mode
  left_drive_motors.tarePosition();
  left_drive_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  right_drive_motors.tarePosition();
  right_drive_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

  // okapi::AbstractMotor::GearsetRatioPair drive_ratio = okapi::AbstractMotor::gearset::DRIVE_GEARSET * (DRIVE_GEARWHEEL/DRIVE_GEARMOTOR);
  // auto my_chassis = okapi::ChassisControllerBuilder()
  //     .withMotors(left_drive_motors,right_drive_motors)
  //     .withGearset(drive_ratio)
  //     .withDimensions({{CHASSIS_WHEELS, CHASSIS_TRACK}, DRIVE_TPR})
  //     .build();
  //
  // chassis = my_chassis;
  // start the display live telematry task
  pros::Task telm_task (live_telemetry, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "telm");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
