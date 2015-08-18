
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

//PWM outputs
int PWMA = 9;
int PWMB = 10;

//Motor Values
int motorA = 0;
int motorB = 0;

// the setup routine runs once when you press reset:
void setup() {
  shiftSetup();
  // initialize the digital pin as an output.
  //Serial.begin(9600);
  ReceiverSetup(10);
}

//makes Robot Drive foward
void driveForward() {
  motorDirection(1, 1);
  analogWrite(PWMA, motorA); //left wheel
  analogWrite(PWMB, motorB); //right wheel
  
}
void driveBackward() {
  motorDirection(2, 2);
  analogWrite(PWMA, motorA); //left wheel
  analogWrite(PWMB, motorB); //right wheel
}
void driveStop() {
 motorDirection(0,0);
  digitalWrite(PWMA, LOW); //left wheel
  digitalWrite(PWMB, LOW); //right wheel
}

void processData(){
 
 GetData();
 delay(2);
 motorA = a + b + c;
 motorB = a + b + d;

if(motorA > 240){ motorA = 240;} 
if(motorB > 240){ motorB = 240;} 
}

// the loop routine runs over and over again forever:
void loop(){
  processData();
 
  
  if(a > 2){driveForward();}
  else if(b > 2){driveBackward();}
  else if(c > 40 || d > 40){driveForward();}
  else{driveStop();}
 
  
  delay(1);
  
  
  
}



