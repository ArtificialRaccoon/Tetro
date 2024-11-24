#include "GameOverState.h"

void GameOverState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BACKGROUND = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    DIALOG = create_bitmap(112, 32);
    clear_to_color(DIALOG, makecol(0, 0, 0));
    blit(screen, BACKGROUND, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    int destXPos = 0;
    int destYPos = 0;
    int srcXPos = 0;
    int srcYPos = 0;

    unsigned tile_index = 0;

    for (int y = 0; y < dialogHeight; y++)
    {
        destXPos = 0;
        tile_index = y * dialogWidth;

        for (int x = 0; x < dialogWidth; x++)
        {
            bool H = GameContext::Instance()->DialogTileData[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
            unsigned tileID = GameContext::Instance()->DialogTileData[tile_index];

            tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

            srcXPos = tileWidth * ((tileID - 1) % tilesetWidth);
            srcYPos = tileHeight * floor((tileID - 1) / tilesetWidth);

            masked_blit(GameContext::Instance()->GAMEUI, DIALOG, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);

            tile_index += 1;
            destXPos += tileWidth;
        }

        destYPos += tileHeight;
    }
}

void GameOverState::Pause()
{

} 


void GameOverState::Resume()
{

}

void GameOverState::AquireInput(GameProcessor* game)
{
    if(keypressed())
    {
        switch(readkey() >> 8)
        {        
            case KEY_Y:
                GameState::Instance()->Reset();
                game->ChangeState(GameState::Instance());
                break;
            case KEY_N:
                game->ChangeState(TitleState::Instance());
                break;
        }
        clear_keybuf();
    }    
}

void GameOverState::ProcessInput(GameProcessor* game)
{ 

}

void GameOverState::Render(GameProcessor* game)
{
    draw_sprite(BUFFER, BACKGROUND, 0, 0);
    textout_ex(DIALOG, GameContext::Instance()->GAME_FONT, "Play Again?", 24, 6, makecol(255, 255, 255), -1);
    textout_ex(DIALOG, GameContext::Instance()->GAME_FONT, "Y / N", 42, 18, makecol(255, 255, 255), -1);
    masked_blit(DIALOG, BUFFER, 0, 0, 120, 64, dialogWidth * 8, dialogHeight * 8);
    draw_sprite(screen, BUFFER, 0, 0);
}