// Pin à connecter à la LED
int LEDPin = 4;
// Pin à connecter à la feuille de papier
int capSensePin = 2;
// Seuil de détection du capteur, à régler par essais
int touchedCutoff = 4;

void setup(){
  Serial.begin(9600);
  // Mise en place de la LED
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
}
// readCapacitivePin
//  Entrée: Arduino pin number
//  Sortie: Un nombre, de 0 à 17, représentant la capacité.
//  Lorsqu'on touche la sortie (ou quoi que ce soit attache), le nombre va augmenter
uint8_t readCapacitivePin(int pinToMeasure){
  // This is how you declare a variable which
  //  will hold the PORT, PIN, and DDR registers
  //  on an AVR
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  if ((pinToMeasure >= 0) && (pinToMeasure <= 7)){
    port = &PORTD;
    ddr = &DDRD;
    bitmask = 1 << pinToMeasure;
    pin = &PIND;
  }
  if ((pinToMeasure > 7) && (pinToMeasure <= 13)){
    port = &PORTB;
    ddr = &DDRB;
    bitmask = 1 << (pinToMeasure - 8);
    pin = &PINB;
  }
  if ((pinToMeasure > 13) && (pinToMeasure <= 19)){
    port = &PORTC;
    ddr = &DDRC;
    bitmask = 1 << (pinToMeasure - 13);
    pin = &PINC;
  }
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Make the pin an input WITHOUT the internal pull-up on
  *ddr &= ~(bitmask);
  // Now see how long the pin to get pulled up
  int cycles = 16000;
  for(int i = 0; i < cycles; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }
  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  
  return cycles;
}
void loop(){
  int valcap = readCapacitivePin(capSensePin);
  // Si le capteur atteint un certain seuil de tension, la led s'allume
  Serial.println(readCapacitivePin(capSensePin));
  if (valcap > 25 && valcap < 50) 
  {
    digitalWrite(LEDPin, HIGH);
  }
  else if (valcap > 50 && valcap < 70) 
  {
    
    digitalWrite(LEDPin, HIGH);
    delay(100);
    digitalWrite(LEDPin, LOW);
    delay(100);
  }
  else if (valcap > 80) 
  {
    digitalWrite(LEDPin, HIGH);
    delay(1000);
    digitalWrite(LEDPin, LOW);
    delay(1000);
  }
  else 
  {
    digitalWrite(LEDPin, LOW);
  }
  
}



