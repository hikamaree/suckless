#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx      = 2;
static const unsigned int gappx         = 10;
static const unsigned int snap          = 32;
static const int showbar                = 1;
static const int topbar                 = 1;
static const unsigned int baralpha      = 0x80;
static const unsigned int borderalpha   = OPAQUE;
static const char col_bornorm[]         = "#2d3034";
static const char col_borsel[]          = "#9090a0";
static const char col_black[]           = "#000000";
static const char col_white[]           = "#80c0d0";
static const char *fonts[]              = { "SauceCodePro Nerd Font:style=Regular:size=14" };

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_white, col_black, col_bornorm },
    [SchemeSel]  = { col_white, col_black, col_borsel },
};

static const unsigned int alphas[][3] = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", ""};

static const Rule rules[] = {
    /* class      instance      title       tags mask     isfloating   monitor */
    { NULL,       "spst",       NULL,       SPTAG(0),       1,          -1 },
    { NULL,       "splf",       NULL,       SPTAG(1),       1,          -1 },
    { NULL,       "spmpd",      NULL,       SPTAG(2),       1,          -1 },
};

/* layout(s) */
static const float mfact        = 0.55;
static const int nmaster        = 1;
static const int resizehints    = 0;
static const int lockfullscreen = 1;

static const Layout layouts[] = {
    /* symbol   arrange function */
    { "",      tile },
    { "",      NULL },
};

static char dmenumon[2] = "0";

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* key definitions */
#define MODKEY  Mod1Mask

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

/* scratchpads */
static void *scratchpads[][10] = {
    {"st", "-n", "spst", "-g", "120x30", NULL },
    {"st", "-n", "splf", "-g", "120x30", "-e", "lf", NULL },
    {"st", "-n", "spmpd", "-g", "120x30", "-e", "ncmpcpp", NULL },
};

/* commands */
static const char *termcmd[]        = { "st", NULL };
static const char *dmenucmd[]       = { "dmenu_run", NULL };
static const char *volumeup[]       = { "volume", "up", NULL };
static const char *volumedown[]     = { "volume", "down", NULL };
static const char *mute[]           = { "volume", "mute", NULL };
static const char *brightnessup[]   = { "brightness", "up", NULL };
static const char *brightnessdown[] = { "brightness", "down", NULL };
static const char *browser[]        = { "firefox", NULL };
static const char *discord[]        = { "discord", NULL };

/* shortcuts */
static const Key keys[] = {
	/* modifier         key             function        argument */
	{ MODKEY|ShiftMask, XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,           XK_x,           togglescratch,  {.ui = 0 } },
	{ MODKEY,           XK_c,           togglescratch,  {.ui = 1 } },
	{ MODKEY,           XK_v,	        togglescratch,  {.ui = 2 } },
	{ 0,                XK_Super_L,     spawn,    	    {.v = dmenucmd } },
	{ MODKEY,           XK_b,           spawn,          {.v = browser } },
	{ MODKEY,           XK_n,           spawn,          {.v = discord } },
	{ MODKEY,           XK_q,           togglebar,      {0} },
	{ 0,                Mute,     	    spawn,          {.v = mute} },
	{ 0,                VolDown,        spawn,          {.v = volumedown} },
	{ 0,                VolUp,          spawn,          {.v = volumeup} },
	{ 0,                BrtDown,        spawn,          {.v = brightnessdown} },
	{ 0,                BrtUp,          spawn,          {.v = brightnessup} },
	{ MODKEY,           XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY,           XK_i,           incnmaster,     {.i = +1 } },
	{ MODKEY,           XK_d,           incnmaster,     {.i = -1 } },
	{ MODKEY,           XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_z,           zoom,           {0} },
	{ MODKEY,           XK_Tab,         view,           {0} },
	{ MODKEY|ShiftMask, XK_c,           killclient,     {0} },
	{ MODKEY,           XK_t,           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_f,           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,           XK_space,       setlayout,      {0} },
	{ MODKEY,           XK_0,           view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,           tag,            {.ui = ~0 } },
	{ MODKEY,           XK_comma,       focusmon,       {.i = -1 } },
	{ MODKEY,           XK_period,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period,      tagmon,         {.i = +1 } },
	TAGKEYS(            XK_1,           0)
	TAGKEYS(            XK_2,           1)
	TAGKEYS(            XK_3,           2)
	TAGKEYS(            XK_4,           3)
	TAGKEYS(            XK_5,           4)
	TAGKEYS(            XK_6,           5)
	TAGKEYS(            XK_7,           6)
	TAGKEYS(            XK_8,           7)
	TAGKEYS(            XK_9,           8)
	{ MODKEY|ShiftMask, XK_q,           quit,           {0} },
	{ 0,                PrtSc,          spawn,
        SHCMD("/usr/bin/maim -su | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/Pictures/screenshots/$(date '+%b%d_%H%M%S').png")
    },
	{ ShiftMask,        PrtSc,          spawn,
        SHCMD("/usr/bin/maim -u | xclip -selection clipboard -t image/png; xclip -out -selection clipboard > ~/Pictures/screenshots/$(date '+%b%d_%H%M%S').png")
    },
};

/* buttons */
static const Button buttons[] = {
	/* click            event mask      button          function        argument */
	{ ClkLtSymbol,      0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,      0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,    0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,     MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,     MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,     MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,        0,              Button1,        view,           {0} },
	{ ClkTagBar,        0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,        MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,        MODKEY,         Button3,        toggletag,      {0} },
};
