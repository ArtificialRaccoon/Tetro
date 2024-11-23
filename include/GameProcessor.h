#ifndef GAMEPROCESSOR_H
#define GAMEPROCESSOR_H

#include <vector>
#include <iostream>
#include "allegro.h"
#include "GameUIDefines.h"

using namespace std;

class BaseState;
class GameProcessor 
{
	public:
		void InitializeGame();
		void HandleEvents();
		void ProcessEvents();
		void Render();
		void DeallocateResources();

		void ChangeState(BaseState *state);
		void PushState(BaseState *state);
		void PopState();

	private:
		std::vector<BaseState *> states;		
};

#endif// GAMEPROCESSOR_H
