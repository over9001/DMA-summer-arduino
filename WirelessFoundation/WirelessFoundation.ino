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
//                        //   //                        //   
//      X   D11  D7  3V3  //   //      X   D51  D7  3V3  //   
//     D12  D13  D8  GND  //   //     D50  D52  D8  GND  //   
//************************//   //************************//   

#include <SPI.h>
#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>

byte data[30];

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
int i = 0;
int j = 0;
int k = 0;
int l = 0;
int m = 0;
int n = 0;
int o = 0;
int p = 0;
int q = 0;
int r = 0;
int s = 0;
int t = 0;
int u = 0;
int v = 0;
int w = 0;
int x = 0;
int y = 0;
int z = 0;

int allDataValsPrev[26] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
int allDataVals[26] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};

void TransmitterSetup(int channel)
{
  mode = 0;
  Mirf.spi = &MirfHardwareSpi;
  // init the transceiver
  Mirf.init();
  
  // we transmit only a single byte each time
  Mirf.payload = 30;
  
  // selecting a channel which is not too noisy
  Mirf.channel = channel;
  Mirf.config();
 
  // Set 1MHz data rate
  Mirf.configRegister(RF_SETUP,0x06);
  
  // Set address - this one must match the 
  // address the receiver is using!
  Mirf.setTADDR((byte *)"TX_01");
}

void SendData()
{
  if(millis()-timer > 1)
  {
    for(int count = 0; count < 26; count++)
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
  byte allData[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  allData[0] = 0;
  for(counter; counter < 78; counter += 3)
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
      Serial.print(char(allData[byteCounter]));
      Serial.print(" ");
      Serial.print(allData[byteCounter+1]*255+allData[byteCounter+2]);
      delay(10);
      
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
    Serial.println();
  }
  else if(counter < 78 && byteCounter == 10)
  { 
    Serial.println();
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
    case 'i':
      return i;
      break;
    case 'j':
      return j;
      break;
    case 'k':
      return k;
      break;
    case 'l':
      return l;
      break;
    case 'm':
      return m;
      break;
    case 'n':
      return n;
      break;
    case 'o':
      return o;
      break;
    case 'p':
      return p;
      break;
    case 'q':
      return q;
      break;
    case 'r':
      return r;
      break;
    case 's':
      return s;
      break;
    case 't':
      return t;
      break;
    case 'u':
      return u;
      break;
    case 'v':
      return v;
      break;
    case 'w':
      return w;
      break;
    case 'x':
      return x;
      break;
    case 'y':
      return y;
      break;
    case 'z':
      return z;
      break;
  }
}


//Receiver

void ReceiverSetup(int channel)
{
  mode = 1;
  Serial.begin(57600);
  
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  
  // name the receiving channel - must match tranmitter setting!
  Mirf.setRADDR((byte *)"TX_01");
  
  // just a single byte is transmitted
  Mirf.payload = 30;

  // we use channel 90 as it is outside of WLAN bands 
  // or channels used by wireless surveillance cameras 
  Mirf.channel = channel;
  
  // now config the device.... 
  Mirf.config();  
  
  // Set 1MHz data rate - this increases the range slightly
  Mirf.configRegister(RF_SETUP,0x06);
}

int GetData()
{
  byte data[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  if(Mirf.dataReady())
  {
    Mirf.getData(data);
    //delay(25);
    for(int i = 0; i < 30; i += 3)
    {
      //Serial.print(char(data[0+i]));
      //Serial.print(" = ");
      //Serial.println(int(data[1+i]*255+data[2+i]));
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
  Serial.print(" i=");
  Serial.print(i);
  Serial.print(" j=");
  Serial.print(j);
  Serial.print(" k=");
  Serial.print(k);
  Serial.print(" l=");
  Serial.print(l);
  Serial.print(" m=");
  Serial.print(m);
  Serial.print(" n=");
  Serial.print(n);
  Serial.print(" o=");
  Serial.print(o);
  Serial.print(" p=");
  Serial.print(p);
  Serial.print(" q=");
  Serial.print(q);
  Serial.print(" r=");
  Serial.print(r);
  Serial.print(" s=");
  Serial.print(s);
  Serial.print(" t=");
  Serial.print(t);
  Serial.print(" u=");
  Serial.print(u);
  Serial.print(" v=");
  Serial.print(v);
  Serial.print(" w=");
  Serial.print(w);
  Serial.print(" x=");
  Serial.print(x);
  Serial.print(" y=");
  Serial.print(y);
  Serial.print(" z=");
  Serial.print(z);
  Serial.println();
  delay(50);
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
    case 'i':
      i = val;
      break;
    case 'j':
      j = val;
      break;
    case 'k':
      k = val;
      break;
    case 'l':
      l = val;
      break;
    case 'm':
      m = val;
      break;
    case 'n':
      n = val;
      break;
    case 'o':
      o = val;
      break;
    case 'p':
      p = val;
      break;
    case 'q':
      q = val;
      break;
    case 'r':
      r = val;
      break;
    case 's':
      s = val;
      break;
    case 't':
      t = val;
      break;
    case 'u':
      u = val;
      break;
    case 'v':
      v = val;
      break;
    case 'w':
      w = val;
      break;
    case 'x':
      x = val;
      break;
    case 'y':
      y = val;
      break;
    case 'z':
      z = val;
      break;
  }
}
