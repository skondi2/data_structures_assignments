#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  basePng = &png;
  baseStart = &start;
  baseTolerance = tolerance;
  (this->pointsStack).push(start);

  // initialize all the points as not been visited
  for (unsigned row = 0; row < png.width(); row++) {
    std::vector<bool> rowVector;
    (this->hasPointBeenVisited).push_back(rowVector);
    for (unsigned col = 0; col < png.height(); col++) {
      (this->hasPointBeenVisited.at(row)).push_back(false);
    }
  }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS* dfsP = new DFS(*basePng, *baseStart, baseTolerance);
  return ImageTraversal::Iterator(dfsP, *baseStart);
}
/*
DFS::~DFS() {
  delete this;
}
*/

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  //DFS* dfsP = new DFS(this->png, this->start, this->tolerance);
  //Point invalidPoint(-1, -1);
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  pointsStack.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if (pointsStack.empty()) {
    Point invalidPoint(-1, -1);
    return invalidPoint;
  }
  Point currentPoint = pointsStack.top();
  pointsStack.pop();
  return currentPoint;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if (pointsStack.empty()) {
    Point invalidPoint(-1, -1);
    return invalidPoint;
  }
  Point currentPoint = pointsStack.top();
  return currentPoint;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return pointsStack.empty();
}
