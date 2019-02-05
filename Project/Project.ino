
#include "ZumoHelper.h"

//#define DEBUG
//#define FLIP_MOTORS

#ifdef DEBUG
  #define PAUSE button.waitForButton();
#else
  #define PAUSE delay(300);
#endif

// Solve each part of the maze
void partI();
void partII();
void partIII();
void partIV();
void partV();
void partVI();
void partVII();
void partVIII();

// Path A (preferred, but lazy)
void partIXA();
void partXA();

// Path B
void partIXB();
void partXB();
void partXIB();

void setup() {
  // Set up the LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Flip the motors if we need to
  #ifdef FLIP_MOTORS
    motors.flipLeftMotor(true);
    motors.flipRightMotor(true);
  #endif

  // Wait until we're ready to calibrate
  button.waitForButton();

  // Initialise the reflectance sensors and start calibration
  digitalWrite(13, HIGH);
  refSensors.init();
  lineCalibrate();
  digitalWrite(13, LOW);

  // Wait until we're ready to start
  button.waitForButton();

  // Run each part
  partI();
  partII();
  partIII();
  partIV();
  partV();
  partVI();
  partVII();
  partVIII();
  partIXB();
  partXB();
  partXIB();
}

void partI()
{
  drive(5, RELSPEED_NORMAL, 1, false); // Leave the starting gate
  drive(30, RELSPEED_NORMAL, 1, true); // Get to the first alignment line
}

void partII()
{
  drive(2, RELSPEED_NORMAL, 1, false);  // Drive forward a little
  PAUSE
  spin(-45);                            // Turn left a little
  PAUSE
  drive(2, RELSPEED_NORMAL, 1, false);  // Push the bottle cap in
  PAUSE
  drive(2, -RELSPEED_NORMAL, 1, false); // Back up, Terry!
  PAUSE
  spin(90);                             // Turn to face the embassy
  PAUSE
  drive(4, RELSPEED_NORMAL, 1, false);  // Drive a little
  PAUSE
  spin(45);                             // Turn to face the alignment line
  PAUSE
  drive(10, RELSPEED_NORMAL, 1, true);  // Drive until we hit the embassy
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
  drive(10, RELSPEED_NORMAL, 1, false);  // Drive down the avenue
  drive(20, RELSPEED_NORMAL, 1.6, true); // Veer right until we hit the safe zone at the plaza toward the end
}

void partV()
{
  spin(-110);                           // Turn to face north
  PAUSE
  drive(10, RELSPEED_NORMAL, 1, true);  // Drive up to the shop on the corner
}

void partVI()
{
  spin(-160);                           // Turn to face the south west
  PAUSE
  drive(10, RELSPEED_NORMAL, 1, true);  // Drive up to the man stranded on the island
}

void partVII()
{
  drive(5, -RELSPEED_NORMAL, 1, false);  // Reverse back from the island
  PAUSE
  spin(50);                             // Spin to face west
  PAUSE
  drive(20, RELSPEED_NORMAL, 1, true);  // Push the sandbags until we hit the alignment line
  drive(5, RELSPEED_NORMAL, 1, false);  // Push the sandbags into the safe zone
  drive(5, -RELSPEED_NORMAL, 1, true);  // Back up the the alignment line
}

void partVIII()
{
  float spd = RELSPEED_SLOW;
  drive(3.0f, spd, 1.0f, false);
  PAUSE
  spin(-85); // turns weird on the seam
  PAUSE
  lineFollow(1000, false);
  PAUSE
  lineFollow(3000, true);
  PAUSE
  drive(0.8f, spd, 1.0f, false); // just to not hit the wall
  PAUSE
  spin(-45);
  PAUSE
  drive(3.0f, RELSPEED_NORMAL, 1.0f, false);
  PAUSE
  drive(3.0f, -RELSPEED_NORMAL, 1.0f, false);
  PAUSE
  spin(45);
}

void partIXA()
{
  spin(25);
  PAUSE
  drive(3.0f, RELSPEED_NORMAL, 1.0f, false);
  PAUSE
  drive(5.0f, RELSPEED_NORMAL, 1.0f, true);
}

void partXA()
{
  spin(-110);
  PAUSE
  drive(30.0f, RELSPEED_NORMAL, 1.0f, true);
}

void partIXB()
{
  drive(1, RELSPEED_NORMAL, 1.0f, false);
  PAUSE
  spin(45);
  PAUSE
  drive(2, RELSPEED_NORMAL, 1.0f, false);
  PAUSE
  drive(5, RELSPEED_NORMAL, 1.0f, true);
}

void partXB()
{
  drive(5.0f, -RELSPEED_ALMOSTNORMAL, 1.0f, false);
  spin(-55);
  drive(5.0f, RELSPEED_ALMOSTNORMAL, 1.0f, true);
}

void partXIB()
{
  spin(-90);
  PAUSE
  drive(30.0f, RELSPEED_NORMAL, 1.0f, true);
}
