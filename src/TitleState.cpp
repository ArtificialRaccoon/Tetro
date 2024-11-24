#include "TitleState.h"

void TitleState::InitState()
{
    BUFFER = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    BACKGROUND = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    clear_to_color(BUFFER, makecol(0, 0, 0));
    clear_to_color(BACKGROUND, makecol(0, 0, 0));
    
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
            bool H = GameContext::Instance()->TitleTileData[tile_index] & FLIPPED_HORIZONTALLY_FLAG;
            unsigned tileID = GameContext::Instance()->TitleTileData[tile_index];

            tileID &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

            srcXPos = tileWidth * ((tileID - 1) % tilesetWidth);
            srcYPos = tileHeight * floor((tileID - 1) / tilesetWidth);

            masked_blit(GameContext::Instance()->GAMEUI, BACKGROUND, srcXPos, srcYPos, destXPos, destYPos, tileWidth, tileHeight);

            tile_index += 1;
            destXPos += tileWidth;
        }

        destYPos += tileHeight;
    }

    draw_sprite(BUFFER, BACKGROUND, 0, 0);
    draw_sprite(screen, BUFFER, 0, 0);

    play_midi(GameContext::Instance()->TITLEMUSIC, 1);
}

void TitleState::Pause()
{

} 


void TitleState::Resume()
{

}

void TitleState::AquireInput(GameProcessor* game)
{
    if(keypressed())
    {
        switch(readkey() >> 8)
        {        
            case KEY_DOWN:
                selectedItem++;
                break;
            case KEY_UP:                
                selectedItem--;
                break;
            case KEY_ENTER:
                trigger = true;
                break;
        }
        clear_keybuf();
    }    
}

void TitleState::ProcessInput(GameProcessor* game)
{ 
    if(selectedItem < 0)
        selectedItem = 2;
    if(selectedItem > 2)
        selectedItem = 0;

    if(trigger)
    {
        trigger = false;
        if(selectedItem == 0)
            game->ChangeState(GameState::Instance());
        else if(selectedItem == 1)
            GameContext::Instance()->SwapRandomizer();
        else
            exit(0);
    }
}

void TitleState::Render(GameProcessor* game)
{
    bool use7Bag = GameContext::Instance()->UseSevenBag();
    int textWidth = text_length(GameContext::Instance()->GAME_FONT, "Randomizer: ");

    draw_sprite(BUFFER, BACKGROUND, 0, 0);
    textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, "Play Game", menuXStart, menuYStart, makecol(255, 255, 255), -1);
    textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, "Randomizer: ", menuXStart, menuYRandom, makecol(255, 255, 255), -1);
    textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, use7Bag ? "7-Bag" : "TGM", menuXStart + textWidth, menuYRandom, use7Bag ? makecol(255, 0, 255) : makecol(255, 255, 0), -1);
    textout_ex(BUFFER, GameContext::Instance()->GAME_FONT, "Exit to DOS", menuXStart, menuYExit, makecol(255, 255, 255), -1);        
    
    if(selectedItem == 0)
        blit(GameContext::Instance()->GAMEUI, BUFFER, 104, 88, menuXStart - 10, menuYStart - 1, 8, 8);

    if(selectedItem == 1)
        blit(GameContext::Instance()->GAMEUI, BUFFER, 104, 88, menuXStart - 10, menuYRandom - 1, 8, 8);

    if(selectedItem == 2)
        blit(GameContext::Instance()->GAMEUI, BUFFER, 104, 88, menuXStart - 10, menuYExit - 1, 8, 8);

    draw_sprite(screen, BUFFER, 0, 0);
}