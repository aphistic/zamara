#include <stdint.h>

#include "config.h"
#include "zamara/zamara.h"

namespace zamara {

uint16_t Zamara::version_major() {
  return VERSION_MAJOR;
}

uint16_t Zamara::version_minor() {
  return VERSION_MINOR;
}

uint16_t Zamara::version_revision() {
  return VERSION_REV;
}

std::string Zamara::version() {
  return VERSION;
}

}
