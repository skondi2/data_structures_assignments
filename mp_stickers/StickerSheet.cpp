#include "StickerSheet.h"
#include "Sticker.h"
#include <iostream>

/**
  Initializes this StickerSheet with a deep copy of the base picture and the
  ability to hold a max number of stickers (Images) with indices 0 through
  max - 1
*/
StickerSheet::StickerSheet(const Image& picture, unsigned max) {
  this->maxStickers = max;

  this->currentStickers = 0;

  this->basePicture = new Image(picture); // create deep copy of base picture

  this->xCount = new int[maxStickers];
  this->yCount = new int[maxStickers];
  this->images = new Image*[maxStickers];
  this->imageExists = new int[maxStickers];
  for (int i = 0; i < maxStickers; i++) {
    xCount[i] = 0;
    yCount[i] = 0;
    images[i] = NULL;
    imageExists = 0;
  }
}

void StickerSheet::destroy() {
// delete each image in the image array
  for (int i = 0; i < maxStickers; i++) {
    if (imageExists[i]) {
      delete images[i];
      images[i] = NULL;
    }
  }
  // delete all the pointers
  delete basePicture;
  delete[] xCount;
  delete[] yCount;
  delete[] images;
  delete[] imageExists;
  //set all the pointers to NULL
  images = NULL;
  xCount = NULL;
  yCount = NULL;
  basePicture = NULL;
  imageExists = NULL;
}

/**
  Frees all space that was dynamically allocated by this StickerSheet.
*/
StickerSheet::~StickerSheet() {
  destroy();
}

void StickerSheet::copy(StickerSheet const & other) {
  this->basePicture = new Image(*(other.basePicture));
  this->currentStickers = other.currentStickers;
  this->maxStickers = other.maxStickers;
  this->xCount = new int[maxStickers];
  this->yCount = new int[maxStickers];
  this->images = new Image*[maxStickers];
  this->imageExists = new int[maxStickers];

  for (int i = 0; i < maxStickers; i++) {
    if (!(other.imageExists[i])) {
      xCount[i] = 0;
      yCount[i] = 0;
      images[i] = NULL;
      imageExists[i] = 0;
    } else {
      xCount[i] = other.xCount[i];
      yCount[i] = other.yCount[i];
      images[i] = new Image(*(other.images[i]));
      imageExists[i] = other.imageExists[i];
    }
  }
}

/**
The copy constructor makes this StickerSheet an independent copy of the source.

Hint: Code is likely shared between all of the "Rule of Three" functions.
Would a helper function (or two) make your life easier?
*/
StickerSheet::StickerSheet(const StickerSheet & other) {

  copy(other);

}

/**
Adds a sticker to the StickerSheet, so that the top-left of the sticker's
Image is at (x, y) on the StickerSheet.

The sticker must be added to the lowest possible layer available.
*/
int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {

  int layerAddedTo = -1;
  Image* stickerToAdd = new Image(sticker);
  if (stickerToAdd != NULL) {
  if (currentStickers < maxStickers) {
    for (int i = 0; i < maxStickers; i++) {
      if ((imageExists[i]) == 0) {
        images[i] = stickerToAdd;
        xCount[i] = x;
        yCount[i] = y;
        currentStickers++;
        imageExists[i] = 1;
        layerAddedTo = i;
      }
    }
  }
}
  return layerAddedTo;
}

/**
Modifies the maximum number of stickers that can be stored on this StickerSheet
without changing existing stickers' indices.

If the new maximum number of stickers is smaller than the current number number
of stickers, the stickers with indices above max - 1 will be lost.
*/
void StickerSheet::changeMaxStickers(unsigned max) {

  // need to create new copy of everything and destroy all old stuff
  Image** imagesNew = new Image*[max];
  int* xCountNew = new int[max];
  int* yCountNew = new int[max];
  int currentStickersNew = 0;
  Image* basePictureNew = new Image(*(this->basePicture));
  int* imageExistsNew = new int[max];
  int maxS = (int) max;
  // if max is still greater than current sticker amount
  if (currentStickers < maxStickers) {
    for (int i = 0; i < maxS; i++) {
      imagesNew[i] = NULL;
      imageExistsNew[i] = 0;
    }
  }

  // if overflowing with stickers
  if (currentStickers > maxStickers) {
    for (int i = maxS; i < maxStickers ; i++) {
      if (imageExists[i] == 1) {
        currentStickers--;
        imageExists[i] = 0;
        delete images[i];
        images[i] = NULL;
      }
    }
    this->maxStickers = max;
  }
  //unsigned maxSt = (unsigned) maxStickers;
    for (int i = 0; i < maxStickers; i++) {
      if (imageExists[i] == 1) {
        imagesNew[i] = new Image(*(images[i]));
        xCountNew[i] = xCount[i];
        yCountNew[i] = yCount[i];
        imageExistsNew[i] = imageExists[i];
        currentStickersNew++;
      } else {
        imageExistsNew[i] = 0;
      }
    }


  // destroy the old stuff
  destroy();
  // initialize all the new stuff
  this->maxStickers = maxS;
  this->images = imagesNew;
  this->currentStickers = currentStickersNew;
  this->xCount = xCountNew;
  this->yCount = yCountNew;
  this->basePicture = basePictureNew;
  this->imageExists = imageExistsNew;
}


/**
Returns a pointer to the sticker at the specified index, not a copy of it.

That way, the user can modify the Image.

If the index is invalid, return NULL.
*/
Image* StickerSheet::getSticker(unsigned index) {
  for (int i = 0; i < maxStickers ; i++) {
    if ((unsigned)i == index && imageExists[index] == 1) {
      return images[i];
    }
  }
  return NULL;
}

/**
The assignment operator for the StickerSheet class.

Hint: Code is likely shared between all of the "Rule of Three" functions.
Would a helper function (or two) make your life easier?
*/
const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
  if (this != &other) {
    destroy();
    copy(other);
  }
  return *this;
}

/**
Removes the sticker at the given zero-based layer index.

Make sure that the other stickers don't change order.
*/
void StickerSheet::removeSticker(unsigned index) {
  for (int i = 0; i < maxStickers; i++) {
    if ((unsigned)i == index) {
      if (imageExists[i] == 1) {
        delete images[i];
        images[i] = NULL;
        xCount[i] = 0;
        yCount[i] = 0;
        currentStickers--;
        imageExists[i] = 0;
      }
    }
  }
}

/**
Renders the whole StickerSheet on one Image and returns that Image.

The base picture is drawn first and then each sticker is drawn in order starting
with layer zero (0), then layer one (1), and so on.

If a pixel's alpha channel in a sticker is zero (0), no pixel is drawn for that
sticker at that pixel. If the alpha channel is non-zero, a pixel is drawn.
(Alpha blending is awesome, but not required.)

The returned Image always includes the full contents of the picture and all
stickers. This means that the size of the result image may be larger than the
base picture if some stickers go beyond the edge of the picture.
*/
Image StickerSheet::render() const {
  Image* renderedPointer = new Image(*basePicture);
  Image renderedImage = *renderedPointer;

  int resizeX = basePicture->width();
  int resizeY = basePicture->height();
  for (int i = 0; i < maxStickers; i++) {
    if (imageExists[i] == 1) {
      if (xCount[i] + images[i]->width() > resizeX) {
        resizeX = xCount[i] + images[i]->width();
      }

      if (yCount[i] + images[i]->height() > resizeY) {
        resizeY = yCount[i] + images[i]->height();
      }
    }
  }
  renderedImage.resize(resizeX, resizeY);


  for (int i = 0; i < maxStickers; i++) {
    if (imageExists[i] == 1) {
      for (int j = xCount[i]; j < images[i]->width() + xCount[i]; j++) {
        for (int k = yCount[i]; k < images[i]->height() + yCount[i]; k++) {
          cs225::HSLAPixel& pixel = images[i]->getPixel(j + xCount[i], k + yCount[i]);
          cs225::HSLAPixel& renderedPixel = renderedImage.getPixel(j, k);
          if (pixel.a != 0.0) {
            renderedPixel = pixel;
          }
        }
      }
    }
  }
  delete renderedPointer;
  renderedPointer = NULL;
  return renderedImage;
}

/**
Changes the x and y coordinates of the Image in the specified layer.

If the layer is invalid or does not contain a sticker, this function must
return false. Otherwise, this function returns true.
*/
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {

  for (int i = 0; i < maxStickers; i++) {
    if (index == i) {
      if (imageExists[i] == 1) {
        xCount[i] = x;
        yCount[i] = y;
        return true;
      }
    }
  }
  return false;
}
