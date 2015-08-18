//Bare Minimuim Driver code
int A_power = 255; //Motor A tweaking
int B_power = 255; //Motor B tweaking

int PWMA = 9; //  MotorA
int PWMB = 10; // MotorB

void setup() {
  
  //Shift Register Initialize
  shiftSetup();
}

// the loop routine runs over and over again forever:
void loop() {

  //Debugging! Uncomment Both PrintData(); & delay(50);
  //**********************
  //PrintData();
  //delay(50);
  //**********************
  driveForward(200, 200);
  delay(1000);
  driveStop();
  delay(1000);
  
  driveForward(200, 200);
  delay(100);
  driveStop();
  delay(100);
  
  
}

void driveForward(int aLeft, int bRight) { //Manual control of the robot.
  aLeft = map(aLeft, 0, 255, 0, A_power);
  bRight = map(bRight, 0, 255, 0, B_power);
  
  motorDirection(2, 2);
  analogWrite(PWMA, aLeft);
  analogWrite(PWMB, bRight);
}

void driveStop() {
  //mamapMotors();
  motorDirection(0, 0);
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
}
