#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdlib>
#include <algorithm>
#include <memory>
#include <fstream>
#include <cmath>
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
    private: //Variables
        int ticks;        
        int currentLevel = 1;
        int currentScore = 0;
        int topScore = 0;
        int currentLines = 0;
        int tetronimoTally[7] = {0,0,0,0,0,0,0};
        static GameState mGameState;
        BITMAP *BUFFER;
        BITMAP *BACKGROUND;
        BITMAP *GAMEUI;
        FONT *GAME_FONT;
        PALETTE palette;
        std::vector<int> tileData;

    private: //Constants
        const int tilesetWidth = 16;
        const int tilesetHeight = 8;
        const int tileWidth = 8;
        const int tileHeight = 8;
        const int backgroundWidth = 40;
        const int backgroundHeight = 25;
        const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
        const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
        const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;
};

#endif // GAMESTATE_H
