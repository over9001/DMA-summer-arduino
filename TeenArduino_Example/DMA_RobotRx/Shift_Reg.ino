int SER_Pin = 16;   //pin 14 on the 75HC595
int RCLK_Pin = 14;  //pin 12 on the 75HC595
int SRCLK_Pin = 15; //pin 11 on the 75HC595

//Location of Motor Controllers on the shift Register.
int AIN1 = 0;
int AIN2 = 1;
int BIN1 = 2;
int BIN2 = 3;

//Store State
int aState, bState;

//How many of the shift registers - change this
#define number_of_74hc595s 2

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

void shiftSetup() {
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);

  //reset all register pins
  clearRegisters();
  writeRegisters();
}


//set all register pins to LOW
void clearRegisters() {
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    registers[i] = LOW;
  }
}


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters() {

  digitalWrite(RCLK_Pin, LOW);

  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value) {
  registers[index] = value;
}

void motorDirection(int motorAout, int motorBout) {

  int statechange;

  if (aState != motorAout) {
    statechange = 1;

    if (motorAout == 2) {
      setRegisterPin(0, HIGH);
      setRegisterPin(1, LOW);

    } else if (motorAout == 1) {
      setRegisterPin(0, LOW);
      setRegisterPin(1, HIGH);

    } else {
      setRegisterPin(0, LOW);
      setRegisterPin(1, LOW);
    }
  }
  if (bState != motorBout) {
    statechange = 1;
    if (motorBout == 2) {
      setRegisterPin(2, HIGH);
      setRegisterPin(3, LOW);

    } else if (motorBout == 1) {
      setRegisterPin(2, LOW);
      setRegisterPin(3, HIGH);
    } else {
      setRegisterPin(2, LOW);
      setRegisterPin(3, LOW);
    }
  }
  //If states are changed update ouputs! Takes ~8ms
  if (statechange == 1) {
    writeRegisters();
    aState = motorAout;
    bState = motorBout;
  }
}


