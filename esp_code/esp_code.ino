
//Library
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>


//Firebase Setting
#define FIREBASE_URL "https://smarthouse-f876a-default-rtdb.firebaseio.com/"    //Firebase URL
#define FIREBASE_AUTH "KdtohvQYDWJUqXi8sVioFH3D2OalLTuUtj2Ls5v9"  //Firebase Token
#define WIFI_SSID "wifi_moez"          //WiFi Name
#define WIFI_PASSWORD "11111111"         //WiFi Password             

FirebaseData firebaseData;

String login="{code=mefteh22, name=moez}";
///////////////////////
int l_chambre_n,l_bain_n,fen_n,porte_n;  

String s,z="0000",h="0000";
char c;
boolean StringReady;

/////////////////////////////////////////////////
void getDataFireBase2();

void sendToArduino();
void readFromArduino();
void setDataFireBase();
void setup() {
  Serial.begin(115200);


//WiFi Configuration
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
  Firebase.begin(FIREBASE_URL, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}


void loop() {


getDataFireBase2();
if (z != h){
  sendToArduino();
  h=z;
}


StringReady = false;
 
 while (Serial.available()){
   readFromArduino();
   StringReady= true;
  
  if (StringReady){
    setDataFireBase();
  } 
 }
}

void getDataFireBase2(){
    Firebase.getInt(firebaseData, "/donnes/"+login+"/chambre/lampe", l_chambre_n);
    Firebase.getInt(firebaseData, "/donnes/"+login+"/salle de bain/lampe", l_bain_n);
    Firebase.getInt(firebaseData, "/donnes/"+login+"/salon/fenêtre", fen_n);
    Firebase.getInt(firebaseData, "/donnes/"+login+"/jardin/porte", porte_n);
    z=String(l_chambre_n)+String(l_bain_n)+String(fen_n)+String(porte_n);
}
void sendToArduino() {
    Serial.print(l_chambre_n);
    Serial.print(l_bain_n);
    Serial.print(fen_n);
    Serial.println(porte_n);
    
}
void readFromArduino(){
  s="";

  while (Serial.available()) {
    c = Serial.read();
    s += c;
    delay(4);
  }
}
void setDataFireBase(){ 
      Firebase.setInt(firebaseData, "/donnes/"+login+"/chambre/lampe", String(s[0]).toInt());
      Firebase.setInt(firebaseData, "/donnes/"+login+"/salle de bain/lampe", String(s[1]).toInt());
      Firebase.setInt(firebaseData, "/donnes/"+login+"/salon/fenêtre", String(s[2]).toInt());
      Firebase.setInt(firebaseData, "/donnes/"+login+"/jardin/porte", String(s[3]).toInt());
      Firebase.setInt(firebaseData, "/donnes/"+login+"/cuisine/gaz", String(s[4]).toInt());
      Firebase.setInt(firebaseData, "/donnes/"+login+"/cuisine/température", String( String(s[5])+ String(s[6])).toInt());
      Firebase.setInt(firebaseData, "/donnes/"+login+"/jardin/humidité", String( String(s[7])+  String(s[8])).toInt());
}
