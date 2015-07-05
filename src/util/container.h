#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <algorithm>
#include <vector>

struct ContainedPair {
  void* ptr;
  int z;

  ContainedPair(void* p, int s): ptr(p), z(s) {}

  bool operator<(const ContainedPair& other) const { return z < other.z; }
};

class Container {
private:
  std::vector<ContainedPair> container;

public:
  Container() {};

  void add(void* ptr, int z);
  void sort();
  void iterate(int event);
};

#endif
