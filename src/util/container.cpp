#include "util/container.h"
#include "ceuvars.h"

void Container::add(void* ptr, int z) { container.push_back(ContainedPair(ptr, z)); }

void Container::remove(void* ptr) {
	for(auto i = container.begin(); i != container.end(); ++i)
		if(i->ptr == ptr) {
			i->removed = true;
			i->ptr = 0;
		}
}

void Container::sort() { std::sort(container.begin(), container.end()); }

void Container::cleanup() {
	for(auto i = container.begin(); i != container.end(); ) {
		if(i->removed)
			i = container.erase(i);
		else
			++i;
	}
}

void Container::iterate(int event) {	
	cleanup();

	for(auto i: container) {
		ceu_out_go(&CEUapp, event, &i.ptr);
	}
}

size_t Container::size() { return container.size(); }

void* Container::get(size_t index) {
	if(container[index].removed) return 0;
	return container[index].ptr;
}
