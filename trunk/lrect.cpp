#include "lhge.h"

/*-------------------------------------------------------------*/
// Rect
/*-------------------------------------------------------------*/
int lhge_newrect(lua_State *L)
{
	hgeRect * rect = new hgeRect(
			luaL_checknumber(L, 1),
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4)
		);
	HHANDLE * udp = newudp(L, RECT);
	*udp = (HHANDLE)rect;
	return 1;
}

static int rect_clear(lua_State *L)
{
	hgeRect * rect = (hgeRect *)(*toudp(L, 1, RECT));
	rect->Clear();
	return 0;
}

static int rect_isclean(lua_State *L)
{

	hgeRect * rect = (hgeRect *)(*toudp(L, 1, RECT));
	lua_pushboolean(L, rect->IsClean() ? 1 : 0);
	return 1;
}	

static int rect_set(lua_State *L)
{
	hgeRect * rect = (hgeRect *)(*toudp(L, 1, RECT));
	rect->Set( luaL_checknumber(L, 1),
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4)
		);
	return 0;
}

static int rect_set_radius(lua_State *L)
{
	hgeRect * rect = (hgeRect *)(*toudp(L, 1, RECT));
	rect->SetRadius( luaL_checknumber(L, 1),
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3)
		);
	return 0;
}

static int rect_encapsulate(lua_State *L)
{
	hgeRect * rect = (hgeRect *)(*toudp(L, 1, RECT));
	rect->Encapsulate( luaL_checknumber(L, 1),
			luaL_checknumber(L, 2)
		);
	return 0;
}

static int rect_testpoint(lua_State *L)
{
	hgeRect * rect = (hgeRect *)(*toudp(L, 1, RECT));
	bool val = rect->TestPoint( luaL_checknumber(L, 1),
				luaL_checknumber(L, 2)
		);
	lua_pushboolean(L, val ? 1: 0);
	return 1;
}

static int rect_intersect(lua_State *L)
{
	hgeRect * rect = (hgeRect *)(*toudp(L, 1, RECT));
	hgeRect * rectb = (hgeRect *)(*toudp(L, 2, RECT));
	bool val = rect->Intersect(rectb);
	lua_pushboolean(L, val ? 1: 0);
	return 1;
}	

static const luaL_Reg rectlib[] = {
	{"Clear", rect_clear}, // 	Clears bounding box.
	{"IsClean", rect_isclean}, // 	Tests if bounding box is clean.
	{"Set", rect_set}, // 	Sets bounding box to the specified screen coordinates.
	{"SetRadius", rect_set_radius}, // 	Sets up bounding box, based on it's center coordinates and radius.
	{"Encapsulate", rect_encapsulate}, // 	Encapsulates a point into bounding box.
	{"TestPoint", rect_testpoint}, // 	Tests if a point lies within bounding box.
	{"Intersect", rect_intersect}, // 	Tests two bounding boxes for an intersection.
	{NULL, NULL}
};

void luaopen_rect(lua_State *L)
{
	create_meta(L, RECT, rectlib);
}
