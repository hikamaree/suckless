#include <string.h>
static const Block blocks[] = {
/*   Icon   Command             Update Interval     Update Signal*/
	{"",    "net",              2,                  4 },
	{"",    "vol",              0,                  10},
	{"",    "brt",              0,                  6 },
	{"",    "bat",              10,                 0 },
	{" ",  "date '+%I:%M '",   10,                 0 },
};

static char delim[] = "  ";
static unsigned int delimLen = 5;
