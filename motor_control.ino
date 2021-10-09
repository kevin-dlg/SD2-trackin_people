#include <SoftwareSerial.h>
SoftwareSerial HM10(2, 3); // RX = 2, TX = 3
char appData;
String inData;
int enA = 9;
int enB = 10; 
int A_1 = 5;
int A_2 = 6;
int B_1 = 7;
int B_2 = 8;

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(A_1,OUTPUT);
  pinMode(A_2,OUTPUT);
  pinMode(B_1,OUTPUT);
  pinMode(B_2,OUTPUT);
  
  Serial.begin(9600);
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  pinMode(13, OUTPUT); // onboard LED
  digitalWrite(13, LOW); // switch OFF LED

}

void loop()
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
  digitalWrite(A_1,HIGH);
  digitalWrite(A_2,LOW);
  digitalWrite(B_1,HIGH);
  digitalWrite(B_2,LOW);
  }
  else if ( inData == "8") {
  digitalWrite(A_1,LOW);
  digitalWrite(A_2,HIGH);
  digitalWrite(B_1,LOW);
  digitalWrite(B_2,HIGH);

  }
  else if(inData == "6"){
  digitalWrite(A_1,HIGH);
  digitalWrite(A_2,LOW);
  digitalWrite(B_1,LOW);
  digitalWrite(B_2,LOW);
  }
  else if(inData == "4"){
  digitalWrite(A_1,LOW);
  digitalWrite(A_2,LOW);
  digitalWrite(B_1,HIGH);
  digitalWrite(B_2,LOW);
  }
  else if(inData == "5"){
  digitalWrite(A_1,LOW);
  digitalWrite(A_2,LOW);
  digitalWrite(B_1,LOW);
  digitalWrite(B_2,LOW);
  }
  
  }

