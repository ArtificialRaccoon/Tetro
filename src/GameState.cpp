#include "GameState.h"

GameState GameState::mGameState;

void GameState::InitState()
{
    //Init Sound
	reserve_voices (16, -1);    
	if (install_sound (DIGI_AUTODETECT, MIDI_NONE, NULL) < 0)
	{
		printf ("Error initializing sound card");
		exit(0);
	}

    if (install_mod (8) < 0) 
	{
		printf ("Error setting digi voices");
		exit(0);
	}

	JGMOD *ex;
	char modPath[] = ".\\OTHER\\tetris.mod";
	ex = load_mod (modPath);     
    if (ex == NULL)
	{
		printf ("Error reading tetris.mod");
		exit(0);
	}    
    
    GAME_FONT = load_font(".\\OTHER\\DEFAULT.bmp", palette, NULL);
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BACKGROUND = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    clear_to_color(BACKGROUND, makecol(0,0,0));

    GAMEUI = load_bitmap(".\\GFX\\GAMEUI.bmp", palette);  
    DrawBackground();

    //Statistics Header
    textout_centre_ex(BACKGROUND, GAME_FONT, "STATISTICS", 50, 8, makecol(255, 255, 255), -1);

    //Lines Header
    textout_centre_ex(BACKGROUND, GAME_FONT, "Lines ", 170, 8, makecol(255, 255, 255), -1);

    //Level Header
    textout_ex(BACKGROUND, GAME_FONT, "Level", 262, 12, makecol(255, 255, 255), -1);

    //Next Block Header
    textout_centre_ex(BACKGROUND, GAME_FONT, "Next", 288, 38, makecol(255, 255, 255), -1);

    //Score Headers
    textout_ex(BACKGROUND, GAME_FONT, "TOP", 262, 110, makecol(255, 255, 255), -1);    
    textout_ex(BACKGROUND, GAME_FONT, "SCORE", 262, 130, makecol(255, 255, 255), -1); 

    draw_sprite(BUFFER, BACKGROUND, 0, 0);

    //Play Soundtrack
    play_mod (ex, TRUE);
}

void GameState::Pause()
{

}

void GameState::Resume()
{

}

void GameState::AquireInput(GameProcessor* game)
{
    if(keypressed())
    {
        switch(readkey() >> 8)
        {        
            case KEY_W:
            case KEY_UP:       
                //Rotate         
                break;
            case KEY_S:
            case KEY_DOWN:
                //Drop
                break;        
            case KEY_A:
            case KEY_LEFT:       
                //Move Left
                break;
            case KEY_D:
            case KEY_RIGHT:
                //Move Right
                break;                                   
            case KEY_ESC:
                exit(0); //Just Exit for now
                break;
        }
    }    
}

void GameState::ProcessInput(GameProcessor* game)
{ 
    
}

void GameState::Render(GameProcessor* game)
{
    //Lines
    textout_ex(BUFFER, GAME_FONT, formatInteger(3, currentLines).c_str(), 186, 8, makecol(255, 255, 255), -1);

    //Statistics
    textout_ex(BUFFER, GAME_FONT, formatInteger(3, tetronimoTally[0]).c_str(), 56, 24, makecol(255, 255, 255), -1);
    textout_ex(BUFFER, GAME_FONT, formatInteger(3, tetronimoTally[0]).c_str(), 56, 48, makecol(255, 255, 255), -1);
    textout_ex(BUFFER, GAME_FONT, formatInteger(3, tetronimoTally[0]).c_str(), 56, 72, makecol(255, 255, 255), -1);
    textout_ex(BUFFER, GAME_FONT, formatInteger(3, tetronimoTally[0]).c_str(), 56, 96, makecol(255, 255, 255), -1);
    textout_ex(BUFFER, GAME_FONT, formatInteger(3, tetronimoTally[0]).c_str(), 56, 120, makecol(255, 255, 255), -1);
    textout_ex(BUFFER, GAME_FONT, formatInteger(3, tetronimoTally[0]).c_str(), 56, 144, makecol(255, 255, 255), -1);
    textout_ex(BUFFER, GAME_FONT, formatInteger(3, tetronimoTally[0]).c_str(), 56, 168, makecol(255, 255, 255), -1);

    //Current Level    
    textout_ex(BUFFER, GAME_FONT, formatInteger(2, currentLevel).c_str(), 303, 12, makecol(255, 255, 255), -1);

    //Scores
    textout_ex(BUFFER, GAME_FONT, formatInteger(6, topScore).c_str(), 262, 118, makecol(255, 255, 255), -1);  
    textout_ex(BUFFER, GAME_FONT, formatInteger(6, currentScore).c_str(), 262, 138, makecol(255, 255, 255), -1); 

    draw_sprite(screen, BUFFER, 0, 0);
}

void GameState::DrawBackground()
{
    std::ifstream ifs(".\\GFX\\GAMEUI.jsn");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject guiJson = json::jobject::parse(content);  
    this->tileData = guiJson["data"];

    int destXPos = 0;
    int destYPos = 0;
    int srcXPos = 0;
    int srcYPos = 0;

    unsigned tile_index = 0;

    for (int y = 0; y < backgroundHeight; y++)
    {
        destXPos = 0;
        tile_index = y * backgroundWidth;

        for (int x = 0; x < backgroundWidth; x++)
        {
            bool H = tileData[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
            unsigned tileID = tileData[tile_index];

            tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

            srcXPos = tileWidth * ((tileID - 1) % tilesetWidth);
            srcYPos = tileHeight * floor((tileID - 1) / tilesetWidth);

            masked_blit(GAMEUI, BACKGROUND, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);

            tile_index += 1;
            destXPos += tileWidth;
        }

        destYPos += tileHeight;
    }
}

std::string GameState::formatInteger(int leadingZeros, int value)
{
    std::string returnValue = std::to_string(value);
    int neededPadding = leadingZeros - returnValue.size();
    if (neededPadding > 0)
        returnValue.insert(0, neededPadding, '0');
    return returnValue;
}