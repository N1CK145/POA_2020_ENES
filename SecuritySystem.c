#include "SecuritySystem.h"
#include "PlatineDefines.h"
#include "DatabaseConnection.h"
#include <wiringPi.h>
#include <stdio.h>

void enableSecuritySystem(){
    //digitalWrite(PIN_RGB_GREEN, LOW);
    digitalWrite(PIN_RGB_RED, HIGH);

    printf("Enabled Securitysystem!\n");
}

void disableSecuritySystem(){
    digitalWrite(PIN_RGB_RED, LOW);
    //digitalWrite(PIN_RGB_GREEN, HIGH);
    printf("Disabled Securitysystem!\n");
}

int isPersonInRoom(){
    MYSQL_RES* result = getMySQLResult("SELECT * FROM v_personsInRoom LIMIT 1;");
    MYSQL_ROW* row = mysql_fetch_row(result);

    if(!row)
        return 0;
    else
        return 1;
}
