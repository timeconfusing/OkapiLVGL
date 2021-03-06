////////////////////////////////////////////////////////////////////////
//! @file: mab.c
//! @brief Match Autonomous Blue functions
//
// This is the collection of intermediate functions that call
// the actual auton function with the parameter BLUE. The actual
// auton function is written to work on the RED or BLUE side
// but the function pointer cannot pass that information so it
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

#include "robot.h"
#include "robot_gui.h"

void mabl1() {
 info_printf(1,"in mabl1");
 // example usage
 // match_auton1(BLUE); // mirror of RED right

 // velocity is in rpms which is dependent on the gear cartridge.
 double gearing = (double)left_drive_motors.getGearing();

 // test pathfinder using different profiles
 profileControllerF->generatePath({{0_in, 0_in, 0_deg}, {36_in, 0_in, 0_deg}}, "A");
 profileControllerF->setTarget("A");
 // path with one waypoint. all points are suppose to be relative to the first point
 // but to end close to x=0 from x=36 above, 24_in was needed. it should be noted
 // that the runs are consistent even if the points are not exact.
 profileControllerM->generatePath({{0_in, 0_in, 0_deg}, {10_in, 0_in, 0_deg}, {24_in, 28_in, 0_deg}}, "B");
 profileControllerF->waitUntilSettled();

 profileControllerM->setTarget("B", true); // true means to use the path in reverse
 profileControllerF->removePath("A");
 profileControllerF->generatePath({{0_in, 0_in, 0_deg}, {36_in, 0_in, 0_deg}}, "C");
 profileControllerM->waitUntilSettled();

 profileControllerF->setTarget("C");
 profileControllerM->removePath("B");
 profileControllerF->generatePath({{0_in, 0_in, 0_deg}, {24_in, 0_in, 0_deg}}, "D");
 profileControllerF->waitUntilSettled();

 profileControllerF->setTarget("D",true); // true means to use the path in reverse
 profileControllerF->removePath("C");
 profileControllerM->generatePath({{0_in, 0_in, 0_deg}, {12_in, 0_in, 0_deg}}, "E");
 profileControllerF->waitUntilSettled();

 chassis->setMaxVelocity(gearing*.66); // set the turn to be slower for more accuracy
 chassis->turnAngle(-270_deg);
 chassis->setMaxVelocity(gearing); // set veolcity back to full cartride value

 profileControllerM->setTarget("E");
 profileControllerM->waitUntilSettled();
 profileControllerM->removePath("E");
}

void mabl2() {
 info_printf(1,"in mabl2");

 // velocity is in rpms which is dependent on the gear cartridge.
 double gearing = (double)left_drive_motors.getGearing();

 // test pathfinder using different profiles
 profileControllerM->generatePath({{0_in, 0_in, 0_deg}, {36_in, 0_in, 0_deg}}, "A");
 profileControllerM->setTarget("A");
 profileControllerS->generatePath({{0_in, 0_in, 0_deg}, {32_in, 28_in, 0_deg}}, "B");
 profileControllerM->waitUntilSettled();

 profileControllerS->setTarget("B", true); // true means to use the path in reverse
 profileControllerM->removePath("A");
 profileControllerM->generatePath({{0_in, 0_in, 0_deg}, {36_in, 0_in, 0_deg}}, "C");
 profileControllerS->waitUntilSettled();

 profileControllerM->setTarget("C");
 profileControllerS->removePath("B");
 profileControllerM->generatePath({{0_in, 0_in, 0_deg}, {24_in, 0_in, 0_deg}}, "D");
 profileControllerM->waitUntilSettled();

 profileControllerM->setTarget("D",true); // true means to use the path in reverse
 profileControllerM->removePath("C");
 profileControllerS->generatePath({{0_in, 0_in, 0_deg}, {12_in, 0_in, 0_deg}}, "E");
 profileControllerM->waitUntilSettled();

 chassis->setMaxVelocity(gearing*.25); // set the turn to be slower for more accuracy
 chassis->turnAngle(-270_deg);
 chassis->setMaxVelocity(gearing); // set veolcity back to full cartride value

 profileControllerS->setTarget("E");
 profileControllerS->waitUntilSettled();
 profileControllerS->removePath("E");
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
 // example usage
 // match_auton2(BLUE); // mirror of RED right
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
