/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const {
    if (first[curDim] < second[curDim]) {
      return true;
    }

    if (first[curDim] == second[curDim]) {
      return (first < second);
    }

    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const {
    double distTargetPotential = 0.0;
    double distTargetCurrent = 0.0;
    for (int i = 0; i < Dim; i++) {
      distTargetPotential += ( (target[i] - potential[i]) * (target[i] - potential[i]) ); //distanceNotRooted(target, potential, i); //( (target[i] - potential[i]) * (target[i] - potential[i]) );
      distTargetCurrent += ( (target[i] - currentBest[i]) * (target[i] - currentBest[i]) );//distanceNotRooted(target, currentBest, i); //( (target[i] - currentBest[i]) * (target[i] - currentBest[i]) );
    }

    if (distTargetPotential < distTargetCurrent) {
      return true;
    }

    if (distTargetPotential == distTargetCurrent) {
      return potential < currentBest;
    }

    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints) {

  if (!newPoints.empty()) {
    // 1. copy over the const newPoints
    vector<Point<Dim>> newPointsNotConst(newPoints);

    // 2. build the tree
    this->root = nullptr;
    this->root = buildTree(newPointsNotConst, 0, newPointsNotConst.size() - 1, 0);
  } else {
    this->root = NULL;
  }

}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>>& pointsVec, int l, int r, int dimension) {
  // 1. base case to return null
  if (pointsVec.empty()) {
    return NULL;
  }

  if (l <= r) {
    // 2. find mediam to call quick select
    int medianIndex = std::floor( (l + r) / 2 );

    //std::cout << "dimension : " << dimension << std::endl;
    unsigned medianElement = quickSelect(pointsVec, l, r, medianIndex, dimension);
    KDTreeNode* subroot;
    // 3. create new node that contains the median
    if (medianElement <= pointsVec.size() -1 && medianElement >= 0) {
      subroot = new KDTreeNode(pointsVec[medianIndex]);
      subroot->left = buildTree(pointsVec, l, medianIndex-1, (dimension + 1) % Dim);
      subroot->right = buildTree(pointsVec, medianIndex+1, r, (dimension + 1) % Dim);
  } else {
    return NULL;
  }

    // 4. if root == NULL, set that new node to be the root
    if (this->root == NULL) {
      this->root = subroot;
    }
    return subroot;

  }

  // 5. place median location in placeMedianLoc
  //pointsVec[medianIndex] = medianElement;

  // 6. you have to increase the dimension/ modulo
  // 7. initialize the subroot left and right
  return NULL;

}

/**
  Helper function to return the index of the k-th smallest element in the vector
*/
template <int Dim>
int KDTree<Dim>::quickSelect(vector<Point<Dim>>& pointsVec, int l, int r, int k, int dimension) {
  if (l == r) {
    return l;
  }

  int pivotIndex = (l + r) / 2;

  pivotIndex = partition(pointsVec, l, r, pivotIndex, dimension % Dim);

  if (k == pivotIndex) {
    return k;

  } else if (k < pivotIndex) {
    return quickSelect(pointsVec, l, pivotIndex - 1, k, dimension % Dim);
  } else {
    return quickSelect(pointsVec, pivotIndex+1, r, k, dimension % Dim);
  }
}

/**
  Helper function to move elements smaller than the element in vector at the pivotIndex
  to the left of the pointsVec and everything greater than the pivotValue to the right
  of the pointsVec
*/
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& pointsVec, int l, int r, int pivotIndex, int dim) {

  Point<Dim> temp = pointsVec[pivotIndex];
  pointsVec[pivotIndex] = pointsVec[r];
  pointsVec[r] = temp;

  int storeIndex = l;

  for (int i = l; i < r; i++) {
    if (smallerDimVal(pointsVec[i], temp, dim % Dim)) {
      Point<Dim> temp1 = pointsVec[storeIndex];
      pointsVec[storeIndex] = pointsVec[i];
      pointsVec[i] = temp1;

      storeIndex++;
    }

  }
  Point<Dim> temp2 = pointsVec[storeIndex];
  pointsVec[storeIndex] = pointsVec[r];
  pointsVec[r] = temp2;
  return storeIndex;

}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  copyhelper(root, other->root);
}

//copy helper function
template <int Dim>
void KDTree<Dim>::copyhelper(KDTreeNode* root, KDTreeNode* otherRoot){

  if(otherRoot== NULL){
    return;
  }

  KDTreeNode* newNode= new KDTreeNode(otherRoot->point);
  copyhelper(root->left, otherRoot->left);
  copyhelper(root->right, otherRoot->right);

}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {

   deletehelper(root);
   copyhelper(root, rhs->root);
  return *this;

}

template <int Dim>
KDTree<Dim>::~KDTree() {
  KDTreeNode* temp = root;

  //while (temp != NULL) {
   deletehelper(root);


}

//destructor helper
template <int Dim>
void KDTree<Dim>::deletehelper(KDTreeNode* root){

  if(root==NULL){return;}

  deletehelper(root->left);
  deletehelper( root->right);
  delete root;

  //root = NULL;
  //root->left = NULL;
  //root->right = NULL;

}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {

  // 1. recursively step down the tree to get current best point
  Point<Dim> nearestNeighbor = recurseDownTree(root, query, 0);

  return nearestNeighbor;

}

/**
  Helper function to calculate distance between two points
*/
template <int Dim>
double KDTree<Dim>::distanceNotRooted(Point<Dim> p1, Point<Dim> p2) const {
  double a = 0;
  for (int i =0; i < Dim; i++) {
    a += pow((p1[i] - p2[i]), 2);
  }
  return a;
}


/**
  Helper function
*/
template <int Dim>
Point<Dim> KDTree<Dim>::recurseDownTree(KDTreeNode* subroot, Point<Dim> target, int splittingDim) const {

  Point<Dim> bestPoint = subroot->point;
  bool traversingLeft = false;
  bool traversingRight = false;

  // base case: stop if at leaf
  if (subroot->left == NULL && subroot->right == NULL) {
    return subroot->point;
  }

  if (smallerDimVal(subroot->point, target, splittingDim)) {
    if (subroot->right == NULL) {
      // can't go right, traverse left
      bestPoint = recurseDownTree((subroot->left), target, (splittingDim+1) % Dim);
    } else {
      // traverse right
      bestPoint = recurseDownTree((subroot->right), target, (splittingDim+1) % Dim);
    }
    traversingRight = true;
  } else {
    if (subroot->left == NULL) {
      // can't go left, traverse right
      bestPoint = recurseDownTree((subroot->right), target, (splittingDim+1) % Dim);
    } else {
      bestPoint = recurseDownTree((subroot->left), target, (splittingDim+1) % Dim);
    }
    traversingLeft = true;
  }


  // compare subroot and best point
  if (shouldReplace(target, bestPoint, subroot->point)) {
    bestPoint = subroot->point;
  }

    double distance = distanceNotRooted(target, bestPoint);
    double otherDist = pow((subroot->point)[splittingDim] - target[splittingDim], 2);

    if (otherDist <= distance) {
      //typename KDTree<Dim>::KDTreeNode* otherSubroot;

      if (traversingLeft && !traversingRight) {
        //otherSubroot = (subroot->right);
        if (subroot->right != NULL) {
        // find potential best in the other subtree
          Point<Dim> potentialBest = recurseDownTree(subroot->right,
            target, (splittingDim + 1) % Dim);

          if (shouldReplace(target, bestPoint, potentialBest)) {
            // if the potential best is closer than the best point
            bestPoint = potentialBest;
          }
        }
      } else if (traversingRight && !traversingLeft) {
          //otherSubroot = (subroot->left);

          // find potential best in the other subtree
          if (subroot->left != NULL) {
            Point<Dim> potentialBest = recurseDownTree(subroot->left,
              target, (splittingDim + 1) % Dim);

            if (shouldReplace(target, bestPoint, potentialBest)) {
              // if the potential best is closer than the best point
              bestPoint = potentialBest;
            }
          }
      }
    }

  return bestPoint;
}

  /*
  int currDistance = 0;
  typename KDTree<Dim>::KDTreeNode otherResult;
  typename KDTree<Dim>::KDTreeNode childResult;

  // base case:
  if (subroot.left == NULL && subroot.right == NULL) {
    return subroot.point;
  }

  if (target[splittingDim % Dim] < subroot.point[splittingDim % Dim]) {

    if (subroot.right != NULL) {
      otherResult = subroot.right;
    }


    if (subroot.left == NULL) {
      otherResult = otherResult = subroot.right;
      return subroot;
    }
    currDistance = distanceNotRooted(subroot.point, target);
    childResult = recurseDownTree(*(subroot.left), *(subroot), target, (splittingDim + 1) % Dim);

  } else {

    if (subroot.left != NULL) {
      otherResult = subroot.left;
    }

    if (subroot.right == NULL) {
        return subroot;
    }

    currDistance = distanceNotRooted(subroot.point, target);
    childResult = recurseDownTree(*(subroot.right), *(subroot), target, (splittingDim + 1) % Dim);
  }

  int childDistance = distanceNotRooted(childResult.point, target);


  if (currDistance < childDistance) {
    // check for the possible other tree
    if (pow(target[splittingDim % Dim] - subrootParent[(splittingDim + 1) % Dim], 2) < currDistance) {
      otherResult = recurseDownTree(otherResult, subrootParent, target, (splittingDim+2) % Dim);
      int otherDist = distanceNotRooted(target, otherResult);
      if (otherDist)
    }
    return subroot;
  }

  if (currDistance == childDistance) {
    if (subroot.point < childResult.point) {
      return subroot;
    } else {
      return childResult;
    }
  }

  return childResult;
  */
  /*
  if (subroot->left == NULL && subroot->right == NULL) {
    // or return subroot????
    return NULL;
  }

  if (subroot[splittingDim] < target[splittingDim]) {
    // recurse left
    recurseDownTree(subroot->left, target, (splittingDim + 1) % Dim);
  } else if (subroot[splittingDim] == target[splittingDim]) {
    if (subroot < target) {
      // recurse left
      recurseDownTree(subroot->left, target, (splittingDim + 1) % Dim);
    } else {
      // recurse right
      recurseDownTree(subroot->right, target, (splittingDim + 1) % Dim);
    }
  } else {
    // recurse right
    recurseDownTree(subroot->right, target, (splittingDim + 1) % Dim);
  }

  return subroot;
  */
