# OTAStart

## The OTAStart() Function

### Description

The `OTAStart()` function starts OTA (OverTheAir updates).  OTA is over the air programming.  So if this function is used, it will enable you to program your microcontroller without being connected to it via USB.  Keep in mind though that you will need to call `WiFiStart()` first, as this type of programming uses WiFi.

### Syntax

`Gate.OTAStart(string password);`

### definition

This function takes one input; password.  The input must be enclosed in quotes as this is a string type.
