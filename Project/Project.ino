
#include "ZumoHelper.h"

//#define DEBUG

#ifdef DEBUG
  #define PAUSE button.waitForButton();
#else
  #define PAUSE delay(500);
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
  button.waitForButton();

  // Run each part
  partII();
}

void loop() {
  // put your main code here, to run repeatedly:

  button.waitForButton();

  // Part 1:
  // Move forward to button (line 1)
  // Turn left slightly, move forward slightly
  // Reverse last movemvent
  // Align on line 1

  // Part 2:
  // Turn right and move to next line. Stop at house.
  // Align to line 2, face South. Follow line South to line 3
  // Push blue things forward a little. Reverse to line 3
  // Reverse to line 2
  // Align on line 2, face East

  // Part 3:
  // Move forward for a while
  // Turn South and keep moving forward to line 4
  // Align on line 4
  // Reverse till line 5

  // Forward then turn North
  // Pause at house (line 6)
  // Reverse slightly
  // 180
  // Move South to line 7. Pause at person
  // Reverse and face West

  // Move forward to line 5
  // Align and face South
  // Move South till line 8
  // Turn slightly East, move forward slightly
  // Reverse last movement

  // Reverse along line 5...
  
}

void partI()
{
  motors.setSpeeds(400, 400);
  
}

void partII()
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
  drive(1, -RELSPEED_NORMAL, 1, false);  // Drive a bit to get off the alignment line
  PAUSE
  drive(20, -RELSPEED_NORMAL, 1, true); // Reverse until the embassy
  PAUSE
  spin(-90);                            // Turn to face east
}

