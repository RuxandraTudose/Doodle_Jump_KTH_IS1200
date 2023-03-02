/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog
   This file modified 2018-02-xx by Oscar Eklund and Vilhelm Elofsson
   For copyright and licensing, see file COPYING */
#include <stdint.h>	 /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

volatile int *porte = (volatile int *)0xbf886110;
int start = 1;
int col = 0;
int level = 0;
int page  = 3;

int gameovercheck = 0;
int record = 0;

/* Interrupt Service Routine */
void user_isr(void) //from lab 3 and continued by Ruxandra
{
	if (IFS(0) & 0x100) 
	{
		IFS(0) &= 0xfeff;

		while (gameovercheck)  //while loop for game over
		{  
			display_string(0, "   GAME OVER");
			display_string(1, "                "); //special case - delete "LEVEL 2" after this level we don't empty screen
			display_string(2, " BTN2 - RESTART");
			display_update();

			if (getbtns() == 0b001)	
			{
				print_empty_screen();
				start = 1; //set parametr to one to enter start while loop
				gameovercheck = 0; //reset parameter for the gameover while loop oncde button 2 is pressed
			}
		}

		while (start) //while loop for start
		{
			display_string(0, "  DOODLE JUMP");
			display_string(2, "  BTN2 - START");
			display_update();
			
			//from game over always go to start - reset parameters here
			level = 0;
			col = 0;
			page = 3;
			record = 0;
			*porte = 0x0; //reset LEDs to restart counting coins

			if (getbtns() == 0b001) 
			{
				print_empty_screen();
				check_level();
				start = 0; //reset parameter for the start while loop oncde button 2 is pressed
			}
		}
	}
}

/* Lab-specific initialization goes here */
void labinit(void) //from lab 3
{
	volatile int *trise = (volatile int *)0xbf886100;
	*trise = *trise & 0xffffff00;
	*porte = 0x00;
	TRISDSET = 0xfe;

	T2CON = 0x70;			   // set tckps bits 1:256 (value 111) - the other bits set to zero (disable other functions - we want well-defined behaviour)
	PR2 = 80000000 / 256 / 10; // set in period register the value timer has to reach
	TMR2 = 0;
	T2CONSET = 0x8000; // Start the timer (activate the ON bit)

	/*THE THREE STEPS TO ENABLE INTERRUPT*/
	IECSET(0) = 0x900;	// set bit 8 to 1 (T2IE bit)
	IPC(2) = 0x3000004; // set non-zero priority (any value between 4 and 31 works)

	enable_interrupt(); // set to 1 the IE bit in CP0 Regiter via "ei" instruction

	return;
}

/* This function is called repetitively from the main program */
void labwork(void) //from lab 3 continued by Ruxandra (this function is in a forever loop in mipslabmain - always get changes for buttons)
{
	page = 3; //after check coins go back to page no 3 (doodle is on the ground)

	if (level == 3) //the condition to end the game 
	{
		gameovercheck = 1;
	}

	switch (getbtns()) 
	{
		case 0b100:
			if(level == 2)
				change_coins(); //feature to bring coins lower by inverting only for last level

			page = 2; //get ready to jump
			jump(col);

		break;

		case 0b010:
		
			if (col > 127) // take last column as well (col from 0 to 127)
			{
				level++; //finish screen, increase level
				check_level();
				col = 0; //reset column - beginning of the screen 
			}

			else //otherwise just keep on moving to right
			{   
				//col  represents starting point of doodle

				moveright(col+2); //we don't send parameter by address
				col = col + 2 + 1; //+2 to remember column where I took it right and +1 to go one more position to right
			}

		break;
		
	}

	check_coins(); //after you press any button check that you touched coin 
}

void check_level() //Ruxandra
{
	restartscreen(); //after each level we need empty screen only with ground
//haven't touched the new coins (every time you change levels reset them)	
	coin1.check = 0;
	coin2.check = 0;
	coin3.check = 0;

	switch (level) //distribution of coins on screen depending on the level
	{
		case 0:
		{
			display_string(1, "    LEVEL 0");
			display_update();
			quicksleep(10000000);

			coin1.x = 31;
			coin1.page = 3;
			coin2.x = 61;
			coin2.page = 3;
			coin3.x = 91;
			coin3.page = 3;
			break;
		}
		case 1:
		{
			display_string(1, "    LEVEL 1");
			display_update();
			quicksleep(10000000);

//change page only for coin 1 and 3 (rest of data stays saved)
			coin1.page = 2;
			coin3.page = 2;
			break;
		}
		case 2:
		{
			display_string(1, "    LEVEL 2");
			display_update();
			quicksleep(10000000);

			coin1.page = 3;
			coin2.page = 2;
			coin3.page = 3;
			break;
		}
	}	
	update_screen_level(); //after changes made respective to level print new screen with new coins
	display_image(0, Screen); //print whole screen with changes
}

void update_screen_level() //Oleksandra
{
	int i, j, k;
    for (i = 2; i < 4; i++) 
	{ 
        for(j = 0; j < 128; j++)
		{//condition to print coin on new level:
			if((i == coin1.page && j == coin1.x)  || (i == coin2.page && j == coin2.x) || (i == coin3.page && j == coin3.x))
			{
				for ( k = 0; k < 3; k++)//go through the width of coin - 3
				{
					Screen[i*128 + j + k] = Start_screen[i*128 + j + k] | coin[k]; //bitwise or to add coin on screen 
				}
			}
			if(j < 11)// width of Doodle is 10 to begin game with Doodle starting with col = 0
				Screen[3*128 + j] = Start_screen[i*128 + j] | doodle[j];
		}
    }  
}

void check_coins() //Oleksandra
{
	if(page == coin1.page && (coin1.x <= col+10) && coin1.check!=1)//checking for coin1 that you only count it once when LEDs are increased by 1
	{
		coin1.check = 1; //mark coin that has been counted
		record++; 
		*porte = *porte + 1; //only increase by one the LEDs if the coin is touched 
	}
	if(page == coin2.page && (coin2.x <= col+10) && coin2.check!=1) //checking for coin2 that you only count it once when LEDs are increased by 1
	{
		coin2.check = 1;
		record++;
		*porte = *porte + 1;
	}
	if(page == coin3.page && (coin3.x <= col+10) && coin3.check!=1)//checking for coin3 that you only count it once when LEDs are increased by 1
	{
		coin3.check = 1;
		record++;
		*porte = *porte + 1;
	}

}	

void change_coins() //Oleksandra
{
	int j, k, i;
	//interchange the pages to change position of coins 
	coin1.page = coin2.page;
	coin2.page = coin3.page;
	coin3.page = coin1.page;

	for (i = 2; i < 4; i++)  //coins are only on page 2 and three 
	{
        for(j = col; j < 128; j++) {//start from col - you can move right without changing coins 
											//- update only from Doodle's new position up untill the end of screen
	
			if((i == coin1.page && j == coin1.x)  || (i == coin2.page && j == coin2.x) || (i == coin3.page && j == coin3.x))
			{
				for ( k = 0; k < 3; k++)
					Screen[i*128 + j + k] = Start_screen[i*128 + j + k] | coin[k];
				j+=k;
			}
			else
				Screen[i*128 + j ] = Start_screen[i*128 + j ];
		}
	}
	
}

	
