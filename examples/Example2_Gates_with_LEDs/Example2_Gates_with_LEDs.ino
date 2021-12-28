/*************************************************************
File Name: Example2_Gates_with_LEDs.ino
Processor/Platform: ESP8266 (D1-Mini tested)
Development Environment: Arduino 1.8.19

Download latest code here:
https://github.com/Kgray44/Automated--Driveway-Gate

Download latest library code here:
https://github.com/Kgray44/Gates

Driveway Gates code meant to be used alongside the tutorial found here:
https://www.hackster.io/k-gray/new-automated-driveway-gates-ef5c75


Copyright 2021 K Gray

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Liscense found here:
https://opensource.org/licenses/MIT
 *************************************************************/


#include <Gate.h>

Gate myGate;

void setup(){
  myGate.serial();
  myGate.begin(D3,D4,D7,D8,1);
  myGate.WiFiStart("MYSSID", "MYPASS");
  myGate.OTAStart("maker");		//OTA
  myGate.Magnet(D5); 			//magnet lock
  myGate.LEDStrip(D1,D2,D6);
}

void loop(){
  myGate.ledStrip(0,0,255);		//blue
  myGate.gate(1); 			//gates go in one direction; opens or closes depending on the direction variable at the beginning
  myGate.waitForGate(12,0.4,0.8);		//wait for the gates to open / close; this example has 12 inch actuators, that move 0.4 inches per second and use 80% of the actuator
  myGate.ledStrip(0,255,0);		//green
  myGate.stop();				//stop the gates
  myGate.delayForGate(5000);		//just delay 5 seconds (number in milliseconds)
  myGate.ledStrip(0,0,255);		//blue
  myGate.gate(2);			//gates go in the other direction; opens or closes depending on the direction variable at the beginning
  myGate.waitForGate(12,0.4,0.8);		//wait for gates again
  myGate.ledStrip(255,0,0);		//red
  myGate.stop();				//stop the gates
  myGate.delayForGate(5000);		//just delay 5 seconds
}
