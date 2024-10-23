#pragma once
#include "grid.h"
#include "block.h"

class Game
{
  public:
    Game();
    ~Game();
    void HandleInput();
    void MoveBlockDown();
    void Draw();
    void Reset();
    int score;
    bool isGameOver;
    Music music;

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool isBlockOutside();
    void rotateBlock();
    void LockBlock();
    void UpdateScore(int linesCleared, int movedDownPoints);
    bool BlockFits();

    Grid grid;
    std::vector<Block> blocks;

    Block currentBlock;
    Block nextBlock;
    Sound soundRotate;
    Sound soundClear;
};