#include "Keypad.h"
#include "PlatineDefines.h"
#include <wiringPi.h>

int keyboardPins[8] = {PIN_KEYBOARD_1, PIN_KEYBOARD_2, PIN_KEYBOARD_3, PIN_KEYBOARD_4, PIN_KEYBOARD_5, PIN_KEYBOARD_6, PIN_KEYBOARD_7, PIN_KEYBOARD_8};
char keyboardValues[4][4] = {
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}
};

void readKeypadAndWriteToSegment(){
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
}
