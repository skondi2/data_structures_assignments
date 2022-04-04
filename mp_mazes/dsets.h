#pragma once
#include <vector>

class DisjointSets {

  public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
    std::vector<int> union1;
};
