#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "GameConstants.h"
#include "BaseState.h"

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
            return &mGameOverState;
        }

    protected:
        GameOverState() { }          

    private: //Variables       
        static GameOverState mGameOverState;
};

#endif // GAMEOVERSTATE_H
