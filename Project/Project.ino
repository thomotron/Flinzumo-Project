
#include "ZumoHelper.h"

//#define DEBUG

#ifdef DEBUG
  #define PAUSE button.waitForButton();
#else
  #define PAUSE delay(300);
#endif

// Solve each part of the maze
void partI();
void partII();
void partIII();

void setup() {
  // Wait until we're ready to calibrate
  button.waitForButton();

  // Initialise the reflectance sensors and start calibration
  refSensors.init();
  lineCalibrate();

  // Wait until we're ready to start
  //button.waitForButton();
  lineAlign();
  // Run each part
  //partII();
}

void loop() {
  // put your main code here, to run repeatedly:

  button.waitForButton();
  lineAlign();

}

void partI()
{
  drive(5, RELSPEED_NORMAL, 1, false); // Leave the starting gate
  drive(30, RELSPEED_NORMAL, 1, true); // Get to the first alignment line
}

void partII()
{
  drive(3, RELSPEED_NORMAL, 0.6, false);  // Veer left into the bottle cap
  drive(3, -RELSPEED_NORMAL, 0.6, true);  // Return to where we started
  drive(2, RELSPEED_NORMAL, 1.4, false);  // Veer right a little so we don't hit the cap again
  spin(45);                               // Turn to face the embassy
  drive(5, RELSPEED_NORMAL, 1, true);     // Drive until we hit the embassy
}

void partIII()
{
  drive(1, RELSPEED_NORMAL, 1, false);  // Overshoot line at embassy a little
  PAUSE
  spin(90);                             // Turn to face south
  PAUSE
  drive(5, RELSPEED_NORMAL, 1, false);  // Drive a bit to get off the embassy alignment line
  PAUSE
  drive(20, RELSPEED_NORMAL, 1, true);  // Drive into the blue sticks until the alignment line
  PAUSE
  drive(3, RELSPEED_NORMAL, 1, false);  // Push the sticks into the safe zone
  PAUSE
  drive(3, -RELSPEED_NORMAL, 1, true);  // Reverse until the alignment line
  PAUSE
  drive(1, -RELSPEED_NORMAL, 1, false); // Drive a bit to get off the alignment line
  drive(20, -RELSPEED_NORMAL, 1, true); // Reverse until the embassy
  PAUSE
  spin(-90);                            // Turn to face east
}

void partIV()
{
  drive(5, RELSPEED_NORMAL, 1.0f, false);  // move back away from building slightly
  spin(-90);                               // spin face N
  drive(10, RELSPEED_NORMAL, 1.0f, true);  // drive till line
  drive(-10, RELSPEED_NORMAL, 0.8, false); // reverse curve left
  spin(100);                               // spin to face S (slightly W)
  drive(15, RELSPEED_NORMAL, 0.9, true);   // drive forwards curving slight right, stop at line

  // Align perpendicular to line if possible
}

void partV()
{
  spin(-110);                           // Turn to face north
  drive(10, RELSPEED_NORMAL, 1, true);  // Drive up to the shop on the corner
}

void partVI()
{
  spin(-120);                           // Turn to face the south west
  drive(10, RELSPEED_NORMAL, 1, true);  // Drive up to the man stranded on the island
}

void partVII()
{
  drive(5, RELSPED_NORMAL, 1, false);   // Reverse back from the island
  spin(45);                             // Spin 45 degrees to face west
  drive(20, RELSPEED_NORMAL, 1, true);  // Push the sandbags until we hit the alignment line
  drive(5, RELSPEED_NORMAL, 1, false);  // Push the sandbags into the safe zone
  drive(5, -RELSPEED_NORMAL, 1, true);  // Back up the the alignment line
}
