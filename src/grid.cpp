#include "Grid.h"
#include <vector>
#include <raylib.h>
#include <iostream>
#include "color.h"

bool Grid::IsRowFull(int row)
{
    for(int col=0; col < numCols; col++)
    {
        if(grid[row][col] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int col=0; col < numCols; col++)
    {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for(int col=0; col < numCols; col++)
    {
        grid[row+numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int row = numRows-1; row >=0; row--)
    {
        if(IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

Grid::Grid()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initilize();
    colors = GetCellColors();
}

void Grid::Initilize(){
    for (int row=0; row <numRows; row++){
        for (int col=0; col <numCols; col++){
            grid[row][col] = 0;
        }
    }
}

void Grid::Print(){
    for (int row=0; row <numRows; row++){
        for (int col=0; col <numCols; col++){
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

bool Grid::isCellOutside(int row, int column)
{
    if(row >= 0 && row < numRows && column >= 0 && column < numCols)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if(grid[row][column] == 0)
    {
        return true;
    }
    return false;
}

void Grid::Draw() {
    
    for(int row=0; row < numRows; row++) {
        for(int col=0; col < numCols; col++) {
            int cellValue = grid[row][col];
            Color cellColor = colors[cellValue];
            DrawRectangle(col*cellSize+11, row*cellSize+11, cellSize-1, cellSize-1, cellColor);
        }
    }
}