//arduino code for motor control for the robot
//requirements: control motor by the press of a key #include <SoftwareSerial.h>
#include<Servo.h>
SoftwareSerial HM10(2, 3); // RX = 2, TX = 3
Servo guide;
char appData;  
String inData = "";
int pos = 90;

//Variables for motor speed control
bool In1;
bool In2;  //pins to the motor driver
int pulsePin = 3; //pin that will output PWM signal
int dutyCycle;

void setup() {
  // put your setup code here, to run once:
  guide.attach(9);
  guide.write(pos);
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate

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
    //input motor control code here
  }
  else if ( inData == "S") 
  {
    Serial.println("Moving Back");
    //input motor control code here 
  }
  else if ( inData == "D") 
  {
    Serial.println("Moving Left");
    if(pos > 0 && pos < 180){  
    pos = pos + 5;
    guide.write(pos);
    delay(500);
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
  
