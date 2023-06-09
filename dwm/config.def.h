/* See LICENSE file for copyright and license details. */

/* appearance */
#include <X11/XF86keysym.h>

static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 16;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int baralpha = 0x80;
static const unsigned int borderalpha = OPAQUE;
static const char *fonts[]          = { "SauceCodePro Nerd Font:style=Regular:size=14" };
static const char col_bornorm[]     = "#2d3034";
static const char col_borsel[]      = "#9090a0";
static const char col_black[]       = "#000000";
static const char col_white[]       = "#80c0d0";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_bornorm },
	[SchemeSel]  = { col_white, col_black, col_borsel },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border*/
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", ""};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor*/
	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
};

/* layout(s) */
static const float mfact     	= 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     	= 1;    /* number of clients in master area */
static const int resizehints 	= 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; 	/* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
};

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* key definitions */
#define PrtSc 0x0000ff61
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] 		= { "dmenu_run", NULL };
static const char *steam[]    		= { "steam", NULL };
static const char *termcmd[]  		= { "st", NULL };
static const char *browser[]  		= { "firefox", NULL };
/* screenshot */
/* volume */
static const char *volumeup[] 		= { "volume", "up", NULL };
static const char *volumedown[] 	= { "volume", "down", NULL };
static const char *mute[] 			= { "volume", "mute", NULL };
/* brightness */
static const char *brightnessup[] 	= { "brightness", "up", NULL };
static const char *brightnessdown[] = { "brightness", "down", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask, 	        XK_Return, spawn,          {.v = termcmd } },
	{ 0,                			XK_Super_L, spawn,    	   {.v = dmenucmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browser } },
	{ MODKEY,						XK_g,      spawn,	   	   {.v = steam} },
	{ MODKEY,                       XK_q,      togglebar,      {0} },
	{ 0,             XF86XK_AudioMute,     	   spawn,          {.v = mute} },
	{ 0,  	         XF86XK_AudioLowerVolume,  spawn,          {.v = volumedown} },
	{ 0,             XF86XK_AudioRaiseVolume,  spawn,          {.v = volumeup} },
	{ 0,             XF86XK_MonBrightnessDown, spawn,          {.v = brightnessdown} },
	{ 0,             XF86XK_MonBrightnessUp,   spawn,          {.v = brightnessup} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ 0,                       		PrtSc,     spawn,          SHCMD("/usr/bin/maim -su | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/Pictures/screenshots/$(date '+%b%d_%H%M%S').png")},
	{ ShiftMask,                    PrtSc,     spawn,          SHCMD("/usr/bin/maim -u | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/Pictures/screenshots/$(date '+%b%d_%H%M%S').png")},
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
