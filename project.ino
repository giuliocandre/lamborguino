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

// Self-drive & proximity sensor part
int state = 4; // stop
int nxtState = 4; // avanti
bool X=true,D=true,S=true;
const int trig = A5;
int echo[3];
bool selfDrive = true;

/**** Custom functions ****/ 

/*** Motor part ****/ 
void indietro(){

  //ruote a sinistra all'indietro
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //ruote a destra all'indietro
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 30);
  analogWrite(enB, 30);
  //delay(1000);

  
}

void avanti(){
  
   //ruote a sinistra in avanti
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //ruote a destra in avanti
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 30);
  analogWrite(enB, 30);
  //delay(1000);
}

void curvaSx(){

  //ruote a sinistra all'indietro
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // ruote a destra in avanti
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // per quanto riguarda la velocità, non ho la minima idea: facciamo curvare per un tempo indicativo T=1000 e poi fermiamo
  analogWrite(enA, 10);
  analogWrite(enB, 10);
  //delay(1000);
}

void curvaDx(){

   //ruote a sinistra in avanti
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   //ruote a destra all'indietro
   digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   // per quanto riguarda la velocità, non ho la minima idea, facciamo curvare per un tempo indicativo T=1000 ms e poi fermiamo
  analogWrite(enA, 10);
  analogWrite(enB, 10);
  //delay(1000);
}

void ferma(){

   analogWrite(enA, 0);
   analogWrite(enB, 0);
   digitalWrite(in1, LOW);
   digitalWrite(in2, LOW);
   digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

/**** Self drive part******/


long measureCm(int pin) {
    long duration, cm;
 
  // The PING))) is triggered by a HIGH pulse of 12 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(12);
  digitalWrite(trig, LOW);

  // the echo pin provides a pulse
  // whose duration is the time (in microseconds) from the sending of the trigger
  // to the reception of its echo off of an object.
  pinMode(echo[pin], INPUT);
  duration = pulseIn(echo[pin], HIGH);

  // convert the time into a distance
  cm = (duration) / 29 / 2;
  return cm;
}


void call(int state) {
  Serial.print("State = ");
  Serial.println(state);
  Serial.print("X = ");
  Serial.println(X);
  Serial.print("S = ");
  Serial.println(S);
  Serial.print("D = ");
  Serial.println(D);
  switch(state) {
    case 0:
    avanti();
    break;
    case 1:
    curvaDx();
    break;
    case 2:
    indietro();
    break;
    case 3:
    curvaSx();
    break;
    case 4:
    ferma();
    break;
  }
}

void getDangers() {
  long dX=0, dD=0, dS=0;
  X=0; D=0; S=0;
  for (int i=0; i<3; i++) {
  dX =measureCm(2); dD = measureCm(1); dS = measureCm(0);
    X = X || (dX > 20);
    D = D || (dD > 20);
    S = S || (dS > 20);
  }
  Serial.print("distance X "); Serial.println(dX);
}

int nxtStateLogic(int state) {
    int nxtState;
    switch(state) { // 0 = avanti, 1 = dx, 2 = indietro, 3 = sx, 4 = stop
   
    case 0: 
      if (X) nxtState = 0; //se è libero davanti, continua così
      else {
        if (D) nxtState = 1; // se è libero a destra vai a destra
        else if (S) nxtState = 3; // se è libero a sinistra vai a sinistra
        else nxtState = 4; // stop 
      }
     break;

     case 1:
      if (X) nxtState = 0; // se è libero davanti vai avanti
      else {
        if (D) nxtState = 1; // se è libero a destra continua ad andare a destra
        else nxtState = 2; // altrimenti vai indietro
      }
     break;

     case 2:
      if (D) nxtState = 1; 
      else {
        if (S) nxtState = 3;
        else nxtState = 2;
        }
     break;

     case 3:
      if (X) nxtState = 0;
      else {
        if (S) nxtState = 3;
        else nxtState = 2;
      }
     break;
     case 4:
      nxtState=4;
     break;
     
     
  }
  return nxtState;
}
/***** BT functions Part *****/

void parseCommand(String BT_message) {
  if (BT_message == "drive!") {
    selfDrive = 1;
    nxtState = 0;
    call(0);
  } else {
    selfDrive = 0;
    if (BT_message == "avanti!") avanti();
    if (BT_message == "indietro!") indietro();
    if (BT_message == "destra!") curvaDx();
    if (BT_message == "stop!") ferma();
    if (BT_message == "sinistra!") curvaSx();
  }

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

 // sonar pins
   // Set pins 
  echo[0] = A4; // left
  echo[1] = A1; // right
  echo[2] = A2; // forward
}




/**** Loop part ***/
void loop() {
Serial.println(selfDrive);
// BT part
 if (BT_message.indexOf("!") > -1) {
  Serial.println(BT_message);
  parseCommand(BT_message);
  BT_message = "";
 }
 if (btSerial.available() > 0) { 
    BT_message.concat((char) btSerial.read());
    //Serial.println(BT_message); // ONLY FOR debugging purposes
 } 
 //if (Serial.available() > 0) btSerial.write(Serial.read());
  
// Self Drive part
  if (selfDrive) {
   if (state != nxtState) call(nxtState); // se lo stato è diverso da quello precedente allora devo chiamare la funzione corrispondente, altrimenti no
   // dopodichè calcolo il nuovo nxtState
   //getDangers(); //  questa funzione mi deve settare tutti i valori X,S,D
   state = nxtState;
   nxtState = nxtStateLogic(state);
  }
  
}

