#include <SoftwareSerial.h>
#include <Servo.h>        // Include Servo Library
#include <NewPing.h>      // Include Newping Library

// Motor driver logic pins
const int motor1_A = 4;     //In1
const int motor1_B = 5;     //In2
const int motor2_A = 6;     //In3
const int motor2_B = 7;     //In4    

//defining analog pins
#define TRIGGER_PIN  A1  
#define ECHO_PIN     A2  
#define MAX_DISTANCE 250 //distance in centimeters

Servo servo_motor;  // Servo's name
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int distance = 100;
char choice;

void setup()
{
  // Set motor driver control pins
  pinMode(motor1_A, OUTPUT);
  pinMode(motor1_B, OUTPUT);
  pinMode(motor2_A, OUTPUT);
  pinMode(motor2_B, OUTPUT);

  //Initializing servo
  servo_motor.attach(10);  
  servo_motor.write(115);   
  
  //initializing serial communication
  Serial.begin(9600);
  HM10.begin(9600);
  Serial.println("HM10 serial started at 9600");
  
 //reading initial distance from ultrasonic sensor
 distance=readPing();

 //PROMPT USER TO ASK IF AUTONOMOUS OR CONTROLLED BY USER
 Serial.println("Autonomous or Controlled?: (a/c)");
 if (Serial.available()>0){
  choice=Serial.read();
 }
}

void loop(){  
  if(choice=='a'){
    autonomous();
  }
  else if (choice=='c'){
    controlled();
  }
  else{
    Serial.println("This choice is not valid. Reset Arduino and try again");
  }
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){      
  servo_motor.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

//obtaining distance reading from ultrasonic sensor
int readPing(){
  delay(50);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop()    {
  digitalWrite(motor1_A, LOW);
  digitalWrite(motor1_B, LOW);
  digitalWrite(motor2_A, LOW);
  digitalWrite(motor2_B, LOW);
}

void moveForward()    {
  digitalWrite(motor1_A, HIGH);
  digitalWrite(motor1_B, LOW);
  digitalWrite(motor2_A, HIGH);
  digitalWrite(motor2_B, LOW);
}

void moveBackward()  {
  digitalWrite(motor1_A, LOW);
  digitalWrite(motor1_B, HIGH);
  digitalWrite(motor2_A, LOW);
  digitalWrite(motor2_B, HIGH);
}

void turnRight()      {
  digitalWrite(motor1_A, LOW);
  digitalWrite(motor1_B, HIGH);
  digitalWrite(motor2_A, HIGH);
  digitalWrite(motor2_B, LOW);
}

void turnLeft()     {
  digitalWrite(motor1_A, HIGH);
  digitalWrite(motor1_B, LOW);
  digitalWrite(motor2_A, LOW);
  digitalWrite(motor2_B, HIGH);
}

//Robot performs obstacle detection without input from the user.
void autonomous()
{
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft){
      turnRight();
      delay(300);
      moveStop();
    }
    else{
      turnLeft();
      delay(300);
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

//Controls the robot via the number pad on computer
void controlled()
{
  HM10.listen();  // listen the HM10 port
  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    Serial.write(appData);
  }

  if (Serial.available()) {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }
  if ( inData == "2") {
    moveBackward();
  }
  else if ( inData == "8") {
    moveForward();
  }
  else if(inData == "6"){
    turnRight();
  }
  else if(inData == "4"){
    turnLeft();
  }
  else if(inData == "5"){
    moveStop();
  }
}
