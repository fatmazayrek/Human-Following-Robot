#include <NewPing.h>           
#include<Servo.h>             
#include<AFMotor.h>  


#define LEFT A3              // Left IR sensor connected to analog pin A2 of Arduino Uno:
#define RIGHT A1              // Right IR sensor connected to analog pin A3 of Arduino Uno:
#define TRIGGER_PIN A5        // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN A0       // Echo pin connected to analog pin A0 of Arduino Uno:
#define MAX_DISTANCE 200      // Maximum ping distance:
#define BuzzerPin A4             //Buzzer pin

unsigned int distance = 0;    //Variable to store ultrasonic sensor distance:
unsigned int Right_Value = 0; //Variable to store Right IR sensor value:
unsigned int Left_Value = 0;  //Variable to store Left IR sensor value:
int pos = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //NewPing setup of pins and maximum distance:

//create motor objects
AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

Servo myservo; //create servo object to control the servo:

void Ultrasonik(int distance){
  
  if(distance < 10){            //check wheather the ultrasonic sensor's value stays between 1 to 10.
  
  //Stop:
  Motor1.setSpeed(0);    //define motor1 speed:
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //define motor2 speed:
  Motor2.run(RELEASE);   //stop motor2:
  Motor3.setSpeed(0);    //define motor3 speed:
  Motor3.run(RELEASE);   //stop motor3:
  Motor4.setSpeed(0);    //define motor4 speed:
  Motor4.run(RELEASE);   //stop motor4:
  }
  
  if((distance >= 10) && (distance <= 15)){            //check wheather the ultrasonic sensor's value stays between 10 to 15.
  
  //Move Forward:
  Motor1.setSpeed(60);  //define motor1 speed:
  Motor1.run(FORWARD);   
  Motor2.setSpeed(60);  //define motor2 speed:
  Motor2.run(FORWARD);   
  Motor3.setSpeed(60);  //define motor3 speed:
  Motor3.run(FORWARD);   
  Motor4.setSpeed(60);  //define motor4 speed:
  Motor4.run(FORWARD);   
  }

  else if((distance > 16) && (distance <= 40)){            
  
  //Move Forward:
  Motor1.setSpeed(150);  //define motor1 speed:
  Motor1.run(FORWARD);   
  Motor2.setSpeed(150);  //define motor2 speed:
  Motor2.run(FORWARD);   
  Motor3.setSpeed(150);  //define motor3 speed:
  Motor3.run(FORWARD);   
  Motor4.setSpeed(150);  //define motor4 speed:
  Motor4.run(FORWARD);  
  }

  else if(distance > 40){
  
  //Stop
  for(int i=0; i<5; i++){
    digitalWrite(BuzzerPin,HIGH);
    delay(50);
    digitalWrite(BuzzerPin,LOW);
  }
  
  Motor1.setSpeed(0);    //define motor1 speed:
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //define motor2 speed:
  Motor2.run(RELEASE);   //stop motor2:
  Motor3.setSpeed(0);    //define motor3 speed:
  Motor3.run(RELEASE);   //stop motor3:
  Motor4.setSpeed(0);    //define motor4 speed:
  Motor4.run(RELEASE);   //stop motor4:
  }
}

void setup() {
  
  // put your setup code here, to run once:
   Serial.begin(9600); //initailize serial communication at 9600 bits per second:
   myservo.attach(10); // servo attached to pin 10 of Arduino UNO
   myservo.write(110);

   pinMode(RIGHT, INPUT); //set analog pin RIGHT as an input:
   pinMode(LEFT, INPUT);  //set analog pin LEFT as an input:
   pinMode(BuzzerPin, OUTPUT); //set BuzzerPin as an output:
}

void loop() {
  
  // put your main code here, to run repeatedly:
  delay(50);     //wait 50ms between pings:
  distance = sonar.ping_cm();     //send ping, get distance in cm and store it in 'distance' variable:

  Right_Value = digitalRead(RIGHT);   // read the value from Right IR sensor:
  Left_Value = digitalRead(LEFT);     // read the value from Left IR sensor:

  Serial.print("Distance");
  Serial.println(distance);
  Serial.print("LSensor");
  Serial.println(Left_Value);
  Serial.print("RSensor");
  Serial.println(Right_Value);

  Ultrasonik(distance);
  
  if((Right_Value==1) && (Left_Value==0)) {   //If leftside=0 then turn the left
    
    myservo.write(160);
    delay(100);
  
    //Turn Left                                                
    Motor1.setSpeed(150);  //define motor1 speed:
    Motor1.run(FORWARD);   //rotate motor1 cloclwise:
    Motor2.setSpeed(150);  //define motor2 speed:
    Motor2.run(FORWARD);   //rotate motor2 clockwise:
    Motor3.setSpeed(150);  //define motor3 speed:
    Motor3.run(BACKWARD);  //rotate motor3 anticlockwise:
    Motor4.setSpeed(150);  //define motor4 speed:
    Motor4.run(BACKWARD);  //rotate motor4 anticlockwise:
    
    delay(200);
    myservo.write(110);
  }

  else if((Right_Value==0) && (Left_Value==1)) {   //If rightside=0 then turn the right
  
    myservo.write(60);
    delay(100);
    
    //Turn Right                                                
    Motor1.setSpeed(150);  //define motor1 speed:
    Motor1.run(BACKWARD);   //rotate motor1 anticlockwise:
    Motor2.setSpeed(150);  //define motor2 speed:
    Motor2.run(BACKWARD);   //rotate motor2 anticlockwise:
    Motor3.setSpeed(150);  //define motor3 speed:
    Motor3.run(FORWARD);  //rotate motor3 clockwise:
    Motor4.setSpeed(150);  //define motor4 speed:
    Motor4.run(FORWARD);  //rotate motor4 clockwise:
    
    delay(200);
    myservo.write(110);

  }
}
