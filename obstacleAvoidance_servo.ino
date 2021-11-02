#include <Servo.h>        // Include Servo Library
#include <NewPing.h>      // Include Newping Library

// Motor driver logic pins
const int motor1_A = 4;     //In1
const int motor1_B = 5;     //In2
const int motor2_A = 6;     //In3
const int motor2_B = 7;     //In4    
const int MAX_DISTANCE = 250; //Max distance to ping. Max distance of ultrasonic sensor is 250cm

//defining analog pins
#define TRIGGER_PIN  A1  
#define ECHO_PIN     A2  

Servo servo_motor;  // Servo's name
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

boolean goesForward = false;
int distance = 100;

void setup()
{
  // Set motor driver control pins
  pinMode(motor1_A, OUTPUT);
  pinMode(motor1_B, OUTPUT);
  pinMode(motor2_A, OUTPUT);
  pinMode(motor2_B, OUTPUT);

  //initialize servo pin and location
  servo_motor.attach(10);  .
  servo_motor.write(115);   
 
  delay(2000);              // Wait for 2s.
  distance = readPing();    // Get Ping Distance.
  delay(100);               // Wait for 100ms.
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop()
{  
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20)
  {
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

    if (distanceRight >= distanceLeft)
    {
      turnRight();
      delay(300);
      moveStop();
    }
    else
    {
      turnLeft();
      delay(300);
      moveStop();
    }
  
  }
  else
  {
    moveForward(); 
  }

    distance = readPing();
}

int lookRight()     // Look Right Function for Servo Motor
{  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft()      // Look Left Function for Servo Motor 
{
  servo_motor.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int readPing()      // Read Ping Function for Ultrasonic Sensor.
{
  delay(100);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar.ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0)
  {
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
