/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
  mirrorHelper(getRoot());
}

template <typename T>
void BinaryTree<T>::mirrorHelper(Node* subRoot) {
  if (subRoot == NULL) {
    return;
  }
  Node* tmp = subRoot->left;
  subRoot->left = subRoot->right;
  subRoot->right = tmp;

  mirrorHelper(subRoot->left);
  mirrorHelper(subRoot->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    if (getRoot() == NULL) {
      return true;
    }
    return isOrderedIterativeHelper(getRoot());
}

template <typename T>
bool BinaryTree<T>::isOrderedIterativeHelper(Node* root) const {
  InorderTraversal<T> inOrder(getRoot());
  bool a = true;
  T temp;
  int position = 0;

  for (typename TreeTraversal<T>::Iterator it = inOrder.begin(); it != inOrder.end(); ++it) {
    if (position != 0) {
      if ((*it)->elem <= temp) {
        a = false;
      }
    }

    temp = (*it)->elem;
    position++;
  }
  return a;
}


/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
  Node* treeRoot = getRoot();

    return (isOrderedHelper(treeRoot));

}

template <typename T>
bool BinaryTree<T>::isOrderedHelper(Node* subRoot) const {
  if (subRoot == NULL) {
    return true;
  }

  if (subRoot->left == NULL && subRoot->right == NULL) {
    return true;
  }

  if (subRoot->left != NULL && subRoot->right != NULL) {
    // left != null
    bool rightSide = false;
    Node* mostRight = subRoot->left;
    // find rightmost on the left side:
    while (mostRight->right != NULL) {
      mostRight = mostRight->right;
    }

    if (mostRight->elem <= subRoot->elem) {
      rightSide = true;
    }


    // right != null
    bool leftSide = false;
    Node* mostLeft = subRoot->right;
    // find leftmost on the right branch
    while (mostLeft->left != NULL) {
      mostLeft = mostLeft->left;
    }
    if (mostLeft->elem >= subRoot->elem) {
      leftSide = true;
    }


    return isOrderedHelper(subRoot->left) && isOrderedHelper(subRoot->right) && leftSide && rightSide;
  }

  if (subRoot->left != NULL && subRoot->right == NULL) {

    bool rightSide = false;
    Node* mostRight = subRoot->left;
    // find rightmost on the left side:
    while (mostRight->right != NULL) {
      mostRight = mostRight->right;
    }

    if (mostRight->elem <= subRoot->elem) {
      rightSide = true;
    }

    return isOrderedHelper(subRoot->left) && rightSide;
  }

  if (subRoot->left == NULL && subRoot->right != NULL) {

    bool leftSide = false;
    Node* mostLeft = subRoot->right;
    // find leftmost on the right branch
    while (mostLeft->left != NULL) {
      mostLeft = mostLeft->left;
    }
    if (mostLeft->elem >= subRoot->elem) {
      leftSide = true;
    }

    return isOrderedHelper(subRoot->right) && leftSide;
  }
  return false;
}


/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    std::vector<T> pathVec;
    getPaths(paths, getRoot(), pathVec);
}

template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths, Node* subRoot, std::vector<T> pathVec) const {
  if (subRoot == NULL) {
    return;
  }

  pathVec.push_back(subRoot->elem);
  if (subRoot->left == NULL && subRoot->right == NULL) {
    paths.push_back(pathVec);
  }
  getPaths(paths, subRoot->left, pathVec);
  getPaths(paths, subRoot->right, pathVec);

  pathVec.pop_back();
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return sumDistancesHelper(getRoot(), 0);
}

template <typename T>
int BinaryTree<T>::sumDistancesHelper(Node* subRoot, int dist) const
{
    // your code here
    if (subRoot == NULL) { return 0;}
    Node* left = subRoot->left;
    Node* right = subRoot->right;
    return dist + sumDistancesHelper(left, dist + 1) + sumDistancesHelper(right, dist + 1);
}
