#include "util/container.h"
#include "ceuvars.h"

void Container::add(void* ptr, int z) { container.push_back(ContainedPair(ptr, z)); }

void Container::remove(void* ptr) {
	for(auto i: container)
		if(i.ptr == ptr)
			i.removed = true;
}

void Container::sort() { std::sort(container.begin(), container.end()); }

void Container::iterate(int event) {	
	for(auto i = container.begin(); i != container.end(); ) {
		if(i->removed)
			i = container.erase(i);
		else
			++i;
	}

	for(auto i: container) {
		ceu_out_go(&CEUapp, event, &i.ptr);
	}
}
