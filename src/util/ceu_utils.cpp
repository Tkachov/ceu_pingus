#include "util/ceu_utils.h"
#include "ceuvars.h"

void ceu_utils::async_emit(int event, void* arg) {
  ceu_out_go(&CEUapp, event, arg);
}