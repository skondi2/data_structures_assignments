#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...

    return evalHelper(getRoot());
}

double AbstractSyntaxTree::evalHelper(Node* subRoot) const {

  if (subRoot == NULL) {
    return -1.0;
  }
  Node* left = subRoot->left;
  Node* right = subRoot->right;

  if (subRoot->elem == "+") {
    return evalHelper(left) + evalHelper(right);
  } else if (subRoot->elem == "*") {
    return evalHelper(left) * evalHelper(right);
  } else if (subRoot->elem == "/") {
    return evalHelper(left) / evalHelper(right);
  } else if (subRoot->elem == "-") {
    return evalHelper(left) - evalHelper(right);
  }
  // the node contains a number, convert the node string into a double
  return std::stod(subRoot->elem);
}
