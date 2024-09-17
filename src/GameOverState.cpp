#include "GameOverState.h"

GameOverState GameOverState::mGameOverState;

void GameOverState::InitState()
{
    
}

void GameOverState::Pause()
{

}

void GameOverState::Resume()
{

}

void GameOverState::AquireInput(GameProcessor* game)
{
    if(keypressed())
    {
        switch(readkey() >> 8)
        {        
            
        }
        clear_keybuf();
    }    
}

void GameOverState::ProcessInput(GameProcessor* game)
{ 

}

void GameOverState::Render(GameProcessor* game)
{
    
}