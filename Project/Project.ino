#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

ZumoReflectanceSensorArray refSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

#define MAX_SPEED 400
#define REFLECTANCE_THRESHOLD 500

// Helpful tools
void lineCalibrate();
void lineAlign();
void lineFollow();

void spin(int angle); // angle in degrees. + is c, - is cc
void drive(int distance, float relSpeed, float ratioLR, bool stopAtLine);

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
  delay(abs(angle)*3.3); // will need to calibrate this later, based off 300 ms for 90 deg
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
  
  if(stopAtLine)
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
