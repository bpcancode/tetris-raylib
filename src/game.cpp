#include <random>

#include "game.h"
#include "blocks.cpp"

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    isGameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("sounds/music.mp3");
    PlayMusicStream(music);
    soundClear = LoadSound("sounds/clear.mp3");
    soundRotate = LoadSound("sounds/rotate.mp3");
}

Game::~Game()
{
    UnloadSound(soundRotate);
    UnloadSound(soundClear);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = GetAllBlocks(); 
    }
    int randomIndex = rand() % blocks.size();
    Block randomBlock = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return randomBlock;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(isGameOver && keyPressed != 0)
    {
        isGameOver = false;
        Reset();
    }
    switch(keyPressed)
    {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1);
            break;
        case KEY_UP:
            rotateBlock();
            break;
    }
}

void Game::MoveBlockLeft()
{
    if(!isGameOver)
    {
        currentBlock.Move(0, -1);
        if(isBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if(!isGameOver)
    {
        currentBlock.Move(0, 1);
        if(isBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0, -1);
        }
    }
   
}

void Game::MoveBlockDown()
{
    if(!isGameOver){
        currentBlock.Move(1, 0);
        if(isBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}


void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);

    switch(nextBlock.id)
    {
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
            break;

    }
}

void Game::Reset()
{
    grid.Initilize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position tile : tiles)
    {
        if(grid.isCellOutside(tile.row, tile.column))
        {
            return true;
        }
    }
    return false;
}

void Game::rotateBlock()
{
    currentBlock.Rotate();
    if(isBlockOutside())
    {
        currentBlock.UndoRotation();
    }
    else
    {
        PlaySound(soundRotate);
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position tile : tiles)
    {
        grid.grid[tile.row][tile.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(!BlockFits())
    {
        isGameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if(rowsCleared > 0)
    {
        PlaySound(soundClear);
        UpdateScore(rowsCleared, 0);
    }
}

void Game::UpdateScore(int linesCleared, int movedDownPoints)
{
    switch(linesCleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        default:
            break;
    }
    score += movedDownPoints;
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position tile: tiles)
    {
        if(!grid.IsCellEmpty(tile.row, tile.column))
        {
            return false;
        }
    }
    return true;
}
