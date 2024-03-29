#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx      = 2;
static const unsigned int gappx         = 10;
static const unsigned int snap          = 32;
static const int showbar                = 1;
static const int topbar                 = 1;
static const unsigned int baralpha      = OPAQUE;
static const unsigned int borderalpha   = OPAQUE;
static const char col_bornorm[]         = "#16161e";
static const char col_borsel[]          = "#61afef";
static const char col_black[]           = "#1a1b26";
static const char col_white[]           = "#c0caf5";
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

static const Rule rules[] = { NULL };

/* layout(s) */
static const float mfact = 0.50;
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

/* commands */
static const char *termcmd[]    = { "st", NULL };
static const char *dmenucmd[]   = { "dmenu_run", NULL };
static const char *volup[]      = { "vol", "up", NULL };
static const char *voldown[]    = { "vol", "down", NULL };
static const char *mute[]       = { "vol", "mute", NULL };
static const char *brtup[]      = { "brt", "up", NULL };
static const char *brtdown[]    = { "brt", "down", NULL };
static const char *browser[]    = { "org.mozilla.firefox", NULL };
static const char *discord[]    = { "io.github.spacingbat3.webcord", NULL };

static const char spname[]      = "sp";
static const char *sp[]         = { "st", "-t", spname, "-g", "110x30", NULL };

/* shortcuts */
static const Key keys[] = {
	/* modifier         key             function        argument */
	{ MODKEY,           XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY,           XK_b,           spawn,          {.v = browser } },
	{ MODKEY,           XK_n,           spawn,          {.v = discord } },
	{ 0,                XK_Alt_R,       spawn,          {.v = dmenucmd } },
	{ 0,                Mute,           spawn,          {.v = mute} },
	{ 0,                VolDown,        spawn,          {.v = voldown} },
	{ 0,                VolUp,          spawn,          {.v = volup} },
	{ 0,                BrtDown,        spawn,          {.v = brtdown} },
	{ 0,                BrtUp,          spawn,          {.v = brtup} },
	{ MODKEY,           XK_grave,       togglescratch,  {.v = sp } },
	{ MODKEY,           XK_z,           zoom,           {0} },
	{ MODKEY,           XK_Tab,         view,           {0} },
	{ MODKEY,           XK_c,           killclient,     {0} },
	{ MODKEY,           XK_space,       setlayout,      {0} },
	{ MODKEY,           XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,           XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY,           XK_i,           incnmaster,     {.i = +1 } },
	{ MODKEY,           XK_d,           incnmaster,     {.i = -1 } },
	{ MODKEY,           XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_t,           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_f,           setlayout,      {.v = &layouts[1]} },
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
	{ MODKEY,           XK_q,           quit,           {0} },
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
	{ ClkStatusText,    0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,     MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,     MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,     MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,        0,              Button1,        view,           {0} },
	{ ClkTagBar,        0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,        MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,        MODKEY,         Button3,        toggletag,      {0} },
};
