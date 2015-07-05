#include "util/container.h"
#include "ceuvars.h"

void Container::add(void* ptr, int z) { container.push_back(ContainedPair(ptr, z)); }

void Container::sort() { std::sort(container.begin(), container.end()); }

void Container::iterate(int event) {
  for(auto i: container) {
    ceu_out_go(&CEUapp, event, &i.ptr);
  }
}
