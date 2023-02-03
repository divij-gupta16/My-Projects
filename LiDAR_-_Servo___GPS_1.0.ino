#include <AltSoftSerial.h>
#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial gpsSerial(11,12);
TinyGPSPlus gps;

Servo servo;
AltSoftSerial mySerial;

//const int rs = 7, en = 6, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float velocity;
float total = 0.;
float average = 0;
int count = 0;

float dist1 = 0.;
float dist2 = -1;
float dist;
int check;//save check value
int uart[9];//save data measured by LiDAR
const int HEADER=0x59;//frame header of data package
unsigned long t;
unsigned long t1;
unsigned long t2;
float Speed;
float diff;
float highSpeed = 10.;
//bool boo = true;
int c = 0;
float avg = 0;
float tot = 0;
int turn = 50;
int printCount;

float relVel;

void setup() {
//  lcd.begin(16, 2);
  Serial.begin(9600);//set bit rate of serial port connecting Arduino with computer
  mySerial.begin(115200); //set bit rate of serial port connecting LiDAR with Arduino
  gpsSerial.begin(9600); // GPS serial, baud 9600
  servo.attach(7);
  t1 = micros();
  Serial.print("t1: ");
  Serial.println(t1);
  Serial.print("dist1 = ");
  Serial.println(dist1);
  servo.write(90);
}

void loop() {
  //Serial.println(servo.read());
  if (servo.read() > 100 || servo.read() < 80) {
    turn *= -1;
    }    
  //Serial.println(turn);
  servo.write(servo.read() + turn);
  delay(400);
  printCount = 0;
  while (printCount <= 10) {
    Serial.println("Yes");    
    if (mySerial.available()) { //check if serial port has data input
      Serial.println("YEET"); 
      if(mySerial.read()==HEADER) { //assess data package frame header 0x59 
        uart[0]=HEADER;
        if(mySerial.read()==HEADER) { //assess data package frame header 0x59
          uart[1]=HEADER;
          for(int i2 = 2; i2 < 9; i2++) {
            uart[i2]=mySerial.read();
          } 
          check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7]; 
          if(uart[8]==(check&0xff)) {  // verify the received data as per protocol
            //Serial.println("YIPPEE");
            dist = uart[2] + uart[3] * 256; // calculate distance value
            dist = dist / 100;
            t2 = micros();
            //Serial.print("t2: ");
            //Serial.println(t2);
            if ((dist < 12.) && (dist >= 0.)) {
              dist2 = dist;
              //Serial.print("dist2 = ");
              //Serial.println(dist2);//output measure distance value of LiDAR Serial.print('\t');
              //Serial.print('\n');
            }
          }
        }
      }
    }
    
    if (gpsSerial.available()) {
      Serial.println("YOOOO");
      int data = gpsSerial.read();
      if (gps.encode(data)) {
        Serial.println("YOOOOTTTTTTT");
        velocity = (gps.speed.kmph());
        velocity = velocity / 1.6;
        Serial.print("V: ");
        Serial.println(velocity);
        total += velocity;
        count += 1;
      
        if (count >= 12) {
          average = total / 12;
          Serial.print("Avg: ");
          Serial.println(avg);
          count = 0;
          total = 0.;
        }
      }
    } 
    while ((dist1 >= 0) && (dist2 >= 0)) {
      diff = dist2 - dist1;
      //Serial.print("Diff: ");
      //Serial.println(diff);
      t = t2 - t1;
      //Serial.print("T: ");
      //Serial.println(t);
      Speed = diff * (1000000 / t);
      Speed = Speed * 3.6;
      //Serial.print("Speed: ");
      //Serial.println(Speed);
      //Serial.print('\n');
      //if ((Speed < 1.) && (Speed > -1.)) {
        tot += Speed;
        c += 1;
      //}   
      if (c >= 20) {
        avg = tot / 20;
        Serial.print("Average Speed: ");
        Serial.println(avg);
        Serial.println(printCount);
        printCount ++;
        tot = 0;
        c = 0;  
      }
      dist1 = dist2;
      //Serial.print("dist1 = ");
      //Serial.println(dist1);
      dist2 = -1;
      t1 = t2;
      //Serial.print("t1: ");
      //Serial.println(t1);
      //boo = false;
    }
    relVel = avg + average;
    //Serial.println(relVel);
  }
  delay(400);  
}
