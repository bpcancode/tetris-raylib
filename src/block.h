#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "color.h"

class Block
{
public:
    Block();
    void Draw(int xoffset, int yoffset);
    void Move(int rows, int columns);
    std::vector<Color> colors;
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int id;
    std::map<int, std::vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
    int rowOffset;
    int columnOffset;
};