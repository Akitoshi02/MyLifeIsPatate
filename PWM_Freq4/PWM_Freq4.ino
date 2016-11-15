//****************************************************************************************
// PWM Square Wave Generator
// VLO 2013-2014
//****************************************************************************************


const int outPin = 9; // output pin
const float maxFreq = 16000000; //max freq supported by Arduino (16MHz)

void setup()
{

  Serial.begin(115200); //for sending A0 pin values
  
    tone(9, 6000); //génération de la fréquence sur le pin 9
  
  //for test
  //Serial.println();
  //Serial.println(ICR1);
  //Serial.println(TCCR1B);
}

void loop()
{


  int val = analogRead(0);                                              
  Serial.write( 0xff );                                                         
  Serial.write( (val >> 8) & 0xff );                                            
  Serial.write( val & 0xff );

 
}

//set frequency (Hz)
//min frequency: 0.24 Hz
//max frequency: 8MHz

