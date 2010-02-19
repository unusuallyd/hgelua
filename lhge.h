#ifndef __LHGE_H__
#define __LHGE_H__

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <hge.h>
#include <hgesprite.h>
#include <hgerect.h>
#include <hgeanim.h>
#include <hgefont.h>
#include <lua.hpp>
#include <windows.h>

typedef unsigned int HHANDLE;

extern HGE * hge;
extern lua_State * global_L;

#undef NULL
#define NULL 0

#define SYSTEM "hge"
#define TEXTURE "Texture"
#define TARGET "Target"
#define EFFECT "Effect"
#define CHANNEL "Channel"
#define STREAM "Stream"
#define RESOURCE "Resource"
#define SPRITE "Sprite"
#define RECT "Rect"
#define ANIMATION "Animation"
#define FONT "Font"


void luaopen_hge(lua_State *L); 
void luaopen_sprite(lua_State *L);
void luaopen_rect(lua_State *L);
void luaopen_animation(lua_State *L);
void luaopen_font(lua_State *L);


int empty_func(lua_State *L);
void stackDump (lua_State *L);
HHANDLE* newudp(lua_State *L, const char* metatable);
HHANDLE* toudp(lua_State *L, int index, const char* metatable);
int lhge_newsprite(lua_State *L);
int lhge_newrect(lua_State *L);
int lhge_newanimation(lua_State *L);
int lhge_newfont(lua_State *L);
void create_meta(lua_State *L, const char* metatable, const luaL_Reg lib[]);

struct ConstValue
{
	int value;
	const char* name;
};

void lhge_register_const(lua_State *L, const ConstValue* values);


/* -------------------------------------------------------*/
static const ConstValue system_state[] =
{
	// bool state
	{	HGE_WINDOWED,		"HGE_WINDOWED"	},	
	{	HGE_ZBUFFER,		"HGE_ZBUFFER"		},	
	{	HGE_TEXTUREFILTER,	"HGE_TEXTUREFILTER"},	
	{	HGE_USESOUND,		"HGE_USESOUND"	},	
	{	HGE_DONTSUSPEND,	"HGE_DONTSUSPEND"	},	
	{	HGE_HIDEMOUSE,		"HGE_HIDEMOUSE"	},	
	{	HGE_SHOWSPLASH,		"HGE_SHOWSPLASH"	},
	// func state
	{	HGE_FRAMEFUNC,		"HGE_FRAMEFUNC"	},	
	{	HGE_RENDERFUNC,		"HGE_RENDERFUNC"	},	
	{	HGE_FOCUSLOSTFUNC,	"HGE_FOCUSLOSTFUNC"},	
	{	HGE_FOCUSGAINFUNC,	"HGE_FOCUSGAINFUNC"},	
	{	HGE_GFXRESTOREFUNC,	"HGE_GFXRESTOREFUNC"},	
	{	HGE_EXITFUNC,		"HGE_EXITFUNC"	},
	// HWND state
	{	HGE_HWND,			"HGE_HWND"		},	
	{	HGE_HWNDPARENT,		"HGE_HWNDPARENT"	},	
	// int state
	{	HGE_SCREENWIDTH,	"HGE_SCREENWIDTH"	},	
	{	HGE_SCREENHEIGHT,	"HGE_SCREENHEIGHT"},	
	{	HGE_SCREENBPP,		"HGE_SCREENBPP"	},	
	{	HGE_SAMPLERATE,		"HGE_SAMPLERATE"	},	
	{	HGE_FXVOLUME,		"HGE_FXVOLUME"	},	
	{	HGE_MUSVOLUME,		"HGE_MUSVOLUME"	},	
	{	HGE_STREAMVOLUME,	"HGE_STREAMVOLUME"},	
	{	HGE_FPS,			"HGE_FPS"			},	
	{	HGE_POWERSTATUS,	"HGE_POWERSTATUS"	},	
	// string state
	{	HGE_ICON,			"HGE_ICON"		},	
	{	HGE_TITLE,			"HGE_TITLE"		},	
	{	HGE_INIFILE,		"HGE_INIFILE"		},	
	{	HGE_LOGFILE,		"HGE_LOGFILE"		},
	// state end
	{	NULL, "NULL"}
};
const int HGE_STATE_BOOL_START = HGE_WINDOWED;
const int HGE_STATE_BOOL_END = HGE_SHOWSPLASH;

const int HGE_STATE_FUNC_START = HGE_FRAMEFUNC;
const int HGE_STATE_FUNC_END = HGE_EXITFUNC;

const int HGE_STATE_HWND_START = HGE_HWND;
const int HGE_STATE_HWND_END = HGE_HWNDPARENT;

const int HGE_STATE_INT_START = HGE_SCREENWIDTH;
const int HGE_STATE_INT_END = HGE_POWERSTATUS;

const int HGE_STATE_STRING_START = HGE_ICON;
const int HGE_STATE_STRING_END = HGE_LOGFILE;


/* -------------------------------------------------------*/
static const ConstValue keycode[] =
{
	{	HGEK_LBUTTON, "HGEK_LBUTTON"},//		Left mouse button
	{	HGEK_RBUTTON, "HGEK_RBUTTON"},//		Right mouse button
	{	HGEK_MBUTTON, "HGEK_MBUTTON"},//		Middle mouse button (wheel button)
		 
	{	HGEK_ESCAPE, "HGEK_ESCAPE"},//		ESCAPE key
	{	HGEK_BACKSPACE, "HGEK_BACKSPACE"},//		BACKSPACE key
	{	HGEK_TAB,	"TAB"},// key HGEK_ENTER	
	{	HGEK_ENTER,	"Any"},// of HGEK_SPACE	 the two ENTER keys
	{	HGEK_SPACE, "HGEK_SPACE"},//		SPACE key
		 
	{	HGEK_SHIFT, "HGEK_SHIFT"},//		Any of the two SHIFT keys
	{	HGEK_CTRL,	"Any"},// of the HGEK_ALT	 two CTRL keys
	{	HGEK_ALT, "HGEK_ALT"},//		Any of the two ALT keys
		 
	{	HGEK_LWIN, "HGEK_LWIN"},//		Left WINDOWS key
	{	HGEK_RWIN, "HGEK_RWIN"},//		Right WINDOWS key
	{	HGEK_APPS, "HGEK_APPS"},//		APPLICATIONS key
		 
	{	HGEK_PAUSE, "HGEK_PAUSE"},//		PAUSE key
	{	HGEK_CAPSLOCK, "HGEK_CAPSLOCK"},//		CAPS LOCK key
	{	HGEK_NUMLOCK, "HGEK_NUMLOCK"},//		NUM LOCK key
	{	HGEK_SCROLLLOCK, "HGEK_SCROLLLOCK"},//		SCROLL LOCK key
		 
	{	HGEK_PGUP, "HGEK_PGUP"},//		PAGE UP key
	{	HGEK_PGDN, "HGEK_PGDN"},//		PAGE DOWN key
	{	HGEK_HOME, "HGEK_HOME"},//		HOME key
	{	HGEK_END, "HGEK_END"},//		END key
	{	HGEK_INSERT, "HGEK_INSERT"},//		INSERT key
	{	HGEK_DELETE, "HGEK_DELETE"},//		DELETE key
		 
	{	HGEK_LEFT, "HGEK_LEFT"},//		LEFT ARROW key
	{	HGEK_UP, "HGEK_UP"},//		UP ARROW key
	{	HGEK_RIGHT, "HGEK_RIGHT"},//		RIGHT ARROW key
	{	HGEK_DOWN, "HGEK_DOWN"},//		DOWN ARROW key
		 
	{	HGEK_0, "HGEK_0"},//		Main keyboard '0' key
	{	HGEK_1, "HGEK_1"},//		Main keyboard '1' key
	{	HGEK_2, "HGEK_2"},//		Main keyboard '2' key
	{	HGEK_3, "HGEK_3"},//		Main keyboard '3' key
	{	HGEK_4, "HGEK_4"},//		Main keyboard '4' key
	{	HGEK_5, "HGEK_5"},//		Main keyboard '5' key
	{	HGEK_6, "HGEK_6"},//		Main keyboard '6' key
	{	HGEK_7, "HGEK_7"},//		Main keyboard '7' key
	{	HGEK_8, "HGEK_8"},//		Main keyboard '8' key
	{	HGEK_9, "HGEK_9"},//		Main keyboard '9' key
		 
	{	HGEK_A, "HGEK_A"},//		'A' key
	{	HGEK_B, "HGEK_B"},//		'B' key
	{	HGEK_C, "HGEK_C"},//		'C' key
	{	HGEK_D, "HGEK_D"},//		'D' key
	{	HGEK_E, "HGEK_E"},//		'E' key
	{	HGEK_F, "HGEK_F"},//		'F' key
	{	HGEK_G, "HGEK_G"},//		'G' key
	{	HGEK_H, "HGEK_H"},//		'H' key
	{	HGEK_I, "HGEK_I"},//		'I' key
	{	HGEK_J, "HGEK_J"},//		'J' key
	{	HGEK_K, "HGEK_K"},//		'K' key
	{	HGEK_L, "HGEK_L"},//		'L' key
	{	HGEK_M, "HGEK_M"},//		'M' key
	{	HGEK_N, "HGEK_N"},//		'N' key
	{	HGEK_O, "HGEK_O"},//		'O' key
	{	HGEK_P, "HGEK_P"},//		'P' key
	{	HGEK_Q, "HGEK_Q"},//		'Q' key
	{	HGEK_R, "HGEK_R"},//		'R' key
	{	HGEK_S, "HGEK_S"},//		'S' key
	{	HGEK_T, "HGEK_T"},//		'T' key
	{	HGEK_U, "HGEK_U"},//		'U' key
	{	HGEK_V, "HGEK_V"},//		'V' key
	{	HGEK_W, "HGEK_W"},//		'W' key
	{	HGEK_X, "HGEK_X"},//		'X' key
	{	HGEK_Y, "HGEK_Y"},//		'Y' key
	{	HGEK_Z, "HGEK_Z"},//		'Z' key
		 
	{	HGEK_GRAVE, "HGEK_GRAVE"},//		Grave accent (`)
	{	HGEK_MINUS, "HGEK_MINUS"},//		Main keyboard MINUS key (-)
	{	HGEK_EQUALS, "HGEK_EQUALS"},//		Main keyboard EQUALS key (=)
	{	HGEK_BACKSLASH, "HGEK_BACKSLASH"},//		BACK SLASH key (\)
	{	HGEK_LBRACKET, "HGEK_LBRACKET"},//		Left square bracket ([)
	{	HGEK_RBRACKET, "HGEK_RBRACKET"},//		Right square bracket (])
	{	HGEK_SEMICOLON, "HGEK_SEMICOLON"},//		Semicolon (;)
	{	HGEK_APOSTROPHE, "HGEK_APOSTROPHE"},//		Apostrophe (')
	{	HGEK_COMMA, "HGEK_COMMA"},//		Comma (,)
	{	HGEK_PERIOD, "HGEK_PERIOD"},//		Main keyboard PERIOD key (.)
	{	HGEK_SLASH, "HGEK_SLASH"},//		Main keyboard SLASH key (/)
		 
	{	HGEK_NUMPAD0, "HGEK_NUMPAD0"},//		Numeric keyboard '0' key
	{	HGEK_NUMPAD1, "HGEK_NUMPAD1"},//		Numeric keyboard '1' key
	{	HGEK_NUMPAD2, "HGEK_NUMPAD2"},//		Numeric keyboard '2' key
	{	HGEK_NUMPAD3, "HGEK_NUMPAD3"},//		Numeric keyboard '3' key
	{	HGEK_NUMPAD4, "HGEK_NUMPAD4"},//		Numeric keyboard '4' key
	{	HGEK_NUMPAD5, "HGEK_NUMPAD5"},//		Numeric keyboard '5' key
	{	HGEK_NUMPAD6, "HGEK_NUMPAD6"},//		Numeric keyboard '6' key
	{	HGEK_NUMPAD7, "HGEK_NUMPAD7"},//		Numeric keyboard '7' key
	{	HGEK_NUMPAD8, "HGEK_NUMPAD8"},//		Numeric keyboard '8' key
	{	HGEK_NUMPAD9, "HGEK_NUMPAD9"},//		Numeric keyboard '9' key
		 
	{	HGEK_MULTIPLY, "HGEK_MULTIPLY"},//		Numeric keyboard MULTIPLY key (*)
	{	HGEK_DIVIDE, "HGEK_DIVIDE"},//		Numeric keyboard DIVIDE key (/)
	{	HGEK_ADD, "HGEK_ADD"},//		Numeric keyboard ADD key (+)
	{	HGEK_SUBTRACT, "HGEK_SUBTRACT"},//		Numeric keyboard SUBTRACT key (-)
	{	HGEK_DECIMAL, "HGEK_DECIMAL"},//		Numeric keyboard DECIMAL key (.)
		 
	{	HGEK_F1, "HGEK_F1"},//		F1 key
	{	HGEK_F2, "HGEK_F2"},//		F2 key
	{	HGEK_F3, "HGEK_F3"},//		F3 key
	{	HGEK_F4, "HGEK_F4"},//		F4 key
	{	HGEK_F5, "HGEK_F5"},//		F5 key
	{	HGEK_F6, "HGEK_F6"},//		F6 key
	{	HGEK_F7, "HGEK_F7"},//		F7 key
	{	HGEK_F8, "HGEK_F8"},//		F8 key
	{	HGEK_F9, "HGEK_F9"},//		F9 key
	{	HGEK_F10, "HGEK_F10"},//		F10 key
	{	HGEK_F11, "HGEK_F11"},//		F11 key
	{	HGEK_F12, "HGEK_F12"},//		F12 key
	{	NULL,	"NULL"}
};
/* -------------------------------------------------------*/
static ConstValue coloropt [] = {
	{	BLEND_COLORADD,	"BLEND_COLORADD"},
	{	BLEND_ALPHABLEND, "BLEND_ALPHABLEND"},
	{	BLEND_ZWRITE, "BLEND_ZWRITE"},
	{	BLEND_DEFAULT_Z, "BLEND_DEFAULT_Z"},
	{	BLEND_DEFAULT, "BLEND_DEFAULT"},
	{	NULL,	"NULL"}	
};


#endif // __LHGE_H__
