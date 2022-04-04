/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

/**
  Implement this
*/
template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value) {
  // have to insert at front
  elems++;
  if (shouldResize()) {
    resizeTable();
  }
  unsigned int n = hashes::hash(key, size);
  table[n].push_front(std::make_pair(key, value));
}

/**
  Implement this
*/
template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    unsigned int n = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[n].begin(); it != table[n].end(); it++) {
      if (it->first == key) {
        // remove
        table[n].erase(it);
        elems--;
        break;
      }
    }
    /*
    if (*(it).first == key) {
      // remove
      table[n].erase(it);
      elems--;
      break;
    } else {
      it++;
    }
    */
}

/**
  Implement this
*/
template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const {

  unsigned int n = hashes::hash(key, size);
  typename std::list<std::pair<K, V>>::iterator it;
  for (it = table[n].begin(); it != table[n].end(); it++) {
    if (it->first == key) {
      // found it
      return it->second;
    }
  }
  /*
  if (*(it).first == key) {
    // found it
    return *(it).second;
  } else {
    it++;
  }
  */

  return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

/**
 * @todo Implement this function.
 *
 * Please read the note in the spec about list iterators!
 * The size of the table should be the closest prime to size * 2.
 *
 * @hint Use findPrime()!
 */
template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{

    size_t prime = findPrime(size * 2);

    std::list<std::pair<K, V>>* newTable = new std::list<std::pair<K, V>>[prime];

    for (size_t i = 0; i < size; i++) {
      if (table[i].size() != 0) {
        for (auto it = table[i].begin(); it != table[i].end(); it++) {
          unsigned n = hashes::hash(it->first, prime);
          std::pair<K, V> pair(it->first, it->second);
          newTable[n].push_front(pair);
        }
      }
    }
    delete[] table;
    size = prime;
    table = newTable;


    // get new prime size with find prime functions
    // create new table with the size prime size
    // for loop through the original table dimensions
    // if that array in the table is not empty, then iterator through it and get the hash between
    // it->first and prime size

}
