
/*
  Robot car controlled by 4 light sensors
*/

#define BLACK 0
#define GREY 1
#define WHITE 2

#define LEFT 0
#define RIGHT 1
//-------------------------------------------------------------------------------------------------

int leftPinColor = 0;
int rightPinColor = 0;

/* analog pins for the 4 light sensors*/
int leftPin = A4;
int rightPin = A5;

int leftPinPrevColor;
int rightPinPrevColor;

/* LEDs */
int LEDPin = 6;
int LEDTest = 11;

/* digital pins for the Hbridge controlling the 2 motors */
int motor1PinA = 2;
int motor1PinB = 4;
int enablePinMotor1 = 5;

int motor2PinA = 7;
int motor2PinB = 8;
int enablePinMotor2 = 9;

// algorithms variables
int lastTransition = 0;
int lastTransitionSensor;
int transitionThreshold = 100;
int loopDelay = 5;
int changeDirection = false;

int timerFor = 0;
int timerBack = 0;
//-------------------------------------------------------------------------------------------------

//------------------------------------------initialization-----------------------------------------
void setup() {

  //Serial.begin(9600);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);

  // if necessary enable the pull up resistor GEHT GRAD NICHT
  //  digitalWrite(18, HIGH);
  //  pinMode(leftPin, INPUT_PULLUP);
  //  digitalWrite(19, HIGH);
  //  pinMode(rightPin, INPUT_PULLUP);

  pinMode(motor1PinA, OUTPUT);
  pinMode(motor1PinB, OUTPUT);
  pinMode(motor2PinA, OUTPUT);
  pinMode(motor2PinB, OUTPUT);

  // set enablePin high so that motors can turn on:
  digitalWrite(enablePinMotor1, HIGH);
  digitalWrite(enablePinMotor2, HIGH);

  analogWrite(LEDPin, 255); //LED for rotation detection on

  //Serial.println("Car initialized, ready to go!");
}

//
//-----------------------------------main loop-----------------------------------------------------------
void loop() {

  if (changeDirection)
  {
    return;
  }

  checkRightSensorToCenter();
  // retrieve values of lightness
  readSensors();
  
  //driveToBrightness();

  // print values
  printLightValues(leftPin, rightPin);

  //delay(loopDelay);
  timerFor += loopDelay;
  timerBack += loopDelay;
  //Stop();
}

//
//----------------------------------readSensors-------------------------------------------------------
void readSensors()
{
  leftPinColor = analogRead(leftPin);
  rightPinColor = analogRead(rightPin);
}

//
//----------------------------------determine direction-----------------------------------------------
void driveToBrightness()
{ 
//  if(timerFor < 500){
//    timerFor += loopDelay;
//    Forward();
//   }else{
//     timerBack = 0;
//     if (timerBack < 500){
//    timerBack += loopDelay;
//    Backward();
//      }else{
//        timerFor = 0;
//        }
//    }
//   
   
    Backward();
  
  //transfer python sudo code to arduino code
  analogWrite(enablePinMotor1, 0);
  analogWrite(enablePinMotor2, 250);
  

}

//
//----------------------------------debug functions --------------------------------------------------
void printLightValues(int left, int right)
{
  int s = analogRead(right);
  //Serial.println(s);
  if (s > 300) {
    analogWrite(LEDTest, 255);
    //Serial.print("moved ");
    //
  }else{
    analogWrite(LEDTest, 0);  
  }
  //    Serial.print("light sensors: ");
  //    Serial.print(analogRead(left));
  //    Serial.print("    ");
  //    Serial.println(analogRead(right));
}


//
//----------------------------------turning functions --------------------------------------------------

void checkRightSensorToCenter()
{
  bool outIn = (rightPinColor == BLACK && rightPinPrevColor == WHITE)
        || (rightPinColor == GREY && rightPinPrevColor == BLACK)
        || (rightPinColor == WHITE && rightPinPrevColor == GREY);

   if (outIn && leftPinColor == rightPinPrevColor)
   {
      if(driveStraigh(RIGHT)){
        return;
      }
       //turnRight();
   }
   if (outIn && leftPinColor == leftPinColor)
   {
      if(driveStraigh(RIGHT)){
        return;
      }
       //turnLeft();     
   }
     
   lastTransition = millis();
}

void checkLeftSensorToCenter()
{
  bool outIn = (leftPinColor == BLACK && leftPinPrevColor == WHITE)
        || (leftPinColor == GREY && leftPinPrevColor == BLACK)
        || (leftPinColor == WHITE && leftPinPrevColor == GREY);

   if (outIn && rightPinColor == leftPinPrevColor)
   {
        if(driveStraigh(LEFT)){
          return;
        } 
       //turnLeft();
   }
   if (outIn && rightPinColor == leftPinColor)
   {
      if(driveStraigh(LEFT)){
        return;
      } 
       //turnRight();     
   }
     
   lastTransition = millis();
}

void checkRightSensorToBorder()
{
   
  bool inOut = (rightPinColor == GREY && rightPinPrevColor == WHITE)
        || (rightPinColor == BLACK && rightPinPrevColor == GREY)
        || (rightPinColor == WHITE && rightPinPrevColor == BLACK);

   if (inOut && leftPinColor == rightPinPrevColor)
   {
       if(driveStraigh(RIGHT)){
          //turn180();
          changeDirection = true;
          return;
        }
       //turnStrongerRight();
   }
   if (inOut && leftPinColor == rightPinColor)
   {
      if(driveStraigh(RIGHT)){
        //turn180();
        changeDirection = true;
        return;
      }
       //turnStrongerLeft();     
   }

   changeDirection = true;
   lastTransition = millis();
}

void checkLeftSensorToBorder()
{
   
  bool inOut = (leftPinColor == GREY && leftPinPrevColor == WHITE)
        || (leftPinColor == BLACK && leftPinPrevColor == GREY)
        || (leftPinColor == WHITE && leftPinPrevColor == BLACK);

   if (inOut && rightPinColor == leftPinPrevColor)
   {
       if(driveStraigh(LEFT)){
          //turn180();
          changeDirection = true;
          return;
        }
       //turnStrongerRight();
   }
   if (inOut && rightPinColor == leftPinColor)
   {
      if(driveStraigh(LEFT)){
        //turn180();
        changeDirection = true;
        return;
      }
       //turnStrongerLeft();     
   }

   changeDirection = true;
   lastTransition = millis();
}

bool driveStraigh(int sensor)
{
  if((millis() - lastTransition < transitionThreshold) && (lastTransitionSensor != sensor))
  {
     lastTransitionSensor = sensor;
     lastTransition = millis();
     return true;
  }
  return false;
}

//
//----------------------------------motor functions --------------------------------------------------
void Forward()
{
  Serial.println("move forward");
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, HIGH);
  digitalWrite(motor2PinA, HIGH);
  digitalWrite(motor2PinB, LOW);
}

void Backward() // inverse voltage of both motors
{
  Serial.println("move backward");
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, HIGH);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, HIGH);
}

void RotateLeft() // inverse voltage of only one motor
{
  Serial.println("rotate left");
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, HIGH);
  digitalWrite(motor2PinA, HIGH);
  digitalWrite(motor2PinB, LOW);
}

void RotateRight() // inverse voltage of only one motor
{
  Serial.println("rotate right");
  digitalWrite(motor1PinA, HIGH);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, HIGH);
}

void Stop()
{
  Serial.println("stop");
  digitalWrite(motor1PinA, LOW);
  digitalWrite(motor1PinB, LOW);
  digitalWrite(motor2PinA, LOW);
  digitalWrite(motor2PinB, LOW);
}
