#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */


void gamemap () 
{
  int page, col, i;
	for(page = 0; page < 4; page++)
  {
		for(col = 0; col < 128; col++)
    {
			switch(page)
      {
        case 0:
        {

        }
        case 1:
        {

        }
        case 2:
        {

        }
        case 3:
        {
          
          if((GAME.jumping == 0) && col == DOODLE.x)
          {
            for(i = 0; i < DOODLE.WIDTH; i++)
              spi_send_recv(ground[col] | doodle[i]);
          }
          else
            spi_send_recv(ground[col]);

        }
      }
    }
  }
  

}