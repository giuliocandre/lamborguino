int state = 4; // stop
int nxtState = 0; // avanti
bool X,D,S;
const int trig = A5;
int echo[3];

void setup() {

  // Set pins 
  echo[0] = A4; // left
  echo[1] = A3; // right
  echo[2] = A2; // forward
  // initialize serial communication:
  Serial.begin(9600);
}


long measureCm(int pin) {
    long duration, cm;
  String direzione;
  switch (pin) {
    case 0:
      direzione = "Left";
      break;
     case 1:
      direzione = "Right";
     break;
     case 2:
      direzione = "Forward";
     break;
  }
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
  Serial.print("distance ");
  Serial.print(direzione);
  Serial.print(" ");
  Serial.println(cm);
  delay(1000);
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
}

void getDangers() {
  X = (measureCm(2) > 10);
  D = (measureCm(1) > 10);
  S = (measureCm(0) > 10);
}



void loop() {

  if (state != nxtState) call(nxtState); // se lo stato è diverso da quello precedente allora devo chiamare la funzione corrispondente, altrimenti no
  // dopodichè calcolo il nuovo nxtState
  getDangers(); //  questa funzione mi deve settare tutti i valori X,S,D
  state = nxtState;
  
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
     
  }
  
}
