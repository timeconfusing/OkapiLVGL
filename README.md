# OkapiLVGL
5090Z LVGL GUI with Okapi Chassis Control

Since 5090Z has disbanded, the team has given me permission to release their TP GUI.
5090Z did not use Okapi for TP. But it looked interesting so when I decide to make a toy 
for my dog to chase, I though why have him chase a $50 RC car when he could chase a 
$500 V5 chassis. Since I stared with PROS 3.1.6 it needed to work across multiple files. 
Figuring out how to do that took longer than it should (don't ask) but I'm not a programmer.
Since then some teams have asked how to do that so I decided to combine my Okapi code
with the 5090Z GUI. Now the kernel is PROS 3.2.0 but code retains the multi-file format. 

To make sure this fusion worked I added an auton in which I did/do have some issues with 
Okapi turnAngle completing the turn. This prompted the addition of a live telemetry tab and 
the ability to run auton from opcontrol via the LCD. Also, when an auton function is selected 
during opcontrol the telemetry tab is set to the active screen. It should be easy enough to 
see how to move "lv_set_tab_act" to make telemetry be active of normal auton runs if 
desired. 

There are 6 tabs: Auton Red Left, Red Right, Blue Left, Blue Right, Info, and Telm. The tabs 
are selected by touching them. Each of the auton tabs has 6 buttons to select an auton for 
that starting position. There is a status bar at the bottom of the screen to indicate which 
auton was selected. The name of the auton is set in the robot_gui.h file. When the matrix 
button is pressed the status bar at the bottom displays the auton name.

Disclaimer, since I am not programmer, I don’t know that Okapi is used correctly for a 
multi-file project but it seems to work in both opcontrol and auton functions. Also, this
code should be considered unsupported and use at your own risk.  

