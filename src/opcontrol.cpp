////////////////////////////////////////////////////////////////////////
//! @file: opcontrol.c
//! @brief Operator Control: provides an example of Okapi Chassis control
//         across multiple files for use with OpControl and Auton functions
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

// joy1 def can be inside opcontrol() b/c it is not used elsewhere. if it is
// then buttons probably need to be declared in robot.h and defined here.
std::shared_ptr<okapi::Controller> joy1(nullptr);

// define the motor groups and chassis controller here so they can be used in any file (including robot.h via main.h).
// the minus, "-", makes the right side the reverse of the left side.
//
#ifdef LEFT_DRIVE_MOTOR2_PORT
okapi::MotorGroup left_drive_motors({LEFT_DRIVE_MOTOR1_PORT, LEFT_DRIVE_MOTOR2_PORT});
okapi::MotorGroup right_drive_motors({-RIGHT_DRIVE_MOTOR1_PORT, -RIGHT_DRIVE_MOTOR2_PORT});
#else
okapi::MotorGroup left_drive_motors({LEFT_DRIVE_MOTOR1_PORT});
okapi::MotorGroup right_drive_motors({-RIGHT_DRIVE_MOTOR1_PORT});
#endif

// hey what happened to using GearsetRatioPair on the chassis?
okapi::AbstractMotor::GearsetRatioPair drive_ratio = okapi::AbstractMotor::gearset::DRIVE_GEARSET * (DRIVE_GEARWHEEL/DRIVE_GEARMOTOR);
std::shared_ptr<okapi::ChassisController> chassis = okapi::ChassisControllerBuilder()
    .withMotors(left_drive_motors,right_drive_motors)
    .withDimensions(okapi::AbstractMotor::gearset::DRIVE_GEARSET,{{CHASSIS_WHEELS, CHASSIS_TRACK}, DRIVE_TPR})
    .build();

// each parameter should be measured (or calculated) but can have individual scaling
// multple controllers can be defined for different uses for instance performing turns more slowly
std::shared_ptr<okapi::AsyncMotionProfileController> profileControllerF = okapi::AsyncMotionProfileControllerBuilder()
  .withLimits({ 1.06 * 0.9,  // Maximum linear velocity of the Chassis in m/s
                2.00 * 0.9,  // Maximum linear acceleration of the Chassis in m/s/s
               10.00 * 0.9}) // Maximum linear jerk of the Chassis in m/s/s/s
  .withOutput(*chassis) // Chassis Controller
  .buildMotionProfileController();

std::shared_ptr<okapi::AsyncMotionProfileController> profileControllerM = okapi::AsyncMotionProfileControllerBuilder()
  .withLimits({ 1.06 * 0.66,  // Maximum linear velocity of the Chassis in m/s
                2.00 * 0.66,  // Maximum linear acceleration of the Chassis in m/s/s
               10.00 * 0.66}) // Maximum linear jerk of the Chassis in m/s/s/s
  .withOutput(*chassis) // Chassis Controller
  .buildMotionProfileController();

std::shared_ptr<okapi::AsyncMotionProfileController> profileControllerS = okapi::AsyncMotionProfileControllerBuilder()
  .withLimits({ 1.06 * 0.4,  // Maximum linear velocity of the Chassis in m/s
                2.00 * 0.4,  // Maximum linear acceleration of the Chassis in m/s/s
               10.00 * 0.4}) // Maximum linear jerk of the Chassis in m/s/s/s
  .withOutput(*chassis) // Chassis Controller
  .buildMotionProfileController();

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  bool toggle_speed=1;

  joy1 = std::make_shared<okapi::Controller>(okapi::ControllerId::master);
  okapi::ControllerButton toggle_break_mode_btn(okapi::ControllerId::master, okapi::ControllerDigital::A);
  okapi::ControllerButton toggle_drive_control(okapi::ControllerId::master, okapi::ControllerDigital::B);
  okapi::ControllerButton toggle_speed_control(okapi::ControllerId::master, okapi::ControllerDigital::X);
  okapi::ControllerButton generate_master_rumble(okapi::ControllerId::master, okapi::ControllerDigital::Y);

  joy1->clear();
  // okapi::ControllerButton lift_up_btn(okapi::ControllerId::master, okapi::ControllerDigital::L1);
  // okapi::ControllerButton lift_dn_btn(okapi::ControllerId::master, okapi::ControllerDigital::L2);
  // okapi::ControllerButton arm_forward_btn(okapi::ControllerId::master, okapi::ControllerDigital::R1);
  // okapi::ControllerButton arm_backward_btn(okapi::ControllerId::master, okapi::ControllerDigital::R2);
  // okapi::ControllerButton intake_in_btn(okapi::ControllerId::master, okapi::ControllerDigital::up);
  // okapi::ControllerButton intake_out_btn(okapi::ControllerId::master, okapi::ControllerDigital::down);

	while (true) {

    // test auton without a comp switch
    // see ma**_btnm_action in robot_gui_.cpp for go=1
    // this is not match tested but should be fine for competition
    if (auton_go) {
       auton_ptr();
       auton_go=0;
    }

    // select between Tank, Arcade and Split Arcade (joy4=forward/reverse, joy1=left/right)
    // use changedToPressed() instead of isPressed() since this is a toggle select
    // the former will only be true once per press while the later will be true as long as the button is pressed
    if (toggle_drive_control.changedToPressed()) {
      if (drive_control == TANK) {
        drive_control = ARCADE;
        info_printf(2,"Arcade Drive");
        joy1->setText(0, 0, "Arcade Drive"); // joystick display can't update faster than 50ms
      } else if (drive_control == ARCADE) {
         drive_control = SPLIT_ARCADE;
         info_printf(2,"Split Arcade Drive");
         joy1->setText(0, 0, "Split Arcade");
      } else {
       drive_control = TANK;
       info_printf(2,"Tank Drive");
       joy1->setText(0, 0, "Tank Drive  "); // add space(s) to make sure char count is same
      }
    }

    // switch between the driver control modes as selected above
    if (drive_control == SPLIT_ARCADE) {
      chassis->getModel()->arcade(joy1->getAnalog(okapi::ControllerAnalog::leftY),
                      joy1->getAnalog(okapi::ControllerAnalog::rightX),
                      JOYSTICK_THRESHOLD);
    } else if (drive_control == ARCADE) {
      chassis->getModel()->arcade(joy1->getAnalog(okapi::ControllerAnalog::rightY),
                      joy1->getAnalog(okapi::ControllerAnalog::rightX),
                      JOYSTICK_THRESHOLD);
    } else {
      chassis->getModel()->tank(joy1->getAnalog(okapi::ControllerAnalog::leftY),
                    joy1->getAnalog(okapi::ControllerAnalog::rightY),
                    JOYSTICK_THRESHOLD);
    }

    // select between and switch to the different brake modes
    if (toggle_break_mode_btn.changedToPressed()) {
      if (right_drive_motors.getBrakeMode() == okapi::AbstractMotor::brakeMode::coast) {
        left_drive_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
        right_drive_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
        info_printf(3,"BrakeMode: Brake");
        joy1->setText(1, 0, "BrakeMode: Brake");
      } else if (right_drive_motors.getBrakeMode() == okapi::AbstractMotor::brakeMode::brake) {
        left_drive_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        right_drive_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
        info_printf(3,"BrakeMode: Hold");
        joy1->setText(1, 0, "BrakeMode: Hold "); // add space(s) to make sure char count is same
      } else {
        left_drive_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
        right_drive_motors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
        info_printf(3,"BrakeMode: Coast");
        joy1->setText(1, 0, "BrakeMode: Coast");
      }
    }

    // select between and switch to the different drive speed
    if (toggle_speed_control.changedToPressed()) {
      if (toggle_speed) {
        chassis->getModel()->setMaxVoltage(6000); // setMaxVelocity is not applied to Tank or Arcade drive
        info_printf(4,"Half Speed");
        joy1->setText(2, 0, "Half Speed");
      }  else {
        chassis->getModel()->setMaxVoltage(12000); // setMaxVelocity is not applied to Tank or Arcade drive
        info_printf(4,"Full Speed");
        joy1->setText(2, 0, "Full Speed");
      }
      toggle_speed = !toggle_speed;
    }

    // it appears the joy cannot take another access (rumble or text) until
    // then proir access (rumble or text) completes
    if (generate_master_rumble.changedToPressed()) {
      joy1->rumble("- . -"); // long, pause, short, pause, long
    }

		pros::delay(20);
	}
}
