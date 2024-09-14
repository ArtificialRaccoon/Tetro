#include <allegro.h>
#include <vector>
#include <ctime>
#include "GameProcessor.h"
#include "GameState.h"

volatile int ticks = 0;
void timer(void)
{
    ticks = ticks + 1;
}
END_OF_FUNCTION(timer)

int main() 
{
    GameProcessor objGame;
    objGame.InitializeGame();

    /* SETUP THE MAIN TIMER TO 60 FPS */
    install_timer(); //Setup the timer
    LOCK_VARIABLE(ticks); //Set timer variable
    LOCK_FUNCTION(timer); //Set timer function
    install_int_ex(timer, BPS_TO_TIMER(60));

    objGame.ChangeState(GameState::Instance());
    while ( true )
    {
        while(ticks == 0)
            rest(1);

        while(ticks > 0)
        {
            int old_ticks = ticks;

            ticks = ticks - 1;
            if(old_ticks <= ticks)
                break;

            objGame.ProcessEvents();
            objGame.HandleEvents();
        }

        objGame.Render();
    }
    return 0;
}