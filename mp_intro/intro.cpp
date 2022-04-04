#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  cs225::PNG png = cs225::PNG();

  bool imageLoaded = png.readFromFile(inputFile);

  cs225::PNG newPng = cs225::PNG(png.width(), png.height());

  if (imageLoaded) {

    for (unsigned int j = 0; j < png.height(); j++) {
      for (unsigned int i = 0; i < png.width(); i++) {
        cs225::HSLAPixel & pixel = png.getPixel(i, j);
        cs225::HSLAPixel & newPixel = newPng.getPixel(png.width() - i - 1, png.height() - j - 1);
        newPixel = pixel;
      }
    }
    
    newPng.writeToFile(outputFile);
  }
}

cs225::PNG myArt(unsigned int width, unsigned int height) {

  cs225::PNG pngImage = cs225::PNG(width, height);

  for (unsigned int i = 0; i < pngImage.width(); i++) {
    for (unsigned int j = 0; j < pngImage.height(); j++) {
      cs225::HSLAPixel & pixel = pngImage.getPixel(i, j);
      cs225::HSLAPixel artPixel = cs225::HSLAPixel(i * j, 1.0, 0.5);
      pixel = artPixel;
    }
  }


  for (unsigned int i = 0; i < pngImage.width(); i++) {
    for (unsigned int j = 0; j < pngImage.height(); j+= 5) {
      // dark pink horizontal
      cs225::HSLAPixel & pixel = pngImage.getPixel(i, j);
      cs225::HSLAPixel artPixel = cs225::HSLAPixel(337.0, 0.5, 0.5);
      pixel = artPixel;
    }
  }

  for (unsigned int i = 0; i < pngImage.height(); i++) {
    for (unsigned int j = 0; j < pngImage.width(); j+= 5) {
      // orange vertical
      cs225::HSLAPixel & pixel = pngImage.getPixel(i, j);
      cs225::HSLAPixel artPixel = cs225::HSLAPixel(29.0, 1.0, 0.5);
      pixel = artPixel;
    }
  }

  return pngImage;
}
