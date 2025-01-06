#include "GameState.h"

void GameState::InitState()
{
    DISPLAY = create_video_bitmap(SCREEN_W, SCREEN_H);
    BUFFER = create_video_bitmap(SCREEN_W, SCREEN_H);
    BACKGROUND = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    NEXTWINDOW = create_bitmap(blockSize * 4, blockSize * 4);
    PLAYGRID = create_sub_bitmap(BUFFER, 136, 24, blockSize * playGridWidth, blockSize * playGridHeight);

    clear_to_color(BACKGROUND, makecol(0, 0, 0));
    clear_to_color(NEXTWINDOW, makecol(57,85,113));
    clear_to_color(PLAYGRID, makecol(0, 0, 0));

    DrawBackground();

    //Statistics Header
    textout_centre_ex(BACKGROUND, GameContext::Instance()->GAME_FONT, "STATISTICS", 50, 8, makecol(255, 255, 255), -1);

    //Lines Header
    textout_centre_ex(BACKGROUND, GameContext::Instance()->GAME_FONT, "Lines ", 170, 8, makecol(255, 255, 255), -1);

    //Level Header
    textout_ex(BACKGROUND, GameContext::Instance()->GAME_FONT, "Level", 262, 12, makecol(255, 255, 255), -1);

    //Next Block Header
    textout_centre_ex(BACKGROUND, GameContext::Instance()->GAME_FONT, "Next", 288, 38, makecol(255, 255, 255), -1);

    //Score Headers
    textout_ex(BACKGROUND, GameContext::Instance()->GAME_FONT, "TOP", 262, 110, makecol(255, 255, 255), -1);    
    textout_ex(BACKGROUND, GameContext::Instance()->GAME_FONT, "SCORE", 262, 130, makecol(255, 255, 255), -1); 

    draw_sprite(BUFFER, BACKGROUND, 0, 0);

    //Play Soundtrack
    play_looped_midi(GameContext::Instance()->INGAMEMUSIC, 0, 97);
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
                GameContext::Instance()->GetCurrentPiece().Rotate(GameContext::Instance()->PlayGrid(), GameContext::Instance()->ChangedGrid());        
                break;
            case KEY_S:
            case KEY_DOWN:
                GameContext::Instance()->GetCurrentPiece().Down(GameContext::Instance()->PlayGrid(), GameContext::Instance()->ChangedGrid());
                break;        
            case KEY_A:
            case KEY_LEFT:       
                GameContext::Instance()->GetCurrentPiece().Left(GameContext::Instance()->PlayGrid(), GameContext::Instance()->ChangedGrid());
                break;
            case KEY_D:
            case KEY_RIGHT:
                GameContext::Instance()->GetCurrentPiece().Right(GameContext::Instance()->PlayGrid(), GameContext::Instance()->ChangedGrid());
                break;  
            case KEY_SPACE:
                GameContext::Instance()->GetCurrentPiece().HardDrop(GameContext::Instance()->PlayGrid(), GameContext::Instance()->ChangedGrid());
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
    if (GameContext::Instance()->ShouldDrop())
        GameContext::Instance()->GetCurrentPiece().Down(GameContext::Instance()->PlayGrid(), GameContext::Instance()->ChangedGrid());

    if (GameContext::Instance()->GetCurrentPiece().CanLock(GameContext::Instance()->PlayGrid())) 
    {
        GameContext::Instance()->IncreaseTetrominoTally(GameContext::Instance()->GetCurrentPiece().GetType());
        GameContext::Instance()->GetCurrentPiece().LockPiece(GameContext::Instance()->PlayGrid(), GameContext::Instance()->ChangedGrid());
        GameContext::Instance()->CheckForCompletedLines(GameContext::Instance()->POINTS);
        
        if (GameContext::Instance()->CanSpawn())
            GameContext::Instance()->SpawnTetromino();
        else
        {
            stop_midi();
            play_sample(GameContext::Instance()->GAMEOVER, 255, 128, 1000, FALSE);

            // Show the player HOW they lost
            GameContext::Instance()->SpawnTetromino();
            Render(game);
            this->UnloadResources();
            game->ChangeState(GameOverState::Instance());
        }
    }
}

void GameState::Render(GameProcessor* game)
{
    //Lines
    if(GameContext::Instance()->CurrentLinesChanged())
    {
        rectfill(BUFFER, 186, 8, 210, 16, makecol(57,85,113));
        textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, formatInteger(3, GameContext::Instance()->GetCurrentLines()).c_str(), 186, 8, makecol(255, 255, 255), -1);
        GameContext::Instance()->SetCurrentLinesChanged(false);
    }

    //Statistics
    for(int i = 0; i < 7; i++)
    {
        if(GameContext::Instance()->TetrominoTallyChanged(i))
        {
            rectfill(BUFFER, 56, 24 + (i * 24), 56 + (3 * 8), 24 + (i * 24) + 8, makecol(57,85,113));
            textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, formatInteger(3, GameContext::Instance()->GetTetrominoTally(i)).c_str(), 56, 24 + (i * 24), makecol(255, 255, 255), -1);
            GameContext::Instance()->SetTetrominoTallyChanged(i, false);
        }
    }

    //Current Level   
    if(GameContext::Instance()->CurrentLevelChanged())
    {
        rectfill(BUFFER, 303, 12, 313, 20, makecol(101,101,101));
        textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, formatInteger(2, GameContext::Instance()->GetCurrentLevel()).c_str(), 303, 12, makecol(255, 255, 255), -1);
        GameContext::Instance()->SetCurrentLevelChanged(false);
    }

    //Scores
    if(GameContext::Instance()->TopScoreChanged() || GameContext::Instance()->CurrentScoreChanged())
    {
        rectfill(BUFFER, 262, 118, 310, 126, makecol(101,101,101));
        textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, formatInteger(6, GameContext::Instance()->GetTopScore()).c_str(), 262, 118, makecol(255, 255, 255), -1); 
        rectfill(BUFFER, 262, 138, 310, 146, makecol(101,101,101)); 
        textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, formatInteger(6, GameContext::Instance()->GetCurrentScore()).c_str(), 262, 138, makecol(255, 255, 255), -1); 
        GameContext::Instance()->SetCurrentScoreChanged(false);
        GameContext::Instance()->SetTopScoreChanged(false);
    }

    //Draw Next Piece
    if(GameContext::Instance()->NextPieceChanged())
    {
        clear_to_color(NEXTWINDOW, makecol(57,85,113));
        GameContext::Instance()->GetNextPiece().Draw(NEXTWINDOW, GameContext::Instance()->GAMEUI, true);
        blit(NEXTWINDOW, BUFFER, 0, 0, 272, 48, blockSize * 4, blockSize * 4);
        GameContext::Instance()->SetNextPieceChanged(false);
    }

    //Draw Play Grid
    for (int y = 0; y < playGridHeight; y++) 
    {
        for (int x = 0; x < playGridWidth; x++) 
        {
            if (GameContext::Instance()->ChangedGrid()[y][x] == true)
            {
                if (GameContext::Instance()->PlayGrid()[y][x] > 0)
                    blit(GameContext::Instance()->GAMEUI, PLAYGRID, 72 + ((GameContext::Instance()->PlayGrid()[y][x] - 1) * 8), 56, x * blockSize, y * blockSize, blockSize, blockSize);
                else
                    blit(GameContext::Instance()->GAMEUI, PLAYGRID, 120, 0, x * blockSize, y * blockSize, blockSize, blockSize);
                GameContext::Instance()->ChangedGrid()[y][x] = false;
            }
        }
    }    

    //Draw Current Piece
    GameContext::Instance()->GetCurrentPiece().Draw(PLAYGRID, GameContext::Instance()->GAMEUI, 0);
    blit(BUFFER, DISPLAY, 0, 0, 0, 0, 320, 200);
}

void GameState::DrawBackground()
{
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
            bool H = GameContext::Instance()->BackTileData[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
            unsigned tileID = GameContext::Instance()->BackTileData[tile_index];

            tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

            srcXPos = tileWidth * ((tileID - 1) % tilesetWidth);
            srcYPos = tileHeight * floor((tileID - 1) / tilesetWidth);

            masked_blit(GameContext::Instance()->GAMEUI, BACKGROUND, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);

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

void GameState::Reset()
{
    GameContext::Instance()->Reset();
}

void GameState::UnloadResources()
{
    destroy_bitmap(DISPLAY);
    destroy_bitmap(PLAYGRID);
    destroy_bitmap(BUFFER);
    destroy_bitmap(BACKGROUND);
    destroy_bitmap(NEXTWINDOW);
}