#include <string.h>
static const Block blocks[] = {
/*   Icon   Command             Update Interval     Update Signal*/
	{"",         "mpc current",      2,                  0 },
	{"NET: ",    "net",              2,                  4 },
	{"VOL: ",    "vol",              10,                 10},
	{"BRT: ",    "brt",              10,                 6 },
	{"BAT: ",    "btr",              10,                 0 },
	{"",         "date '+%I:%M '",   10,                 0 },
};

static char delim[] = " | ";
static unsigned int delimLen = 5;
