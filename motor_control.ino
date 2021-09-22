//arduino code for motor control for the robot
//requirements: control motor by the press of a key #include <SoftwareSerial.h>
#include<Servo.h>
SoftwareSerial HM10(2, 3); // RX = 2, TX = 3
Servo guide;
char appData;  
String inData = "";
int pos = 90;

//Variables for motor speed control
/*In1=1 & In2=0 : motor moves forward
 *In1=0 & In2=1 : motor moves backward
 *In1=In2 : motor does not move
 */
int dir1=4;
int dir2=5;
int localSpeed;
int motorSpeed=0;
int speedPin = 3; //pin that will output PWM signal

void setup() {
  // put your setup code here, to run once:
  pinMode(dir1,OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(speedPin,OUTPUT);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);  //initializing DC motor. It is not moving until a key is pressed
  
  guide.attach(9);
  guide.write(pos);
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate

}
//converts speed percentage to duty cycle that can be used by PWM pin
void setMotorSpeed(localSpeed){
  int dutyCycle;
  dutyCycle = localSpeed*2.55;
  analogWrite(speedPin,dutyCycle);
}
void loop() {
  // put your main code here, to run repeatedly:
  
  HM10.listen();  // listen the HM10 port
  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    Serial.write(appData);
  }
  if (Serial.available()) 
  {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }
  if ( inData == "W") 
  {
    Serial.println("Moving Forward");
    digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
  }
  else if ( inData == "S") 
  {
    Serial.println("Moving Back");
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,HIGH);
  }
  else if ( inData == "D") 
  {
    Serial.println("Moving Left");
    if(pos > 0 && pos < 180){  
    pos = pos + 5;
    guide.write(pos);
    delay(500);
    digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW);
    setSpeed(95);
    delay(100);
    setSpeed(100);
    }
    else{
      Serial.println("out of bounds");
    }
  }
  else if ( inData == "A") 
  {
    Serial.println("Moving Right");
    if(pos > 0 && pos < 180)
    {  
      pos = pos - 5;
      guide.write(pos);
      delay(500);
      digitalWrite(dir1,HIGH);
      digitalWrite(dir2,LOW);
      setSpeed(95);
      delay(100);
      setSpeed(100);
    }
    else
    {
      Serial.println("out of bounds");
    }
  }
    else
    {
      Serial.println("cammand not accepted");
    }
  }
}
  
