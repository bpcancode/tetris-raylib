#include "block.h"
#include <vector>
#include <iostream>

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int xoffset, int yoffset)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position tile : tiles)
    {
        Color cellColor = colors[id];
        DrawRectangle(tile.column * cellSize + xoffset, tile.row * cellSize + yoffset, cellSize - 1, cellSize - 1, cellColor);
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position tile : tiles)
    {
        
        Position newTile = Position(tile.row + rowOffset, tile.column + columnOffset);
        movedTiles.push_back(newTile);
    }

    return movedTiles;
}

void Block::Rotate()
{
    rotationState = (rotationState + 1) % (int) cells.size();
}

void Block::UndoRotation()
{
    rotationState = (rotationState + 3) % (int) cells.size();
}
