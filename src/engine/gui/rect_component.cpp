#include "engine/gui/rect_component.hpp"
#include "ceuvars.h"

namespace GUI {

void RectComponent::update_layout() {
  RectComponent* self = this;
  ceu_out_go(&CEUapp, CEU_IN_RECT_COMPONENT_UPDATE_LAYOUT, &self);
}

}