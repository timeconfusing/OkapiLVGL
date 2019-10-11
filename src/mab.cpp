////////////////////////////////////////////////////////////////////////
//! @file: mab.c
//! @brief Match Autonomous Blue functions
//
// This is the collection of intermediate functions that call
// the actual auton function with the paramter BLUE. The actual
// auton function is written to work on the RED or BLUE side
// but the function point cannot pass that information so it
// is extracted from the mabl#/mabr# function. This indirection
// also allows for the adjustment of RED right and BLUE left being
// mirrors or RED right and BLUE right being mirrors.
//
//! @author
//
//! @copyright Copyright 2018 VEX Team 5090Z Radioactive
//
//! @license MIT
//
////////////////////////////////////////////////////////////////////////

#include "robot_gui.h"

void mabl1() {
 info_printf(1,"in mabl1");
 // example usage
 // match_auton1(BLUE); // mirror of RED right
}

void mabl2() {
 info_printf(1,"in mabl2");
}

void mabl3() {
 info_printf(1,"in mabl3");
}

void mabl4() {
 info_printf(1,"in mabl4");
}

void mabl5() {
 info_printf(1,"in mabl5");
}

void mabl6() {
 info_printf(1,"in mabl6");
}

void mabr1() {
 info_printf(1,"in mabr1");
}

void mabr2() {
 info_printf(1,"in mabr2");
}

void mabr3() {
 info_printf(1,"in mabr3");
}

void mabr4() {
 info_printf(1,"in mabr4");
}

void mabr5() {
 info_printf(1,"in mabr5");
}

void mabr6() {
 info_printf(1,"in mabr6");
}
