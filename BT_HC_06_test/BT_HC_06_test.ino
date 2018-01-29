
/*    Serial.println("Lista dei comandi HC-06:\n");
  Serial.println("AT              Se la comunicazione funziona il modulo risponde OK");
  Serial.println("AT+VERSION      Restituisce la versione del firmware");
  Serial.println("AT+BAUDx        Imposta il Baudrate, al posto di x mettere 1 per 1200 bps, 2=2400, 3=4800, 4=9600, 5=19200, 6=38400, 7=57600, 8=115200, 9=230400, A=460800, B=921600, C=1382400");
  Serial.println("AT+NAMEstring   Al posto di string mettere il nome che vuoi dare al modulo (massimo 20 caratteri)");
  Serial.println("AT+PINxxxx      Imposta il pincode del modulo bluetooth (es.1234)");*/
#include <SoftwareSerial.h>

#define  BT_RX 12            // PIN to receive from bluetooth
#define  BT_TX 13            // PIN TO transmit to bluetooth

SoftwareSerial btSerial(BT_RX, BT_TX);
String BT_message;
void setup()
{
 // BT setup
 delay (2000);
 BT_message = "";
 Serial.begin(9600);        // Initialize USB Serial port
 btSerial.begin(9600);    // Initialize Bluetooth SoftwareSerial port for selected data speed
 Serial.println("--- BT Ports ready ---");
 Serial.println("");

}

void loop()
{
 if (BT_message.indexOf("!") > -1) {
  Serial.println(BT_message);
  BT_message = "";
 }
 if (btSerial.available() > 0) { 
    BT_message.concat((char) btSerial.read());
    //Serial.println(BT_message); // ONLY FOR debugging purposes
 } 
 if (Serial.available() > 0) btSerial.write(Serial.read());
 
}


