/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s): Ruxandra-Stefania Tudose, Bilovus Oleksandra, 20th Feb 2023

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "declarations.h"  /* Declatations for these labs */

volatile int* porte = (volatile int*) 0xbf886110;

int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void ) {
 
 if(IFS(0) & 0x100) {
    timeoutcount ++;
    IFS(0) &= 0xfeff;
    
  if(timeoutcount == 10) {
      display_update();
      timeoutcount = 0;
    }
  }

}  

/* Lab-specific initialization goes here */
void initports( void ) //called once
{
  volatile int* trise = (volatile int*) 0xbf886100;
  *trise = *trise & 0xffffff00; 
  *porte = 0x00;
  TRISDSET = 0xfe;

  T2CON = 0x70; // set tckps bits 1:256 (value 111) - the other bits set to zero (disable other functions - we want well-defined behaviour)
  PR2 = 80000000/256/10; //set in period register the value timer has to reach 
  TMR2 = 0;
  T2CONSET = 0x8000; // Start the timer (activate the ON bit)

/*THE THREE STEPS TO ENABLE INTERRUPT*/
  IECSET(0) = 0x900; //set bit 8 to 1 (T2IE bit)
  IPC(2) = 4; //set non-zero priority (any value between 4 and 31 works)

  enable_interrupt(); //set to 1 the IE bit in CP0 Regiter via "ei" instruction

  return;
}

void start_game()
{
  init_game();
  initports();

  while (1)
  {
    //Step 1: read inputs
    //Step 2: (decice what will happen)
    //Step 3: Draw graphics to buffer
    //Step4 : Send contents of buffer to display
    //Step 5: Delay


    
  }
}

void init_game()
{
  DOODLE.x = 0;
  DOODLE.y = 0;
  DOODLE.WIDTH = 10;
  DOODLE.HEIGHT = 8;

  SHREK.x = 150;
  SHREK.y = 0;
  SHREK.WIDTH = 7;
  SHREK.HEIGHT = 8;

  STAIR.x = 50;
  STAIR.y = 9;
  STAIR.WIDTH = 10;
  STAIR.HEIGHT = 8;

  GROUND.x = 0;
  GROUND.y = 0;
  GROUND.WIDTH = 128;
  GROUND.HEIGHT = 8;

  GAME.jumping = 0;
  GAME.game_over = 0;
  GAME.shooting = 0;
  GAME.running = 0;
  GAME.score = 0;
}


void jump()
{//sorin
  /*if (!GAME.jumping)
  {
    GAME.jumping = 1;
    DOODLE.velY = 5;
    DOODLE.y += DOODLE.velY;
  }
  else if (GAME.jumping)
  {
    DOODLE.y += DOODLE.velY;
    DOODLE.velY--;
  }
  //reset DOODLE
  if (DOODLE.y <= 0)
  {
    GAME.jumping = 0;
    DOODLE.y = 0;
    DOODLE.velY = 0;
  }*/

  
}
