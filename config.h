/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char font[]            = "MesloLGS NF:style=Regular:pixelsize=16:antialias=true:autohint=true";
static const char *fonts[]          = { font,
                                        "monospace:size=16" };
static const char dmenufont[]       = "MesloLGS NF:style=Regular:pixelsize=16:antialias=true:autohint=true";
static char normbgcolor[]           = "#000000";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#cccccc";
static char selfgcolor[]            = "#cccccc";
static char selbordercolor[]        = "#770000";
static char selbgcolor[]            = "#000000";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance        title       tags_mask   isfloating  monitor */
	{ TERMCLASS,        NULL,           NULL,       0,          0,          -1 },
    { "FBReader",       "FBReader",     "FBReader", 1 << 1,     0,          -1 },
    { "Spotify",        "spotify",      "Spotify",  1 << 2,     0,          -1 },
    { "Brave-browser",  "brave-browser","Brave",    1 << 3,     0,          -1 },
    { "Firefox",        "Navigator",    "Firefox",  1 << 3,     0,          -1 },
    { "firefox",        "Navigator",    "Firefox",  1 << 3,     0,          -1 },
    { "discord",        "discord",      "Discord",  1 << 4,     0,          -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

/* Dmemu monitors */
static char dmenumon[2] = "1"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = {
    "dmenu_run",
    "-m", dmenumon,
    "-fn", dmenufont,
    "-nb", normbgcolor,
    "-nf", normfgcolor,
    "-sb", selbordercolor,
    "-sf", selfgcolor,
    NULL
};

static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "shift-tools.c"

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "gappih",		        INTEGER, &gappih },
		{ "gappiv",		        INTEGER, &gappiv },
		{ "gappoh",		        INTEGER, &gappoh },
		{ "gappov",		        INTEGER, &gappov },
		{ "smartgaps",		    INTEGER, &smartgaps },
		{ "mfact",      	 	FLOAT,   &mfact },
};


static const Key keys[] = {
	/* modifier                     key             function        argument */
	{ MODKEY,			            XK_a,           togglegaps,	    {0} },
	{ MODKEY|ShiftMask,		        XK_a,           defaultgaps,	{0} },
	{ MODKEY,                       XK_b,           togglebar,      {0} },
	{ MODKEY,                       XK_d,           spawn,          {.v = dmenucmd } },
	{ MODKEY,			            XK_e,           spawn,		    SHCMD("$EREADER") },
	{ MODKEY,			            XK_r,           spawn,		    SHCMD(TERMINAL " -e htop") },
	{ MODKEY,			            XK_w,           spawn,		    SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,             XK_w,           spawn,          SHCMD("$SECONDARY_BROWSER") },

    /* DWM layouts */
	{ MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} /* tile */ },
	{ MODKEY|ShiftMask,             XK_t,           setlayout,      {.v = &layouts[1]} /* monocle */ },
	{ MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} /* spiral */ },
	{ MODKEY|ShiftMask,             XK_f,           setlayout,      {.v = &layouts[3]} /* dwindle */ },
    { MODKEY,                       XK_i,           setlayout,      {.v = &layouts[4]} /* deck */ },
    { MODKEY|ShiftMask,             XK_i,           setlayout,      {.v = &layouts[5]} /* bstack */ },
    { MODKEY,                       XK_n,           setlayout,      {.v = &layouts[6]} /* bstackhoriz */ },
    { MODKEY|ShiftMask,             XK_n,           setlayout,      {.v = &layouts[7]} /* grid */ },
    { MODKEY|ShiftMask,             XK_m,           setlayout,      {.v = &layouts[8]} /* nrowgrid */ },
    { MODKEY,                       XK_p,           setlayout,      {.v = &layouts[9]} /* horizgrid */ },
    { MODKEY,                       XK_u,           setlayout,      {.v = &layouts[10]} /* gaplessgrid */ },
    { MODKEY|ShiftMask,             XK_u,           setlayout,      {.v = &layouts[11]} /* centeredmaster */ },
    { MODKEY,                       XK_c,           setlayout,      {.v = &layouts[12]} /* centeredfloatingmaster */ },

	{ MODKEY,                       XK_f,           fullscreen,     {0} },
	{ MODKEY,                       XK_space,       setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
	{ MODKEY,                       XK_s,           togglesticky,   {0} },

    /* GUI related keys */
	{ MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_h,           setcfact,       {.f = -0.25} },
	{ MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,           setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_p,           setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_o,           incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,           incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_q,           killclient,     {0} },
	{ MODKEY,                       XK_x,           incrgaps,       {.i = -3 } },
	{ MODKEY,                       XK_z,           incrgaps,       {.i = +3 } },
	{ MODKEY|ShiftMask,             XK_s,           transfer,       {0} },

	{ MODKEY,                       XK_v,       shiftviewclients,   { .i = +1 } },
	{ MODKEY|ShiftMask,	            XK_v,       shiftviewclients,   { .i = -1 } },
	{ MODKEY,                       XK_g,	        shiftview,      { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_g,	        shiftview,      { .i = -1 } },
    { MODKEY,                       XK_k,           focusstack,     {.i = +1 } },
    { MODKEY,                       XK_j,           focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_k,           pushstack,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_j,           pushstack,     {.i = -1 } },
	{ MODKEY,		                XK_semicolon,   shiftboth,      { .i = -1 }	},
	{ MODKEY|ShiftMask,             XK_semicolon,   shiftboth,      { .i = +1 }	},
	{ MODKEY|ShiftMask,		        XK_Page_Up,	    shiftswaptags,	{ .i = -1 } },
	{ MODKEY|ShiftMask,		        XK_Page_Down,	shiftswaptags,	{ .i = +1 } },
	//{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },

    /* Other keys */
	{ 0,	XK_Print,	        spawn,	SHCMD("scrot -s -e 'xclip -selection clipboard  -t image/png -i $f && rm $f' ") },

#ifdef XK_3270
	{ 0,	XK_3270_PrintScreen,spawn,	SHCMD("scrot -s -e 'xclip -selection clipboard  -t image/png -i $f && rm $f' ") },
#endif

	{ MODKEY,                       XK_Tab,         view,           {0} },
	{ MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,      zoom,           {0} },
	{ MODKEY,			            XK_comma,       spawn,          SHCMD("playerctl previous") },
	{ MODKEY,			            XK_period,      spawn,          SHCMD("playerctl next") },
	{ MODKEY,			            XK_slash,       spawn,          SHCMD("playerctl play-pause") },
	{ MODKEY,			            XK_minus,	    spawn,		    SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		        XK_minus,	    spawn,		    SHCMD("xbacklight -dec 5") },
	{ MODKEY,			            XK_equal,	    spawn,		    SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		        XK_equal,	    spawn,		    SHCMD("xbacklight -inc 5") },

    /* Tags and views keys */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_Left,        focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Left,        tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_Right,       focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Right,       tagmon,         {.i = +1 } },

    /* Media keys */
	{ 0, XF86XK_AudioMute,		    spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,          spawn,		SHCMD("playerctl previous") },
	{ 0, XF86XK_AudioNext,          spawn,		SHCMD("playerctl next") },
	{ 0, XF86XK_AudioPause,         spawn,		SHCMD("playerctl pause") },
	{ 0, XF86XK_AudioPlay,          spawn,		SHCMD("playerctl play-pause") },
	{ 0, XF86XK_AudioStop,          spawn,		SHCMD("playerctl stop") },
	{ 0, XF86XK_AudioRewind,        spawn,		SHCMD("mpc seek -10") },
	{ 0, XF86XK_AudioForward,       spawn,		SHCMD("mpc seek +10") },
	{ 0, XF86XK_AudioMedia,         spawn,		SHCMD(TERMINAL " -e ncmpcpp") },
	{ 0, XF86XK_AudioMicMute,       spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,           spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,         spawn,		SHCMD(TERMINAL " -e bc -l") },
	{ 0, XF86XK_Sleep,              spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,                spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,                spawn,		SHCMD(TERMINAL) },
	{ 0, XF86XK_ScreenSaver,        spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ 0, XF86XK_TaskPane,           spawn,		SHCMD(TERMINAL " -e htop") },
	{ 0, XF86XK_Mail,		        spawn,		SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		    spawn,		SHCMD(TERMINAL " -e lf /") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		    spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },

	//{ MODKEY|Mod4Mask,              XK_,       incrigaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_,       incrigaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_,       incrogaps,      {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_,       incrogaps,      {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_6,       incrihgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_6,       incrihgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_7,       incrivgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_7,       incrivgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_8,       incrohgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_8,       incrohgaps,     {.i = -1 } },
	//{ MODKEY|Mod4Mask,              XK_9,       incrovgaps,     {.i = +1 } },
	//{ MODKEY|Mod4Mask|ShiftMask,    XK_9,       incrovgaps,     {.i = -1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click            evmask  button      function        argument */
	{ ClkLtSymbol,      0,      Button1,    setlayout,      {0} },
	{ ClkLtSymbol,      0,      Button3,    setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,      0,      Button2,    zoom,           {0} },
	{ ClkStatusText,    0,      Button2,    spawn,          {.v = termcmd } },
	{ ClkClientWin,     MODKEY, Button1,    movemouse,      {0} },
	{ ClkClientWin,     MODKEY, Button2,    togglefloating, {0} },
	{ ClkClientWin,     MODKEY, Button3,    resizemouse,    {0} },
	{ ClkTagBar,        0,      Button1,    view,           {0} },
	{ ClkTagBar,        0,      Button3,    toggleview,     {0} },
	{ ClkTagBar,        MODKEY, Button1,    tag,            {0} },
	{ ClkTagBar,        MODKEY, Button3,    toggletag,      {0} },
};

