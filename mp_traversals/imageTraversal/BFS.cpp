#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  basePng = &png;
  baseStart = &start;
  baseTolerance = tolerance;

  // initialize all the points as not been visited
  for (unsigned row = 0; row < png.width(); row++) {
    std::vector<bool> rowVector;
    (this->hasPointBeenVisited).push_back(rowVector);
    for (unsigned col = 0; col < png.height(); col++) {
      (this->hasPointBeenVisited.at(row)).push_back(false);
    }
  }

  (this->pointsQueue).push(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  BFS* bfsP = new BFS(*basePng, *baseStart, baseTolerance);
  return ImageTraversal::Iterator(bfsP, *baseStart);
}
/*
BFS::~BFS() {
  delete this;
}
*/

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  // create point that is -1 -1 on teh stack
  //Point endPoint(-1, -1);
  //BFS* bfsP = new BFS(this->png, this->start, this->tolerance);
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  pointsQueue.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if (pointsQueue.empty()) {
    Point invalidPoint(-1, -1);
    return invalidPoint;
  }
  Point currentPoint = pointsQueue.front();
  pointsQueue.pop();
  return currentPoint;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if (pointsQueue.empty()) {
    Point invalidPoint(-1, -1);
    return invalidPoint;
  }
  Point currentPoint = pointsQueue.front();
  return currentPoint;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  return pointsQueue.empty();
}
