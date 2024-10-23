#include "color.h"

const Color darkGray = {45, 45, 45, 255};
const Color green = {34, 139, 34, 255};
const Color red = {220, 70, 57, 255};
const Color yellow = {255, 193, 7, 255};
const Color purple = {138, 43, 226, 255};
const Color blue = {25, 121, 202, 255};
const Color cyan = {0, 206, 209, 255};
const Color orange = {255, 140, 0, 255};
const Color lightBlue = {135, 206, 250, 255};
const Color darkBlue = {0, 0, 128, 255};



std::vector<Color> GetCellColors()
{
    return {darkGray, green, red, yellow, purple, blue, cyan, orange};
}