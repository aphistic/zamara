#include "config.h"

#include "zamara/zamara.h"

int Zamara::VersionMajor() { return VERSION_MAJOR; }
int Zamara::VersionMinor() { return VERSION_MINOR; }
int Zamara::VersionRevision() { return VERSION_REV; }
std::string Zamara::Version() { return VERSION; }


Replay Zamara::LoadReplay(std::string file)
{
}
