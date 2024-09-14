#ifndef BASESTATE_H
#define BASESTATE_H

#include "GameProcessor.h"

class GameProcessor;

class BaseState {
public:
	virtual void InitState() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void AquireInput(GameProcessor *game) = 0;
	virtual void ProcessInput(GameProcessor *game) = 0;
	virtual void Render(GameProcessor *game) = 0;
	void ChangeState(GameProcessor *game, BaseState *state);

protected:
	BaseState() {}
	bool firstRender = true;
private:
};

#endif// BASESTATE_H