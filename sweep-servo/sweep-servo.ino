// /* Sweep
//  by BARRAGAN <http://barraganstudio.com>
//  This example code is in the public domain.

//  modified 8 Nov 2013
//  by Scott Fitzgerald
//  https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
// */

// #include <Servo.h>

// Servo myservo;  // create servo object to control a servo
// // twelve servo objects can be created on most boards

// int pos = 170;    // variable to store the servo position
// int minimum = 0;
// int maximum = 180;
// int increment = 1;

// void setup() {
//   myservo.attach(11);  // attaches the servo on pin 9 to the servo object
//   Serial.begin(9600);
//   Serial.println("** start **");
// }

// void loop() {
//   for (pos = 5; pos <= 175; pos += 5) { // goes from 0 degrees to 180 degrees
//     // in steps of 1 degree
//     myservo.write(pos);              // tell servo to go to position in variable 'pos'
//     Serial.println(pos);
//     delay(1000);                       // waits 15 ms for the servo to reach the position
//   }
//   for (pos = 175; pos >= 5; pos -= 5) { // goes from 180 degrees to 0 degrees
//     myservo.write(pos);              // tell servo to go to position in variable 'pos'
//     Serial.println(pos);
//     delay(1000);                       // waits 15 ms for the servo to reach the position
//   }
// }
// // void loop() {
// //   if (pos <= minimum) { increment = +1; }
// //   if (pos >= maximum) { increment = -1; }
// //   if (pos <= maximum) { pos += increment; }
// //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
// //   Serial.println(pos);
// //   delay(500);
// // }
#include <Servo.h>

Servo servo;
int angle = 10;
void setup() {
  servo.attach(8);
  servo.write(angle);
}
void loop() 
{ 
 // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 
}
