/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int centered = 1;                    /* -c option; centers dmenu on screen */
static int min_width = 500;
static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static const unsigned int alpha = OPAQUE;
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"SauceCodePro Nerd Font:style=Regular:size=15"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#80c0d0", "#1a1b26" },
	[SchemeSel] = { "#61afef", "#292e42" },
	[SchemeOut] = { "#1a1b26", "#1a1b26" },
};

static const unsigned int alphas[SchemeLast][2] = {
	[SchemeNorm] = { OPAQUE, alpha },
	[SchemeSel] = { OPAQUE, alpha },
	[SchemeOut] = { OPAQUE, alpha },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
static unsigned int border_width = 2;
