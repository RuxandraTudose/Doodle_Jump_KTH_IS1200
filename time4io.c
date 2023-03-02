#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


int getbtns(void);  //written for lab 3

int getbtns() {

    int status = (PORTD >> 5) & 0x7; 
    return status;
} 
