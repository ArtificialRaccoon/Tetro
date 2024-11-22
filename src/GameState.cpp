#include "GameState.h"

GameState GameState::mGameState;

void GameState::InitState()
{
    //Init Sound
    reserve_voices (4, -1);    
    if (install_sound (DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) < 0)
    {
        printf ("Error initializing sound card");
        exit(0);
    }

    GAMEOVER = load_sample(".\\SFX\\GAMEOVER.WAV");
    POINTS = load_sample(".\\SFX\\CLEAR.WAV");

    GAME_FONT = load_font(".\\OTHER\\DEFAULT.bmp", palette, NULL);
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BACKGROUND = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    NEXTWINDOW = create_bitmap(blockSize * 4, blockSize * 4);
    PLAYGRID = create_bitmap(blockSize * playGridWidth, blockSize * playGridHeight);

    clear_to_color(BACKGROUND, makecol(0, 0, 0));
    clear_to_color(NEXTWINDOW, makecol(57,85,113));
    clear_to_color(PLAYGRID, makecol(0, 0, 0));

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
    MIDI *music;
    music = load_midi(".\\OTHER\\TETRIS.MID");
    play_looped_midi(music, 25, 100);
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
                context.GetCurrentPiece().Rotate(context.PlayGrid());        
                break;
            case KEY_S:
            case KEY_DOWN:
                context.GetCurrentPiece().Down(context.PlayGrid());
                break;        
            case KEY_A:
            case KEY_LEFT:       
                context.GetCurrentPiece().Left(context.PlayGrid());
                break;
            case KEY_D:
            case KEY_RIGHT:
                context.GetCurrentPiece().Right(context.PlayGrid());
                break;  
            case KEY_SPACE:
                context.GetCurrentPiece().HardDrop(context.PlayGrid());
                break;                                
            case KEY_ESC:
                exit(0); //Just Exit for now, show pause state later
                break;
        }
        clear_keybuf();
    }    
}

void GameState::ProcessInput(GameProcessor* game)
{ 
    if (context.ShouldDrop())
        context.GetCurrentPiece().Down(context.PlayGrid());

    if (context.GetCurrentPiece().CanLock(context.PlayGrid())) 
    {
        context.IncreaseTetrominoTally(context.GetCurrentPiece().GetType());
        context.GetCurrentPiece().LockPiece(context.PlayGrid());
        context.CheckForCompletedLines(POINTS);
        
        if (context.CanSpawn())
            context.SpawnTetromino();
        else
        {
            stop_midi();
            play_sample(GAMEOVER, 255, 128, 1000, FALSE);

            // Show the player HOW they lost
            context.SpawnTetromino();
            Render(game);
            game->ChangeState(GameOverState::Instance());
        }
    }
}

void GameState::Render(GameProcessor* game)
{
    //Lines
    if(context.CurrentLinesChanged())
    {
        rectfill(BUFFER, 186, 8, 210, 16, makecol(57,85,113));
        textout_ex(BUFFER, GAME_FONT, formatInteger(3, context.GetCurrentLines()).c_str(), 186, 8, makecol(255, 255, 255), -1);
        context.SetCurrentLinesChanged(false);
    }

    //Statistics
    for(int i = 0; i < 7; i++)
    {
        if(context.TetrominoTallyChanged(i))
        {
            rectfill(BUFFER, 56, 24 + (i * 24), 56 + (3 * 8), 24 + (i * 24) + 8, makecol(57,85,113));
            textout_ex(BUFFER, GAME_FONT, formatInteger(3, context.GetTetrominoTally(i)).c_str(), 56, 24 + (i * 24), makecol(255, 255, 255), -1);
            context.SetTetrominoTallyChanged(i, false);
        }
    }

    //Current Level   
    if(context.CurrentLevelChanged())
    {
        rectfill(BUFFER, 303, 12, 312, 20, makecol(101,101,101));
        textout_ex(BUFFER, GAME_FONT, formatInteger(2, context.GetCurrentLevel()).c_str(), 303, 12, makecol(255, 255, 255), -1);
        context.SetCurrentLevelChanged(false);
    }

    //Scores
    if(context.TopScoreChanged() || context.CurrentScoreChanged())
    {
        rectfill(BUFFER, 262, 118, 310, 126, makecol(101,101,101));
        textout_ex(BUFFER, GAME_FONT, formatInteger(6, context.GetTopScore()).c_str(), 262, 118, makecol(255, 255, 255), -1); 
        rectfill(BUFFER, 262, 138, 310, 146, makecol(101,101,101)); 
        textout_ex(BUFFER, GAME_FONT, formatInteger(6, context.GetCurrentScore()).c_str(), 262, 138, makecol(255, 255, 255), -1); 
        context.SetCurrentScoreChanged(false);
        context.SetTopScoreChanged(false);
    }

    //Draw Next Piece
    clear_to_color(NEXTWINDOW, makecol(57,85,113));
    context.GetNextPiece().Draw(NEXTWINDOW, GAMEUI, true);
    blit(NEXTWINDOW, BUFFER, 0, 0, 272, 48, blockSize * 4, blockSize * 4);

    //Draw Play Grid
    clear_to_color(PLAYGRID, makecol(0, 0, 0));
    for (int y = 0; y < playGridHeight; y++) 
    {
        for (int x = 0; x < playGridWidth; x++) 
        {
            if (context.PlayGrid()[y][x] > 0)
                blit(GAMEUI, PLAYGRID, 72 + ((context.PlayGrid()[y][x] - 1) * 8), 56, x * blockSize, y * blockSize, blockSize * 4, blockSize * 4);
            else
                blit(GAMEUI, PLAYGRID, 120, 0, x * blockSize, y * blockSize, blockSize * 4, blockSize * 4);
        }
    }    

    //Draw Current Piece
    context.GetCurrentPiece().Draw(PLAYGRID, GAMEUI, 0);
    blit(PLAYGRID, BUFFER, 0, 0, 136, 24, blockSize * playGridWidth, blockSize * playGridHeight);

    draw_sprite(screen, BUFFER, 0, 0);
}

void GameState::DrawBackground()
{
    std::ifstream ifs(".\\GFX\\GAMEUI.jsn");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject guiJson = json::jobject::parse(content);  
    this->tileData = guiJson["background"];

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