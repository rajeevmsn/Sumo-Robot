const int trig = 1; //Trigger connected to PIN 1//
const int echo = 2; //Echo connected yo PIN 2//
const int lir=7; //left IR sensor to PIN 7//
const int rir=8; //right IR sensor to PIN 8//

// After connecting the IR sensors, adjust the range of the sensor by changing the position of the POT/variable resistor on the sensor.//
//position of the sensor and adjusting it accordingly is very important//

//Connect the driver IC pins that are connected to Motor
//Left Motor
#define left_mb 11 //Motor Black Wire to PIN 11
#define left_mr 10 //Motor Red wire to PIN 10
//Right Motor
#define right_mb 6
#define right_mr 5

void setup(){
  Serial.begin(9600);
  pinMode (trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(lir, INPUT);
  pinMode(rir, INPUT);
  pinMode (left_mb, OUTPUT);
  pinMode (left_mr, OUTPUT);
  pinMode (right_mb, OUTPUT);
  pinMode (right_mr, OUTPUT);
}
 
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

void drive_forward(){  // forward //
   analogWrite(left_mb, 5); //rotates left motor in forward//
   analogWrite(left_mr, 150);
   analogWrite(right_mb, 5); //rotates right motor in forward//
   analogWrite(right_mr, 150); 
}

void drive_forward1(){  // forward at higher speeds//
   analogWrite(left_mb, 0); //rotates left motor in forward//
   analogWrite(left_mr, 220);
   analogWrite(right_mb, 0); //rotates right motor in forward//
   analogWrite(right_mr, 220); 
}

void drive_backward(){  // backward //
   analogWrite(left_mr, 5); //rotates left motor in backward//
   analogWrite(left_mb, 150);
   analogWrite(right_mr, 5); //rotates right motor in backward//
   analogWrite(right_mb, 150); 
}

void drive_right(){  // right //
   analogWrite(left_mb, 5); //rotates left motor in forward//
   analogWrite(left_mr, 150);
   analogWrite(right_mr, 5); //rotates right motor in backward//
   analogWrite(right_mb, 150); 
}

void drive_left(){  // left //
   analogWrite(left_mr, 5); //rotates left motor in forward//
   analogWrite(left_mb, 150);
   analogWrite(right_mb, 5); //rotates right motor in backward//
   analogWrite(right_mr, 150); 
}

void drive_stop(){  // stop //
   analogWrite(left_mr, 0); //rotates left motor in forward//
   analogWrite(left_mb, 0);
   analogWrite(right_mb, 0); //rotates right motor in backward//
   analogWrite(right_mr, 0); 
}

void loop(){
  long d, cm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  d=pulseIn(echo, HIGH); 
  cm = microsecondsToCentimeters(d);
  if (digitalRead(lir)==LOW & digitalRead(rir)==LOW) //when both Left IR and Right IR sensors are out of the arena
{
  drive_stop();
  delay(300);
  drive_backward();
  delay(350);
  drive_left();
  delay(300);
}
else if (digitalRead(lir)==LOW & digitalRead(rir)==HIGH) //when both Left IR sensor is Outside and Right IR sensor is inside the arena
{
  drive_stop();
  delay(200);
  drive_backward();
  delay(350);
  drive_right();
  delay(200);
}
else if (digitalRead(lir)==HIGH & digitalRead(rir)==LOW) //when both Right IR sensor is Outside and Left IR sensor is inside the arena
{
  drive_stop();
  delay(200);
  drive_backward();
  delay(350);
  drive_left();
  delay(200);
}

if (digitalRead(lir)==HIGH & digitalRead(rir)==HIGH)
{
  if(cm<=7) //if there is an opponent
{
  drive_forward1();
 }
 else //if there is no opponent
 {
  drive_forward();
  delay(400);
  drive_right();
  delay(800);
 }
}
Serial.println(cm);  
Serial.print("cm");
delay(300);
}

