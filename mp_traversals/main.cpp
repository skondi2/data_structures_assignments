
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG lanternPNG;
  lanternPNG.readFromFile("tests/lantern.png");
  FloodFilledImage image(lanternPNG);
  Point start;
  Point end(lanternPNG.width() - 1, lanternPNG.height() - 1);
  MyColorPicker customColor;
  BFS bfsStart(lanternPNG, start , 0.75);
  BFS bfsEnd(lanternPNG, end, 0.75);
  image.addFloodFill(bfsStart, customColor);
  image.addFloodFill(bfsEnd, customColor);

  Animation animation = image.animate(1000);


  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
