void setup()
{
  ReceiverSetup(100);
  Serial.begin(9600);
}

void loop()
{
  GetData();
  Serial.print("Sent: ");
  PrintData();
}
