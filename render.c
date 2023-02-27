#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */


void gamemap () 
{
  //  display_init();
    int i,j;
    while(1)
       // display_image(0, 1, doodle);
    for (j = 0; j< 4; j++) {
      for(i = 0 ; i < 128; i++)
        spi_send_recv(doodle[i])
    }
  

}