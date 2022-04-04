/* Your code here! */
#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"

class SquareMaze {

  class Cell {
    public:
      bool hasRightWall;
      bool hasDownWall;
  };

  public:
    SquareMaze();

    SquareMaze(int width, int height);

    void makeMaze(int width, int height);

    void setWall(int x, int y, int dir, bool exists);

    std::vector<int> solveMaze();

    bool canTravel(int x, int y, int dir) const;

    cs225::PNG* drawMaze() const;

    cs225::PNG* drawMazeWithSolution();

    int getWidth();

    int getHeight();

    void setWidth(int width);

    void setHeight(int height);

    void clearMaze();

    std::vector<std::vector<Cell>> initializeMaze(int width, int height);

    void bfsPath(std::vector<int>& cellPath, std::vector<int>& distances,
      int currentCell);

    cs225::PNG* drawCreativeMaze();

  private:
    int width;
    int height;
    DisjointSets wallSet;
    std::vector<std::vector<Cell>> mazeCells;
    std::pair<int,int> destinationSquare;
};
