/** Code par MrMOI54 */
float vPow = 4.7;
 float r1 = 30000;
 float r2 = 7500;
 
 void setup() {
   

   Serial.begin(9600);
   Serial.println("--------------------");
   Serial.println("WWW.MRMOI54.COM/TUTO");
   Serial.println("--------------------");
   Serial.println("DC VOLTMETRE");
   Serial.print("Tension Maximum: ");
   Serial.print((int)(vPow / (r2 / (r1 + r2))));
   Serial.println("V");
   Serial.println("--------------------");
   Serial.println("");
   
   delay(2000);
   
 }
 
 void loop() {
   float v = (analogRead(0) * vPow) / 1024.0;
   float v2 = v / (r2 / (r1 + r2));

   Serial.print(v2);
   Serial.println("V");
   delay(200);
 }
