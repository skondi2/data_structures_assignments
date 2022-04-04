/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
  #include <cmath>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* x = t->right;

    t->right = x->left;
    x->left = t;

    t->height = updateHeight(t);
    x->height = updateHeight(x);
    t = x;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* x = t->left;

    t->left = x->right;
    x->right = t;

    t->height = updateHeight(t);
    x->height = updateHeight(x);
    t = x;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
int AVLTree<K, V>::getNodeBalance(Node* subRoot) {
  if (subRoot == NULL) {
    return 0;
  }
  return heightOrNeg1(subRoot->right) - heightOrNeg1(subRoot->left);
}

template <class K, class V>
int AVLTree<K, V>::updateHeight(Node* subRoot) {
  if (subRoot == NULL) {
    return -1;
  }
  return std::max(heightOrNeg1(subRoot->left), heightOrNeg1(subRoot->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  /*
  if (subtree == NULL) {
    return;
  }
  if (getNodeBalance(subtree) == -2 && getNodeBalance(subtree->left) == -1) {
    rotateRight(subtree);
  } else if (getNodeBalance(subtree) == 2 && getNodeBalance(subtree->right) == 1) {
    rotateLeft(subtree);
  } else if (getNodeBalance(subtree) == -2 && getNodeBalance(subtree->right) == 1) {
    rotateLeftRight(subtree);
  } else if (getNodeBalance(subtree) == 2 && getNodeBalance(subtree->left) == -1) {
    rotateRightLeft(subtree);
  }

  subtree->height = updateHeight(subtree);
  */
  // your code here
    if(subtree == NULL){return;}

      if(getNodeBalance(subtree->right) == 1 && getNodeBalance(subtree) == 2){  //stick
        rotateLeft(subtree);
      }
      else if(getNodeBalance(subtree->right) == -1 && getNodeBalance(subtree) == 2){ //elbow
        rotateRightLeft(subtree);
      }

      if(getNodeBalance(subtree->left) == -1 && getNodeBalance(subtree) == -2){  //stick
        rotateRight(subtree);
      }
      else if(getNodeBalance(subtree->left) == 1 && getNodeBalance(subtree) == -2){ //elbow
        rotateLeftRight(subtree);
      }
    subtree->height = updateHeight(subtree);
  /*
    if (subtree == NULL) { return; }
    int leftHeight = heightOrNeg1(subtree->left);
    int rightHeight = heightOrNeg1(subtree->right);
    int balanceFactor = std::abs(leftHeight - rightHeight);
    if (balanceFactor <= 1) { return; } // its already balanced

    int rightChildBalance = 0;
    if (subtree->left == NULL && subtree->right != NULL) {
      // the child below of the root is to the right
      int rightChildLeft = heightOrNeg1(subtree->right->left);
      int rightChildRight = heightOrNeg1(subtree->right->right);
      rightChildBalance = std::abs(rightChildLeft - rightChildRight);
    }

    int leftChildBalance = 0;
    if (subtree->left != NULL && subtree->right == NULL) {
      // the child below the root is to the left
      int leftChildLeft = heightOrNeg1(subtree->left->left);
      int leftChildRight = heightOrNeg1(subtree->left->right);
      leftChildBalance = std::abs(leftChildLeft- leftChildRight);
    }

    if (balanceFactor == -2 && leftChildBalance == -1) {
      // rotate right
      rotateRight(subtree);
    }

    if (balanceFactor == 2 && rightChildBalance == 1) {
      // rotate to the left
      rotateLeft(subtree);
    }

    if (balanceFactor == -2 && leftChildBalance == 1) {
      rotateLeftRight(subtree);
    }

    if (balanceFactor == 2 && rightChildBalance == -1) {
      rotateRightLeft(subtree);
    }

    subtree->height = std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
    */
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{

    if (subtree == NULL) {
      subtree = new Node(key, value);
      return;
    }

    if (subtree->key > key) {
      insert(subtree->left, key, value);

    }

    if (subtree->key <= key) {
      insert(subtree->right, key, value);
    }

    rebalance(subtree);


}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
      remove(subtree->left, key);
    } else if (key > subtree->key) {
      remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node* iop = subtree->left;
            while (iop->right != NULL) {
              iop = iop->right;
            }
            swap(iop, subtree);
            remove(subtree->left, key);
            rebalance(iop);
        } else {
            /* one-child remove */
            Node* child;
            if (subtree->left == NULL && subtree->right != NULL) {
              child = subtree->right;
            }

            if (subtree->left != NULL && subtree->right == NULL) {
              child = subtree->left;
            }
            delete subtree;
            subtree = child;

        }
    }
    rebalance(subtree);
}
