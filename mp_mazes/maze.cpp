/* Your code here! */
#include <vector>
#include <cstdlib>
#include "maze.h"
#include <iostream>
#include <queue>
#include <stack>

/**
  default constructor to set width and height to 0 and keep disjoint set
  and 2d vector empty
*/
SquareMaze::SquareMaze() {
  this->width = 0;
  this->height = 0;
}

int SquareMaze::getWidth() {
  return this->width;
}

int SquareMaze::getHeight(){
  return this->height;
}

void SquareMaze::setWidth(int width) {
  this->width = width;
}

void SquareMaze::setHeight(int height) {
  this->height = height;
}

/**
  constructor to set width and height and default disjoint set and 2d vector
*/
SquareMaze::SquareMaze(int width, int height) {
  this->width = width;
  this->height = height;

  wallSet.addelements(width * height);

  for (int i = 0; i < width; i++) {
    std::vector<Cell> row;
    for (int j = 0; j < height; j++) {
      std::vector<Cell> column;
      Cell c;
      c.hasDownWall = 1;
      c.hasRightWall = 1;
      row.push_back(c);
    }
    mazeCells.push_back(row);
  }

}

/**
  Helper function to set properties of class back to default
*/
void SquareMaze::clearMaze() {
  // clear out the disjoint set
  wallSet.union1.clear();

  // empty out the mazeCells
  mazeCells = std::vector<std::vector<SquareMaze::Cell>>();

  // reset width and getHeight
  setWidth(0);
  setHeight(0);
}

/**
  Helper function to clear the current properties of maze and then
  reinitialize properties of maze. Returns new 2D vector of maze full of walls
*/
std::vector<std::vector<SquareMaze::Cell>> SquareMaze::initializeMaze(int width, int height) {
  clearMaze();
  wallSet.addelements(width * height);

  std::vector<std::vector<SquareMaze::Cell>> newMaze;
  for (int i = 0; i < width; i++) {
    std::vector<SquareMaze::Cell> row;
    for (int j = 0; j < height; j++) {
      std::vector<SquareMaze::Cell> column;
      SquareMaze::Cell c;
      c.hasDownWall = 1;
      c.hasRightWall = 1;
      row.push_back(c);
    }
    newMaze.push_back(row);
  }

  setWidth(width);
  setHeight(height);

  return newMaze;
}

/**
  Makes a new SquareMaze of the given height and width.

  If this object already represents a maze it will clear all the existing data
  before doing so. You will start with a square grid (like graph paper) with the
  specified height and width. You will select random walls to delete without creating
  a cycle, until there are no more walls that could be deleted without creating a cycle.
  Do not delete walls on the perimeter of the grid.

  Hints: You only need to store 2 bits per square: the "down" and "right" walls.
  The finished maze is always a tree of corridors.)
*/
void SquareMaze::makeMaze(int width, int height) {
  // reset mazeCells
  mazeCells = initializeMaze(width, height);

  while (wallSet.size(0) <= (getWidth() * getHeight() - 1)) {
    // continue breaking down wall
    int randomWidth = (rand() % getWidth());
    int randomHeight = (rand() % getHeight());

    bool validRight = false;
    bool validDown = false;

    Cell randomCell = mazeCells[randomWidth][randomHeight];

    if (randomWidth + 1 < width) {
      validRight = true;
    }
    if (randomHeight + 1 < height) {
      validDown = true;
    }

    int cellIndex = randomHeight*getWidth() + randomWidth;
    int rightIndex = cellIndex + 1;
    int cellDown = cellIndex + getWidth();

    int randomNum = (rand() % 2);

    if (randomNum && validRight) {
      if (randomCell.hasRightWall && wallSet.find(cellIndex) != wallSet.find(rightIndex)) {
        // break right wall
        wallSet.setunion(cellIndex, rightIndex);
        setWall(randomWidth, randomHeight, 0, false);
      }
    } else if (validDown) {
      if (randomCell.hasDownWall && wallSet.find(cellIndex) != wallSet.find(cellDown)) {
        // break down wall
        wallSet.setunion(cellIndex, cellDown);
        setWall(randomWidth, randomHeight, 1, false);
      }
    }
  }
}

/**
  Sets whether or not the specified wall exists.

  This function should be fast (constant time). You can assume that in grading we
  will not make your maze a non-tree and then call one of the other member functions.
  setWall should not prevent cycles from occurring, but should simply set a wall to
  be present or not present. Our tests will call setWall to copy a specific maze
  into your implementation.
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if (dir == 1) {
    mazeCells[x][y].hasDownWall = exists;
  }

  if (dir == 0) {
    mazeCells[x][y].hasRightWall = exists;
  }
}

/**
  Solves this SquareMaze.

  For each square on the bottom row (maximum y coordinate), there is a distance
  from the origin (i.e. the top-left cell), which is defined as the length
  (measured as a number of steps) of the only path through the maze from the origin
  to that square.

  Select the square in the bottom row with the largest distance from the origin as
  the destination of the maze. solveMaze() returns the winning path from the origin
  to the destination as a vector of integers, where each integer represents the
  direction of a step, using the same encoding as in canTravel().

  If multiple paths of maximum length exist, use the one with the destination cell
  that has the smallest x value.

  Hint: this function should run in time linear in the number of cells in the maze.
*/
std::vector<int> SquareMaze::solveMaze() {
  // initialize both vectors as unvisited with -1 distance from origin
  std::vector<int> cellPath;
  std::vector<int> distances;
  int currentCell = 0;
  //int x = currentCell.first;
  //int y = currentCell.second;

  cellPath.push_back(currentCell);
  distances.push_back(0);
  for (int i = 1; i < getWidth() * getHeight(); i++) {
    cellPath.push_back(-1);
    distances.push_back(0);
  }

  bfsPath(cellPath, distances, currentCell);

  // find the longest distance
  int maxDistCell = getWidth() * (getHeight() - 1);
  int widthCoor = 0;
  for (int i = 0; i < getWidth(); i++) {
    if (distances[i + (getWidth() * (getHeight() - 1))] > distances[maxDistCell]) {
      maxDistCell = getWidth()*(getHeight()-1) + i;
      widthCoor = i;
    }
  }

  // trace back to get the path traveled
  destinationSquare = std::pair<int,int>(widthCoor, height - 1);
  std::vector<int> result;
  int curr = maxDistCell;
  //std::stack<int> pathTaken;

  while (!(curr == 0)) {

    int indexRight = curr + 1;
    int indexLeft = curr - 1;
    int indexUp = curr - getWidth();
    int indexDown = curr + getWidth();

    // if prev is left
    if (cellPath.at(curr) == indexLeft) {
      //pathTaken.push(0);
      result.push_back(0);
    }
    // if prev is up
    if (cellPath.at(curr)== indexUp) {
      //pathTaken.push(1);
      result.push_back(1);
    }
    // if prev is right
    if (cellPath.at(curr) == indexRight) {
      //pathTaken.push(2);
      result.push_back(2);
    }
    // if prev is down
    if (cellPath.at(curr) == indexDown) {
      //pathTaken.push(3);
      result.push_back(3);
    }
    curr = cellPath[curr];
  }
  std::vector<int> reversed(result.rbegin(), result.rend());
  result.swap(reversed);

  return result;
}

/**
  Helper function to do bfs traversal from origin to inputted point
*/
void SquareMaze::bfsPath(std::vector<int>& cellPath,
  std::vector<int>& distances, int currentCell) {

    // queue to keep track of cells visited
    std::queue<int> bfsTraversal;

    // the origin has been visited
    int x = 0;
    int y = 0;
    //int index = 0;
    bfsTraversal.push(0);

    while (!bfsTraversal.empty()) {
      currentCell = bfsTraversal.front();
      x = currentCell % width;
      y = currentCell / height;
      bfsTraversal.pop();

      int rightPosition = currentCell + 1;
      int leftPosition = currentCell - 1;
      int upPosition = currentCell - getWidth();
      int downPosition = currentCell + getWidth();

      // travel right
      if (canTravel(x,y,0)) {
        if (cellPath[rightPosition]==-1) {
          cellPath[rightPosition] = currentCell;
          distances[rightPosition] = distances[currentCell] + 1;
          bfsTraversal.push(rightPosition);
        }
      }

      // travel down
      if (canTravel(x,y,1)) {
        if (cellPath[downPosition] == -1 ) {
          cellPath[downPosition] = currentCell;
          distances[downPosition] = distances[currentCell] + 1;
          bfsTraversal.push(downPosition);
        }
      }

      // travel left
      if (canTravel(x,y,2)) {
        if (cellPath[leftPosition]==-1 ) {
          cellPath[leftPosition] = currentCell;
          distances[leftPosition] = distances[currentCell] + 1;
          bfsTraversal.push(leftPosition);
        }
      }

      // travel upwards
      if (canTravel(x,y,3)) {
        if (cellPath[upPosition]== -1 ) {
          cellPath[upPosition] = currentCell;
          distances[upPosition] = distances[currentCell] + 1;
          bfsTraversal.push(upPosition);
        }
      }
    }
  }


/**
  This uses your representation of the maze to determine whether it is possible to
  travel in the given direction from the square at coordinates (x,y).

  For example, after makeMaze(2,2), the possible input coordinates will be (0,0),
  (0,1), (1,0), and (1,1).

  dir = 0 represents a rightward step (+1 to the x coordinate)
  dir = 1 represents a downward step (+1 to the y coordinate)
  dir = 2 represents a leftward step (-1 to the x coordinate)
  dir = 3 represents an upward step (-1 to the y coordinate)
  You can not step off of the maze or through a wall.

  This function will be very helpful in solving the maze. It will also be used by
  the grading program to verify that your maze is a tree that occupies the whole grid,
  and to verify your maze solution. So make sure that this function works!
*/
bool SquareMaze::canTravel(int x, int y, int dir) const {
  // make sure x and y are valid locations
  //int width = getWidth();
  //int height = getHeight();
  if ( x < 0 || x >= width) {
    return false;
  }
  if (y < 0 || y >= height) {
    return false;
  }

  // going down
  if (y != height - 1 && !mazeCells[x][y].hasDownWall && dir == 1) {
    return true;
  }
  // going right
  if (x!= height - 1 && !mazeCells[x][y].hasRightWall && dir == 0) {
    return true;
  }
  //going left
  if (x!=0 && !mazeCells[x-1][y].hasRightWall && dir == 2) {
    return true;
  }
  // going up
  if (y!=0 && !mazeCells[x][y-1].hasDownWall && dir == 3) {
    return true;
  }

  return false;
}

/**
  Draws the maze without the solution.

  First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1).
  where height and width were the arguments to makeMaze. Blacken the entire topmost
  row and leftmost column of pixels, except the entrance (1,0) through (9,0).
  For each square in the maze, call its maze coordinates (x,y). If the right wall
  exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0
  to 10. If the bottom wall exists, then blacken the pixels with coordinates
  (x*10+k, (y+1)*10) for k from 0 to 10.

  The resulting PNG will look like the sample image, except there will be no exit
  from the maze and the red line will be missing.
*/
cs225::PNG* SquareMaze::drawMaze() const {
  cs225::PNG* newPNG = new cs225::PNG(width*10+1, width*10+1);

  // blacken the topmost
  for (unsigned i = 10; i < newPNG->width(); i++) {
    cs225::HSLAPixel& pixel = newPNG->getPixel(i, 0);
    pixel.l = 0;
  }

  // blacken leftmost
  for (unsigned j = 0; j < newPNG->height(); j++) {
    cs225::HSLAPixel& pixel = newPNG->getPixel(0, j);
    pixel.l = 0;
  }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (mazeCells[i][j].hasRightWall) {
        for (int k = 0; k <= 10; k++) {
          cs225::HSLAPixel& pixel = newPNG->getPixel((i+1)*10, j*10+k);
          pixel.l = 0;
        }
      }

      if (mazeCells[i][j].hasDownWall) {
        for (int k = 0; k <= 10; k++) {
          cs225::HSLAPixel& pixel = newPNG->getPixel(i*10+k, (j+1)*10);
          pixel.l = 0;
        }
      }
    }
  }
  return newPNG;
}

/**
This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze
to show the solution vector and the exit.

Start at pixel (5,5). Each direction in the solution vector corresponds to a
trail of 11 red pixels in the given direction. If the first step is downward,
color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). Then if the
second step is right, color pixels (5,15) through (15,15) red. Then if the third
step is up, color pixels (15,15) through (15,5) red. Continue in this manner until
you get to the end of the solution vector, so that your output looks analogous the
above picture.

Make the exit by undoing the bottom wall of the destination square: call the
destination maze coordinates (x,y), and whiten the pixels with coordinates
(x*10+k, (y+1)*10) for k from 1 to 9.
*/
cs225::PNG* SquareMaze::drawMazeWithSolution() {
  cs225::PNG* blankMaze = drawMaze();
  std::vector<int> solution = solveMaze();
  std::pair<int,int> coor(5,5);

  int destX = destinationSquare.first;
  int destY = destinationSquare.second;

  for (int i = 1; i <= 9; i++) {
    cs225::HSLAPixel& pixel = blankMaze->getPixel(destX*10 + i, (destY+1)*10);
    pixel.l = 1;
  }

  for (unsigned i = 0; i < solution.size(); i++) {
    //move right
    if (solution[i] == 0) {
      for (unsigned j = 0; j < 11; j++) {
        cs225::HSLAPixel& pixel = blankMaze->getPixel(coor.first+j, coor.second);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }
      coor.first = coor.first + 10;
    } else if (solution[i] == 1) {
      // move down
      for (unsigned j = 0; j < 11; j++) {
        cs225::HSLAPixel& pixel = blankMaze->getPixel(coor.first, coor.second+j);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }
      coor.second = coor.second + 10;
    } else if (solution[i] == 2) {
      for (unsigned j = 0; j < 11; j++) {
        cs225::HSLAPixel& pixel = blankMaze->getPixel(coor.first-j, coor.second);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }
      coor.first = coor.first - 10;
    } else if (solution[i] == 3) {
      for (unsigned j = 0; j < 11; j++) {
        cs225::HSLAPixel& pixel = blankMaze->getPixel(coor.first, coor.second-j);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
        pixel.a = 1;
      }
      coor.second = coor.second - 10;
    }
  }
  return blankMaze;
}

cs225::PNG* SquareMaze::drawCreativeMaze() {
  cs225::PNG* creativeMaze = drawMaze();

  for (unsigned i = 0; i < creativeMaze->width(); i++) {
    for (unsigned j = 0; j < 100; j++) {
      cs225::HSLAPixel& pixel = creativeMaze->getPixel(i, j);
      pixel.l = 0;
    }
  }

  for (unsigned i = creativeMaze->width() / 4; i < creativeMaze->width() / 2; i++) {
    for (unsigned j = 0; j < (creativeMaze->height())/2; j++ ) {
        cs225::HSLAPixel& pixel = creativeMaze->getPixel(i,j);
        pixel.l = 0;
    }
  }
return creativeMaze;

}
