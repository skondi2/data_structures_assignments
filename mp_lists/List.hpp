/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
 #include <iostream>

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  List<T>::ListIterator front(head_);
  return front;
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return NULL;
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* temp;
  ListNode* curr;

  temp = head_;
  while (temp != NULL) {
    curr = temp;
    temp = temp->next;
    delete curr;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T> // no changes here
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = NULL;

  if (head_ == NULL) {
    tail_ = newNode;
  } else {
    head_->prev = newNode;
  }

  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->prev = tail_;
  newNode->next = NULL;

  if (tail_ == NULL) {
    head_ = newNode;
  } else {
    tail_->next = newNode;
  }

  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;
  if (start == NULL) {
    return NULL;
  }

  if (splitPoint >= length_ || splitPoint == 0) {
    return start;
  }

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    curr->prev->next = NULL;
    curr->prev = NULL;
    return curr;
  }

  return NULL;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1

  if (head_ == NULL) {
    return;
  }
  // there are elements in the list and changes need to be made
  ListNode* temp = head_;
  ListNode* tempToMove = head_->next;

  while (temp != NULL) {

    if (temp->next != NULL && temp->next != tail_ && temp->next->next != NULL) {
      ListNode* tempToMove = temp->next;
      ListNode* nextNext = temp->next->next;

      // skip over tempToMove
      temp->next = nextNext;
      (nextNext)->prev = temp;

      // place tempToMove to the end
      tempToMove->next = NULL;
      tempToMove->prev = tail_;
      tail_->next = tempToMove;
      tail_ = tempToMove;

      temp = nextNext;

    } else {
      break;
    }
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_->next, tail_->prev);
}
-=
/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode* temps = head_;
  // while (temps != NULL) {
  //   std::cout << "reverse: list element start: " << temps->data << std::endl;
  //   temps = temps->next;
  // }

  ListNode* startTmp = startPoint;
  ListNode* endTmp = endPoint;
  ListNode* beforeStart = startPoint->prev;
  ListNode* afterEnd = endPoint->next;
  ListNode* startNext = startPoint->next;
  ListNode* endPrev = endPoint->prev;

  if (head_ == startTmp && endTmp != tail_) {
    head_ = endPoint;
    //tail_ = startTmp;
  }

  if (tail_ == endPoint && startTmp != head_) {
    tail_ = startPoint;
    //head_ = endPoint;
  }

  if (beforeStart != NULL) {
    beforeStart->next = endTmp;
  }

  if (afterEnd != NULL) {
    afterEnd->prev = startTmp;
  }

  ListNode* current = startNext;
  while ( current != endTmp) {
    // do reversal
    ListNode* next = current->next;
    current->next = current->prev;
    current->prev = next;
    current = current->prev;
  }
  /*
  if (beforeStart != NULL && afterEnd != NULL) {
    startTmp->next = beforeStart;
    startTmp->prev = startNext;
    endTmp->next = endPrev;
    afterEnd->next = endTmp;
    endTmp->prev = afterEnd;
    beforeStart->prev = startTmp;
  }
  */
  startTmp->next = endTmp->next;
  endTmp->prev = beforeStart;
  startTmp->prev = startTmp;
  endTmp->next = endPrev;

  if (head_ == startTmp && tail_ == endTmp) {
    // swap start and end
    swap(startPoint, endPoint);
  } else {
    // swap start and end pointers
    std::swap(startTmp, endTmp);
  }
/*
// Do reversal
  ListNode* current = startTmp;
  while (current != afterEnd) {
    ListNode* next = current->next;
    current->next = current->prev;
    current->prev = next;
    current = current->prev;
  }


  // need to reverse the start point and end point nodes
  ListNode* temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;

  if (beforeStart != NULL && afterEnd != NULL) {
    beforeStart->prev = endTmp;
    endTmp->next = beforeStart;

    afterEnd->next = startTmp;
    startTmp->prev = afterEnd;
  }

  if (beforeStart == NULL && afterEnd != NULL) {
    afterEnd->next = startTmp;
    startTmp->prev = afterEnd;
  }

  if (beforeStart != NULL && afterEnd == NULL) {
    beforeStart->prev = endTmp;
    endTmp->next = beforeStart;
  }
  ListNode* tempa = head_;
  // while (tempa != NULL) {
  //   // std::cout << "reverse: list element: " << tempa->data << std::endl;
  //   tempa = tempa->next;
  // }
*/
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3

  if (size() <= 1 || n == 1) {
    return;
  }

  if (n >= size()) {
    reverse(head_, tail_);
    return;
  }
  ListNode* temp = head_;
  while (temp != NULL) {
    // std::cout << "list element start: " << temp->data << std::endl;
    temp = temp->next;
  }

  ListNode* current = head_;
  ListNode* end = head_;
  while (end != NULL) {
    for (int i = 0; i < n - 1; i++) {
      // std::cout << "a" << std::endl;
      // if reached the end of list, end needs to prematurely end
      if (end->next == NULL) {
        // std::cout << "b" << std::endl;
        break;
      }
      // otherwise, continue incrementing end until correct position
      // std::cout << "c" << std::endl;
      end = end->next;
    }
    // std::cout << "end before re: " << end->data << std::endl;
    // std::cout << "current before re: " << current->data << std::endl;
    std::cout << "d" << std::endl;
    //if (current != NULL && end != NULL) {
      reverse(current, end);
    //}
    std::cout << "e" << std::endl;
    ListNode* temp = head_;
    while (temp != NULL) {
      // std::cout << "list element : " << temp->data << std::endl;
      temp = temp->next;
    }
    // std::cout << "e" << std::endl;

    // std::cout << "end be: " << end->data << std::endl;
    // std::cout << "current be: " << current->data << std::endl;

    current = end->prev;
    end = end->next;
    // std::cout << "end af: " << end->data << std::endl;
    // std::cout << "current :af " << current->data << std::endl;
  }
  // std::cout << "end : " << end->data << std::endl;
  // std::cout << "current : " << current->data << std::endl;

/*
  ListNode* current = head_;
  int position = 0;
  while (current != NULL) {
    std::cout << "start 1: " << current->data << std::endl;
    if (position % n == 0) {
      // do reversal
      ListNode* start = current;
      ListNode* end = current;
      std::cout << "start : " << start->data << std::endl;

      if (size() - position < n) {
        // shortened reversal
        while (end->next != NULL) {
          std::cout << "end inside loop a: " << end->data << std::endl;
          end = end->next;
        }
        std::cout << "end b: " << end->data << std::endl;
      } else {
        // move end to correct position:
        int nPosition = 0;
        while (nPosition < n-1) {
          end = end->next;
          std::cout << "end inside b: " << end->data << std::endl;
          nPosition++;
        }
        std::cout << "end a: " << end->data << std::endl;
      }
      std::cout << start->data << ", " << end->data << std::endl;
      reverse(start, end);
    }
    std::cout << "reaching here " << std::endl;
    std::cout << "current : " << current->data << std::endl;
    current = current->next;
    std::cout << "current->next : " << current->next->data << std::endl;
    position++;
  }
}
*/
}







/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
// NO NEED TO CHANGE!!
    // set up the current list

    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;

}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* firstPtr = first;
  ListNode* secondPtr = second;

// edge cases
  if (first == NULL && second == NULL) {
    return NULL;
  }
  if (first == NULL && second != NULL) {
    return second;
  }
  if (first != NULL && second == NULL) {
    return first;
  }

  // initialize current
  ListNode* curr = NULL;
  bool currSec = false;
  bool currFirst = false;
  if (first->data < second->data) {
    curr = first;
    currFirst = true;
  } else {
    curr = second;
    currSec = true;
  }

  head_ = curr;

  if (currSec) {
    secondPtr = secondPtr->next;
  }
  if (currFirst) {
    firstPtr = firstPtr->next;
  }

  while (firstPtr != NULL && secondPtr != NULL) {
    if (firstPtr->data < secondPtr->data) {
      ListNode* firstEl = firstPtr;
      curr->next = firstEl;
      firstEl->prev = curr;
      secondPtr->prev = NULL;
      curr = firstEl;

      firstPtr = firstPtr->next;
    } else {
      ListNode* secondEl = secondPtr;
      curr->next = secondEl;
      secondEl->prev = curr;
      firstPtr->prev = NULL;
      curr = secondEl;

      secondPtr= secondPtr->next;
    }
  }

  while (firstPtr == NULL && secondPtr != NULL) {
    ListNode* secondEl = secondPtr;
    curr->next = secondEl;
    secondEl->prev = curr;
    curr = secondEl;

    secondPtr = secondPtr->next;
  }

  while (secondPtr == NULL && firstPtr != NULL) {
    ListNode* firstEl = firstPtr;
    curr->next = firstEl;
    firstEl->prev = curr;
    curr = firstEl;

    firstPtr = firstPtr->next;
  }

  return head_;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2

  if (chainLength == 1) {
    return start;
  }

  int splittingPoint = chainLength / 2;
  ListNode* a = mergesort(split(start, splittingPoint), chainLength - splittingPoint);
  ListNode* b = mergesort(start, splittingPoint);
  return merge(a, b);
}
