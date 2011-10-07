#ifndef __ZAMARA_H
#define __ZAMARA_H

#include <string>

#include "sc2/replay.h"

class Zamara
{
public:
	// Version Info
	static int VersionMajor();
	static int VersionMinor();
	static int VersionRevision();
	static std::string Version();

	// Loading a Replay
	static Replay LoadReplay(std::string file);

private:
};

#endif
