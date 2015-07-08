#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <algorithm>
#include <vector>

struct ContainedPair {
  bool removed;
  void* ptr;
  int z;

  ContainedPair(void* p, int s): removed(false), ptr(p), z(s) {}

  bool operator<(const ContainedPair& other) const { return z < other.z; }
};

class Container {
private:
  std::vector<ContainedPair> container;

public:
  Container() {};

  void add(void* ptr, int z);
  void remove(void* ptr);
  void sort();
  void cleanup();
  void iterate(int event);

  size_t size();
  void* get(size_t);
};

#endif
