/*
  Gate.cpp - Library for controlling gates.
  Created by K Gray, December 26, 2021.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Gate.h"

Gate::Gate() {}

void Gate::Magnet(int magnetPin){
  pinMode(magnetPin, OUTPUT);
  _magPin = magnetPin;
  
  Serial.println("Magnet Lock pin set...");
 
}

void Gate::LEDStrip(int r, int g, int b){
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  _r = r;
  _g = g;
  _b = b;
  
  Serial.println("LED Strip pins set...");
 
}

void Gate::serial(){
  Serial.begin(115200);
}

void Gate::OTAStart(const char OTAPassword[]){
  // Port defaults to 8266
  ArduinoOTA.setPort(8266);
  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("GateESP");
  // No authentication by default
  ArduinoOTA.setPassword(OTAPassword);//(const char 

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  
  Serial.println("OTA Started with hostname 'GatesESP' and password " + String(OTAPassword));
 
}

void Gate::WiFiStart(char WiFiNetwork[], char WiFiPassword[]){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFiNetwork, WiFiPassword);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    
    Serial.println("Connection Failed! Rebooting...");
   
    delay(1000);
    ESP.restart();
  }
  
  Serial.println("WiFi Started with network " + String(WiFiNetwork) + " and password " + String(WiFiPassword));
}

void Gate::begin(int pin1, int pin2, int pin3, int pin4, int direction){
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
  _direction = direction;
  Serial.println("Linear Actuator's pins set...");
}

void Gate::gate(int Direction){
  if (_direction == 1){
    if (Direction == 1){
      digitalWrite(_pin1, HIGH);
      digitalWrite(_pin2, LOW);
      digitalWrite(_pin3, HIGH);
      digitalWrite(_pin4, LOW);
    }
    if (Direction == 2){
      digitalWrite(_pin1, LOW);
      digitalWrite(_pin2, HIGH);
      digitalWrite(_pin3, LOW);
      digitalWrite(_pin4, HIGH);
    }
  }
  else if (_direction == 2){
    if (Direction == 1){
      digitalWrite(_pin1, LOW);
      digitalWrite(_pin2, HIGH);
      digitalWrite(_pin3, LOW);
      digitalWrite(_pin4, HIGH);
    }
    if (Direction == 2){
      digitalWrite(_pin1, HIGH);
      digitalWrite(_pin2, LOW);
      digitalWrite(_pin3, HIGH);
      digitalWrite(_pin4, LOW);
    }
  }
  
  Serial.println("Gates Opened / Closed");
  Serial.println("direction: " + String(_direction));
  Serial.println("Direction: " + String(Direction));
 
}

void Gate::stop(){
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
  digitalWrite(_pin3, LOW);
  digitalWrite(_pin4, LOW);
  
  Serial.println("Gates stopped");
 
}

void Gate::magnet(int magnetValue){
  digitalWrite(_magPin, magnetValue);
  
  Serial.println("Magnet lock status: " + String(magnetValue));
 
}

void Gate::ledStrip(int red, int green, int blue){
  analogWrite(red, _r);
  analogWrite(green, _g);
  analogWrite(blue, _b);
  
  Serial.println("LED Strip: " + String(red) + ", " + String(green) + ", " + String(blue));
 
}

float Gate::calcDist(float CurrentLatitude, float CurrentLongitude, float SavedLatitude, float SavedLongitude){
  // HaverSine version
  const float Deg2Rad = 0.01745329252;               // (PI/180)  0.017453293, 0.0174532925
  //const double EarthRadius = 6372.795;              //6372.7976 In Kilo meters, will scale to other values
  const float EarthRadius = 20908120.1;              // In feet  20908128.6
  float DeltaLatitude, DeltaLongitude, a, Distance;

  // degrees to radians
  CurrentLatitude = (CurrentLatitude + 180) * Deg2Rad;     // Remove negative offset (0-360), convert to RADS
  CurrentLongitude = (CurrentLongitude + 180) * Deg2Rad;
  SavedLatitude = (SavedLatitude + 180) * Deg2Rad;
  SavedLongitude = (SavedLongitude + 180) * Deg2Rad;

  DeltaLatitude = SavedLatitude - CurrentLatitude;
  DeltaLongitude = SavedLongitude - CurrentLongitude;

  a =(sin(DeltaLatitude/2) * sin(DeltaLatitude/2)) + cos(CurrentLatitude) * cos(SavedLatitude) * (sin(DeltaLongitude/2) * sin(DeltaLongitude/2));
  Distance = EarthRadius * (2 * atan2(sqrt(a),sqrt(1-a)));
  return(Distance);
  
  Serial.println("Distance equation result: " + String(Distance));
 
}



void Gate::waitForGate(float travelDist, float travelSpeed, float percentOfTravel){
  int _totalDelay = ((((travelDist*percentOfTravel)/travelSpeed)*1000));
  
  Serial.println("Total delay: " + String(_totalDelay));
 
  Begin:
  _wfg++;
  while(_wfg <= _totalDelay){
    
    Serial.println(_wfg);
   
    void WFGFunction();
    goto Begin;
  }
  _wfg = 0;
}

void Gate::delayForGate(int DFGTime){
  
  Serial.println("Delay for gate: " + String(DFGTime));
 
  delay(DFGTime);
}

void WFGFunction(){
  delay(1);
}
