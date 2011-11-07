#ifndef ZAMARA_ZAMARA_H_
#define ZAMARA_ZAMARA_H_

#include <stdint.h>
#include <string>

#include "sc2/replay.h"

namespace zamara {

class Zamara {
 public:
	// Version Info
	static uint16_t version_major();
	static uint16_t version_minor();
	static uint16_t version_revision();
	static std::string version();

	// Loading a Replay
	//static Replay* LoadReplay(std::string file);
};

}

#endif // ZAMARA_ZAMARA_H_
