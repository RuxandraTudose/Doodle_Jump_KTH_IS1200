/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from displayfuncions.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from displayfuncions.c */
char * itoaconv( int num );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);
void gamemap ();


//new
typedef struct Object{
  int x;
  int y;
  int velX;
  int velY;
  int WIDTH;
  int HEIGHT;
} Object;

struct Object DOODLE;
struct Object SHREK;
struct Object STAIR;
struct Object GROUND;

typedef struct Game{
  int jumping;
  int shooting;
  int game_over;
  int running;
  int score;
} Game;

struct Game GAME;

//graphics
const uint8_t const doodle[128]; //size 128 - space for all columns; zero by default for the others
const uint8_t const stair[128];
const uint8_t const shrek[128];
const uint8_t const ground[128];
const uint8_t const no_ground[128];
uint8_t display[4][128];

//menu
void start_screen();
void print_empty_screen();
void initports();
void jump();
void start_game();
void init_game();
void gamemap();
//void update_Shrek_and_Stairs();

