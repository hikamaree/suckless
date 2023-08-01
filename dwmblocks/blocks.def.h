#include <string.h>
static const Block blocks[] = {
/*   Icon   Command             Update Interval     Update Signal*/
	{"",    "network",          2,                  4 },
	{"",    "volume ",          0,                  10},
	{"",    "brightness",       0,                  6 },
	{"",    "battery",          10,                 0 },
	{" ",  "date '+%I:%M '",   10,                 0 },
};

static char delim[] = "  ";
static unsigned int delimLen = 5;
