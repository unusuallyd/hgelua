#include "lhge.h"

/*-------------------------------------------------------------*/
// Font
/*-------------------------------------------------------------*/

#define HH2FONT(font) (hgeFont*)(*font)

int lhge_newfont(lua_State *L)
{
	hgeFont* font = new hgeFont(
			luaL_checkstring(L, 1),
			lua_toboolean(L, 2)
			);
	HHANDLE * udp = newudp(L, FONT);
	*udp = (HHANDLE)font;
	return 1;
}

static int font_gc(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	delete font;
	return 0;
}

static int font_tostring(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, FONT);
	if (udp == NULL)
		lua_pushliteral(L, "Font (NULL)");
	else
		lua_pushfstring(L, "Font (%p)", udp);
	return 1;
}

static int font_render(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->Render(
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checkinteger(L, 4),
			luaL_checkstring(L, 5)
			);
	return 0;
}

static int font_renderb(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->printfb(
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4),
			luaL_checknumber(L, 5),
			luaL_checkinteger(L, 6),
			luaL_checkstring(L, 7)
			);
	return 0;
}

static int font_setcolor(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->SetColor(luaL_checkinteger(L, 2));
	return 0;
}

static int font_setz(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->SetZ(luaL_checknumber(L, 2));
	return 0;
}

static int font_setblendmode(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->SetBlendMode(luaL_checkinteger(L, 2));
	return 0;
}

static int font_setscale(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->SetScale(luaL_checknumber(L, 2));
	return 0;
}

static int font_setproportion(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->SetProportion(luaL_checknumber(L, 2));
	return 0;
}

static int font_setrotation(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->SetRotation(luaL_checknumber(L, 2));
	return 0;
}

static int font_settracking(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->SetTracking(luaL_checknumber(L, 2));
	return 0;
}

static int font_setspacing(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	font->SetSpacing(luaL_checknumber(L, 2));
	return 0;
}

static int font_getcolor(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushinteger(L, font->GetColor());
	return 1;
}

static int font_getz(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushnumber(L, font->GetZ());
	return 1;
}

static int font_getblendmode(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushinteger(L, font->GetBlendMode());
	return 1;
}

static int font_getscale(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushnumber(L, font->GetScale());
	return 1;
}	

static int font_getproportion(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushnumber(L, font->GetProportion());
	return 1;
}	

static int font_getrotation(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushnumber(L, font->GetRotation());
	return 1;
}

static int font_getspacing(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushnumber(L, font->GetSpacing());
	return 1;
}

static int font_gettracking(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushnumber(L, font->GetTracking());
	return 1;
}

static int font_getsprite(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	char chr = luaL_checkstring(L, 2)[0];
	hgeSprite* spr = font->GetSprite(chr);
	HHANDLE * udp = newudp(L, SPRITE);
	*udp = (HHANDLE)spr;
	return 1;
}

static int font_getprewidth(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	char chr = luaL_checkstring(L, 2)[0];
	lua_pushnumber(L, font->GetPreWidth(chr));
	return 1;
}

static int font_getpostwidth(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	char chr = luaL_checkstring(L, 2)[0];
	lua_pushnumber(L, font->GetPostWidth(chr));
	return 1;
}

static int font_getstringwidth(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	bool hMultiLine = true;
	if (!lua_isnoneornil(L, 3))
		hMultiLine = true;
	lua_pushnumber(L, font->GetStringWidth(
				luaL_checkstring(L, 2),
				hMultiLine)
			);
	return 1;
}

static int font_getheight(lua_State *L)
{
	hgeFont* font = HH2FONT(toudp(L, 1, FONT));
	lua_pushnumber(L, font->GetHeight());
	return 1;
}

static const luaL_Reg fontlib[] = {
	{ "__gc", font_gc},
	{ "__tostring", font_tostring},
	{ "Render", font_render},
	{ "RenderB", font_renderb},

	{ "SetColor", font_setcolor},
	{ "SetZ", font_setz},
	{ "SetBlendMode", font_setblendmode},
	{ "SetScale", font_setscale},
	{ "SetProportion", font_setproportion},
	{ "SetRotation", font_setrotation},
	{ "SetTracking", font_settracking},
	{ "SetSpacing", font_setspacing},

	{ "GetColor", font_getcolor},
	{ "GetZ", font_getz},
	{ "GetBlendMode", font_getblendmode},
	{ "GetScale", font_getscale},
	{ "GetProportion", font_getproportion},
	{ "GetRotation", font_getrotation},
	{ "GetTracking", font_gettracking},
	{ "GetSpacing", font_getspacing},

	{ "GetSprite", font_getsprite},
	{ "GetPreWidth", font_getprewidth},
	{ "GetPostWidth", font_getpostwidth},
	{ "GetStringWidth", font_getstringwidth},
	{ "GetHeight", font_getheight},
	{ NULL, NULL}
};

static const ConstValue fontalign [] = {
	{ HGETEXT_RIGHT, "HGETEXT_RIGHT"},
	{ HGETEXT_CENTER, "HGETEXT_CENTER"},
	{ HGETEXT_HORZMASK, "HGETEXT_HORZMASK"},

	{ HGETEXT_BOTTOM, "HGETEXT_BOTTOM"},
	{ HGETEXT_MIDDLE, "HGETEXT_MIDDLE"},
	{ HGETEXT_VERTMASK, "HGETEXT_VERTMASK"},
	{ NULL, "NULL"}
};

void luaopen_font(lua_State *L)
{
	lhge_register_const(L, fontalign);
	create_meta(L, FONT, fontlib);
}
