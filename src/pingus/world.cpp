#include "pingus/world.hpp"
#include "pingus/pingus_level.hpp"
#include "pingus/worldobj_factory.hpp"
#include "ceuvars.h"

void init_WORLD(const PingusLevel& plf) {  
  printf("creating objects...\n");
  return;
  const std::vector<FileReader>& o = plf.get_objects();
  for(auto i: o) WorldObjFactory::instance()->create(i);
  printf("sending STARTUP_WORLD\n");
  ceu_out_go(&CEUapp, CEU_IN_STARTUP_WORLD, 0);  
}
