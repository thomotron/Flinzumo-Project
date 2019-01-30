#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>

ZumoReflectanceSensorArray refSensors;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON);

// Helpful tools
void LineCalibrate();
void LineAlign();
void LineFollow();


// Solve each part of the maze
void partI();
void partII();
void partIII();

void setup() {
  // put your setup code here, to run once:
  refSensors.init();
  LineCalibrate();
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

void LineCalibrate()
{
  refSensors.init();
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

