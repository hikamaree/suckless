#include <string.h>
//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/						/*Update Interval*/	/*Update Signal*/
	{"    ",  "network",			2,	4 },
	{"",      "volume ",			0,	10},
	{"盛 ",   "B=$(brillo);echo ${B%.*}",	0,	6 },
	{"",      "battery",			10,	0 },
	{" ",    "date '+%I:%M '",		10,	0 },
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = "  ";
static unsigned int delimLen = 5;
