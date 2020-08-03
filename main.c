#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdbool.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#include "SecuritySystem.h"
#include "PlatineDefines.h"
#include "SevenSegmentDisplay.h"


void initPins();
void initDevice();
void connectToDB();

struct deviceInfo thisDeviceInfo;
MYSQL* mysqlConnection;

int keyboardPins[8] = {PIN_KEYBOARD_1, PIN_KEYBOARD_2, PIN_KEYBOARD_3, PIN_KEYBOARD_4,
                        PIN_KEYBOARD_5, PIN_KEYBOARD_6, PIN_KEYBOARD_7, PIN_KEYBOARD_8};

char keyboardValues[4][4] = {
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}
};

int main(){
    // delay(5000);
    wiringPiSetup();
    initPins();

    initDevice();

    // testAll();

    while(true){
        for(int i = 0; i < 4; i++){ // Spalten
            digitalWrite(PIN_KEYBOARD_1, LOW);
            digitalWrite(PIN_KEYBOARD_2, LOW);
            digitalWrite(PIN_KEYBOARD_3, LOW);
            digitalWrite(PIN_KEYBOARD_4, LOW);

            digitalWrite(keyboardPins[i], HIGH);

            for(int j = 0; j < 4; j++){ // Zeilen
                if(digitalRead(keyboardPins[j+4])){
                    char val = keyboardValues[j][i];
                    printf("%c\n", val);

                    switch(val){
                        case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
                            setSegment((int)val - 48);
                            break;

                        case 'A': case 'B': case 'C': case 'D':
                            setSegment((int)val - 55);
                            break;

                        case '*':
                            setSegment(14);
                            break;

                        case '#':
                            setSegment(15);
                            break;
                    }
                }
            }
        }

        delay(50);
    }

    getchar();

    return 0;
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
}

void initDevice(){
    thisDeviceInfo.id = 1;
    thisDeviceInfo.name = "I_Bims_Device_1";

    printf("Running as '%s'\n", thisDeviceInfo.name);
    printf("-----------------------\n");
    connectToDB();
}

void connectToDB(){
    char* host = "lia-gaming.de";
    char* user = "schule";

    mysqlConnection = mysql_init(NULL);
    if(mysqlConnection == NULL){
        printf("Fehler beim Initialisieren von MySQL.");
    }

    if(mysql_real_connect (
        mysqlConnection,
        host,
        user,
        "123",
        "POA_2020",
        0,
        NULL,
        0) == NULL)
    {
        unsigned int error = mysql_errno(mysqlConnection);
        printf("MySQL Error: %u (%s)\n", error, mysql_error(mysqlConnection));
    }else
        printf("MySQL Verbindung hergestellt!\nVerbunden zu '%s' als '%s'\n", host, user);
}
