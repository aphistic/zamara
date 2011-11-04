#ifndef ZAMARA_ZAMARA_H_
#define ZAMARA_ZAMARA_H_

#include <string>

#include "sc2/replay.h"

namespace zamara {

class Zamara {
 public:
	// Version Info
	static int version_major();
	static int version_minor();
	static int version_revision();
	static std::string version();

	// Loading a Replay
	static Replay* LoadReplay(std::string file);
};

}

#endif // ZAMARA_ZAMARA_H_
