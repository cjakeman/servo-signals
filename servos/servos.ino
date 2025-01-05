
#include <Servo.h>

//int pos = 0;    // variable to store the servo position
Servo servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int profile[] = { // Up is index 0 to 8, down is index 8 to 18 
  0, 2, 5, 15, 30, 50, 65, 75, 77, 77, 75, 65, 40, 15, 0, 10, 15, 10, 3, 0, 0
};
float profileMaxY = 77.0;
int profileUpStart = 0;
int profileUpSpan = 9;
int profileDownStart = 9;
int profileDownSpan = 11;

int downAngle[] = {60} ;
int upAngle[] = {120} ;

unsigned long upMs = 1000;
unsigned long downMs = 900;

unsigned long motionStartMs = 0;
// unsigned long prevmotionStartMs = 0;
// unsigned long deltamotionStartMs = 0;

float profileX = 0;
float profileY = 0;
int prevX = 0;
int nextX = 0;
int outY = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  servo.attach(2);  // attaches the servo on pin 9 to the servo object
  servo.write(0);
}

int getAngle(int signalArm, int prevX, float profileX, int profile[]) {
  int nextX = prevX + 1;
  float profileY = profile[prevX] + ((profile[nextX] - profile[prevX]) * (profileX - prevX));
  int outY = downAngle[signalArm] + profileY * (upAngle[signalArm] - downAngle[signalArm]) / 77.0;
  return outY;
}

// the loop function runs over and over again forever
void loop() {
  motionStartMs = millis(); // time of motion start
  //deltamotionStartMs = motionStartMs - prevmotionStartMs;
  profileX = (profileUpSpan) * motionStartMs / (float)upMs;
  if (prevX < 20) { //] && profileY != 0.0) {
    prevX = (int)profileX;
    // nextX = prevX + 1;
    // profileY = profile[prevX] + ((profile[nextX] - profile[prevX]) * (profileX - prevX));
    // outY = downAngle[0] + profileY * (upAngle[0] - downAngle[0]) / profileMaxY;
    // servo.write(outY);

    servo.write(getAngle(0, prevX, profileX, profile));
    //Serial.print("prevX = "); Serial.print(prevX); Serial.print(", profileX = "); Serial.print(profileX); Serial.print(", outY = "); Serial.print(outY); Serial.print(", profileY = "); Serial.print(profileY); Serial.print(", deltamotionStartMs = "); Serial.println(deltamotionStartMs);
  }
  //prevmotionStartMs = millis();

    // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(1000);                       // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000);                       // wait for a second

  // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 ,
  //   servo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15 ms for the servo to reach the position
  // Y
  // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   servo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15 ms for the servo to reach the position
  // }
}