   

   
   //****************************************************************************************
// Illutron take on Disney style capacitive touch sensor using only passives and Arduino
// Dzl 2012
//****************************************************************************************


//                              10n
// PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
//               |            |
//              3.3k          |
//               |            V 1N4148 diode
//              GND           |
//                            |
//Analog 0 ---+------+--------+
//            |      |
//          100pf   1MOmhm
//            |      |
//           GND    GND



#define SET(x,y) (x |=(1<<y))				//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+



#define N 160  //How many frequencies

float results[N];            //-Filtered result buffer
float freq[N];            //-Filtered result buffer
int sizeOfArray = N;

 
//Définition des ports de sortie des couleurs led

const int LEDO = 2; 
const int LEDV = 4; 
const int LEDB = 7;  
   

void setup()
{
  
  
  TCCR1A=0b10000010;        //-Set up frequency generator
  TCCR1B=0b00011001;        //-+
  ICR1=110;
  OCR1A=55;
  //Led en OUTPUT
	pinMode(LEDO, OUTPUT);
	pinMode(LEDV, OUTPUT);
	pinMode(LEDB, OUTPUT);
	
  pinMode(9,OUTPUT);        //-Signal generator pin
  pinMode(8,OUTPUT);        //-Sync (test) pin

  Serial.begin(115200);

  for(int i=0;i<N;i++)      //-Preset results
    results[i]=0;         //-+
}

void loop()
{
       digitalWrite(LEDO, LOW);
      digitalWrite(LEDV, LOW);
      digitalWrite(LEDB, LOW);
  unsigned int d;

  int counter = 0;
  for(unsigned int d=0;d<N;d++)
  {

	
    int v=analogRead(0);    //-Read response signal
    CLR(TCCR1B,0);          //-Stop generator
    TCNT1=0;                //-Reload new frequency
    ICR1=d;                 // |
    OCR1A=d/2;              //-+
    SET(TCCR1B,0);          //-Restart generator

    results[d]=results[d]*0.5+(float)(v)*0.5; //Filter results
   
    freq[d] = d;
  
    Serial.println(results[45]);

    if (results[45] <= 640 && results[45] > 500) //Dans l'eau vert
    {
      digitalWrite(LEDO, HIGH);
      digitalWrite(LEDV, LOW);
      digitalWrite(LEDB, LOW);
    }
    else if (results[45] <= 710 && results[45] > 650)// Touché bleu
    {
      digitalWrite(LEDV, HIGH);
      digitalWrite(LEDB, LOW);
      digitalWrite(LEDO, LOW);
    }
    else if (results[45] > 715) // Attrapé vert droite
    {
     digitalWrite(LEDV, LOW);
     digitalWrite(LEDB, HIGH);
     digitalWrite(LEDO, LOW);
    }

 //   plot(v,0);              //-Display
 //   plot(results[d],1);
  // delayMicroseconds(1);

  
  }


//PlottArray(1,freq,results); //écrit les valeurs sur le port data
 

  TOG(PORTB,0);            //-Toggle pin 8 after each sweep (good for scope)
}
   

   
    
 
