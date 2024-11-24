#include "GameContext.h"

GameContext::GameContext()
{
    //Load Audio
    GAMEOVER = load_sample(".\\SFX\\GAMEOVER.WAV");
    POINTS = load_sample(".\\SFX\\CLEAR.WAV");
    INGAMEMUSIC = load_midi(".\\OTHER\\TETRIS.MID");
    TITLEMUSIC = load_midi(".\\OTHER\\TITLE.MID");

    //Load Graphics
    GAME_FONT = load_font(".\\OTHER\\DEFAULT.bmp", palette, NULL);
    GAMEUI = load_bitmap(".\\GFX\\GAMEUI.bmp", palette); 

    //Load GUI Layout
    std::ifstream ifs(".\\GFX\\GAMEUI.jsn");
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    json::jobject guiJson = json::jobject::parse(content);  
    BackTileData = guiJson["background"];
    DialogTileData = guiJson["popup"];
    TitleTileData = guiJson["title"];

    //Init Random Number Generator
    srand(static_cast<unsigned int>(time(0))); 
    Reset();
}

void GameContext::Reset()
{
    topScore = 0;
    currentScore = 0;        
    currentLevel = 1;        
    currentLines = 0;
    historyIndex = 0;
    dropCounter = 0;

    levelChanged = true;
    scoreChanged = true;
    topScoreChanged = true;
    currentLinesChanged = true; 

    for(int i = 0; i < 7; i++)
    {
        tetrominoTally[i] = 0;
        tetrominoTallyChanged[i] = true;
    }

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

    this->LoadTopScore();
}

bool GameContext::CanSpawn()
{
    return nextPiece.CanSpawn(playGrid);
}

void GameContext::SpawnTetromino()
{
    this->dropCounter = 0;
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

void GameContext::CheckForCompletedLines(SAMPLE* points)
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
            play_sample(points, 255, 128, 1000, FALSE);
            break;
        case 2:
            SetCurrentScore(300);
            play_sample(points, 255, 128, 1000, FALSE);
            break;
        case 3:
            SetCurrentScore(500);
            play_sample(points, 255, 128, 1000, FALSE);
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

bool GameContext::ShouldDrop()
{
    this->dropCounter++;    
    int frameCountBeforeDrop = framesBeforeDrop[this->currentLevel > 19 ? 19 : this->currentLevel];
    if(this->dropCounter >= frameCountBeforeDrop)
    {
        this->dropCounter = 0;
        return true;
    }
    return false;
}

void GameContext::SaveTopScore()
{
    std::ofstream scoreFile("topscore.sav", std::ios::binary);
    std::vector<char> buffer(sizeof(int) * 2);
    memcpy(buffer.data(), &currentScore, sizeof(int));
    memcpy(buffer.data() + sizeof(int), &currentLines, sizeof(int));  //Saving the lines for now; will use later when I add a top score screen.
    EncodeDecodeScore(buffer, ScoreKey);
    scoreFile.write(buffer.data(), buffer.size());
}

void GameContext::LoadTopScore()
{
    std::ifstream scoreFile("topscore.sav", std::ios::binary);
    if(scoreFile.fail())
        return;
    
    std::vector<char> buffer(sizeof(int) * 2);
    scoreFile.read(buffer.data(), buffer.size());
    EncodeDecodeScore(buffer, ScoreKey);
    memcpy(&topScore, buffer.data(), sizeof(int));
}