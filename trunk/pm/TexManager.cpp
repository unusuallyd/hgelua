#include "StdAfx.h"
#include "TexManager.h"

extern HGE *hge;


void TexManager::CleanUp()
{
	for (ResMap::iterator it = tex_map.begin(); it != tex_map.end(); ++it)
	{
		HTEXTURE tex = it->second;
		hge->Texture_Free(tex);
	}
}

void TexManager::Init(const char *srcipt_path)
{
	lua_State *L = lua_open();
	luaL_openlibs(L);

	if (luaL_dofile(L, srcipt_path))
	{
		printf("ÎÆÀí½Å±¾ÔØÈë´íÎó!!\n");
	}
	LoadOnce(L);
}


HTEXTURE TexManager::GetTexture(int tid)
{
	return tex_map[tid];
}

const char* TexManager::GetInfo(int tid)
{
	return info_map[tid];
}

int TexManager::GetWidth(int tid)
{
	return width_map[tid];
}

int TexManager::GetHeight(int tid)
{
	return height_map[tid];
}

int TexManager::GetTop(int tid)
{
	return top_map[tid];
}

int TexManager::GetLeft(int tid)
{
	return left_map[tid];
}

bool TexManager::IsExist(int tid)
{
	return ( tex_map.find(tid) != tex_map.end() );
}

void TexManager::AssertExist(int tid)
{
	assert(IsExist(tid));
}


void TexManager::LoadOnce(lua_State* L)
{
	lua_getglobal(L, "datas");
	luaL_checktype(L,1,LUA_TTABLE);

	lua_pushnil(L); 
	while (lua_next(L, 1) != 0) {
		int tid = lua_tointeger(L, -2);
		// path
		lua_pushinteger(L, 1);
		lua_gettable(L,-2);
		const char* path = lua_tostring(L,-1);
		tex_map[tid] = hge->Texture_Load(path);
		lua_pop(L, 1);
		// info
		lua_pushinteger(L, 2);
		lua_gettable(L, -2);
		info_map[tid] = lua_tostring(L, -1);
		lua_pop(L, 1);
		// width
		lua_pushinteger(L, 3);
		lua_gettable(L, -2);
		width_map[tid] = luaL_optint(L, -1, 32);
		lua_pop(L, 1);
		// height
		lua_pushinteger(L, 4);
		lua_gettable(L, -2);
		height_map[tid] = luaL_optint(L, -1, 32);
		lua_pop(L, 1);
		// left
		lua_pushinteger(L, 5);
		lua_gettable(L, -2);
		left_map[tid] = luaL_optint(L, -1, 0);
		lua_pop(L, 1);
		// top
		lua_pushinteger(L, 6);
		lua_gettable(L, -2);
		top_map[tid] = luaL_optint(L, -1, 0);
		lua_pop(L, 1);
		//
		lua_pop(L, 1);
	}

}

hgeSprite* TexManager::CreateSprite(int tid)
{
	if (IsExist(tid))
	{
		return new hgeSprite(GetTexture(tid), GetLeft(tid), GetTop(tid), GetWidth(tid), GetHeight(tid));
	}else	 
		return NULL;
}