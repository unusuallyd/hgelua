#include "lhge.h"

/*-------------------------------------------------------------*/
// Gui
/*-------------------------------------------------------------*/

#define HH2GUI(udp) (hgeGUI*)(*udp)
#define HH2GUIOBJECT(udp) (hgeGUIObject*)(*udp)
#define HH2GUITEXT(udp) (hgeGUIText*)(*udp)


hgeGUIObject* togui(lua_State *L, int index)
{
	lua_pushvalue(L, index);	
	lua_pushstring(L, "__name");
	lua_gettable(L, -2);
	const char* metaname = luaL_checkstring(L, -1);
	lua_pop(L, 2);
	if (strcmp(metaname, GUITEXT) == 0 )
	{
		return (hgeGUIObject*)*toudp(L, index, GUITEXT);
	}
	else
	{
		luaL_error(L, "Get GUIObject Error");
		return NULL;
	}
}

// GUI Control Manager

int lhge_newgui(lua_State *L)
{
	hgeGUI* gui = new hgeGUI();
	HHANDLE * udp = newudp(L, GUI);
	*udp = (HHANDLE)gui;
	return 1;
}

static int gui_gc(lua_State *L)
{
	hgeGUI* gui = (hgeGUI*)(*toudp(L, 1, GUI));
	delete gui;
	return 0;
}

static int gui_tostring(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, GUI);
	if (udp == NULL)
		lua_pushliteral(L, "Gui (NULL)");
	else
		lua_pushfstring(L, "Gui (%p)", udp);
	return 1;
}

static int gui_addctrl(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	hgeGUIObject* obj = togui(L, 2);
	gui->AddCtrl(obj);
	return 0;
}

static int gui_delctrl(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->DelCtrl(luaL_checkinteger(L, 2));
	return 0;
}

static int gui_getctrl(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	hgeGUIObject* obj = gui->GetCtrl(luaL_checkinteger(L, 2));
	
	// dynamic_cast
	HHANDLE * udp = NULL;

	obj = dynamic_cast<hgeGUIText* >(obj);

	if (obj == 0)
	{
		printf("dynamic_cast guitext failed\n");
		udp = newudp(L, GUIOBJECT);
	}
	else
	{
		udp = newudp(L, GUITEXT);
	}

	*udp = (HHANDLE)obj;
	return 1;
}

static int gui_movectrl(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->MoveCtrl(
			luaL_checkinteger(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4)
			);
	return 0;
}

static int gui_showctrl(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->ShowCtrl(
			luaL_checkinteger(L, 2),
			lua_toboolean(L, 3)
			);
	return 0;
}

static int gui_enablectrl(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->EnableCtrl(
			luaL_checkinteger(L, 2),
			lua_toboolean(L, 3)
			);
	return 0;
}

static int gui_setnavmode(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->SetNavMode(luaL_checkinteger(L, 2));
	return 0;
}

static int gui_setcursor(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	hgeSprite* spr = (hgeSprite*)(*toudp(L, 2, SPRITE));
	gui->SetCursor(spr);
	return 0;
}

static int gui_setcolor(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->SetColor(luaL_checkinteger(L, 2));
	return 0;
}

static int gui_setfocus(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->SetFocus(luaL_checkinteger(L, 2));
	return 0;
}

static int gui_getfocus(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	lua_pushinteger(L, gui->GetFocus());
	return 1;
}

static int gui_enter(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->Enter();
	return 0;
}

static int gui_leave(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->Leave();
	return 0;
}

static int gui_reset(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->Reset();
	return 0;
}

static int gui_move(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->Move(
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3)
			);
	return 0;
}

static int gui_update(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	lua_pushnumber(L, gui->Update(luaL_checknumber(L, 2)));
	return 1;
}

static int gui_render(lua_State *L)
{
	hgeGUI* gui = HH2GUI(toudp(L, 1, GUI));
	gui->Render();
	return 0;
}

// GUIObject

static int guiobject_gc(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	delete obj;
	return 0;
}

static int guiobject_render(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	obj->Render();
	return 0;
}

static int guiobject_update(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	obj->Update(luaL_checknumber(L, 2));
	return 0;
}

static int guiobject_enter(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	obj->Enter();
	return 0;
}

static int guiobject_leave(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	obj->Leave();
	return 0;
}

static int guiobject_reset(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	obj->Reset();
	return 0;
}

static int guiobject_isdone(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	lua_pushboolean(L, obj->IsDone());
	return 1;
}

static int guiobject_focus(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	obj->Focus(lua_toboolean(L, 2));	
	return 0;
}

static int guiobject_mouseover(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	obj->MouseOver(lua_toboolean(L, 2));
	return 0;
}

static int guiojbect_mousemove(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	lua_pushboolean(L, obj->MouseMove(
				luaL_checknumber(L, 2),
				luaL_checknumber(L, 3)
				));
	return 1;
}

static int guiobject_mouselbutton(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	lua_pushboolean(L, obj->MouseLButton(lua_toboolean(L, 2)));
	return 1;
}

static int guiobject_mouserbutton(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	lua_pushboolean(L, obj->MouseRButton(lua_toboolean(L, 2)));
	return 1;
}

static int guiobject_mousewheel(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	lua_pushboolean(L, obj->MouseWheel(luaL_checkinteger(L, 2)));
	return 1;
}

static int guiobject_keyclick(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	lua_pushboolean(L, obj->KeyClick(
				luaL_checkinteger(L, 2),
				luaL_checkstring(L, 3)[0])
			);
	return 1;
}

static int guiobject_setcolor(lua_State *L)
{
	hgeGUIObject* obj = togui(L, 1);
	obj->SetColor(luaL_checkinteger(L, 2));
	return 0;
}

// GUIObject Text

int lhge_newguitext(lua_State *L)
{
	hgeFont* fnt = (hgeFont*)(*toudp(L, 6, FONT));
	hgeGUIText* guitext = new hgeGUIText(
			luaL_checkinteger(L, 1),
			luaL_checknumber(L, 2),
			luaL_checknumber(L, 3),
			luaL_checknumber(L, 4),
			luaL_checknumber(L, 5),
			fnt);

	HHANDLE* udp = newudp(L, GUITEXT);
	*udp = (HHANDLE)guitext;
	return 1;
}

static int guitext_tostring(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, GUITEXT);
	if (udp == NULL)
		lua_pushliteral(L, "GuiText (NULL)");
	else
		lua_pushfstring(L, "GuiText (%p)", udp);
	return 1;
}

static int guitext_setmode(lua_State *L)
{
	hgeGUIText* guitext = HH2GUITEXT(toudp(L, 1, GUITEXT));
	guitext->SetMode(luaL_checkinteger(L, 2));
	return 0;
}

static int guitext_settext(lua_State *L)
{
	hgeGUIText* guitext = HH2GUITEXT(toudp(L, 1, GUITEXT));
	guitext->SetText(luaL_checkstring(L, 2));
	return 0;
}

static const luaL_Reg guitextlib[] = {
	{ "SetMode", guitext_setmode},
	{ "SetText", guitext_settext},
	{ NULL, NULL}
};

// GUIObject Button

// GUI Control Mananger Metatable
static const luaL_Reg guilib[] = {
	{ "__gc", gui_gc},
	{ "__tostring", gui_tostring},
	{ "AddCtrl", gui_addctrl},
	{ "DelCtrl", gui_delctrl},
	{ "GetCtrl", gui_getctrl},
	{ "MoveCtrl", gui_movectrl},
	{ "ShowCtrl", gui_showctrl},
	{ "EnableCtrl", gui_enablectrl},
	{ "SetNavMode", gui_setnavmode},
	{ "SetCursor", gui_setcursor},
	{ "SetColor", gui_setcolor},
	{ "SetFocus", gui_setfocus},
	{ "GetFocus", gui_getfocus},
	{ "Enter", gui_enter},
	{ "Leave", gui_leave},
	{ "Reset", gui_reset},
	{ "Move", gui_move},
	{ "Update", gui_update},
	{ "Render", gui_render},
	{ NULL, NULL}
};

static const ConstValue guinavmode[] = {
	{ HGEGUI_LEFTRIGHT, "HGEGUI_LEFTRIGHT"}, // - left and right arrow keys navigate through controls
	{ HGEGUI_UPDOWN, "HGEGUI_UPDOWN"}, // - up and down arrow keys navigate through controls
	{ HGEGUI_CYCLED, "HGEGUI_CYCLED"}, // - the navigation is wrapped around
	{ NULL, "NULL"}
};

// GUIObject Metatable
static const luaL_Reg guiobjectlib[] = {
	{ "__gc", guiobject_gc},
	{ "Render", guiobject_render},
	{ "Update", guiobject_update},
	{ "Enter", guiobject_enter},
	{ "Leave", guiobject_leave},
	{ "Reset", guiobject_reset},
	{ "IsDone", guiobject_isdone},
	{ "Focus", guiobject_focus},
	{ "MouseOver", guiobject_mouseover},
	{ "MouseLButton", guiobject_mouselbutton},
	{ "MouseRButton", guiobject_mouserbutton},
	{ "MouseWheel", guiobject_mousewheel},
	{ "KeyClick", guiobject_keyclick},
	{ "SetColor", guiobject_setcolor},
	{ NULL, NULL}
};

void luaopen_gui(lua_State *L)
{
	lhge_register_const(L, guinavmode);
	create_meta(L, GUI, guilib);
	create_meta(L, GUIOBJECT, guiobjectlib);
	create_meta(L, GUITEXT, guitextlib);	
	//registy gui control
	luaL_getmetatable(L, GUIOBJECT);
	lua_setmetatable(L, -2);
}
