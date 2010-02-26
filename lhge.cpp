#include "lhge.h"

/*-------------------------------------------------------------*/
// System
/*-------------------------------------------------------------*/

int empty_func(lua_State *L)
{
	return 0;
}

static int lhge_init(lua_State *L)
{
	if ( ! hge->System_Initiate())
		luaL_error(L, "Hge System_Initiate Failed!");
	return 0;
}

static int lhge_mainloop(lua_State *L)
{
	hge->System_Start();
	return 0;
}


static int lhge_snapshot(lua_State *L)
{
	hge->System_Snapshot(luaL_checkstring(L, 1));
	return 0;
}


void lhge_register_const(lua_State *L, const ConstValue* values)
{
	int i = 0;
	while(1)
	{
		if (values[i].value == NULL) break;
		lua_pushinteger(L, values[i].value);
		lua_setglobal(L, values[i].name);
		i ++;
	}
}

static int frame_func_ref;
static int render_func_ref;
static int focus_lost_func_ref;
static int focus_gain_func_ref;
static int gfx_restore_func_ref;
static int exit_func_ref;

bool callfunc(int ref)
{
	lua_getref(global_L, ref);
	if (!lua_isfunction(global_L, -1))
		luaL_error(global_L, "need function to callback"); 
	int result = lua_pcall(global_L, 0, 1, 0); 
	if ( result == LUA_ERRRUN ) {
		printf("callback error: %s\n", lua_tostring(global_L, -1));
		return true;
	}   
	return lua_toboolean(global_L, -1);	
}

bool frame_func() {
	return callfunc(frame_func_ref);
}
bool render_func() {
	hge->Gfx_BeginScene();
	callfunc(render_func_ref);
	hge->Gfx_EndScene();
	return false;
}
bool focus_lost_func() { return callfunc(focus_lost_func_ref); }
bool focus_gain_func() { return callfunc(focus_gain_func_ref); }
bool gfx_restore_func() { return callfunc(gfx_restore_func_ref); }
bool exit_func() { return callfunc(exit_func_ref); }

static void set_funcref(hgeFuncState state, int ref)
{
	switch(state)
	{
		case HGE_FRAMEFUNC:
			frame_func_ref = ref; 
			hge->System_SetState(state, frame_func);
			break;
		case HGE_RENDERFUNC:
			render_func_ref = ref;
			hge->System_SetState(state, render_func);
			break;
		case HGE_FOCUSLOSTFUNC:
			focus_lost_func_ref = ref;
			hge->System_SetState(state, focus_lost_func);
			break;
		case HGE_FOCUSGAINFUNC:
			focus_gain_func_ref = ref;
			hge->System_SetState(state, focus_gain_func);
			break;
		case HGE_GFXRESTOREFUNC:
			gfx_restore_func_ref = ref;
			hge->System_SetState(state, gfx_restore_func);
			break;
		case HGE_EXITFUNC:
			exit_func_ref = ref;
			hge->System_SetState(state, exit_func);
			break;
	}
}

int get_funcref(int state)
{
	switch(state)
	{
		case HGE_FRAMEFUNC:
			return frame_func_ref; 
			break;
		case HGE_RENDERFUNC:
			return render_func_ref;
			break;
		case HGE_FOCUSLOSTFUNC:
			return focus_lost_func_ref;
			break;
		case HGE_FOCUSGAINFUNC:
			return focus_gain_func_ref;
			break;
		case HGE_GFXRESTOREFUNC:
			return gfx_restore_func_ref;
			break;
		case HGE_EXITFUNC:
			return exit_func_ref;
			break;
	}
	return 0;
}

static int lhge_checkstate(lua_State *L, int index)
{
	int state = luaL_checkinteger(L, index);
	if (state > 0 )
	{
		return state;
	}else{
		return luaL_error(L, "state enum value error: state = %d", state);
	}
}

static int lhge_getstate(lua_State *L)
{
	int state = lhge_checkstate(L, 1);
	if ( state >= HGE_STATE_BOOL_START && state <= HGE_STATE_BOOL_END )
	{
		bool result = hge->System_GetState((hgeBoolState)state);
		lua_pushboolean(L, result ? 1 : 0 );
	}
	else if ( state >= HGE_STATE_FUNC_START && state <= HGE_STATE_FUNC_END )
	{
		int ref = get_funcref(state);
		lua_getref(global_L, ref);
	}
	else if ( state >= HGE_STATE_HWND_START && state <= HGE_STATE_HWND_END )
	{
		HWND result = hge->System_GetState((hgeHwndState)state);
		//lua_pushinteger(L, result);
	}
	else if ( state >= HGE_STATE_INT_START && state <= HGE_STATE_INT_END )
	{
		int result = hge->System_GetState((hgeIntState)state);
		lua_pushinteger(L, result);
	}
	else if ( state >= HGE_STATE_STRING_START && state <= HGE_STATE_STRING_END )
	{
		const char* result = hge->System_GetState((hgeStringState)state);
		lua_pushstring(L, result);
	}
	return 1;
}


static int lhge_setstate(lua_State *L)
{
	int state = lhge_checkstate(L, 1);
	if ( state >= HGE_STATE_BOOL_START && state <= HGE_STATE_BOOL_END )
	{
		int val = lua_toboolean(L, 2);	
		hge->System_SetState((hgeBoolState)state, val > 0);
	}
	else if ( state >= HGE_STATE_FUNC_START && state <= HGE_STATE_FUNC_END )
	{
		if (lua_isfunction(L, 2))
		{
			set_funcref((hgeFuncState)state, lua_ref(L, true));
		}else
		{
			luaL_error(L, "except Function for callback");
		}
	}
	else if ( state >= HGE_STATE_HWND_START && state <= HGE_STATE_HWND_END )
	{
		//hge->System_SetState((hgeHwndState)state, luaL_checkinteger(L, 2));
	}
	else if ( state >= HGE_STATE_INT_START && state <= HGE_STATE_INT_END )
	{
		hge->System_SetState((hgeIntState)state, luaL_checkinteger(L, 2));
	}
	else if ( state >= HGE_STATE_STRING_START && state <= HGE_STATE_STRING_END )
	{
		hge->System_SetState((hgeStringState)state, luaL_checkstring(L, 2));
	}
	return 0;
}

static int lhge_log(lua_State *L)
{
	hge->System_Log( luaL_checkstring(L, -1));
	return 0;
}


/*-------------------------------------------------------------*/
// Utility
/*-------------------------------------------------------------*/

void stackDump (lua_State *L) {
	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, i));
			break;
	
		default:  /* other values */
			printf("%s", lua_typename(L, t));
			break;

		}
		printf("  ");	/* put a separator */
	}
	printf("\n");		/* end the listing */
}

HHANDLE* newudp(lua_State *L, const char* metatable)
{
	HHANDLE * udp = (HHANDLE *)lua_newuserdata(L, sizeof(long));
	(*udp) = NULL;
	luaL_getmetatable(L, metatable); 
	lua_setmetatable(L, -2);
	return udp;
}

void create_meta(lua_State *L, const char* metatable, const luaL_Reg lib[])
{
	luaL_newmetatable(L, metatable);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	lua_pushstring(L, metatable);
	lua_setfield(L, -2, "__name");
	luaL_register(L, NULL, lib);
}

HHANDLE* toudp(lua_State *L, int index, const char* metatable)
{
	return (HHANDLE *)luaL_checkudata(L, index, metatable);
}

static HHANDLE tohandle(lua_State *L, int index, const char* metatable)
{
	if(lua_isnil(L, index))
	{
		lua_pop(L, 1);
		lua_pushinteger(L, 0);
	}
	if(lua_isnumber(L, index) && luaL_checkinteger(L, index) == 0) 
		return 0;
	else
		return *toudp(L, index, metatable);
}

static void gettable(lua_State *L, const char* key)
{
	lua_pushstring(L, key);
	lua_gettable(L, -2);
}
static void gettableindex(lua_State *L, int key)
{
	lua_pushinteger(L, key);
	lua_gettable(L, -2);
}

static hgeVertex tovertex(lua_State *L, int index)
{
	luaL_checktype(L, index, LUA_TTABLE);
	lua_pushvalue(L, index); // copy table
	hgeVertex ver;
	gettable(L, "x");
	ver.x = luaL_checknumber(L, -1);	lua_pop(L, 1);
	gettable(L, "y");
	ver.y = luaL_checknumber(L, -1);	lua_pop(L, 1);
	gettable(L, "z");
	ver.z = luaL_optnumber(L, -1, 0);	lua_pop(L, 1);
	gettable(L, "col");
 	ver.col = luaL_optinteger(L, -1, 0x00000000);	lua_pop(L, 1);
	gettable(L, "tx");
	ver.tx = luaL_optnumber(L, -1, 0);	lua_pop(L, 1);
	gettable(L, "ty");
	ver.ty = luaL_optnumber(L, -1, 0);	lua_pop(L, 1);
	lua_pop(L, 1); // pop table
	return ver;
}

static hgeTriple totriple(lua_State *L, int index)
{
	luaL_checktype(L, index, LUA_TTABLE);
	lua_pushvalue(L, index); // copy table
	hgeTriple triple;
	gettable(L, "tex");
	triple.tex = tohandle(L, -1, TEXTURE); lua_pop(L, 1);
	gettable(L, "blend");
	triple.blend = luaL_optinteger(L, -1, BLEND_DEFAULT); lua_pop(L, 1);
	gettable(L, "v"); // table of vertex
	for (int i = 1; i<=3 ; i++)
	{
		gettableindex(L, i); 	
		triple.v[i - 1] = tovertex(L, -1);
		lua_pop(L, 1);
	}
	lua_pop(L, 2); // pop v and table 
	return triple;
}

static hgeQuad toquad(lua_State *L, int index)
{
	luaL_checktype(L, index, LUA_TTABLE);
	lua_pushvalue(L, index); // copy table
	hgeQuad quad;
	gettable(L, "tex");
	quad.tex = tohandle(L, -1, TEXTURE); lua_pop(L, 1);
	gettable(L, "blend");
	quad.blend = luaL_optinteger(L, -1, BLEND_DEFAULT); lua_pop(L, 1);
	gettable(L, "v"); // table of vertex
	for (int i = 1; i<=4 ; i++)
	{
		gettableindex(L, i); 	
		quad.v[i - 1] = tovertex(L, -1);
		lua_pop(L, 1);
	}
	lua_pop(L, 2); // pop v and table 
	return quad;
}

static int checkcolor(lua_State *L, int index)
{
	int color = luaL_checkinteger(L, index);
	if (color < 0 || color >= 256 )
		luaL_error(L, "ARGB color must between 0, 255");
   return color;	
}
static int lhge_argb(lua_State *L)
{
	lua_pushinteger(L, ARGB(checkcolor(L, 1), checkcolor(L, 2), checkcolor(L, 3), checkcolor(L, 4)));
	return 1;
}

static int lhge_colorget(lua_State *L)
{
	DWORD color = luaL_checkinteger(L, 1);
	lua_pushinteger(L, GETA(color));
	lua_pushinteger(L, GETR(color));
	lua_pushinteger(L, GETG(color));
	lua_pushinteger(L, GETB(color));
	return 4;
}

static int lhge_colorset(lua_State *L)
{
	DWORD color = luaL_checkinteger(L, 1);
	const char* s = luaL_checkstring(L, 2);
	int val = checkcolor(L, 3);
	for (int i = 0; s[i]; i ++)
	{
		switch(s[i])
		{
			case 'a':
				color = SETA(color, val);
				break;
			case 'r':
				color = SETR(color, val);
				break;
			case 'g':
				color = SETG(color, val);
				break;
			case 'b':
				color = SETB(color, val);
				break;
			default:
				luaL_error(L, "ColorSet arg2 must in 'argb'! ");
				break;
		}
	}
	lua_pushinteger(L, color);
	return 1;
}

/*-------------------------------------------------------------*/
// Input
/*-------------------------------------------------------------*/
static int lhge_inputgetkey(lua_State *L)
{
	lua_pushinteger(L, hge->Input_GetKey());
	return 1;
}

static int lhge_inputgetchar(lua_State *L)
{
	lua_pushinteger(L, hge->Input_GetChar());
	return 1;
}

static int lhge_inputgetkeystate(lua_State *L)
{
	int key = luaL_checkinteger(L, 1);
	lua_pushboolean(L, hge->Input_GetKeyState(key));
	return 1;
}

static int lhge_inputgetkeyname(lua_State *L)
{
	int key = luaL_checkinteger(L, 1);
	lua_pushstring(L, hge->Input_GetKeyName(key));
	return 1;
}

static int lhge_inputkeyup(lua_State *L)
{
	int key = luaL_checkinteger(L, 1);
	lua_pushboolean(L, hge->Input_KeyUp(key));
	return 1;
}

static int lhge_inputkeydown(lua_State *L)
{
	int key = luaL_checkinteger(L, 1);
	lua_pushboolean(L, hge->Input_KeyDown(key));
	return 1;
}

static int lhge_inputismouseover(lua_State *L)
{
	lua_pushboolean(L, hge->Input_IsMouseOver());
	return 1;
}

static int lhge_inputgetmousewheel(lua_State *L)
{
	lua_pushinteger(L, hge->Input_GetMouseWheel());
	return 1;
}

static int lhge_inputsetmousepos(lua_State *L)
{
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	hge->Input_SetMousePos(x, y);
	return 0;
}

static int lhge_inputgetmousepos(lua_State *L)
{
	float x;
	float y;
	hge->Input_GetMousePos(&x, &y);
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	return 2;
}


/*-------------------------------------------------------------*/
// Resource
/*-------------------------------------------------------------*/

static int lhge_resourceload(lua_State *L)
{
	unsigned long size;
	void* res = hge->Resource_Load(luaL_checkstring(L, 1), &size);
	lua_pushlightuserdata(L, res);
	lua_pushinteger(L, size);
	return 2;
}

static int lhge_resourcefree(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	void * res = lua_touserdata(L, 1);
	hge->Resource_Free(res);
	return 0;
}

static int lhge_resourceattachpack(lua_State *L)
{
	if (lua_isnoneornil(L, 2))
		lua_pushboolean(L, hge->Resource_AttachPack(luaL_checkstring(L, 1)));
	else
		lua_pushboolean(L, hge->Resource_AttachPack(luaL_checkstring(L, 1), luaL_checkstring(L, 2)));
	return 1;
}

static int lhge_resourceremovepack(lua_State *L)
{
	hge->Resource_RemovePack(luaL_checkstring(L, 1));
	return 0;
}

static int lhge_resourceremoveallpacks(lua_State *L)
{
	hge->Resource_RemoveAllPacks();
	return 0;
}

static int lhge_resourcemakepath(lua_State *L)
{
	if (lua_isnil(L, 1))
		lua_pushstring(L, hge->Resource_MakePath());
	else
		lua_pushstring(L, hge->Resource_MakePath(luaL_checkstring(L, 1)));
	return 0;
}

static int lhge_resourceenumfiles(lua_State *L)
{
	if (lua_isnil(L, 1))
		lua_pushstring(L, hge->Resource_EnumFiles());
	else
		lua_pushstring(L, hge->Resource_EnumFiles(luaL_checkstring(L, 1)));
	return 0;
}

static int lhge_resourceenumfolders(lua_State *L)
{
	if (lua_isnil(L, 1))
		lua_pushstring(L, hge->Resource_EnumFolders());
	else
		lua_pushstring(L, hge->Resource_EnumFolders(luaL_checkstring(L, 1)));
	return 0;
}

/*-------------------------------------------------------------*/
// Timer
/*-------------------------------------------------------------*/

static int lhge_timergettime(lua_State *L)
{
	lua_pushnumber(L, hge->Timer_GetTime());
	return 1;
}

static int lhge_timergetlta(lua_State *L)
{
	lua_pushnumber(L, hge->Timer_GetDelta());
	return 1;
}

static int lhge_timergetfps(lua_State *L)
{
	lua_pushinteger(L, hge->Timer_GetFPS());
	return 1;
}

/*-------------------------------------------------------------*/
// Gfx
/*-------------------------------------------------------------*/

static int lhge_beginscene(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, TARGET);
	lua_pushboolean(L, hge->Gfx_BeginScene(*udp));
	return 1;
}

static int lhge_endscene(lua_State *L)
{
	hge->Gfx_EndScene();
	return 0;
}

static int lhge_gfxclear(lua_State *L)
{
	int color = luaL_optinteger(L, 1, 0x00000000);
	hge->Gfx_Clear(color);
	return 0;
}

static int lhge_renderline(lua_State *L)
{
	hge->Gfx_RenderLine(luaL_checknumber(L, 1), luaL_checknumber(L, 2), luaL_checknumber(L, 3), 
			luaL_checknumber(L, 4), luaL_optinteger(L, 5, 0xffffffff), luaL_optnumber(L, 6, 0.5));
	return 0;
}

static int lhge_rendertriple(lua_State *L)
{
	hgeTriple triple = totriple(L, 1);
	hge->Gfx_RenderTriple(&triple);
	return 0;
}

static int lhge_renderquad(lua_State *L)
{
	hgeQuad quad = toquad(L, 1);
	hge->Gfx_RenderQuad(&quad);
	return 0;
}
/*-------------------------------------------------------------*/
// Target
/*-------------------------------------------------------------*/

static int lhge_targetcreate(lua_State *L)
{
	HHANDLE * udp = newudp(L, TARGET);
	(*udp) = hge->Target_Create(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2), lua_toboolean(L, 3));
	if (*udp == NULL)
		luaL_error(L, "Hge Target_Create Failed");
	return 1;
}

static int target_gc(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, TARGET);
	hge->Target_Free(*udp);
	return 0;
}

static int target_gettexture(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, TARGET);
	HHANDLE * tex_udp = newudp(L, TEXTURE);
	*tex_udp = hge->Target_GetTexture(*udp);
	return 1;
	
}

/*-------------------------------------------------------------*/
// Texture
/*-------------------------------------------------------------*/
static int lhge_texcreate(lua_State *L)
{
	HHANDLE tex = hge->Texture_Create(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2));
	HHANDLE * udp = newudp(L, TEXTURE);
	*udp = tex; 
	return 1;
}

static int lhge_texload(lua_State *L)
{
	HHANDLE tex = hge->Texture_Load(luaL_checkstring(L, 1),
		   	luaL_optinteger(L, 2, 0),
		   	lua_toboolean(L, 3));
	HHANDLE * udp = newudp(L, TEXTURE);
	*udp = tex;
	if (*udp == NULL)
		luaL_error(L, "Hge Texture_Load Failed!");
	return 1;
}


static int tex_gc(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, TEXTURE);
	hge->Texture_Free(*udp);
	return 0;
}

static int tex_tostring(lua_State *L)  
{
	HHANDLE * udp = toudp(L, 1, TEXTURE);
	if (udp == NULL)
		lua_pushliteral(L, "Texture (NULL)");
	else
		lua_pushfstring(L, "Texture (%p)", udp);
	return 1;
}

static int tex_getwidth(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, TEXTURE);
	int width = hge->Texture_GetWidth(*udp, lua_toboolean(L, 2));
	lua_pushinteger(L, width);
	return 1;
}

static int tex_getheight(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, TEXTURE);
	int height = hge->Texture_GetHeight(*udp, lua_toboolean(L, 2));
	lua_pushinteger(L, height);
	return 1;
}

static int tex_lock(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, TEXTURE);
	bool bReadOnly = true;
	if (lua_isnoneornil(L, 2))
		bReadOnly = true;
	else
		bReadOnly = lua_toboolean(L, 2);

	hge->Texture_Lock(*udp, bReadOnly, 
			luaL_optinteger(L, 3, 0),
			luaL_optinteger(L, 4, 0),
			luaL_optinteger(L, 5, 0),
			luaL_optinteger(L, 6, 0)
			);
	return 0;
}

static int tex_unlock(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, TEXTURE);
	hge->Texture_Unlock(*udp);
	return 0;
}

/*-------------------------------------------------------------*/
// Channel
/*-------------------------------------------------------------*/

static int lhge_channelpauseall(lua_State *L)
{
	hge->Channel_PauseAll();
	return 0;
}

static int lhge_channelresumeall(lua_State *L)
{
	hge->Channel_ResumeAll();
	return 0;
}

static int lhge_channelstopall(lua_State *L)
{
	hge->Channel_StopAll();
	return 0;
}

static int channel_setpanning(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	hge->Channel_SetPanning(*udp, luaL_checkinteger(L, 2));
	return 0;
}

static int channel_setvolume(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	hge->Channel_SetVolume(*udp, luaL_checkinteger(L, 2));
	return 0;
}

static int channel_setpitch(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	hge->Channel_SetPitch(*udp, luaL_checknumber(L, 2));
	return 0;
}

static int channel_pause(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	hge->Channel_Pause(*udp);
	return 0;
}

static int channel_resume(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	hge->Channel_Resume(*udp);
	return 0;
}

static int channel_stop(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	hge->Channel_Stop(*udp);
	return 0;
}

static int channel_isplaying(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	lua_pushboolean(L, hge->Channel_IsPlaying(*udp));
	return 1;
}

static int channel_getlength(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	lua_pushnumber(L, hge->Channel_GetLength(*udp));
	return 1;
}

static int channel_setpos(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	hge->Channel_SetPos(*udp, luaL_checknumber(L, 2));
	return 0;
}

static int channel_getpos(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	lua_pushnumber(L, hge->Channel_GetPos(*udp));
	return 1;
}

static int channel_slideto(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	hge->Channel_SlideTo(*udp,
			luaL_checknumber(L, 2),
			luaL_checkinteger(L, 3),
			luaL_optinteger(L, 4, -101),
			luaL_optnumber(L, 5, -1)
		);
	return 0;
}

static int channel_issliding(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, CHANNEL);
	lua_pushboolean(L, hge->Channel_IsSliding(*udp));
	return 1;
}

/*-------------------------------------------------------------*/
// Effect
/*-------------------------------------------------------------*/

static int lhge_effectload(lua_State *L)
{
	HHANDLE effect = hge->Effect_Load(
			luaL_checkstring(L, 1),
			luaL_optinteger(L, 2, 0)
		);
	HHANDLE * udp = newudp(L, EFFECT);
	*udp = effect;
	if (*udp == NULL)
		luaL_error(L, "Hge Effect_Load Failed!");
	return 1;
}

static int effect_play(lua_State *L)
{
	HHANDLE * effect_udp = toudp(L, 1, EFFECT);
	HHANDLE effect = hge->Effect_PlayEx(
			*effect_udp,
			luaL_optinteger(L, 2, 100),
			luaL_optinteger(L, 3, 0),
			luaL_optnumber(L, 4, 1.0),
			lua_toboolean(L, 5)
		);
	HHANDLE * udp = newudp(L, CHANNEL);
	*udp = effect;
	return 1;
}

static int effect_gc(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, EFFECT);
	hge->Effect_Free(*udp);
	return 0;
}

static int effect_tostring(lua_State *L)  
{
	HHANDLE * udp = toudp(L, 1, EFFECT);
	if (udp == NULL)
		lua_pushliteral(L, "Effect (NULL)");
	else
		lua_pushfstring(L, "Effect (%p)", udp);
	return 1;
}


/*-------------------------------------------------------------*/
// Stream
/*-------------------------------------------------------------*/

static int lhge_streamload(lua_State *L)
{
	HHANDLE stream = hge->Stream_Load(
			luaL_checkstring(L, 1),
			luaL_optinteger(L, 2, 0)
		);
	if (stream == NULL)
		luaL_error(L, "Hge Stream_Load Failed!");

	HHANDLE * udp = newudp(L, STREAM);
	(*udp) = stream;
	return 1;
}

static int stream_gc(lua_State *L)
{
	HHANDLE * udp = toudp(L, 1, STREAM);
	hge->Stream_Free(*udp);
	return 0;
}

static int stream_tostring(lua_State *L)
{	
	HHANDLE * udp = toudp(L, 1, STREAM);
	if (udp == NULL)
		lua_pushliteral(L, "Stream (NULL)");
	else
		lua_pushfstring(L, "Stream (%p)", udp);
	return 1;
}

static int stream_play(lua_State *L)
{
	HHANDLE * stream = toudp(L, 1, STREAM);
	HHANDLE channel = hge->Stream_Play(
			*stream,
			lua_toboolean(L, 2),
			luaL_optinteger(L, 3, 100)
		);
	HHANDLE * udp = newudp(L, CHANNEL);
	(*udp) = channel;
	return 1;
}

/*-------------------------------------------------------------*/
// Interface
/*-------------------------------------------------------------*/

static const luaL_Reg syslib[] =
{
	{	"System_Init", lhge_init	},
	{	"System_MainLoop", lhge_mainloop	},
	{	"System_Snapshot",	lhge_snapshot	},
	{	"System_GetState",	lhge_getstate	},
	{	"System_SetState", lhge_setstate	},
	{	"System_Log",	lhge_log	},
	// Gfx
	{	"Gfx_BeginScene", lhge_beginscene},
	{	"Gfx_EndScene", lhge_endscene},
	{	"Gfx_Clear", lhge_gfxclear},
	{	"Gfx_RenderLine", lhge_renderline},
	{	"Gfx_RenderTriple", lhge_rendertriple},
	{	"Gfx_RenderQuad", lhge_renderquad},
	{	"Gfx_StartBatch", empty_func},
	{	"Gfx_FinishBatch", empty_func},
	{	"Gfx_SetClipping", empty_func},
	{	"Gfx_SetTransform", empty_func},
	// Timer
	{	"Timer_GetTime", lhge_timergettime},
	{	"Timer_GetDelta", lhge_timergetlta},
	{	"Timer_GetFPS", lhge_timergetfps},
	// Input
	{	"Input_GetMousePos", lhge_inputgetmousepos},
	{	"Input_SetMousePos", lhge_inputsetmousepos},
	{	"Input_GetMouseWheel", lhge_inputgetmousewheel},
	{	"Input_IsMouseOver", lhge_inputismouseover},
	{	"Input_KeyDown", lhge_inputkeydown},
	{	"Input_KeyUp", lhge_inputkeyup},
	{	"Input_GetKeyName", lhge_inputgetkeyname},
	{	"Input_GetKeyState", lhge_inputgetkeystate},
	{	"Input_GetKey", lhge_inputgetkey},
	{	"Input_GetChar", lhge_inputgetchar},
	{	"Input_GetEvent", empty_func},
	// Texture
	{	"Texture_Create", lhge_texcreate},
	{	"Texture_Load", lhge_texload},
	// Resource
	{	"Resource_Load", lhge_resourceload},
	{	"Resource_Free", lhge_resourcefree},
	{	"Resource_AttachPack", lhge_resourceattachpack},
	{	"Resource_RemovePack", lhge_resourceremovepack},
	{	"Resource_RemoveAllPacks", lhge_resourceremoveallpacks},
	{	"Resource_MakePath", lhge_resourcemakepath},
	{	"Resource_EnumFiles", lhge_resourceenumfiles},
	{	"Resource_EnumFolders", lhge_resourceenumfolders},
	// Effect
	{	"Effect_Load", lhge_effectload},
	// Music
	{	"Music_Load", empty_func},
	{	"Music_Free", empty_func},
	{	"Music_Play", empty_func},
	{	"Music_SetAmplification", empty_func},
	{	"Music_GetAmplification", empty_func},
	{	"Music_GetLength", empty_func},
	{	"Music_SetPos", empty_func},
	{	"Music_GetPos", empty_func},
	{	"Music_SetInstrVolume", empty_func},
	{	"Music_GetInstrVolume", empty_func},
	{	"Music_SetChannelVolume", empty_func},
	{	"Music_GetChannelVolume", empty_func},
	// Stream
	{	"Stream_Load", lhge_streamload},
	// Channel
	{	"Channel_PauseAll", lhge_channelpauseall},
	{	"Channel_ResumeAll", lhge_channelresumeall},
	{	"Channel_StopAll", lhge_channelstopall},
	// Target
	{	"Target_Create", lhge_targetcreate},
	// Color
	{	"ARGB", lhge_argb},
	{	"ColorGet", lhge_colorget},
	{	"ColorSet", lhge_colorset},	
	// Sprite
	{	"NewSprite", lhge_newsprite},
	// Rect
	{	"NewRect", lhge_newrect},
	// Animation
	{	"NewAnimation", lhge_newanimation},
	// Font
	{	"NewFont", lhge_newfont},
	// GUI
	{ "NewGUI", lhge_newgui},
	// GUIText
	{	"NewGUIText", lhge_newguitext},
	// NULL
	{	NULL, NULL	}
};

static const luaL_Reg streamlib[] = {
	{"__gc", stream_gc},
	{"__tostring", stream_tostring},
	{"Play", stream_play},
	{NULL, NULL}
};

static const luaL_Reg channellib[] = {
	{"SetPanning", channel_setpanning},
	{"SetVolume", channel_setvolume},
	{"SetPitch", channel_setpitch},
	{"Pause", channel_pause},
	{"Resume", channel_resume},
	{"Stop", channel_stop},
	{"IsPlaying", channel_isplaying},
	{"GetLength", channel_getlength},
	{"SetPos", channel_setpos},
	{"GetPos", channel_getpos},
	{"SlideTo", channel_slideto},
	{"IsSliding", channel_issliding},
	{NULL, NULL}
};

static const luaL_Reg targetlib[] = {
	{"__gc", target_gc},
	{"__tostring", empty_func},
	{"GetTexture", target_gettexture},
	{NULL, NULL}
};

static const luaL_Reg texlib[] = {
	{"__gc", tex_gc},
	{"__tostring", tex_tostring},
	{"Lock", tex_lock},
	{"UnLock", tex_unlock},
	{"GetWidth", tex_getwidth},
	{"GetHeight", tex_getheight},
	{NULL, NULL}
};

static const luaL_Reg effectlib[] = {
	{"__gc", effect_gc},
	{"__tostring", effect_tostring},
	{"Play", effect_play},
	{NULL, NULL}
};


void luaopen_hge(lua_State *L)
{
	lhge_register_const(L, system_state);
	lhge_register_const(L, keycode);
	lhge_register_const(L, coloropt);	
	luaL_register(L, SYSTEM, syslib);
	create_meta(L, TEXTURE, texlib);
	create_meta(L, TARGET, targetlib);
	create_meta(L, EFFECT, effectlib);
	create_meta(L, CHANNEL, channellib);
	create_meta(L, STREAM, streamlib);
	luaopen_sprite(L);
	luaopen_rect(L);
	luaopen_animation(L);
	luaopen_font(L);
	luaopen_gui(L);
}
