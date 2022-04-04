/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {

  HSLAPixel::HSLAPixel() {
    /* A default pixel is completely opaque (non-transparent) and white.
    Opaque implies that the alpha component of the pixel is 1.0.
    Lower alpha values are (semi-)transparent. */
    a = 1.0;
    l = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double lumination) {
    l = lumination;
    h = hue;
    s = saturation;
    a = 1.0;
  }

  HSLAPixel::HSLAPixel(double hue, double saturation, double lumination,
    double alpha) {
      a = alpha;
      l = lumination;
      h = hue;
      s = saturation;
  }

}
