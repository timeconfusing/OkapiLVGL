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

#include "main.h"

void marl1() {
 info_printf(2,"in marl1");
}

void marl2() {
 info_printf(1,"in marl2");
}

void marl3() {
 info_printf(1,"in marl3");
}

void marl4() {
 info_printf(1,"in marl4");
}

void marl5() {
 info_printf(1,"in marl5");
}

void marl6() {
 info_printf(1,"in marl6");
 info_printf(2,"  I: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
 chassis->turnAngle(90_deg);
 info_printf(3," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
 chassis->turnAngle(90_deg);
 info_printf(4," 90: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
 chassis->turnAngle(180_deg);
 info_printf(5,"180: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
 chassis->turnAngle(-360_deg);
 info_printf(6,"360: LDP=%f, RDP=%f",left_drive_motors.getPosition(),right_drive_motors.getPosition());
}

void marr1() {
 info_printf(1,"in marr1");
 // example usage
 // match_auton1(RED); // mirror of BLUE left
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
