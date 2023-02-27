#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */


void gamemap () 
{
  int page, col, i, j;
	for(page = 0; page < 4; page++)
  {
		for(col = 0; col < 128; col++)
    {
			switch(page)
      {
        case 0:
        {
            display[page][col] = 0x00;
            break;
        }
        
        case 1:
        {
        
            display[page][col] = 0x00;
            break;
        }
        
        case 2:
        {
           display[page][col] = 0x00;
           break;
        }
        case 3:
        {
          
          if((GAME.jumping == 0) && col == DOODLE.x)
          {
            for(i = 0; i < DOODLE.WIDTH; i++) {
              //spi_send_recv(ground[i] | doodle[i]);
              display[page][col+i]= (ground[i] | doodle[i]); 
            }
            col+=DOODLE.WIDTH;
            
          }
          else
            display[page][col]= ground[col];
            
            //spi_send_recv(ground[col]);
            break;
        }
      }
    }
  }

 for ( i = 0; i < 4; i++)
 {
    display_image(0, i, display[i]); 
 }
 
  
  
  
  
 delay(1);
 //quicksleep(10);   
 GAME.jumping = 0;
}