#include "GameContext.h"

GameContext::GameContext()
{
    //Init Random Number Generator
    srand(static_cast<unsigned int>(time(0))); 

    //Initialize the Play Grid
    for (int i = 0; i < playGridHeight; i++) 
    {
        playGrid[i] = new int[playGridWidth];
    }

    for (int i = 0; i < playGridHeight; i++) 
    {
        for (int j = 0; j < playGridWidth; j++) 
        {
            playGrid[i][j] = 0;
        }
    }

    this->currentPiece = Tetromino(GetRandomTetromino());
    this->nextPiece = Tetromino(GetRandomTetromino());
}

void GameContext::SpawnTetromino()
{
    currentPiece = Tetromino(nextPiece.GetType());
    nextPiece = Tetromino(GetRandomTetromino());
}

int GameContext::GetRandomTetromino()
{
    //Standard 7-Bag Randomization
    if(useSevenBag)
    {
        if(sevenBag.size() == 0)
            sevenBag.assign({0, 1, 2, 3, 4, 5, 6});
        int randomIndex = rand() % sevenBag.size();
        int value = sevenBag[randomIndex];
        sevenBag.erase(sevenBag.begin() + randomIndex);
        return value;
    }

    //TGM Randomization     
    int randomType = rand() % 7; 
    int matchCount = 0;

    while (matchCount < 4) 
    {
        bool found = false;
        for (int i = 0; i < 4; i++) 
        {
            if (tgmHistory[i] == randomType) 
            {
                found = true;
                break;
            }
        }

        if (found) 
        {
            randomType = rand() % 7;             
            matchCount++;
        } 
        else 
            break;
    }

    tgmHistory[historyIndex] = randomType;
    historyIndex = (historyIndex + 1) % 4;

    return randomType;
}

void GameContext::IncreaseCurrentLines(int input) 
{ 
    currentLines += input; 
    SetCurrentLinesChanged(true); 

    if(currentLines > 0 && (currentLines % 10) == 0)
        IncreaseCurrentLevel();
}

void GameContext::SetCurrentScore(int input) 
{ 
    currentScore += input; 
    SetCurrentScoreChanged(true); 

    if(currentScore > topScore)
        SetTopScore(currentScore);
}

void GameContext::CheckForCompletedLines()
{
    int completedLineCount = 0;

    for(int y = 0; y < playGridHeight; y++)
    {
        bool lineCompleted = true;
        for(int x = 0; x < playGridWidth; x++)
        {
            if(playGrid[y][x] == 0)
            {
                lineCompleted = false;
                break;
            }
        }

        if(lineCompleted)
        {
            IncreaseCurrentLines(1);
            RemoveCompletedLine(y);
            completedLineCount++;
        }
    }

    switch(completedLineCount)
    {
        case 1:
            SetCurrentScore(100);
            break;
        case 2:
            SetCurrentScore(300);
            break;
        case 3:
            SetCurrentScore(500);
            break;
        case 4:
            SetCurrentScore(1000);            
            break;
        default:
            break;
    }
}

void GameContext::RemoveCompletedLine(int rowPosition)
{
    for (int y = rowPosition; y > 0; y--) 
    {
        for (int x = 0; x < playGridWidth; x++) 
        {
            playGrid[y][x] = playGrid[y - 1][x];
        }
    }

    for (int x = 0; x < playGridWidth; x++) 
    {
        playGrid[0][x] = 0;
    }
}