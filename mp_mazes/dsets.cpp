/* Your code here! */
#include "dsets.h"
#include <vector>

void DisjointSets::addelements(int num)	{
  for (int i = 0; i < num; i++) {
    union1.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (union1[elem] < 0) {
    return elem;
  }
  int root = find(union1[elem]);
  union1[elem] = root;
  return root;
}

void DisjointSets::setunion(int a, int b) {
  int aRoot = find(a);
  int bRoot = find(b);

  int newSize = union1[aRoot] + union1[bRoot];

  if (union1[aRoot] <= union1[bRoot]) {
    union1[bRoot] = aRoot;
    union1[aRoot] = newSize;
  }

  if (union1[aRoot] > union1[bRoot]) {
    union1[aRoot] = bRoot;
    union1[bRoot] = newSize;
  }
}

int DisjointSets::size(int elem)	{
  int root = find(elem);
  return union1[root] * -1;
}
