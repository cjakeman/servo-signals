
#include <Servo.h>

int profile[] = { // Up is index 0 to 8, down is index 8 to 18 
  0, 2, 5, 15, 30, 50, 65, 75, 77, 77, 75, 65, 40, 20, 0, 30, 15, 8, 3, 0, 0
};
float profileMaxY = 77.0;
int profileUpStart = 0;
int profileUpSpan = 9;
int profileDownStart = 9;
int profileDownSpan = 11;
int direction = 0;

int downAngle[] = {40} ;
int upAngle[] = {110} ;

unsigned long upMs = 1000;
unsigned long downMs = 900;

//unsigned long motionStartMs = 0;
unsigned long initialBlockMs = 1000;

// float profileX = 0;
// float profileY = 0;
// int prevX = 0;
// int nextX = 0;

enum SignalStates { DANGER, TO_CLEAR, CLEAR, TO_DANGER };
// Configure the SERVOS
// twelve servo objects can be created on most boards
const int SERVOS = 1;
Servo servo[SERVOS];
unsigned long motionStartMs[SERVOS];
int state[SERVOS];

enum Input { SENSED, UNSENSED }; // LOW, HIGH. Works with "pinMode(x, INPUT_PULLUP);" Connect pin to ground to sense input.
const int InPins[] = { 3 };
const int InPinCount = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  servo[0].attach(2);  // attaches servo on pin 2 to the servo object 0
  pinMode(3, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Set up completed");
}

int getAngle(int signalArm, int prevX, float profileX, int profile[]) {
  int nextX = prevX + 1;
  float profileY = profile[prevX] + ((profile[nextX] - profile[prevX]) * (profileX - prevX));
  int outY;
  if (direction == 1) {
    outY = downAngle[signalArm] + profileY * (upAngle[signalArm] - downAngle[signalArm]) / profileMaxY;
  }else{
    outY = upAngle[signalArm] + profileY * (downAngle[signalArm] - upAngle[signalArm]) / profileMaxY;
  }
  return outY;
}

// int operateSignal(int state, int i) {
//   switch(state) {
//     case DANGER:
//       if (digitalRead(InPins[0]) == UNSENSED) {
//         motionStartMs[i] = millis();
//         state = TO_CLEAR;
//       }
//       break;
//     case TO_CLEAR:
//       if (motionStartMs[i] + 1000 < millis()) {
//         state = CLEAR;
//       }
//       break;
//     case CLEAR:
//       if (digitalRead(InPins[0]) == SENSED) {
//         motionStartMs[i] = millis();
//         state = TO_DANGER;
//       }
//       break;
//     case TO_DANGER:
//       if (motionStartMs[i] + 1000 < millis()) {
//         state = DANGER;
//       }
//       break;
//     default:
//       state = CLEAR;
//       break;
//   }
//   Serial.print("state = "); Serial.println(state);
//   return state;
// }
int operateSignal(int state, int i) {
  float profileX = 0;
  unsigned long motionMs;
  int prevX = 0;

  switch(state) {
    case DANGER:
      if (digitalRead(InPins[0]) == UNSENSED) {
        motionStartMs[i] = millis();
        state = TO_CLEAR;
        Serial.println("state = TO_CLEAR");
      }
      break;
    case TO_CLEAR:
      motionMs = millis() - motionStartMs[i];
      profileX = 0 + (profileUpSpan * motionMs) / (float)upMs;
      prevX = (int)profileX;
      servo[i].write(getAngle(i, prevX, profileX, profile));
      Serial.print("prevX = "); Serial.println(prevX);
      if (prevX >= profileUpSpan) {
        state = CLEAR;
        Serial.println("state = CLEAR");
      }
      break;
    case CLEAR:
      if (digitalRead(InPins[0]) == SENSED) {
        motionStartMs[i] = millis();
        state = TO_DANGER;
        Serial.println("state = TO_DANGER");
      }
      break;
    case TO_DANGER:
      motionMs = millis() - motionStartMs[i];
      profileX = profileUpSpan + (profileDownSpan * motionMs) / (float)upMs;
      prevX = (int)profileX;
      servo[i].write(getAngle(i, prevX, profileX, profile));
      Serial.print("prevX = "); Serial.println(prevX);
      if (prevX >= profileUpSpan + profileDownSpan) {
        state = DANGER;
        Serial.println("state = DANGER");
      }
      break;
    default:
      state = CLEAR;
      break;
  }
  //Serial.print("state = "); Serial.println(state);
  return state;
}

// the loop function runs over and over again forever
void loop() {
  if (millis() > initialBlockMs) {
//     float profileX = 0;
// float profileY = 0;
// int prevX = 0;
// int nextX = 0;
  //   motionStartMs = millis() - initialBlockMs; // time of motion start
  //   //deltamotionStartMs = motionStartMs - prevmotionStartMs;
  //   profileX = (profileUpSpan) * motionStartMs / (float)upMs;
  //   if (prevX < profileUpSpan + profileDownSpan) { //] && profileY != 0.0) {
  //     prevX = (int)profileX;
  //     servo.write(getAngle(0, prevX, profileX, profile));
  //     //Serial.print("prevX = "); Serial.print(prevX); Serial.print(", profileX = "); Serial.print(profileX); Serial.print(", outY = "); Serial.print(outY); Serial.print(", profileY = "); Serial.print(profileY); Serial.print(", deltamotionStartMs = "); Serial.println(deltamotionStartMs);
  //   }
  // }
    for (int i = 0; i < SERVOS; i++) {
      digitalWrite(LED_BUILTIN, digitalRead(InPins[i]));
      state[i] = operateSignal(state[i], i);
    }
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