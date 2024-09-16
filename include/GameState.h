#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdlib>
#include <algorithm>
#include <memory>
#include <fstream>
#include <cmath>
#include <cstdlib> 
#include <ctime>
#include "GameContext.h"
#include "GameConstants.h"
#include "Tetromino.h"
#include "BaseState.h"
#include "allegro.h"
#include "json.h"

class GameState : public BaseState
{
    public:
        void InitState();
        void Pause();
        void Resume();
        void AquireInput(GameProcessor* game);
        void ProcessInput(GameProcessor* game);
        void Render(GameProcessor* game);
        static GameState* Instance()
        {
            return &mGameState;
        }

    protected:
        GameState() { }
        void DrawBackground();        
        std::string formatInteger(int leadingZeros, int value);
        GameContext context;

    private: //Variables       
        static GameState mGameState;
        std::vector<int> tileData;                    

    private: //Bitmaps
        BITMAP *BUFFER;
        BITMAP *BACKGROUND;
        BITMAP *NEXTWINDOW;
        BITMAP *PLAYGRID;
        BITMAP *GAMEUI;
        FONT *GAME_FONT;
        PALETTE palette;
};

#endif // GAMESTATE_H
