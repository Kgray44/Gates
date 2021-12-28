# Begin

## The begin() Function

### Description

The begin() function is used to setup the pins for controlling motor drivers / linear actuators.  


### Syntax

Gate.begin(int pin1, int pin2, int pin3, int pin4, int direction);


### Definition

The four pins can be in plain format (i.e. 2) or digital (i.e. D4).  The direction integer is set to 1 normally, but can be set to 2 if you find your gates to be going "backwards".
