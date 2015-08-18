int joystickXpin = A1;
int joystickYpin = A2;
int joystickButton = A3;

int joystickX = 0;
int joystickY = 0;

int counter = 0;
int xState = 0;
int yState = 0;


//Control Mapping
int fromMinH = 550;
int fromMaxH = 1024;
int fromMinL = 450;
int fromMaxL = 0;
int toMin = 30;
int toMax = 240;

long heartBeat_target = 0;
int heartBeat_inter = 500;
int heartBeat_state = 0;

void setup() {
  //Serial.begin(57600);
  TransmitterSetup(10);

}

void readJoystick() {
  joystickX = analogRead(joystickXpin);
  delay(5);
  joystickY = analogRead(joystickYpin);
  delay(5);
  
  if
  if (joystickX > fromMinH) {
    xState = 1;
    a = map(joystickX, fromMinH, fromMaxH, toMin, toMax);
    b = 0;
  } else if (joystickX < fromMinL) {
    xState = 1;
    a = 0;
    b = map(joystickX, fromMinL, fromMaxL, toMin, toMax);
  } else {
    if (xState == 1) {
      a = 0;
      b = 0;
      SendData();
      delay(2);
      a = 1;
      b = 1;
      SendData();
      delay(2);
      a = 0;
      b = 0;
      SendData();
      xState = 0;
    }
    a = 0;
    b = 0;
  }

  if (joystickY > fromMinH) {
    yState = 1;
    c = map(joystickY, fromMinH, fromMaxH, toMin, toMax);
    d = 0;
  } else if (joystickY < fromMinL) {
    yState = 1;
    c = 0;
    d = map(joystickY, fromMinL, fromMaxL, toMin, toMax);
  } else {
    if (yState == 1) {
      c = 0;
      d  = 0;
      SendData();
      delay(2);
      c = 1;
      d = 1;
      SendData();
      delay(2);
      c = 0;
      d = 0;
      SendData();
      yState = 0;
    }
    c = 0;
    d = 0;
  }
}

void loop() {
  readJoystick();
  delay(2);
  SendData();
  delay(1);
  PrintData();
}
