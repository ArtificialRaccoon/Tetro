#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <cmath>
#include "GameContext.h"
#include "allegro.h"
#include "GameConstants.h"
#include "BaseState.h"
#include "GameState.h"

class GameOverState : public BaseState
{
    public:
        void InitState();
        void Pause();
        void Resume();
        void AquireInput(GameProcessor* game);
        void ProcessInput(GameProcessor* game);
        void Render(GameProcessor* game);
        static GameOverState* Instance()
        {
            static GameOverState mGameOverState;
            return &mGameOverState;
        }

    protected:
        GameOverState() { } 

    private: //Bitmaps
        BITMAP *BUFFER;
        BITMAP *BACKGROUND;
        BITMAP *DIALOG;
};

#endif // GAMEOVERSTATE_H
