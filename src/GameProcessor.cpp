#include "BaseState.h"
#include "GameProcessor.h"

void GameProcessor::InitializeGame() 
{
	if (allegro_init() != 0)
		exit(0);

	install_keyboard();

	set_color_depth(8);
	if (set_gfx_mode(GFX_VGA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0) 
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
		exit(0);
	}
}

void GameProcessor::HandleEvents() { states.back()->ProcessInput(this); }

void GameProcessor::ProcessEvents()  { states.back()->AquireInput(this); }

void GameProcessor::Render() { states.back()->Render(this); }

void GameProcessor::DeallocateResources() {}

void GameProcessor::ChangeState(BaseState *state) 
{
	// cleanup the current state
	if (!states.empty()) 
	{
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->InitState();
}

void GameProcessor::PushState(BaseState *state) 
{
	// pause current state
	if (!states.empty())
		states.back()->Pause();

	// store and init the new state
	states.push_back(state);
	states.back()->InitState();
}

void GameProcessor::PopState() 
{
	// cleanup the current state
	if (!states.empty()) 
		states.pop_back();

	// resume previous state
	if (!states.empty())
		states.back()->Resume();
}
