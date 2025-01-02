#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdlib>
#include <algorithm>
#include <memory>
#include <cmath>
#include <cstdlib> 
#include <ctime>
#include "GameContext.h"
#include "GameConstants.h"
#include "Tetromino.h"
#include "GameOverState.h"
#include "BaseState.h"
#include "allegro.h"

class GameState : public BaseState
{
    public:
        void InitState();
        void Pause();
        void Resume();
        void AquireInput(GameProcessor* game);
        void ProcessInput(GameProcessor* game);
        void Render(GameProcessor* game);
        void Reset();
        void UnloadResources();
        static GameState* Instance()
        {
            static GameState mGameState; 
            return &mGameState;
        }

    protected:
        GameState() { }
        void DrawBackground();        
        std::string formatInteger(int leadingZeros, int value);

    private: //Bitmaps
        BITMAP *DISPLAY;
        BITMAP *BUFFER;
        BITMAP *BACKGROUND;
        BITMAP *NEXTWINDOW;
        BITMAP *PLAYGRID;      
};

#endif // GAMESTATE_H
