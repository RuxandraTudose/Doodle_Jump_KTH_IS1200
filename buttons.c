#include <stdint.h>
#include <pic32mx.h>
#include "declarations.h"

int getsw(void);
int getbtns(void); 

int getsw() {

    int value = (PORTD >> 8) & 0xf; //implicit zero extension with andi
    return value;
}

int getbtns() {

    int status = (PORTD >> 5) & 0x7; 
    return status;
} 
