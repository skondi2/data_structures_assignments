#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <algorithm>
#include <cmath>
using namespace cs225;

/**
  Lighten an Image by increasing the luminance of every pixel by 0.1
*/
void Image::lighten() {
  lighten(0.1);
}

void Image::lighten(double amount) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.l + amount > 1.0) {
        pixel.l = 1.0;
      } else {
      pixel.l += amount;
    }
    }
  }
}

/**
  Darken an Image by decreasing the luminance of every pixel by 0.1
*/
void Image::darken() {
  darken(0.1);
}

void Image::darken(double amount) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.l - amount < 0.0) {
        pixel.l = 0.0;
      } else {
      pixel.l -= amount;
    }
    }
  }
}

/**
  Saturates an Image by increasing the saturation of every pixel by 0.1
*/
void Image::saturate() {
  saturate(0.1);
}

void Image::saturate(double amount) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.s + amount > 1.0) {
        pixel.s = 1.0;
      } else {
      pixel.s += amount;
    }
    }
  }
}

/**
  Desaturates an Image by decreasing the saturation of every pixel by 0.1
*/
void Image::desaturate() {
  desaturate(0.1);
}

void Image::desaturate(double amount) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i, j);
      if (pixel.s - amount < 0.0) {
        pixel.s = 0.0;
      } else {
      pixel.s -= amount;
    }
    }
  }
}

/**
  Turns the image grayscale
*/
void Image::grayscale() {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i, j);
      pixel.s = 0.0;
    }
  }
}

/**
Rotates the color wheel by degrees.

Rotating in a positive direction increases the degree of the hue. This function
ensures that the hue remains in the range [0, 360]
*/
void Image::rotateColor(double degrees) {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel& pixel = this->getPixel(i, j);

      double hue = pixel.h + degrees;
      int hueI = hue;
      double difference = 0.0;
      double hueInRange = 0.0;

      if (hue != hueI) {
        if (hue > hueI) {
          difference = hue - hueI;
        } else {
          difference = hueI - hue;
        }
      }

      if (hue > 360.0) {
        int shift = hueI % 360;
        hueInRange = ((0 + shift));

      } else if (hue < 0.0) {
        int shift = hueI % 360;
        hueInRange = ((360 +  shift));
      } else {
      hueInRange = hue;
    }
    pixel.h = hueInRange + difference;
    }
  }
}

/**
  Illinify the image
*/
void Image::illinify() {
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {

        HSLAPixel &pixel = this->getPixel(i, j);
        double pixelHue = pixel.h;

        double distance1 = std::abs(pixelHue - 11.0);
        double distance2 = (360.0 - pixelHue) + 11.0;
        double orangePixelDist = std::min(distance1, distance2);

        double bluePixelDist = std::abs(pixelHue - 216.0);

        if (orangePixelDist > bluePixelDist) {
            // closer to blue;
            pixel.h = 216.0;
        } else {
            // closer to orange;
            pixel.h = 11.0;
        }
    }
  }
}

/**
Scale the Image by a given factor.

For example:

  A factor of 1.0 does not change the image.
  A factor of 0.5 results in an image with half the width and half the height.
  A factor of 2 results in an image with twice the width and twice the height.

This function both resizes the Image and scales the contents
*/
void Image::scale(double factor) {

  unsigned newWidth = this->width() * factor;
  unsigned newHeight = this->height() * factor;

  Image* scaledImage = new Image(*this);
  this->resize(newWidth, newHeight);

  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel &pixel = this->getPixel(i, j);
      HSLAPixel &scaledPixel = scaledImage->getPixel(i / factor, j / factor);
      pixel = scaledPixel;
    }
  }
}

/**
Scales the image to fit within the size (w x h).

This function preserves the aspect ratio of the image, so the result will
always be an image of width w or of height h (not necessarily both).

For example, if the Image is currently (10, 20) and we want to scale to
(100, 100), then this should scale the Image to (50, 100). Note that scaling
the image to (100, 200) does not fit within the (100,100) dimensions given and
is therefore incorrect.

This function both resizes the Image and scales the contents
*/
void Image::scale(unsigned w, unsigned h) {
  double widthRatio = w / this->width();
  double heightRatio = h / this->height();

  if (widthRatio < heightRatio) {
    scale(widthRatio);
  } else {
    scale(heightRatio);
  }

}
