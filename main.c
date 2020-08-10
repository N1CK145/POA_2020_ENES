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

#define ACTION_LOGIN "1"
#define ACTION_LOGOUT "2"

void initPins();
void initDevice();
void printClientInformation();
char* readPin();
int checkForRightLogin(char*, char*);
void updateActivityLog(char*);

struct deviceInfo thisDeviceInfo;
int pinMaxLen = 32;
char* employeeID = "1";
char* pin = "123A";


int main(){
    bool loggedIn = false;

    wiringPiSetup();
    initPins();

    initDevice();
    printClientInformation();

    do{
        /*printf("Please insert your Gelegenheitsunternehmensangestellteidentifikationsnummer:\n");
        employeeID = readPin();

        printf("Please insert your Gelegenheitsunternehmensangestelltenkennwort:\n");
        pin = readPin();*/

        if(!checkForRightLogin(employeeID, pin)){
            printf("Invalid Login...\n");
            loggedIn = false;
        }else
            loggedIn = true;

    }while(!loggedIn);
    updateActivityLog(employeeID);

    disableSecuritySystem();+

    closeDBConnection();

    return 0;
}

void updateActivityLog(char* employeeID){
    char* qry = (char*)malloc(200 * sizeof(char));
    sprintf(qry, "SELECT ActionID FROM tbl_ActivityLog WHERE UserID LIKE '%s' ORDER BY Identifikationsnummer DESC LIMIT 1;", employeeID);

    MYSQL_RES* result = getMySQLResult(qry);
    MYSQL_ROW* row = mysql_fetch_row(result);

    if(!row){
        sprintf(qry, "INSERT INTO `tbl_ActivityLog`(`UserID`, `ActionID`, `DeviceID`) VALUES ('%s', '%s', '%i');",
            employeeID, ACTION_LOGIN, thisDeviceInfo.id);

    }else{
        if(!strcmp(row[0], ACTION_LOGIN))
            sprintf(qry, "INSERT INTO `tbl_ActivityLog`(`UserID`, `ActionID`, `DeviceID`) VALUES ('%s', '%s', '%i');",
                employeeID, ACTION_LOGOUT, thisDeviceInfo.id);
        else
            sprintf(qry, "INSERT INTO `tbl_ActivityLog`(`UserID`, `ActionID`, `DeviceID`) VALUES ('%s', '%s', '%i');",
                employeeID, ACTION_LOGIN, thisDeviceInfo.id);
    }
    sendMySQLQuerry(qry);
}

int checkForRightLogin(char* uID, char* uPin){
    char* qry = (char*)malloc((128 + pinMaxLen) * sizeof(char));

    sprintf(qry, "SELECT * FROM tbl_User WHERE Gelegenheitsunternehmensangestellteidentifikationsnummer LIKE '%s' AND Pin LIKE '%s';", uID, uPin);

    MYSQL_RES* result = getMySQLResult(qry);
    return mysql_fetch_row(result);
}


char* readPin(){
    int lenIndex = 0;

    char input;
    char* pin = (char*)malloc(pinMaxLen * sizeof(char));

    strcpy(pin, "");

    do {
        input = readKeypadAndWriteToSegment();
        if(input != '\0'){
            switch(input){
                case '*': // Remove last char
                    if(lenIndex > 0){
                        pin[strlen(pin)-1] = 0;
                        lenIndex--;
                    }
                    break;

                case '#': // Finish pin
                    lenIndex = pinMaxLen;
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
    } while (lenIndex < pinMaxLen);

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

