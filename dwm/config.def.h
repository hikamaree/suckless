/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char col_bornorm[]     = "#16161e";
static const char col_borsel[]      = "#61afef";
static const char col_black[]       = "#1a1b26";
static const char col_white[]       = "#c0caf5";
static const char col_gray[]        = "#414868";
static const char *fonts[]          = { "SourceCodePro:style=Semibold:size=12" };

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_bornorm },
	[SchemeSel]  = { col_borsel, col_bornorm, col_borsel },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = { NULL };

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "><",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY  Mod4Mask

#define PrtSc   0x0000ff61
#define Mute    XF86XK_AudioMute
#define VolDown XF86XK_AudioLowerVolume
#define VolUp   XF86XK_AudioRaiseVolume
#define BrtDown XF86XK_MonBrightnessDown
#define BrtUp   XF86XK_MonBrightnessUp

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *termcmd[]    = { "st", NULL };
static const char *dmenucmd[]   = { "dmenu_run", NULL };
static const char *volup[]      = { "vol", "-i", NULL };
static const char *voldown[]    = { "vol", "-d", NULL };
static const char *mute[]       = { "vol", "-m", NULL };
static const char *brtup[]      = { "brt", "-i", NULL };
static const char *brtdown[]    = { "brt", "-d", NULL };
static const char *browser[]    = { "org.mozilla.firefox", NULL };
static const char *discord[]    = { "dev.vencord.Vesktop", NULL };
static const char *mpd_prev[]   = { "mpc", "prev", NULL };
static const char *mpd_next[]   = { "mpc", "next", NULL };
static const char *mpd_toggle[] = { "mpc", "toggle", NULL };

static const char scratchpadname[]      = "sp";
static const char *sp[]         = { "st", "-t", scratchpadname, "-g", "160x40", "ncmpcpp", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Alt_R,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browser } },
	{ MODKEY,                       XK_d,      spawn,          {.v = discord } },
	{ 0,                            XK_Alt_R,  spawn,          {.v = dmenucmd } },
	{ 0,                            Mute,      spawn,          {.v = mute} },
	{ 0,                            VolDown,   spawn,          {.v = voldown } },
	{ 0,                            VolUp,     spawn,          {.v = volup} },
	{ 0,                            BrtDown,   spawn,          {.v = brtdown } },
	{ 0,                            BrtUp,     spawn,          {.v = brtup} },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = sp } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  spawn,          {.v = mpd_prev } },
	{ MODKEY,                       XK_period, spawn,          {.v = mpd_next } },
	{ MODKEY,                       XK_slash,  spawn,          {.v = mpd_toggle } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = gappx  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,                            PrtSc,     spawn,          SHCMD("/usr/bin/maim -su | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/pictures/screenshots/$(date '+%b%d_%H%M%S').png") },
	{ ShiftMask,                    PrtSc,     spawn,          SHCMD("/usr/bin/maim -u | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/pictures/screenshots/$(date '+%b%d_%H%M%S').png") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

