#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */

int MENU = 0;

void start_screen()
{
	MENU = 1;
	display_init();

	display_string(0, "  DOODLE JUMP");
	display_string(2, " BTN4 - START");
	display_string(3, " BTN3 - SCORE");
	display_update();
//	new_display_image(118, 0, 10, doodle);
//	new_display_image(3, 0, 7, shrek);

	while (MENU)
	{
		//button 4 pressed to start game
		if(getbtns() & 0b100)
		{
			print_empty_screen();
			//call function to start game
			start_game();		
			MENU = 0;
		}

		//button 3 pressed to see score
		if(getbtns() & 0b010) {

			print_empty_screen();
		
			//show score table
			MENU = 0;
		}
	
	}
	
		

}