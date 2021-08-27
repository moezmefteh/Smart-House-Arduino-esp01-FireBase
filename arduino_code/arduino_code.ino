#include <dht.h>
#include <Servo.h>

Servo servo_port;
dht DHT;
char c;
String h;
int gaz,trouve=1;

#define DHT11_PIN 7
int analoog = A3; // define the flame sensor interface
int sensor; //read analoog value
long time = 0;
int counter = 0;
const int pin_INTERRUPTEUR1 = 2;
const int pin_INTERRUPTEUR2 = 3;
const int pin_INTERRUPTEUR3 = 18;

String l_chambre_n="0",l_bain_n="0";
String fen_n="0",porte_n="0",gaz_n="0";
int tem_n=25,hum_n=20;
const int mqxPin = A4;

const int pin_LED1 = 12;
const int pin_LED2 = 11;
const int pin_LED3 = 10;
const int pin_LED4 = 9;
const int pin_LEDR = 17;
const int pin_LEDV = 16;

boolean ledAllumer1 = 0;
boolean boutonAppuyer1 = 0;
boolean ledAllumer2 = 0;
boolean boutonAppuyer2 = 0;
boolean ledAllumer3 = 0;
boolean boutonAppuyer3 = 0;


////////////////////////

void readFromESP(); 
void writeToESP();

void setup(){
Serial.begin(115200);
pinMode(pin_INTERRUPTEUR1, INPUT_PULLUP);
pinMode(pin_INTERRUPTEUR2, INPUT_PULLUP); 
pinMode(pin_INTERRUPTEUR3, INPUT_PULLUP); 
 
pinMode (analoog, INPUT) ;
pinMode(pin_LED1, OUTPUT);
pinMode(pin_LED2,OUTPUT);
pinMode(pin_LED3,OUTPUT);
pinMode(pin_LED4,OUTPUT);
pinMode(pin_LEDR,OUTPUT);
pinMode(pin_LEDV,OUTPUT);
digitalWrite(pin_LED3,HIGH);
digitalWrite(pin_LED4,HIGH);

digitalWrite(pin_LEDV,HIGH);
digitalWrite(pin_LEDR,LOW);
attachInterrupt(digitalPinToInterrupt(pin_INTERRUPTEUR1), onEvent1, CHANGE);
attachInterrupt(digitalPinToInterrupt(pin_INTERRUPTEUR2), onEvent2, CHANGE);
attachInterrupt(digitalPinToInterrupt(pin_INTERRUPTEUR3), onEvent3, CHANGE);


}

//////////////////////////////////////////////// 

void loop(){
 boolean StringReady = false;
 


 while (Serial.available()){
   readFromESP();
   StringReady= true;
  
  if (StringReady){
    if (h[0]=='1' && l_chambre_n=="0"){
      l_chambre_n="1";
      digitalWrite(pin_LED1,HIGH);
    }
    else if (h[0]=='0' && l_chambre_n=="1"){
      l_chambre_n="0";
      digitalWrite(pin_LED1,LOW);
    }
   if (h[1]=='1' && l_bain_n=="0"){
     l_bain_n="1";
      digitalWrite(pin_LED2,HIGH);
    }
    else if (h[1]=='0' && l_bain_n=="1"){
      l_bain_n="0";
      digitalWrite(pin_LED2,LOW);
    } 
    if (h[2]=='1' && fen_n=="0"){
      fen_n="1";
      digitalWrite(pin_LED3,LOW);
    } 
    else if (h[2]=='0' && fen_n=="1"){
      fen_n="0";
      digitalWrite(pin_LED3,HIGH);
    } 
   
    if (h[3]=='1' && porte_n=="0"){
      porte_n="1";
      digitalWrite(pin_LED4,LOW);
    } 
    else if (h[3]=='0' && porte_n=="1"){
      porte_n="0";
      digitalWrite(pin_LED4,HIGH);
    }
    } 

 
    }
gaz=analogRead(mqxPin);
int chk = DHT.read11(DHT11_PIN);
tem_n=int(DHT.temperature);
hum_n=int(DHT.humidity);
if(trouve==1){
    writeToESP();
    trouve=0;
}
if((gaz>250) && (gaz_n=="0") ){
  gaz_n="1";
  digitalWrite(pin_LEDR,HIGH);
  digitalWrite(pin_LEDV,LOW);

  trouve=1;

}
else if((gaz<250) && (gaz_n=="1") ){
  gaz_n="0";
  digitalWrite(pin_LEDV,HIGH);
  digitalWrite(pin_LEDR,LOW);
  trouve=1;
 } 

  }

  
 /////////////////////////////////////////////////////////
void writeToESP(){
    Serial.print(l_chambre_n.toInt());
    Serial.print(l_bain_n.toInt());
    Serial.print(fen_n.toInt());
    Serial.print(porte_n.toInt());
    Serial.print(gaz_n.toInt());
    Serial.print(tem_n);
    Serial.println(hum_n);
 } 
void readFromESP() {
h="";
  while (Serial.available()) {
    c = Serial.read();
    h += c;
    delay(4);
  }
 }

 void onEvent1() { 
boolean etatBouton1 = digitalRead(pin_INTERRUPTEUR1) ; // Récupère l’état du bouton
if(etatBouton1 == 0 and boutonAppuyer1 == 0) { // On appuie sur le bouton
boutonAppuyer1 = 1;
if(ledAllumer1 == 0) { // Si la led est éteinte on l’allume
digitalWrite(pin_LED1,HIGH);
ledAllumer1 = 1;
l_chambre_n="1";
writeToESP();
}

else { // Si la led est allumée on l’éteint
digitalWrite(pin_LED1,LOW);

ledAllumer1 = 0;
l_chambre_n="0";
writeToESP();
}
}

if(etatBouton1 == 1 and boutonAppuyer1 == 1) { //On arrête d’appuyer sur le bouton
boutonAppuyer1 = 0;
}}


 void onEvent2() { 
boolean etatBouton2 = digitalRead(pin_INTERRUPTEUR2) ; // Récupère l’état du bouton
if(etatBouton2 == 0 and boutonAppuyer2 == 0) { // On appuie sur le bouton
boutonAppuyer2 = 1;
if(ledAllumer2 == 0) { // Si la led est éteinte on l’allume
digitalWrite(pin_LED2,HIGH);

ledAllumer2 = 1;
l_bain_n="1";
writeToESP();
}

else { // Si la led est allumée on l’éteint
digitalWrite(pin_LED2,LOW);
ledAllumer2 = 0;
l_bain_n="0";
writeToESP();
}
}

if(etatBouton2 == 1 and boutonAppuyer2 == 1) { //On arrête d’appuyer sur le bouton
boutonAppuyer2 = 0;
}}
 void onEvent3() { 
boolean etatBouton3 = digitalRead(pin_INTERRUPTEUR3) ; // Récupère l’état du bouton
if(etatBouton3 == 0 and boutonAppuyer3 == 0) { // On appuie sur le bouton
boutonAppuyer3 = 1;
if(ledAllumer3 == 0) { // Si la led est éteinte on l’allume
digitalWrite(pin_LED3,LOW);

ledAllumer3 = 1;
fen_n="1";
writeToESP();
}

else { // Si la led est allumée on l’éteint
digitalWrite(pin_LED3,HIGH);

ledAllumer3 = 0;
fen_n="0";
writeToESP();
}
}

if(etatBouton3 == 1 and boutonAppuyer3 == 1) { //On arrête d’appuyer sur le bouton
boutonAppuyer3 = 0;
}}
