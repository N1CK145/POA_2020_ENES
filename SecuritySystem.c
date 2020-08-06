#include "SecuritySystem.h"
#include "PlatineDefines.h"
#include <wiringPi.h>
#include <stdio.h>

int securitySystemLedPin = PIN_RGB_RED;

void enableSecuritySystem(){
    digitalWrite(securitySystemLedPin, HIGH);
    printf("Enabled Securitysystem!\n");
}

void disableSecuritySystem(){
    digitalWrite(securitySystemLedPin, LOW);
    printf("Disabled Securitysystem!\n");
}

int isSecurtySystemEnabled(){
    return digitalRead(securitySystemLedPin);
}

//void goIn(char* pin)
