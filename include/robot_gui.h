////////////////////////////////////////////////////////////////////////
//! @file: robot_gui.h
//! @brief defines and prototypes for the robot GUI
//
//  TODO: ADD description
//
//! @author DSP
//
//! @copyright Copyright 2018 VEX Team 5090Z Radioactive
//
//! @license MIT
//
////////////////////////////////////////////////////////////////////////

#pragma once
/*********************
 *      INCLUDES
 *********************/
//#include "pros/apix.h"
#include "version.h"

/*********************
 *      DEFINES
 *********************/
#define MARL1_TEXT "MARL 1: F2, F1"
#define MARL2_TEXT "MARL 2: F2, F1, C3"
#define MARL3_TEXT "MARL 3: F2, F1, C3, C4"
#define MARL4_TEXT "MARL 4: Park"
#define MARL5_TEXT "MARL 5: C1, Park"
#define MARL6_TEXT "MARL 6: C1, C2, Park"

#define MARR1_TEXT "MARR 1: F2, F1"
#define MARR2_TEXT "MARR 2: F2, F1, C3"
#define MARR3_TEXT "MARR 3: F2, F1, C3, C4"
#define MARR4_TEXT "MARR 4: Park"
#define MARR5_TEXT "MARR 5: C1, Park"
#define MARR6_TEXT "MARR 6: C1, C2, Park"

#define MABL1_TEXT "MABL 1: F2, F1"
#define MABL2_TEXT "MABL 2: F2, F1, C3"
#define MABL3_TEXT "MABL 3: F2, F1, C3, C4"
#define MABL4_TEXT "MABL 4: Park"
#define MABL5_TEXT "MABL 5: C1, Park"
#define MABL6_TEXT "MABL 6: C1, C2, Park"

#define MABR1_TEXT "MABR 1: F2, F1"
#define MABR2_TEXT "MABR 2: F2, F1, C3"
#define MABR3_TEXT "MABR 3: F2, F1, C3, C4"
#define MABR4_TEXT "MABR 4: Park"
#define MABR5_TEXT "MABR 5: C1, Park"
#define MABR6_TEXT "MABR 6: C1, C2, Park"

#define ITAB 0
#define TTAB 1

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void info_printf(int label_line, const char *format, ...);
void telm_printf(int label_line, const char *format, ...);
void robot_gui(void);

extern void (*auton_ptr)(void);
void auton_non(void);

void marl1();
void marl2();
void marl3();
void marl4();
void marl5();
void marl6();

void marr1();
void marr2();
void marr3();
void marr4();
void marr5();
void marr6();

void mabl1();
void mabl2();
void mabl3();
void mabl4();
void mabl5();
void mabl6();

void mabr1();
void mabr2();
void mabr3();
void mabr4();
void mabr5();
void mabr6();

/**********************
 *      MACROS
 **********************/
