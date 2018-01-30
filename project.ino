// Sketch of the program 
// Global variables & pre-instructions
// BT part
#include <SoftwareSerial.h>

#define  BT_RX 12            // PIN to receive from bluetooth
#define  BT_TX 13            // PIN TO transmit to bluetooth
SoftwareSerial btSerial(BT_RX, BT_TX);
String BT_message;
// Motor part
// motori sinsitra
int enA = 11; //enA ruote a sinistra
int in1 = 9;
int in2 = 8;
// motori destra
int enB = 5; //enB ruote a destra
int in3 = 7;
int in4 = 6;


/**** Custom functions ****/ 

/*** Motor part ****/ 
void indietro(){

  //ruote a sinistra all'indietro
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //ruote a destra all'indietro
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 50);
  analogWrite(enB, 50);
  delay(1000);

  
}

void avanti(){
  
   //ruote a sinistra in avanti
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //ruote a destra in avanti
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  delay(1000);
}

void curvaSx(){

  //ruote a sinistra all'indietro
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // ruote a destra in avanti
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // per quanto riguarda la velocità, non ho la minima idea: facciamo curvare per un tempo indicativo T=1000 e poi fermiamo
  analogWrite(enA, 33);
  analogWrite(enB, 33);
  delay(1000);
}

void curvaDx(){

   //ruote a sinistra in avanti
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   //ruote a destra all'indietro
   digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   // per quanto riguarda la velocità, non ho la minima idea, facciamo curvare per un tempo indicativo T=1000 ms e poi fermiamo
  analogWrite(enA, 33);
  analogWrite(enB, 33);
  delay(1000);
}

void ferma(){

   analogWrite(enA, 0);
   analogWrite(enB, 0);
   digitalWrite(in1, LOW);
   digitalWrite(in2, LOW);
   digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}




/**** Setup part ****/


void setup() {
  // Motor part
 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);
 
 // BT setup
 delay (2000);
 BT_message = "";
 Serial.begin(9600);        // Initialize USB Serial port
 btSerial.begin(9600);    // Initialize Bluetooth SoftwareSerial port for selected data speed
 Serial.println("--- BT Ports ready ---");
 Serial.println("");
}

/**** BT functions *****/
//void parseMessage(String 


/**** Loop part ***/
void loop() {

// BT part
 if (BT_message.indexOf("!") > -1) {
  Serial.println(BT_message);
  if (BT_message == "avanti!") avanti();
  if (BT_message == "indietro!") indietro();
  if (BT_message == "destra!") curvaDx();
  if (BT_message == "stop!") ferma();
  if (BT_message == "sinistra!") curvaSx();
  BT_message = "";
 }
 if (btSerial.available() > 0) { 
    BT_message.concat((char) btSerial.read());
    //Serial.println(BT_message); // ONLY FOR debugging purposes
 } 
 if (Serial.available() > 0) btSerial.write(Serial.read());
  

}

