#ifndef ZAMARA_ZAMARA_H_
#define ZAMARA_ZAMARA_H_

#include <string>

#include "sc2/replay.h"

class Zamara
{
public:
	// Version Info
	static int versionMajor();
	static int versionMinor();
	static int versionRevision();
	static std::string version();

	// Loading a Replay
	static Replay* loadReplay(std::string file);

private:
};

#endif // ZAMARA_ZAMARA_H_
