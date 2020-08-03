#include "SecuritySystem.h"
#include "PlatineDefines.h"
#include <wiringPi.h>

int securitySystemLedPin = PIN_RGB_RED;

void enableSecuritySystem(){
    digitalWrite(securitySystemLedPin, HIGH);
}

void disableSecuritySystem(){
    digitalWrite(securitySystemLedPin, LOW);
}

int isSecurtySystemEnabled(){
    return digitalRead(securitySystemLedPin);
}
