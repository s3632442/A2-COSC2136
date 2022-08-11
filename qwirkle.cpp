// working complete functionality of main menu need to look
// closer at the double implementation of the game_over ptr
// but this is a low priority and something to look at in
// the ref- iteration - we want to create game over here
// and pass references to it everywhere else

#include "qwirkle.h"

#define EXIT_SUCCESS 0

int main(void)
{

   // ptr to instance variables
   startMenu = new Menu();
   list = new LinkedList();
   game_over = new bool(false);

   // run list while quit not selected
   do
   {

      // welcome msg
      startMenu->prompt("Welcome to Qwirkle!\n-------------------\n");

      // run menu
      *game_over = startMenu->runMenu();

   } while (!*game_over);

   // exit msg
   startMenu->prompt("GAME OVER");

   delete startMenu;
   delete list;
   delete game_over;

   return EXIT_SUCCESS;
};
