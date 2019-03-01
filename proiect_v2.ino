//L293D

//Motor A

const int motorPin1  = 5;  // Pin 14 of L293
const int motorPin2  = 6;  // Pin 10 of L293

//Motor B

const int motorPin3  = 10; // Pin  7 of L293
const int motorPin4  = 9;  // Pin  2 of L293

#define TRIG1 A1
#define ECHO1 A0  
#define TRIG2 A2
#define ECHO2 A3
#define TRIG3 11
#define ECHO3 12

long durationFront, durationBack, durationLeft, durationRight;
int distanceFront, distanceBack, distanceLeft, distanceRight;

void setup(){
 
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT); 
  pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT); 
   
  Serial.begin(9600);
}

// Sends power to both motors for the car to go forward
void forward(){
  
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  
}

// Sends power to both motors for the car to go backward
void back(){

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  
}

// Sends power only to the left motor for the car to make a left turn
void left(){

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  
}

// Stop sending to both motors
void stopare(){

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  
}

// If the ultrasonic sensor placed in front of the car reads less than a certain distance executes functions
void ifFront(){

  if ( distanceFront < 7 && distanceBack > 7 )
      back();
     
   
   if ( distanceBack > 7 && distanceFront > 7  && distanceLeft + 1 > 2 )
       stopare();
}

// If the ultrasonic sensor placed in the back of the car reads less than a certain distance executes functions
void ifBack(){

  if ( distanceBack < 7 && distanceFront > 7)
      forward();
 
  if ( distanceBack > 7 && distanceFront > 7 && distanceLeft + 1 > 2 )
      stopare();
      
}

// If the ultrasonic sensor placed in the left of the car reads less than a certain distance executes functions
void ifLeft(){

  if ( distanceLeft + 1 < 3)
      right();
      
  if ( distanceBack > 3 && distanceFront > 3 && distanceLeft + 1 > 2 )
      stopare();
}

// If the ultrasonic sensor placed in front and in the back of the car reads less than a certain distance executes functions
void ifFrontAndBack(){

  if ( distanceFront < 5 && distanceBack < 5)
      right();
      
  if ( distanceBack > 3 && distanceFront > 3 && distanceLeft + 1 > 2 )
      stopare();
  
}

// Reads data from the ultrasonic sensor placed in the back of the car
void readBack(){
  
  digitalWrite(TRIG3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG3, LOW);
  
  // Reads the ECHOPin, returns the sound wave travel time in microseconds
  durationBack = pulseIn(ECHO3, HIGH);
  
  // Calculating the distance
  distanceBack = durationBack * 0.034 / 2;

  ifBack();
  
}

// Reads data from the ultrasonic sensor placed in the front of the car
void readFront(){
  
  digitalWrite(TRIG1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  
  // Reads the ECHOPin, returns the sound wave travel time in microseconds
  durationFront = pulseIn(ECHO1, HIGH);
  
  // Calculating the distance
  distanceFront = durationFront * 0.034 / 2;

  ifFront();
 
}

// Reads data from the ultrasonic sensor placed in the left of the car
void readLeft(){

  digitalWrite(TRIG2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  
  // Reads the ECHOPin, returns the sound wave travel time in microseconds
  durationLeft = pulseIn(ECHO2, HIGH);
  
   // Calculating the distance
  distanceLeft = durationLeft * 0.034 / 2;

  ifLeft();
  
}

void readyToWork(){

  readRight();

  readFront();

  readBack();

  ifFrontAndBack();
  
}
void loop(){

  readyToWork();
  
}
