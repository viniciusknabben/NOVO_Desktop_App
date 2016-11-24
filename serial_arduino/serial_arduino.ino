void setup() 
{
  Serial.begin(9600);
  pinMode(8,INPUT); 
}

void loop() 
{
  unsigned int data;
  unsigned char *bytes;
  bytes =(unsigned char*)&data;

  float pi_frac = 3.14159/32.;
  float frac = 0;

  /*
  while(1)
  {
      if(digitalRead(8) == HIGH)
      {
        data = (sin(frac)+1)*32767;
        Serial.write(bytes,2); 
        delay(1000);
        frac+=pi_frac; 
      }  
  }
  */
  
  for(int x=0;x<64;x++)
  {
    data = (sin(frac)+1)*32767;
    Serial.write(bytes,2);
    //delay(1);
    delayMicroseconds(260);
    frac+=pi_frac;
  }

}
