#pragma once
#include <raylib.h>
#include <vector>

class Grid
{
private:
    int numRows;
    int numCols;
    int cellSize;
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    std::vector<Color> colors;
public:
    Grid();
    bool isCellOutside(int row, int column);
    int ClearFullRows();
    bool IsCellEmpty(int row, int column);
    void Initilize();
    void Draw();
    void Print();
    int grid[20][10];
};
