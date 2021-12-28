/*
  Gate.h - Library for controlling gates.
  Created by K Gray, December 26, 2021.
  Released into the public domain.
*/

#ifndef Gate_h
#define Gate_h

#include "Arduino.h"

#include <math.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>

class Gate
{
  public:
    Gate();
    void serial();
    void Magnet(int magnetPin);
    void LEDStrip(int r, int g, int b);
    
    void OTAStart(const char OTAPassword[]);
    void WiFiStart(char WiFiNetwork[], char WiFiPassword[]);
    void begin(int pin1, int pin2, int pin3, int pin4, int direction);
    
    void gate(int Direction);
    void stop();
    void magnet(int magnetValue);
    void ledStrip(int red, int green, int blue);
    float calcDist(float CurrentLatitude, float CurrentLongitude, float SavedLatitude, float SavedLongitude);
    void waitForGate(float travelDist, float travelSpeed, float percentOfTravel);
    void delayForGate(int DFGTime);

    void WFGFunction();
    
    boolean emergencyStop;
  private:
    int _pin1;
    int _pin2;
    int _pin3;
    int _pin4;
    int _magPin;
    int _r;
    int _g;
    int _b;
    char _OTAPassword;
    String _WiFiSSID;
    String _WiFiPASS;
    int _Direction;
    int _direction;
    int _magnetValue;
    int _red;
    int _green;
    int _blue;
    float _CurrentLatitude;
    float _CurrentLongitude;
    float _SavedLatitude;
    float _SavedLongitude;
    float _travelDist;
    float _travelSpeed;
    float _percentOfTravel;
    int _DFGTime;
    
    int _wfg;
    int _totalDelay;
};

#endif
