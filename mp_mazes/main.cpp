#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze mazeObject;
    mazeObject.makeMaze(100,100);
    cs225::PNG* creativeMaze = mazeObject.drawCreativeMaze();
    creativeMaze->writeToFile("creative.png");
    return 0;
}
