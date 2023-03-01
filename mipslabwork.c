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

int pos = 2;

int start = 1;
int col = 0;

int gameovercheck = 0;
int countjump = 0;

/* Interrupt Service Routine */
void user_isr(void)
{
	if (IFS(0) & 0x100) {
		IFS(0) &= 0xfeff;

		while (gameovercheck) {

			display_string(0, " GAME OVER");
			display_string(2, " BTN2 - RESTART");
			display_update();
			col = 0;

			if (getbtns() == 0b001)	{

				print_empty_screen();
				restartscreen();
				start = 1;
				gameovercheck = 0;
			}
		}

		while (start) {

			display_string(0, "  DOODLE JUMP");
			display_string(2, " BTN2 - START");
			display_update();

			countjump = 0;
			col = 0;
			*porte = 0x0;

			if (getbtns() == 0b001) {

				print_empty_screen();
				start = 0;
			}
		}
	}
}

/* Lab-specific initialization goes here */
void labinit(void)
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
void labwork(void)
{

	switch (getbtns()) {
	case 0b100:

		jump(col);
		countjump++;
		*porte = *porte + 1;

		if (countjump == 3) {
			gameovercheck = 1;
		}

		break;

	case 0b010:

		if (col == 128) // take last column as well
			col = 0;

		else {
			moveright(col);
			col++;
		}
		break;
	}
}

