/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
  std::map<Point<3>, unsigned> map;
  std::vector<Point<3>> points;
  for (unsigned i = 0; i < theTiles.size(); i++) {
    Point<3> insertPoint = convertToXYZ(theTiles[i].getAverageColor());
    points.push_back(insertPoint);
    map.insert(pair<Point<3>, unsigned>(insertPoint, i));
  }
     MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
     KDTree<3>* tilesTree = new KDTree<3>(points);

     for (int i = 0; i < theSource.getRows(); i++) {
       for (int j = 0; j < theSource.getColumns(); j++) {
         LUVAPixel avgColor = theSource.getRegionColor(i, j);
         Point<3> targetPoint(avgColor.l, avgColor.u, avgColor.v);
         Point<3> nearestPoint = tilesTree->findNearestNeighbor(targetPoint);
         unsigned index = map[nearestPoint];
         canvas->setTile(i, j, &theTiles.at(index));
       }
     }
     delete tilesTree;
    return canvas;
}
