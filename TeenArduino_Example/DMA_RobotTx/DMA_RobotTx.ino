//This is the source code for the nRF24L01 Module - Sam Jaffe for DMA

//TransmitterSetup( channel )    call once to set up transmitter
//SendData()                     call to send a,b,c...z

//ReceiverSetup( channel )       call once to set up receiver
//GetData()                      call to update a,b,c...z

//**bottom view NANO******//   //**bottom view MEGA******//   
//                        //   //                        //   
//                        //   //                        //   
//                        //   //                        //   
//                        //   //                        //   
//                        //   //                        //   
//                        //   //                        //   
//                        //   //                        //   
//                        //   //                        //   
//                         //   //                        //   
//      X   D11  D7  3V3  //   //      X   D51  D7  3V3  //   
//     D12  D13  D8  GND  //   //     D50  D52  D8  GND  //Â   
//************************//   //************************//   

#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>

byte data[8];

long timer = 0;

int mode = 0;

int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;
int g = 0;
int h = 0;

int allDataValsPrev[8] = {a,b,c,d,e,f,g,h};
int allDataVals[8] = {a,b,c,d,e,f,g,h};

void TransmitterSetup(int channel)
{
  mode = 0;
  Mirf.spi = &MirfHardwareSpi;
  // init the transceiver
  Mirf.init();
  
  // we transmit only a single byte each time
  Mirf.payload = 8;
  
  // selecting a channel which is not too noisy
  Mirf.channel = channel;
  Mirf.config();
 
  // Set 1MHz data rate
  Mirf.configRegister(RF_SETUP,0x06);
  
  // Set address - this one must match the 
  // address the receiver is using!
  Mirf.setTADDR((byte *)"TX_01");
  
   byte rf_setup = 0;
  Mirf.readRegister( RF_SETUP, &rf_setup, sizeof(rf_setup) );
  Serial.print( "rf_setup = " );
  Serial.println( rf_setup, BIN );
  
}

void SendData()
{
  if(millis()-timer > 1)
  {
    for(int count = 0; count < 8; count++)
    {
      allDataVals[count] = ReturnVal('a'+count);
    }
    SendAllData(0);
    timer = millis();
  }
}

void SendAllData(int counter)
{
  int byteCounter = 0;
  byte allData[8] = {0,0,0,0,0,0,0,0};
  allData[0] = 0;
  for(counter; counter < 24; counter += 3)
  {
    if(allDataVals[counter/3] != allDataValsPrev[counter/3])
    {
      int value = allDataVals[counter/3];
      allData[byteCounter*3] = ('a'+counter/3);
      if(value < 32768 && value >= 0)
      {
        if(value > 255)
        {
          allData[(byteCounter*3+1)] = floor(value/255);
          value %= 255;
        }
        else
        {
          allData[(byteCounter*3+1)] = 0;
        }
        allData[(byteCounter*3+2)] = value;
      }
      /*
      Serial.print(char(allData[byteCounter]));
      Serial.print(" ");
      Serial.print(allData[byteCounter+1]*255+allData[byteCounter+2]);
      */
      //delay(10);
      
      allDataValsPrev[counter/3] = allDataVals[counter/3];
      
      byteCounter++;
      if(byteCounter >= 10)
      {
        break;
      }
    }
  }
  if(allData[0] != 0)
  {
    Mirf.send(allData);
    while(Mirf.isSending());
    Mirf.send(allData);
    while(Mirf.isSending());
    //Serial.println();
  }
  else if(counter < 78 && byteCounter == 10)
  { 
    //Serial.println();
    Serial.println();
    SendAllData(counter);
  }
}

int ReturnVal(char address)
{
  switch(address)
  {
    case 'a':
      return a; 
      break;
    case 'b':
      return b;
      break;
    case 'c':
      return c;
      break;
    case 'd':
      return d;
      break;
    case 'e':
      return e;
      break;
    case 'f':
      return f;
      break;
    case 'g':
      return g;
      break;
    case 'h':
      return h;
      break;
  }
}


//Receiver

void ReceiverSetup(int channel)
{
  mode = 1;
  Serial.begin(57600);
  //Mirf.csnPin = 7;
  //Mirf.cePin = 8;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  // name the receiving channel - must match tranmitter setting!
  Mirf.setRADDR((byte *)"TX_01");
  
  // just a single byte is transmitted
  Mirf.payload = 8;

  // we use channel 90 as it is outside of WLAN bands 
  // or channels used by wireless surveillance cameras 
  Mirf.channel = channel;
  
  // now config the device.... 
  Mirf.config();  
  
  // Set 1MHz data rate - this increases the range slightly
  Mirf.configRegister(RF_SETUP,0x06);
  
  byte rf_setup = 0;
  Mirf.readRegister( RF_SETUP, &rf_setup, sizeof(rf_setup) );
  Serial.print( "rf_setup = " );
  Serial.println( rf_setup, BIN );

  Serial.println( "Wireless initialized!" );
  
}

int GetData()
{
   //Serial.print(" = ");
  byte data[8] = {0,0,0,0,0,0,0,0};
  if(Mirf.dataReady())
  {
    Mirf.getData(data);
    delay(5);
    Serial.println();
    for(int i = 0; i < 8; i += 3)
    {
      /*
      Serial.print(char(data[0+i]));
      Serial.print(" = ");
      Serial.println(int(data[1+i]*255+data[2+i]));
      */
      SetVariables(char(data[0+i]), int(data[1+i]*255+data[2+i]));
    }
    return(1);
  }
  else
  {
    return(0);
  }
}

void PrintData()
{
  Serial.print("a=");
  Serial.print(a);
  Serial.print(" b=");
  Serial.print(b);
  Serial.print(" c=");
  Serial.print(c);
  Serial.print(" d=");
  Serial.print(d);
  Serial.print(" e=");
  Serial.print(e);
  Serial.print(" f=");
  Serial.print(f);
  Serial.print(" g=");
  Serial.print(g);
  Serial.print(" h=");
  Serial.print(h);
  Serial.println();
  delay(20);
}

void SetVariables(char address, int val)
{
  switch(address)
  {
    case 'a':
      a = val;
      break;
    case 'b':
      b = val;
      break;
    case 'c':
      c = val;
      break;
    case 'd':
      d = val;
      break;
    case 'e':
      e = val;
      break;
    case 'f':
      f = val;
      break;
    case 'g':
      g = val;
      break;
    case 'h':
      h = val;
      break;
  }
}
