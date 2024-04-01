/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int user_bh            = 2;        /* 2 is the default spacing around the bar's font */
static const int showbar            = 5;        /* 0 means no bar */
static const int topbar             = 5;        /* 0 means bottom bar */
// DroidSansM Nerd Font Mono:style=Regular
static const char *fonts[]          = { "Ubuntu Mono:style=Bold:size=14", "Font Awesome 6 Brands Regular:style=Regular:size=14" };
static const char dmenufont[]       = "Ubuntu Mono:style=Bold:size=14";
//background color
static const char col_gray1[]       = "#0d1c0e";
//inactive window border color
static const char col_gray2[]       = "#2c2f31";
//font color
static const char col_gray3[]       = "#a8b6b9";  //"#e2ebe3";
//current tag and currnet window font color
static const char col_gray4[]       = "#a8b6b9";
//Top bar second color (blue) and active window border color
static const char col_cyan[]        = "#2c6a63";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "C", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance    title       tags mask     isfloating   monitor */
	{ "Gimp",           NULL,       NULL,       0,            1,           -1 },
	{ "Galculator",     NULL,       NULL,       0,            1,           -1 },
	{ "Pavucontrol",     NULL,       NULL,       0,            1,           -1 },
	{ "Thunderbird",    NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",        NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.85; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0.95; /* 1 will force focus on the fullscreen window */

#include "fibonaci.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = {"rofi", "-show", "drun", "-theme", "android_notification", "-show-icons", NULL};
static const char *voldown[] = {"pulsemixer", "--change-volume",  "-5", NULL};
static const char *volup[] = {"pulsemixer", "--change-volume", "+5", NULL};
static const char *scrsh_d[] = {"scrot", "-d", "1", "/home/tribadelic/Pictures/screenshots/screenshot.png", NULL};
static const char *scrsh_s[] = {"scrot", "-s", "/home/tribadelic/Pictures/screenshots/screenshot.png", NULL};

// Programs
static const char *termcmd[]  = { "st", NULL };
static const char *alacritty[]  = { "alacritty", NULL };
static const char *google[] = {"google-chrome-stable", NULL};
static const char *fox[] = {"firefox", NULL};
static const char *nemo[] = {"nemo", NULL};
static const char *slack[] = {"slack", NULL};
static const char *gimp[] = {"gimp", NULL};
static const char *calc[] = {"galculator", NULL};
static const char *mail[] = {"thunderbird", NULL};
static const char *postman[] = {"postman", NULL};

// Scripts
static const char *wall[] = {"/home/tribadelic/.local/bin/wall.sh", NULL};
static const char *togglemute[] = {"/home/tribadelic/.local/bin/toggle-mute.sh", NULL};
static const char *dmenu_local[] = { "/home/tribadelic/.local/bin/dmenu.sh", NULL};

#include "shiftview.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenu_local } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = alacritty } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = roficmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = nemo } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = google } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = fox } },
	{ MODKEY|ShiftMask,             XK_i,      spawn,          {.v = gimp } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = slack } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = wall } },
	{ 0,                            XK_F12,    spawn,          {.v = volup } },
	{ 0,                            XK_F11,    spawn,          {.v = voldown } },
	{ 0,                            XK_F10,    spawn,          {.v = togglemute } },
	{ 0,                            XK_F4,     spawn,          {.v = calc } },
	{ 0,                            XK_F3,     spawn,          {.v = mail } },
	{ 0,                            XK_Print,  spawn,          {.v = scrsh_d } },
	{ MODKEY,                       XK_Print,  spawn,          {.v = scrsh_s } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = postman } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_n,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_n,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_x,      shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_z,      shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

