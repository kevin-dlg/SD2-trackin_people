
#include <NewPing.h>      // Library that controls ultrasonic sensors

#define LFR_SONAR 3

// Motor driver logic pins
const int motor1_A = 4;     //In1
const int motor1_B = 5;     //In2
const int motor2_A = 6;     //In3
const int motor2_B = 7;     //In4    

//defining analog pins for front (F), left(L), and right(R) ultrasonic sensors
#define TRIGGER_PIN_F  A1  
#define ECHO_PIN_F     A2
#define TRIGGER_PIN_R  A3  
#define ECHO_PIN_R     A4
#define TRIGGER_PIN_L  A5  
#define ECHO_PIN_L     A6
#define MAX_DISTANCE 250    //max distance to ping

//Initializing array of ultrasonic sensors
NewPing sonar[LFR_SONAR-1] = {
  NewPing(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE);
  NewPing(TRIGGER_PIN_F, ECHO_PIN_F, MAX_DISTANCE);
  NewPing(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE);
}

//array that will store the distances recorded by the sensors 
unsigned long distance[LRF_SONAR-1];  

//Storing the distance for the three sensors
for (uint8_t i=0; i<LFR_SONAR; i++){
  distance[i]=sonar[i].ping_cm();
}

void setup()
{
  Serial.begin(115200);
  
  // Set motor driver control pins
  pinMode(motor1_A, OUTPUT);
  pinMode(motor1_B, OUTPUT);
  pinMode(motor2_A, OUTPUT);
  pinMode(motor2_B, OUTPUT);
 
 for (uint8_t i=0; i<LRF_SONAR; i++){
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    Serial.print(sonar[i].ping_cm());
    Serial.println("cm ");
 }

void loop()
{  
  //get the distance readings for all three sensors
  for (uint8_t i=0; i<LRF_SONAR; i++){
    delay(50);
    distance[i]=sonar[i].ping_cm();}
        
    //move robot to the right if too close to obstacle on the left
    if(distance(0)<=10){
      turnRight();
      delay(250);
    }
    //move robot to the right if too close to obstacle on the left
    else if (distance(2)<=10){
      turnLeft();
      delay(250);
    }

    if (distance(1)<=20){
      //stop the car and move back
      moveStop();
      delay(250);
      moveBackward();
      delay(400);
      moveStop();

      //Check distance to the right and left of the car
      distance[0]=sonar[0].ping_cm();
      delay(50);
      distance[2]=sonar[2].ping_cm();

      if(distance(1)
    }
    else{
      moveForward();
    }

 }
 

}


//READ PING FROM ULTRASONIC SENSOR
int readDistance(int i)      
{
  delay(100);                 // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int cm = sonar[i].ping_cm();   //Send ping, get ping distance in centimeters (cm).
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

//FUNCTIONS TO CONTROL THE MOTOR DRIVER
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
