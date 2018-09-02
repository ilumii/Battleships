#include <cstdlib>
#include <iostream>
#include "bot.h"
#include "screen.h"

using namespace std;

int ROWS;
int COLS;
int iter = 0;
int counter = 0;
int checkhit = 0;

/* Initialization procedure, called when the game starts:

   init (rows, cols, num, screen, log) 
 
   Arguments:
    rows, cols = the boards size
    num        = the number of ships 
    screen     = a screen to update your knowledge about the game
    log        = a cout-like output stream
*/


void init(int rows, int cols, int num, Screen &screen, ostream &log) 
{
  ROWS = rows;
  COLS = cols;
  log << "Start." << endl;
}

/* The procedure handling each turn of the game:
 
   next_turn(sml, lrg, num, gun, screen, log)
 
   Arguments:
    sml, lrg = the sizes of the smallest and the largest ships that are currently alive
    num      = the number of ships that are currently alive
    gun      = a gun.
               Call gun.shoot(row, col) to shoot: 
                  Can be shot only once per turn. 
                  Returns MISS, HIT, HIT_N_SUNK, ALREADY_HIT, or ALREADY_SHOT.
    screen   = a screen to update your knowledge about the game
    log      = a cout-like output stream
*/

void next_turn(int sml, int lrg, int num, Gun &gun, Screen &screen, ostream &log)
{	

		int r = iter / COLS;
		int c = iter % COLS;
		
		if(screen.read(r, c)=='x'){
			do{	
			iter+=1;
			r = iter / COLS;
			c = iter % COLS;
			}while (screen.read(r, c)=='x' || screen.read(r, c)=='@' || screen.read(r, c)=='S');
		}
		
		iter += 1;
	
		log << "Smallest: " << sml << " Largest: " << lrg << " S.alive " << num <<" . "; //S.alive as in Ships Alive which pretty much doesnt help a lot right now
		log << "Shoot at  " << r << " " << c << endl;

		result res = gun.shoot(r, c);
		
	// add result on the screen
		if (res == MISS && checkhit == 0)
		{
			screen.mark(r, c, 'x', BLUE); 
		}
		else if (res == MISS && checkhit == 1){
			screen.mark(r, c, 'x', BLUE);
			iter = iter - (COLS * counter);
			counter = 0;
			checkhit = 2;
		}
		else if (res == HIT && checkhit == 0){
			screen.mark(r, c, '@', GREEN); 
			iter = iter + COLS - 1;
			counter++;
			checkhit = 1;
		}
		else if (res == HIT && checkhit == 1){
			screen.mark(r, c, '@', GREEN);
			if (c != COLS){
				screen.mark(r, c+1, 'x', BLUE);	
			}
			if (c != 0){
			screen.mark(r, c-1, 'x', BLUE);
			}
			iter = iter + COLS - 1;
			counter++;
		}
		else if (res == HIT && checkhit == 2){
			screen.mark(r, c, '@', GREEN);
			if (screen.read(r,c-1)== '@'){
				screen.mark(r+1, c-1, 'x', BLUE);
			}
		}
		else if (res == HIT_N_SUNK)
		{
			screen.mark(r, c, 'S', RED); 
			screen.mark(r+1, c, 'x', BLUE);
			screen.mark(r, c+1, 'x', BLUE);
			if (screen.read(r, c-1) == '@')
			{
				screen.mark(r+1, c-1, 'x', BLUE);
			}
			if (checkhit == 1){
				iter = iter - (COLS * counter);
				counter = 0;
				checkhit = 0;
			}
			else if (checkhit == 2){
				checkhit = 0;
			}
			
		}
	}
