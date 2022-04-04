
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        position_ = position_->next;
        return *this;
    }

    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP3.1
        ListNode* temp = position_;
        position_ = position_->next;
        return temp;
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
        ListNode* temp = position_;
        position_ = position_ ->prev;
        return temp;
    }

    // is it okay to use != in the function itself?
    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP3.1
        if (this->position_ != rhs.position_) {
          return true;
        }
        return false;
    }

    // no changes
    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    // no changes
    const T& operator*() {
        return position_->data;
    }

    // no changes.. is this correct?
    const T* operator->() {
      // return a reference to the node
        return &(position_->data);
    }
};
