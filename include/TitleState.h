#ifndef TITLESTATE_H
#define TITLESTATE_H

#include <cmath>
#include "GameContext.h"
#include "allegro.h"
#include "GameConstants.h"
#include "BaseState.h"
#include "GameState.h"

class TitleState : public BaseState
{
    public:
        void InitState();
        void Pause();
        void Resume();
        void AquireInput(GameProcessor* game);
        void ProcessInput(GameProcessor* game);
        void Render(GameProcessor* game);
        void UnloadResources();
        static TitleState* Instance()
        {
            static TitleState mTitleState;
            return &mTitleState;
        }

    protected:
        TitleState() { } 

    private: //Bitmaps
        BITMAP *BUFFER;
        BITMAP *BACKGROUND;
    
    private:
        int selectedItem = 0;
        bool trigger = false;
};

#endif // TitleState_H
