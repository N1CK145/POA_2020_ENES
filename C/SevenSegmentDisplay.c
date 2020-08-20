#include <stdio.h>
#include "SevenSegmentDisplay.h"
#include "PlatineDefines.h"

int currentSegmentVal;


void int_to_bin_digit(unsigned int in, int count, int* out){
    // Hier Passiert Magie
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}

void setSegment(int value){
    int out[4];
    int_to_bin_digit(value, 4, out);

    digitalWrite(PIN_SEG_A, out[3]);
    digitalWrite(PIN_SEG_B, out[2]);
    digitalWrite(PIN_SEG_C, out[1]);
    digitalWrite(PIN_SEG_D, out[0]);

    currentSegmentVal = value;
}

void segmentCountUp(){
    if(currentSegmentVal < 15){
        currentSegmentVal++;
        setSegment(currentSegmentVal);
    }
}

void segmentCountDown(){
    if(currentSegmentVal > 0){
        currentSegmentVal--;
        setSegment(currentSegmentVal);
    }
}

int getSegmentValue(){
    return currentSegmentVal;
}
