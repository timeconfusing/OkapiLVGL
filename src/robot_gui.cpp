////////////////////////////////////////////////////////////////////////
//! @file: robot_gui.cpp
//! @brief The robot GUI for selecting Autonomous and displaying info
//
//   1) Autonomous selection for each of the 4 starting places:
//   Red Left, Red Right, Blue Left and Blue Right. Each location
//   has 6 autonomous programs that can be selected via the associated
//   tab and button matrix.
//
//   2) Includes an info tab for general information to be displayed
//
//   functionality added by RPM
//   3) Includes an telm tab for telemetry information to be displayed (copy of info_printf)
//
//   4) opcontrol initiation of auton program
//
//! @author: DSP, with minor update by RPM
//
//! @copyright Copyright 2018 VEX Team 5090Z Radioactive
//
//! @license MIT
//
////////////////////////////////////////////////////////////////////////

/*********************
 *      INCLUDES
 *********************/
#include "main.h"
#include "robot_gui.h"
#include <stdio.h>
#include <stdarg.h>

/*********************
 *      DEFINES
 *********************/
#define INFO_LINES 8
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void marl_create(lv_obj_t *parent);
static void marr_create(lv_obj_t *parent);
static void mabl_create(lv_obj_t *parent);
static void mabr_create(lv_obj_t *parent);
static void info_create(lv_obj_t *parent);
static void telm_create(lv_obj_t *parent);

static lv_res_t marl_btnm_action(lv_obj_t * btnm, const char *txt);
static lv_res_t marr_btnm_action(lv_obj_t * btnm, const char *txt);
static lv_res_t mabl_btnm_action(lv_obj_t * btnm, const char *txt);
static lv_res_t mabr_btnm_action(lv_obj_t * btnm, const char *txt);

/**********************
 *  VARIABLES
 **********************/
static lv_obj_t *g_tv_region; //tab view region of the screen
static lv_obj_t *g_sb_region; //status bar region of the screen
static lv_obj_t *g_sb_label;
static lv_obj_t *g_info_label; // info
static lv_obj_t *g_telm_label; // telemetry

int g_tv_tab_height;

int auton_go; // global variable to start a selected auton during opcontrol

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

// the default function assigned to auton_ptr
// this goes in competition_initialize()
// auton_ptr = &auton_non;
void auton_non()
{
//  static long cnt = 0;
//  info_printf(1, "auton non %d", cnt++);
}

// function pointer so linker see a function
// the gcc linker on the pc doesn't need this
void (*auton_ptr)(void);

//
// info_printf; a printf like function to print a formatted string to a line in the info tab.
// line: range = 1 to INFO_LINES
// format, ... : just like printf  -- dont use \n
// based on information at http://www.cplusplus.com/reference/cstdio/vsnprintf/
// print a formatted string to a sized buffer.
void info_printf(int line, const char * format, ...) {
	// holds the strings of each line in a 2d array of chars
	// b/c only the specified line is updated and keep the other lines unchanged
	static char buffer[INFO_LINES][64] = { "" };

	// lv_label_set_text() takes a simple string. copy the 2d buffer in to this string
	char info[INFO_LINES * 64];

	// makes sure line is in range
	if ((line >= 1) || (line <= INFO_LINES))
	{
		va_list args;
		va_start(args, format);
		vsnprintf(buffer[line], 63, format, args); // 63 b/c reserve a spot for newline char
		// perror(buffer[line]);
		va_end(args);

		strcpy(info, ""); // info must be empty before we write each buffer line to it
		for (int i = 1; i <= INFO_LINES; i++) {
			strcat(info, buffer[i]);
			strcat(info, "\n"); // makes sure each buffer is on it a new line
		}
	  lv_label_set_text(g_info_label, info);
	}
} //end info_printf

//
// telm_printf; a printf like function to print a formatted string to a line in the info tab.
// line: range = 1 to INFO_LINES
// format, ... : just like printf  -- dont use \n
// based on information at http://www.cplusplus.com/reference/cstdio/vsnprintf/
// print a formatted string to a sized buffer.
void telm_printf(int line, const char * format, ...) {
	// holds the strings of each line in a 2d array of chars
	// b/c only the specified line is updated and keep the other lines unchanged
	static char buffer[INFO_LINES][64] = { "" };

	// lv_label_set_text() takes a simple string. copy the 2d buffer in to this string
	char info[INFO_LINES * 64];

	// makes sure line is in range
	if ((line >= 1) || (line <= INFO_LINES))
	{
		va_list args;
		va_start(args, format);
		vsnprintf(buffer[line], 63, format, args); // 63 b/c reserve a spot for newline char
		// perror(buffer[line]);
		va_end(args);

		strcpy(info, ""); // info must be empty before we write each buffer line to it
		for (int i = 1; i <= INFO_LINES; i++) {
			strcat(info, buffer[i]);
			strcat(info, "\n"); // makes sure each buffer is on it a new line
		}
    lv_label_set_text(g_telm_label, info);
	}
} //end telm_printf


/**********************
 *   LOCAL FUNCTIONS
 **********************/

// most of the code in this file is copied from LVGL examples and expanded or
// contracted as needed.
// styles however proved much more confusing since the documentation is not complete.
// color settings are fairly obvious or at least trial and error worked quickly.
// alignmnet, padding and border sizing took a long time to get right.

// styles create clutter, this makes functional code harder to read. by putting our
// styles here our functions will be easer to read

// set the style for the tab view 5090 colors, square tabs (aka buttons)
void set_tv_style(lv_obj_t *tv) {
	// set the style of the tab view background
	static lv_style_t style_tv_bg;
	lv_style_copy(&style_tv_bg, &lv_style_plain);
	style_tv_bg.body.main_color = LV_COLOR_BLACK;
	style_tv_bg.body.grad_color = LV_COLOR_BLACK;
	//   style_tv_bg.body.padding.hor = 0;  // no noticeable difference
	//   style_tv_bg.body.padding.ver = 0;  // no noticeable difference

	// style for tab background
	static lv_style_t style_tv_btn_bg;
	lv_style_copy(&style_tv_btn_bg, &lv_style_plain);
	style_tv_btn_bg.body.main_color = LV_COLOR_RED;
	style_tv_btn_bg.body.grad_color = LV_COLOR_BLACK;
	//   style_tv_btn_bg.body.padding.hor = 0;  // removes L/R tab background spacing so tabs hit L/R edges - not included in tab height
	//   style_tv_btn_bg.body.padding.ver = 0;  // removes T/B tab background spacing so tabs hit T/B edges - not included in tab height

	// style for tab released
	static lv_style_t style_tv_btn_rel;
	lv_style_copy(&style_tv_btn_rel, &lv_style_btn_rel);
	style_tv_btn_rel.body.radius = 0; //the curve of the btn corners 0 = square
	style_tv_btn_rel.body.main_color = LV_COLOR_MAKE(0x30, 0x30, 0x30); // dark gray
	style_tv_btn_rel.body.grad_color = LV_COLOR_BLACK;
	style_tv_btn_rel.body.border.width = 0;
	style_tv_btn_rel.text.color = LV_COLOR_RED;
	style_tv_btn_rel.body.padding.ver = 6; // make tabs shorter - match for all btn styles
	//  style_tv_btn_rel.body.padding.hor = 0;                // no noticeable difference

	// style for tab pressed
	static lv_style_t style_tv_btn_pr;
	lv_style_copy(&style_tv_btn_pr, &style_tv_btn_rel);
	style_tv_btn_pr.body.main_color = LV_COLOR_BLACK;
	style_tv_btn_pr.body.grad_color = LV_COLOR_BLACK;

	// style for tab indicator
	static lv_style_t style_tv_btn_indic;
	lv_style_copy(&style_tv_btn_indic, &lv_style_plain);
	style_tv_btn_indic.body.main_color = LV_COLOR_RED;
	style_tv_btn_indic.body.grad_color = LV_COLOR_RED;
	style_tv_btn_indic.body.opa = LV_OPA_70;

	lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BG, &style_tv_bg);
	lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_BG, &style_tv_btn_bg);
	lv_tabview_set_style(tv, LV_TABVIEW_STYLE_INDIC, &style_tv_btn_indic); // the bar that is under the selected tab
	lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_REL, &style_tv_btn_rel);
	lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_PR, &style_tv_btn_pr);
	lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_TGL_REL, &style_tv_btn_pr);
	lv_tabview_set_style(tv, LV_TABVIEW_STYLE_BTN_TGL_PR, &style_tv_btn_pr);

	// removes the height of the tab from the btnm
	g_tv_tab_height = 2 * style_tv_btn_rel.body.padding.ver
			+ 2 * style_tv_btn_bg.body.padding.ver
			+ lv_font_get_height(style_tv_btn_rel.text.font);

	lv_obj_align(tv, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
}

//set the style of the status bar with a black background
void set_sb_style(lv_obj_t *sb) {
	static lv_style_t style_sb_region_bg;
	lv_style_copy(&style_sb_region_bg, &lv_style_plain);
	style_sb_region_bg.body.main_color = LV_COLOR_BLACK;
	style_sb_region_bg.body.grad_color = LV_COLOR_BLACK;
	lv_obj_set_style(sb, &style_sb_region_bg);
}

//  set status bar text style with red colors
void set_sb_lbl_style(lv_obj_t *sb_lbl) {
	static lv_style_t style_sb_txt;
	lv_style_copy(&style_sb_txt, &lv_style_plain);
	style_sb_txt.text.color = LV_COLOR_RED;
	lv_obj_set_style(sb_lbl, &style_sb_txt);
}

// set btm matrix style with 5090 colors
void set_btnm_style(lv_obj_t *btnm, lv_obj_t *parent) {
	static lv_style_t style_bg;
	lv_style_copy(&style_bg, &lv_style_plain);
	style_bg.body.main_color = LV_COLOR_RED;
	style_bg.body.grad_color = LV_COLOR_RED;
	style_bg.body.padding.hor = 7; // adds padding to the L/R most buttons - allows the style_bg color to be seen
	style_bg.body.padding.ver = 0;
	style_bg.body.padding.inner = 0;

	// button style
	static lv_style_t style_btn_rel;
	lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
	style_btn_rel.body.main_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);
	style_btn_rel.body.grad_color = LV_COLOR_BLACK;
	style_btn_rel.body.border.color = LV_COLOR_RED;
	style_btn_rel.body.border.width = 2;
	//  style_btn_rel.body.padding.hor = 0;
	//  style_btn_rel.body.padding.ver = 0;
	style_btn_rel.body.border.opa = LV_OPA_50;
	style_btn_rel.body.radius = 0;

	static lv_style_t style_btn_pr;
	lv_style_copy(&style_btn_pr, &style_btn_rel);
	style_btn_pr.body.main_color = LV_COLOR_BLACK;
	style_btn_pr.body.grad_color = LV_COLOR_MAKE(0x30, 0x30, 0x30);

	lv_obj_set_size(btnm, lv_obj_get_width(parent),
			lv_obj_get_height(parent) - g_tv_tab_height - 32);
	lv_btnm_set_style(btnm, LV_BTNM_STYLE_BG, &style_bg);
	lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_REL, &style_btn_rel);
	lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_PR, &style_btn_pr);

	lv_obj_align(btnm, NULL, LV_ALIGN_CENTER, 0, 0);
}

/**
 * Create robot gui
 */
// NOTE: children don't automatically inherit the size of the parent
//
lv_obj_t *tv;

void robot_gui(void) {
	// create the tabview region
	g_tv_region = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(g_tv_region, lv_obj_get_width(lv_scr_act()),
			lv_obj_get_height(lv_scr_act()) * 0.8);
	lv_obj_align(g_tv_region, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

	// create the status bar region
	g_sb_region = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(g_sb_region, lv_obj_get_width(lv_scr_act()),
			lv_obj_get_height(lv_scr_act()) * 0.2);
	set_sb_style(g_sb_region);
	lv_obj_align(g_sb_region, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

	// set the status bar label to the status bar region
	g_sb_label = lv_label_create(g_sb_region, NULL);
	set_sb_lbl_style(g_sb_label);

	// set the tabview to the tabview region
	tv = lv_tabview_create(g_tv_region, NULL);
	lv_obj_set_size(tv, lv_obj_get_width(g_tv_region), lv_obj_get_height(g_tv_region));
	set_tv_style(tv);

  // defin the auton tab objects with tab names
	lv_obj_t *marl_tab = lv_tabview_add_tab(tv, "MARL");
	lv_obj_t *marr_tab = lv_tabview_add_tab(tv, "MARR");
	lv_obj_t *mabl_tab = lv_tabview_add_tab(tv, "MABL");
	lv_obj_t *mabr_tab = lv_tabview_add_tab(tv, "MABR");

	// set the tab size to the size of the tv region
	lv_obj_set_size(marl_tab, lv_obj_get_width(tv), lv_obj_get_height(tv));
	lv_obj_set_size(marr_tab, lv_obj_get_width(tv), lv_obj_get_height(tv));
	lv_obj_set_size(mabl_tab, lv_obj_get_width(tv), lv_obj_get_height(tv));
	lv_obj_set_size(mabr_tab, lv_obj_get_width(tv), lv_obj_get_height(tv));

  // create the auton tabs
	marl_create(marl_tab);
	marr_create(marr_tab);
	mabl_create(mabl_tab);
	mabr_create(mabr_tab);

  // create an INFO Tab and a Telemetery Tab objects
  lv_obj_t *info_tab = lv_tabview_add_tab(tv, "INFO");
  lv_obj_t *telm_tab = lv_tabview_add_tab(tv, "TELM");

  // info/telm tab sizes
  lv_obj_set_size(info_tab, lv_obj_get_width(tv), lv_obj_get_height(tv));
  lv_obj_set_size(telm_tab, lv_obj_get_width(tv), lv_obj_get_height(tv));

  // create info/telm tabs
  info_create(info_tab);
  telm_create(telm_tab);

  // this code was originally tested on the LVGL PC Simulator with 480x272
  // screen resolution, but with the blue status bar it only has 480x240
	info_printf(1, "SCR=%dx%d, TV=%dx%d, SB=%dx%d\n",
			lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()),
			lv_obj_get_width(tv), lv_obj_get_height(tv),
			lv_obj_get_width(g_sb_region), lv_obj_get_height(g_sb_region));

	lv_label_set_text(g_sb_label, CODE_VERSION);
	lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Called when a button is released ot long pressed*/
// "static" was copied from the exmaple but it means the function
// is visible to this file only so it doesn't seem necessary
static lv_res_t marl_btnm_action(lv_obj_t * btnm, const char *txt) {
	//  printf("Button: %s released\n", txt); // verify long hold does not repeat
	//
	int btn_num = atoi(txt);

  // run selected auton function when not in auton and not disabled
  if (!pros::competition::is_autonomous() && !pros::competition::is_disabled()) {
    auton_go=1;
    lv_tabview_set_tab_act(tv, 6, false);
  }

	switch (btn_num) {
	case 1:
		lv_label_set_text(g_sb_label, MARL1_TEXT);
		auton_ptr = &marl1;
		break;
	case 2:
		lv_label_set_text(g_sb_label, MARL2_TEXT);
		auton_ptr = &marl2;
		break;
	case 3:
		lv_label_set_text(g_sb_label, MARL3_TEXT);
		auton_ptr = &marl3;
		break;
	case 4:
		lv_label_set_text(g_sb_label, MARL4_TEXT);
		auton_ptr = &marl4;
		break;
	case 5:
		lv_label_set_text(g_sb_label, MARL5_TEXT);
		auton_ptr = &marl5;
		break;
	case 6:
		lv_label_set_text(g_sb_label, MARL6_TEXT);
		auton_ptr = &marl6;
		break;
	}
	lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

	return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

/*Called when a button is released ot long pressed*/
static lv_res_t marr_btnm_action(lv_obj_t * btnm, const char *txt) {
	// printf("Button: %s released\n", txt); // verify long hold does not repeat
	//
	int btn_num = atoi(txt);

  if (!pros::competition::is_autonomous() && !pros::competition::is_disabled()) {
    auton_go=1;
    lv_tabview_set_tab_act(tv, 6, false);
  }

	switch (btn_num) {
	case 1:
		lv_label_set_text(g_sb_label, MARR1_TEXT);
		auton_ptr = &marr1;
		break;
	case 2:
		lv_label_set_text(g_sb_label, MARR2_TEXT);
		auton_ptr = &marr2;
		break;
	case 3:
		lv_label_set_text(g_sb_label, MARR3_TEXT);
		auton_ptr = &marr3;
		break;
	case 4:
		lv_label_set_text(g_sb_label, MARR4_TEXT);
		auton_ptr = &marr4;
		break;
	case 5:
		lv_label_set_text(g_sb_label, MARR5_TEXT);
		auton_ptr = &marr5;
		break;
	case 6:
		lv_label_set_text(g_sb_label, MARR6_TEXT);
		auton_ptr = &marr6;
		break;
	}
	lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

	return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

/*Called when a button is released ot long pressed*/
static lv_res_t mabl_btnm_action(lv_obj_t * btnm, const char *txt) {
	// printf("Button: %s released\n", txt); // verify long hold does not repeat
	//
	int btn_num = atoi(txt);

  if (!pros::competition::is_autonomous() && !pros::competition::is_disabled()) {
    auton_go=1;
    lv_tabview_set_tab_act(tv, 6, false);
  }

	switch (btn_num) {
	case 1:
		lv_label_set_text(g_sb_label, MABL1_TEXT);
		auton_ptr = &mabl1;
		break;
	case 2:
		lv_label_set_text(g_sb_label, MABL2_TEXT);
		auton_ptr = &mabl2;
		break;
	case 3:
		lv_label_set_text(g_sb_label, MABL3_TEXT);
		auton_ptr = &mabl3;
		break;
	case 4:
		lv_label_set_text(g_sb_label, MABL4_TEXT);
		auton_ptr = &mabl4;
		break;
	case 5:
		lv_label_set_text(g_sb_label, MABL5_TEXT);
		auton_ptr = &mabl5;
		break;
	case 6:
		lv_label_set_text(g_sb_label, MABL6_TEXT);
		auton_ptr = &mabl6;
		break;
	}

	lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

	return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

/*Called when a button is released ot long pressed*/
static lv_res_t mabr_btnm_action(lv_obj_t * btnm, const char *txt) {
	// printf("Button: %s released\n", txt);  // verify long hold does not repeat
	//
	int btn_num = atoi(txt);

  if (!pros::competition::is_autonomous() && !pros::competition::is_disabled()) {
    auton_go=1;
    lv_tabview_set_tab_act(tv, 6, false);
  }

	switch (btn_num) {
	case 1:
		lv_label_set_text(g_sb_label, MABR1_TEXT);
		auton_ptr = &mabr1;
		break;
	case 2:
		lv_label_set_text(g_sb_label, MABR2_TEXT);
		auton_ptr = &mabr2;
		break;
	case 3:
		lv_label_set_text(g_sb_label, MABR3_TEXT);
		auton_ptr = &mabr3;
		break;
	case 4:
		lv_label_set_text(g_sb_label, MABR4_TEXT);
		auton_ptr = &mabr4;
		break;
	case 5:
		lv_label_set_text(g_sb_label, MABR5_TEXT);
		auton_ptr = &mabr5;
		break;
	case 6:
		lv_label_set_text(g_sb_label, MABR6_TEXT);
		auton_ptr = &mabr6;
		break;
	}

	lv_obj_align(g_sb_label, NULL, LV_ALIGN_CENTER, 0, 0); // must be after set_text

	return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static void marl_create(lv_obj_t *parent) {
	// Create a button descriptor string array w/ no repeat "\224"
	static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
			                           "\2244", "\2245", "\2246", "" };

	// Create a default button matrix* no repeat
	lv_obj_t *btnm = lv_btnm_create(parent, NULL);
	set_btnm_style(btnm, parent);
	lv_btnm_set_map(btnm, btnm_map);
	lv_btnm_set_action(btnm, marl_btnm_action);
}

static void marr_create(lv_obj_t *parent) {
	// Create a button descriptor string array w/ no repeat "\224"
	static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
			                           "\2244","\2245", "\2246", "" };

	// Create a button descriptor string array w/ no repeat
	lv_obj_t *btnm = lv_btnm_create(parent, NULL);
	set_btnm_style(btnm, parent);
	lv_btnm_set_map(btnm, btnm_map);
	lv_btnm_set_action(btnm, marr_btnm_action);
}

static void mabl_create(lv_obj_t *parent) {
	// Create a button descriptor string array w/ no repeat "\224"
	static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
			                           "\2244", "\2245", "\2246", "" };

	// Create a button descriptor string array w/ no repeat
	lv_obj_t *btnm = lv_btnm_create(parent, NULL);
	set_btnm_style(btnm, parent);
	lv_btnm_set_map(btnm, btnm_map);
	lv_btnm_set_action(btnm, mabl_btnm_action);
}

static void mabr_create(lv_obj_t *parent) {
	// Create a button descriptor string array w/ no repeat "\224"
	static const char * btnm_map[] = { "\2241", "\2242", "\2243", "\n",
			                           "\2244", "\2245", "\2246", "" };

	// Create a button descriptor string array w/ no repeat
	lv_obj_t *btnm = lv_btnm_create(parent, NULL);
	set_btnm_style(btnm, parent);
	lv_btnm_set_map(btnm, btnm_map);
	lv_btnm_set_action(btnm, mabr_btnm_action);
}

static void info_create(lv_obj_t *parent) {
	// add the label the status bar
	// set the style of the info tab label text so it is white
	static lv_style_t style_info_txt;
	lv_style_copy(&style_info_txt, &lv_style_plain);
	style_info_txt.text.color = LV_COLOR_WHITE;
  g_info_label = lv_label_create(parent, NULL);
  lv_obj_set_style(g_info_label, &style_info_txt);
}

static void telm_create(lv_obj_t *parent) {
	// add the label the status bar
	// set the style of the info tab label text so it is white
	static lv_style_t style_telm_txt;
	lv_style_copy(&style_telm_txt, &lv_style_plain);
	style_telm_txt.text.color = LV_COLOR_WHITE;
  g_telm_label = lv_label_create(parent, NULL);
  lv_obj_set_style(g_telm_label, &style_telm_txt);
}
