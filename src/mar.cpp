////////////////////////////////////////////////////////////////////////
//! @file: mar.c
//! @brief Match Autonomous RED functions
//
// This is the collection of intermediate functions that call
// the actual auton function with the paramter RED. The actual
// auton function is written to work on the RED or BLUE side
// but the function point cannot pass that information so it
// is extracted from the mabl#/mabr# function. This indirection
// also allows for the adjustment of RED right and BLUE left being
// mirrors or RED right and BLUE right being mirrors.
//
//! @author DSP
//
//! @copyright Copyright 2018 VEX Team 5090Z Radioactive
//
//! @license MIT
//
////////////////////////////////////////////////////////////////////////

#include "robot.h"
#include "robot_gui.h"

void marl1() {
 info_printf(2,"in marl1");
 // example usage
 // match_auton2(RED); // mirror of BLUE right
}

void marl2() {
 info_printf(1,"in marl2");
}

void marl3() {
  double gearing = (double)left_drive_motors.getGearing();
  //chassis->setMaxVoltage(12000); // in case this is run from opcontrol
  info_printf(1,"in marl4: Gearing=%3.2d",gearing);
  chassis->setMaxVelocity(gearing*1.0); // see if speed affects turning
  info_printf(2,"  I: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(90.0_deg);
  info_printf(3," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(90.0_deg);
  info_printf(4," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(180.0_deg);
  info_printf(5,"180: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(-360.0_deg);
  info_printf(6,"360: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());

  chassis->setMaxVelocity(gearing);
}

void marl4() {
  double gearing = (double)left_drive_motors.getGearing();
  //chassis->setMaxVoltage(12000); // in case this is run from opcontrol
  info_printf(1,"in marl4: Gearing=%3.2d",gearing);
  chassis->setMaxVelocity(gearing*0.75); // see if speed affects turning
  info_printf(2,"  I: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(90.0_deg);
  info_printf(3," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(90.0_deg);
  info_printf(4," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(180.0_deg);
  info_printf(5,"180: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(-360.0_deg);
  info_printf(6,"360: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());

  chassis->setMaxVelocity(gearing);
}

void marl5() {
  double gearing = (double)left_drive_motors.getGearing();
  //chassis->setMaxVoltage(12000); // in case this is run from opcontrol
  info_printf(1,"in marl5: Gearing=%3.2d",gearing);
  chassis->setMaxVelocity(gearing*0.5); // see if speed affects turning
  info_printf(2,"  I: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(90.0_deg);
  info_printf(3," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(90.0_deg);
  info_printf(4," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(180.0_deg);
  info_printf(5,"180: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
  chassis->turnAngle(-360.0_deg);
  info_printf(6,"360: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());

  chassis->setMaxVelocity(gearing);
}

void marl6() {
 double gearing = (double)left_drive_motors.getGearing();
 //chassis->setMaxVoltage(12000); // in case this is run from opcontrol
 info_printf(1,"in marl6: Gearing=%3.2d",gearing);
 chassis->setMaxVelocity(gearing*0.25); // see if speed affects turning
 info_printf(2,"  I: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
 chassis->turnAngle(90.0_deg);
 info_printf(3," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
 chassis->turnAngle(90.0_deg);
 info_printf(4," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
 chassis->turnAngle(180.0_deg);
 info_printf(5,"180: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
 chassis->turnAngle(-360.0_deg);
 info_printf(6,"360: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());

 chassis->setMaxVelocity(gearing);
}

void marr1() {
 info_printf(1,"in marr1");
 // example usage
 // match_auton1(RED); // mirror of BLUE leftY
}

void marr2() {
 info_printf(1,"in marr2");
}

void marr3() {
 info_printf(1,"in marr3");
}

void marr4() {
 info_printf(1,"in marr4");
}

void marr5() {
 info_printf(1,"in marr5");
}

void marr6() {
 info_printf(1,"in marr6");
}
