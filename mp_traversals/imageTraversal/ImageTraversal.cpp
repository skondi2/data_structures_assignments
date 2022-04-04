#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"
#include <vector>

#include "ImageTraversal.h"


/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */

  //this->start = Point();
  //this->png = PNG();
  //this->tolerance = 0.0;
  //this->imageTraversal = NULL;
  this->currentPoint = Point(-1, -1); // point off the grid
  this->imageTraversal = NULL;
/*
  // initialize all the points as not been visited
  for (unsigned row = 0; row < png.width(); row++) {
    std::vector<bool> rowVector;
    (this->hasPointBeenVisited).push_back(rowVector);
    for (unsigned col = 0; col < png.height(); col++) {
      (this->hasPointBeenVisited.at(row)).push_back(false);
    }
  }
  */
}

ImageTraversal::~ImageTraversal() {

}

ImageTraversal::Iterator::~Iterator() {
  delete imageTraversal;
  this->imageTraversal = NULL;
}

/**
  Constructor for iterator that points to a Point
*/
ImageTraversal::Iterator::Iterator(ImageTraversal* imageTraversal, Point point) {
  //this->start = start;
  //this->tolerance = tolerance;
  //this->png = png;
  this->imageTraversal = imageTraversal;
  //(this->imageTraversal)->add(point); // i'm already adding in the BFS/DFS constructor
  this->currentPoint = point;

/*
  // initialize all the points as not been visited
  for (unsigned row = 0; row < png.width(); row++) {
    std::vector<bool> rowVector;
    (this->hasPointBeenVisited).push_back(rowVector);
    for (unsigned col = 0; col < png.height(); col++) {
      (this->hasPointBeenVisited.at(row)).push_back(false);
    }
  }
  */
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if ((this->imageTraversal)->empty()) { return *this; }

  const PNG* traversalPNG = (this->imageTraversal)->basePng;
  unsigned currentPointX = currentPoint.x;
  unsigned currentPointY = currentPoint.y;
  (this->imageTraversal)->pop(); // we have visited the current point
  (this->imageTraversal)->hasPointBeenVisited[currentPointX][currentPointY] = 1; // that position has been visited

  const HSLAPixel& startPixel = traversalPNG->getPixel((this->imageTraversal)->baseStart->x, (this->imageTraversal)->baseStart->y);

  if (currentPointX + 1 < traversalPNG->width()) { // within png dimension
    if (((this->imageTraversal)->hasPointBeenVisited[currentPointX+1][currentPointY]) == 0) { // if the point has not been visited yet
      const HSLAPixel& pixel = traversalPNG->getPixel(currentPointX + 1, currentPointY);
      if (calculateDelta(pixel, startPixel) < (this->imageTraversal)->baseTolerance) { // if within the tolerance
        Point rPoint(currentPointX + 1, currentPointY);
        (this->imageTraversal)->add(rPoint);
        //currentPoint.x = rPoint.x;
        //currentPoint.y = rPoint.y;
      }
    }
  }

  if (currentPointY + 1 < traversalPNG->height()) {
    if (((this->imageTraversal)->hasPointBeenVisited[currentPointX][currentPointY+1]) == 0) {
      const HSLAPixel& belowPixel = traversalPNG->getPixel(currentPointX, currentPointY + 1);
      if (calculateDelta(belowPixel, startPixel) < (this->imageTraversal)->baseTolerance) {
        Point bPoint(currentPointX, currentPointY + 1);
        imageTraversal->add(bPoint);
        //currentPoint.x = bPoint.x;
        //currentPoint.y = bPoint.y;
      }
    }
  }

  if (currentPointX - 1 >= 0 && currentPointX != 0) {
    if (((this->imageTraversal)->hasPointBeenVisited[currentPointX-1][currentPointY]) == 0) {
      const HSLAPixel& leftPixel = traversalPNG->getPixel(currentPointX - 1, currentPointY);
      if (calculateDelta(leftPixel, startPixel) < (this->imageTraversal)->baseTolerance) {
        Point lPoint(currentPointX - 1, currentPointY);
        imageTraversal->add(lPoint);
        //currentPoint.x = lPoint.x;
        //currentPoint.y = lPoint.y;
      }
    }
  }

  if (currentPointY - 1 >= 0 && currentPointY != 0) {
    if (((this->imageTraversal)->hasPointBeenVisited[currentPointX][currentPointY-1]) == 0) {
      const HSLAPixel& abovePixel = traversalPNG->getPixel(currentPointX, currentPointY - 1);
      if (calculateDelta(abovePixel, startPixel) < (this->imageTraversal)->baseTolerance) {
        Point aPoint(currentPointX, currentPointY - 1);
        imageTraversal->add(aPoint);
        //currentPoint.x = aPoint.x;
        //currentPoint.y = aPoint.y;
      }
    }
  }
  currentPoint = (this->imageTraversal)->peek();
  while (!(this->imageTraversal)->empty()) {
    if ((this->imageTraversal)->hasPointBeenVisited[currentPoint.x][currentPoint.y] == 1) {
    (this->imageTraversal)->pop();
      if (!(this->imageTraversal)->empty()) {
      currentPoint = (this->imageTraversal)->peek();
      }
    } else { break; }
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return currentPoint;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  // CHECK WHETHER TO COMPARE CURRENT POINT!!
  bool thisEmpty = false;
  bool otherEmpty = false;

  if (imageTraversal == NULL) { thisEmpty = true; }
  if (other.imageTraversal == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = imageTraversal->empty(); }
  if (!otherEmpty) { otherEmpty = other.imageTraversal->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (imageTraversal != other.imageTraversal); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true

}
