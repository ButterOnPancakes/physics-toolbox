#include "utils.h"

template <class DstType, class SrcType>
bool is_instance(const SrcType* src) {
  return dynamic_cast<const DstType*>(src) != nullptr;
}