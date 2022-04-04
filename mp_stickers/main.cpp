#include "Image.h"
#include "StickerSheet.h"
#include "PNG.h"
#include "Sticker.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  PNG png;
  StickerSheet* sticker  = new StickerSheet("/home/skondi2/cs225git/mp_stickers/pnggrad16rgb.png", 3);
  sticker.addSticker("/home/skondi2/cs225git/mp_stickers/22-223085_rose-bouquet-cli-part-transparent-transparent-background-flowers.png", 0, 0);
  sticker.addSticker("/home/skondi2/cs225git/mp_stickers/png-1342113__340.png", 60, 60 );
  sticker.addSticker("/home/skondi2/cs225git/mp_stickers/ec7ea48bbed08df173696fe167374849.png", 180, 180);
  sticker.render();
  png.writeToFile("myImage.png");
  return 0;
}
