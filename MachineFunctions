// motori sinsitra
int enA = 11;
int in1 = 9;
int in2 = 8;
// motori destra
int enB = 5;
int in3 = 7;
int in4 = 6;

//enB ruote a destra
//enA ruote a sinistra

void setup() {
 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);
}

void loop() {

  // funzione esempio
  avanti();
  delay(300);
  indietro();
  

}

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

void stop(){

   analogWrite(enA, 0);
   analogWrite(enB, 0);
  
}
