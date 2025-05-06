/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  	  = 1;         /* ширина рамки в пикселях вокруг окон */
static const unsigned int snap      	  = 150;       /* расстояние в пикслях при котором плавающее окно прилипает к краям экрана */
static const unsigned int systraypinning  = 0;         /* 0 - systray будет плавающим: он будет отображаться на том мониторе, где сейчас 
							  выбран рабочий стол (активныймонитор), 
							  > 0 - systray будет всегда отображаться на мониторе с номером systraypinning, 
							  например, если указать 1, то всегда на втором мониторе */
static const unsigned int systrayonleft   = 0;         /* определяет, с какой стороны будет находиться системный трей по отношению к строке статуса, 
							  0 — трей будет в правом углу панели, 
							  > 0 — трей будет слева от строки статуса */
static const unsigned int systrayspacing  = 0;         /* задает расстояние в пикселях между иконками в системном трее */
static const int systraypinningfailfirst  = 1;         /* 1(true) - если не удалось закрепить на выбранном мониторе, то трей покажется на первом мониторе, 
							  0(false) - если не удалось закрепить, то трей окажется на последнем монитор */
static const int showsystray        	  = 1;         /* включает(1) или выключает(0) отображение системного трея */
static const int showbar            	  = 1;         /* включает(1) или выключает(0) панель (bar) наверху или внизу экрана */
static const int topbar             	  = 1;         /* определяет, где будет расположена панель — сверху(1) или снизу(0) экрана */
static const char *fonts[]          	  = { "Jetbrains Mono NerdFont:size=8:style=Bold", "Font Awesome 6 Free Solid:size=12" };
static const char dmenufont[]       	  = { "Jetbrains Mono NerdFont:size=8:style=Bold" };
static char normbgcolor[]           	  = "#23252e"; /* цвет фона не выбранного элемента */
static char normbordercolor[]       	  = "#23252e"; /* цвет рамки не выбранного элемента */
static char normfgcolor[]           	  = "#fafbfc"; /* цвет текста не выбранного элемента */
static char selfgcolor[]            	  = "#80e5ff"; /* цвет текста выбранного элемента */
static char selbordercolor[]        	  = "#80e5ff"; /* цвет рамки выбранного элемента*/
static char selbgcolor[]            	  = "#23252e"; /* цвет фона выбранного элемента*/
static char termcol0[] 			  = "#000000"; /* чёрный */
static char termcol1[] 			  = "#ff0000"; /* красный */
static char termcol2[] 			  = "#33ff00"; /* зелёный */
static char termcol3[] 		          = "#ff0099"; /* жёлтый */
static char termcol4[] 			  = "#0066ff"; /* синий */
static char termcol5[] 			  = "#cc00ff"; /* пурпурный */
static char termcol6[]	 		  = "#00ffff"; /* голубой */
static char termcol7[] 			  = "#d0d0d0"; /* белый */
static char termcol8[]  		  = "#808080"; /* чёрный */
static char termcol9[]  		  = "#ff0000"; /* красный */
static char termcol10[] 		  = "#33ff00"; /* зелёный */
static char termcol11[] 		  = "#ff0099"; /* жёлтый */
static char termcol12[] 		  = "#0066ff"; /* синий */
static char termcol13[] 		  = "#cc00ff"; /* пурпурный */
static char termcol14[] 		  = "#00ffff"; /* голубой */
static char termcol15[] 		  = "#ffffff"; /* белый */
static char *termcolor[] 		  = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};
static char *colors[][3] = {
/*               		                     текст          фон          граница         */
/* обычный, не выбранный элемент */   [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
/* выбранный(активный) элемент   */   [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#include <X11/XF86keysym.h>

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *flameshot[] = { "flameshot", "gui", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	             	XK_c,      killclient,     {0} },
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
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
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
	{ 0,                            XK_Print,                 spawn,          {.v = flameshot } },
    	{ 0,                            XF86XK_AudioMute,         spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
    	{ 0,                            XF86XK_AudioLowerVolume,  spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") },
    	{ 0,                            XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
    	{ 0,                            XF86XK_MonBrightnessUp,   spawn,          SHCMD("brightnessctl set +10%") },
    	{ 0,                            XF86XK_MonBrightnessDown, spawn,          SHCMD("brightnessctl set 10%-") },
    	{ 0,                            XK_ISO_Next_Group,        spawn,          SHCMD("pkill -RTMIN+1 dwmblocks") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

