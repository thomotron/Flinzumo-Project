/* This file contains all the helper functions we use in Project.ino
 *  
 *  
 */


#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

ZumoReflectanceSensorArray refSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

#define MAX_SPEED 400
#define REFLECTANCE_THRESHOLD 500

#define RELSPEED_SLOW 0.3
#define RELSPEED_NORMAL 0.8
#define RELSPEED_FAST 1

// 2.8 @ 5.25v
// 3.8 @ 4.9v
#define SPIN_MS_PER_DEG 2.8

// Helpful tools
void lineCalibrate();
void lineAlign();
void lineFollow();
bool isLinePresent(int threshold);
float linePositionFromCentre();

void spin(int angle); // angle in degrees. + is c, - is cc
void drive(int distance, float relSpeed, float ratioLR, bool stopAtLine); // distance in cm, ratioLR is the ratio between L and R power


void lineCalibrate()
{
  for(int i = 0; i < 80; i++)
  {
    if((i > 10 && i <= 30) || (i > 50 && i <= 70))
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200,-200);
    }
    refSensors.calibrate();
    delay(20); // Total delay of 20*80 = 1600 ms
  }

  // Stop the motors after calibrating
  motors.setSpeeds(0, 0);
}

void spin(int angle) // angle in degrees. + is c, - is cc
{
  motors.setSpeeds(MAX_SPEED * angle/abs(angle), -MAX_SPEED * angle/abs(angle));
  delay(abs(angle)*SPIN_MS_PER_DEG); // will need to calibrate this later, based off 300 ms for 90 deg
  motors.setSpeeds(0, 0);
}

void drive(int distance, float relSpeed, float ratioLR, bool stopAtLine)
{
  if(ratioLR < 1.0f)
  {
    motors.setSpeeds(MAX_SPEED*relSpeed*ratioLR, MAX_SPEED*relSpeed);
  }
  else
  {
    motors.setSpeeds(MAX_SPEED*relSpeed, MAX_SPEED*relSpeed/ratioLR);
  }
  
  if(!stopAtLine)
  {
    delay(distance*100); // needs calibration, just an estimate
  }
  else
  {
    while(!isLinePresent(REFLECTANCE_THRESHOLD))
    {} // wait
  }
  motors.setSpeeds(0, 0); // stop
}

// Returns whether the reflectance array senses a dark presence
// stirring from the depths
bool isLinePresent(int threshold)
{
  // Initialise a uint array to hold individual sensor values
  unsigned int sensors[6];

  // Get the position of the line (0-5000, left-to-right)
  // from the reflectance sensors and populate the array
  int position = refSensors.readLine(sensors);

  // Return if any of the sensors read above the threshold
  for (int i = 0; i < 6; i++)
  {
    if (sensors[i] > threshold) return true;
  }

  // ...otherwise return false
  return false;
}

// Returns the line position as a percentage from the centre.
// Negative values indicate the line is within the left half of
// the reflectance array, positive values indicate the line is
// within the right half.
float linePositionFromCentre()
{
  // Initialise a uint array to hold individual sensor values
  unsigned int sensors[6];

  // Get the position of the line (0-5000, left-to-right)
  // from the reflectance sensors and populate the array
  int position = refSensors.readLine(sensors);

  // Get the position of the line relative to the centre of the reflectance array
  int centredPosition = position - 2500;

  // Return the centre-relative position as a percentage from the centre
  // (e.g. '43% to the left' or '6% to the right')
  return centredPosition / 2500;
}
