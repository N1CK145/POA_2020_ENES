#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <string.h>
#include <mysql/mysql.h>

#include "SecuritySystem.h"
#include "PlatineDefines.h"
#include "SevenSegmentDisplay.h"
#include "Keypad.h"

void initPins();
void initDevice();
void printClientInformation();
char* readPin();

struct deviceInfo thisDeviceInfo;

int main(){
    // delay(5000);
    wiringPiSetup();
    initPins();

    initDevice();
    printClientInformation();

    // testAll();

    printf("Please inser your pin: \n");
    char * pin = readPin();
    printf("Pin: %s\n", pin);

    getchar();

    return 0;
}

char* readPin(){
    int pinLen = 4;
    int lenIndex = 0;

    char input;
    char* pin = (char*)malloc(pinLen+1 * sizeof(char));
    strcpy(pin, "");
    do {
        input = readKeypadAndWriteToSegment();
        if(input != '\0'){
            switch(input){
                case '*': // Remove last char

                    break;
                default:
                    sprintf(pin, "%s%c", pin, input);
                    lenIndex++;
                    break;
            }

        }

        while(isKeypadPressed()){
            delay(50);
        }
        delay(10);
    } while (lenIndex < pinLen);

    return pin;
}

void initPins(){
    pinMode(PIN_RGB_RED, OUTPUT);
    pinMode(PIN_RGB_GREEN, OUTPUT);
    pinMode(PIN_RGB_BLUE, OUTPUT);

    pinMode(PIN_SEG_A, OUTPUT);
    pinMode(PIN_SEG_B, OUTPUT);
    pinMode(PIN_SEG_C, OUTPUT);
    pinMode(PIN_SEG_D, OUTPUT);

    pinMode(PIN_KEYBOARD_1, OUTPUT);
    pinMode(PIN_KEYBOARD_2, OUTPUT);
    pinMode(PIN_KEYBOARD_3, OUTPUT);
    pinMode(PIN_KEYBOARD_4, OUTPUT);
    pinMode(PIN_KEYBOARD_5, INPUT);
    pinMode(PIN_KEYBOARD_6, INPUT);
    pinMode(PIN_KEYBOARD_7, INPUT);
    pinMode(PIN_KEYBOARD_8, INPUT);

    pullUpDnControl(PIN_KEYBOARD_5, PUD_DOWN);
    pullUpDnControl(PIN_KEYBOARD_6, PUD_DOWN);
    pullUpDnControl(PIN_KEYBOARD_7, PUD_DOWN);
    pullUpDnControl(PIN_KEYBOARD_8, PUD_DOWN);
}

void initDevice(){
    char* qry = (char*)malloc(75 * sizeof(char));
    thisDeviceInfo.id = 1;

    printf("Connecting to database...\n");
    openDBConnection();

    printf("Reading Client data...\n");
    sprintf(qry, "SELECT Bezeichnung FROM tbl_Devices WHERE Identifikationsnummer = %i;", thisDeviceInfo.id);
    MYSQL_ROW row = mysql_fetch_row(getMySQLResult(qry));
    thisDeviceInfo.name = row[0];
}

void printClientInformation(){
    printf("----- Client Information: -----\n");
    printf("MySQL: %s\n", getMySQLClientInfo());
    printf("Client name: %s\n", thisDeviceInfo.name);
    printf("-------------------------------\n");
}

