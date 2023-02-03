#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Servo.h>

Servo servo;
TinyGPSPlus gps;

SoftwareSerial Serial1(8,9);
SoftwareSerial gpsSerial(11,12);

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
int turn = 50;
int printCount;

long lat1_bill,long1_bill,raw_lat1,raw_long1 = 0;
long lat2_bill,long2_bill;
int lat1_deg,long1_deg = 0;
int lat2_deg,long2_deg;
long raw_lat2 = 2000000000;
long raw_long2 = 2000000000;
float dlat,dlong;
float distance; // CONSIDER FLOAT OR LONG?
long t1,t2,dt;
float Speed;
float total, avg = 0.0;
int c = 0;
const float pi = 3.1415;
const long d = 6371000;
float kmh;

const long mill = 1000000;
int data;


void setup() {
  // put your setup code here, to run once:
  gpsSerial.begin(9600);
  Serial.begin(9600);
//  if (gpsSerial.available()) {
//    data = gpsSerial.read();
//    if (gps.encode(data)) {
//      if (gps.location.isValid()) {
//        
//        // Raw Latitude 1
//        lat1_deg = (gps.location.rawLat().deg);
//        lat1_bill = (gps.location.rawLat().billionths);
//        raw_lat1 = (lat1_bill * 0.001) + (lat1_deg * mill);
//        Serial.print("Raw Lat 1: ");
//        Serial.println(raw_lat1);
//        
//        // Raw Longitude 1
//        long1_deg = (gps.location.rawLng().deg);
//        long1_bill = (gps.location.rawLng().billionths);
//        raw_long1 = (long1_bill * 0.001) + (long1_deg * mill);
//        Serial.print("Raw Long 1: ");
//        Serial.println(raw_long1);
//      }
//
//      // Time 1
//      t1 = micros();
//      Serial.print("T1: ");g
//      Serial.println(t1);
//    }
//  }
}

void loop() {
  // put your main code here, to run repeatedly:

}



void setup() {

}

void loop() {
  while (gpsSerial.available()) {
    data = gpsSerial.read();
    if (gps.encode(data)) {
      if (gps.location.isValid()) {
        
        // Raw Latitude 2
        lat2_deg = (gps.location.rawLat().deg);
        lat2_bill = (gps.location.rawLat().billionths);
        raw_lat2 = (lat2_bill * 0.001) + (lat2_deg * mill);
        //Serial.print("Raw Lat 2: ");
        //Serial.println(raw_lat2);
        
        // Raw Longitude
        long2_deg = (gps.location.rawLng().deg);
        long2_bill = (gps.location.rawLng().billionths);
        raw_long2 = (long2_bill * 0.001) + (long2_deg * mill);
//        Serial.print("Raw Long 2: ");
//        Serial.println(raw_long2);
      }

      // Time 2
      t2 = micros();
//      Serial.print("T2: ");
//      Serial.println(t2);
      
    }
  }

//  Serial.println("*-------------------*--------------NO DATA --------------*-------------------*");
  if (((raw_lat2 >= -90000000) && (raw_lat2 <= 90000000)) && ((raw_long2 >= -180000000) && (raw_long2 <= 180000000))) {
    // Change in Raw Latitude
    dlat = raw_lat2 - raw_lat1;
//    Serial.print("D Lat: ");
//    Serial.println(dlat);
    dlat = dlat * 0.11;
//    Serial.print("D Lat: ");
//    Serial.println(dlat);
    
    // Change in Raw Longitude
    dlong = raw_long1 - raw_long2;
//    Serial.print("D Long: ");
//    Serial.println(dlong);
    dlong = dlong * 0.11;
//    Serial.print("D Long: ");
//    Serial.println(dlong);
    
    // Change in Time
    dt = t2 - t1; 
//    Serial.print("dt: ");
//    Serial.println(dt);
  
    // Distance - Pythagoras' Theorem
    distance = sqrt(sq(dlat) + sq(dlong));
//    Serial.print("Distance: ");
//    Serial.println(distance);
  
    // Speed = d / t
    Speed = distance * (1000000 / dt);
//    Serial.print("SPEED: ");
//    Serial.println(Speed);
    //Serial.print('\n');
    //if (Speed > 0.) {
      //Serial.print("SPEED KMPH: ");
      kmh = Speed * 1.6;
      //Serial.println(kmh);
      //ppSerial.print('\n');
    //}

    // Avg Speed
    total += kmh;
    c += 1;
    if (c >= 5) {
      avg = total / 5.;
      Serial.print("Average Speed: ");
      Serial.println(avg);
      total = 0.0;  
      c = 0;
    }
    
    // Reset
    raw_lat1 = raw_lat2;
//    Serial.print("Raw Lat 1: ");
//    Serial.println(raw_lat1);
    
    raw_long1 = raw_long2;
//    Serial.print("Raw Long 1: ");
//    Serial.println(raw_long1);
    
    t1 = t2;
//    Serial.print("T1: ");
//    Serial.println(t1);

    raw_lat2,raw_long2 = 2000000000;
  }
}




void setup() {
//  lcd.begin(16, 2);
  Serial.begin(9600);//set bit rate of serial port connecting Arduino with computer
  Serial1.begin(115200);//set bit rate of serial port connecting LiDAR with Arduino
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
    //Serial.println("Yes");    
    if (Serial1.available()) { //check if serial port has data input
      //Serial.println("YEET"); 
      if(Serial1.read()==HEADER) { //assess data package frame header 0x59 
        uart[0]=HEADER;
        if(Serial1.read()==HEADER) { //assess data package frame header 0x59
          uart[1]=HEADER;
          for(int i2 = 2; i2 < 9; i2++) {
            uart[i2]=Serial1.read();
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
    while ((dist1 >= 0) && (dist2 >= 0)) {
      diff = dist2 - dist1;
      //Serial.print("Diff: ");
      //Serial.println(diff);
      t = t2 - t1;
      //Serial.print("T: ");
      //Serial.println(t);
      Speed = diff * (1000000 / t);
      //Speed = Speed * 1.6;
      //Serial.print("Speed: ");
      //Serial.println(Speed);
      //Serial.print('\n');
      if ((Speed < 1.) && (Speed > -1.)) {
        avg += Speed;
        c += 1;
      }   
      if (c >= 20) {
        avg = avg / 20;
        Serial.print("Average Speed: ");
        Serial.println(avg);
        Serial.println(printCount);
        printCount ++;
        avg = 0;
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
  }
  delay(400);  
}
