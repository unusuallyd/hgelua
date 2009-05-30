#include "StdAfx.h"
#include "TexManager.h"

extern HGE *hge;

TexManager::TexManager(void)
{
	L = NULL;
	is_load_once = true;
}

void TexManager::CleanUp()
{
	if(L) lua_close(L);
	for (ResMap::iterator it = tex_map.begin(); it != tex_map.end(); ++it)
	{
		HTEXTURE tex = it->second;
		hge->Texture_Free(tex);
	}
}

void TexManager::Init(const char *srcipt_path)
{
	L = lua_open();
	luaL_openlibs(L);

	if (luaL_dofile(L, srcipt_path))
	{
		printf("纹理脚本载入错误!!\n");
	}
	if(is_load_once)
	{	
		LoadOnce();
	}
}

void TexManager::SetLoadMode(bool load_once)
{
	is_load_once = load_once;
}

HTEXTURE TexManager::GetTexture(int tid)
{
	if(AssertExist(tid))
		return tex_map[tid];
	else
		return NULL;
}

const char* TexManager::GetInfo(int tid)
{
	if(AssertExist(tid))
		return info_map[tid];
	else
		return NULL;
}

bool TexManager::AssertExist(int tid)
{
	bool res = ( tex_map.find(tid) != tex_map.end() );
	if(res)
	{
		return true;
	}else
	{
		if (is_load_once)
		{
			printf("编号为[ %d ]的纹理不存在!\n", tid);
			return false;
		}else
		{
			return TryAddTexture(tid);
		}
	}
}

bool TexManager::TryAddTexture(int tid)
{
	StackDump(L);
	lua_getglobal(L, "GetData");
	lua_pushinteger(L, tid);
	if (lua_pcall(L, 1, 2, 0) )
	{
		printf(" 尝试调用脚本函数 GetData 错误!\n");
		//StackDump(L);
		lua_pop(L, 1);
		return false;
	}
	bool suc = !lua_isnil(L, -2);
	if(suc)
	{
		const char* path = lua_tostring(L, -2);
		const char* info = lua_isnil(L, -1) ? "None" : lua_tostring(L, -1);
		HTEXTURE tex = hge->Texture_Load(path);
		if(tex==NULL){
			suc = false;
		}else{
			tex_map[tid] = tex;
			info_map[tid] = info;
			printf("载入纹理 %s , %s\n", path, info);
		}
	}
	if(!suc)
	{
		printf("动态载入失败, 编号为[ %d ]的纹理不存在!\n", tid);
	}
	//StackDump(L);
	lua_pop(L, 2);	
	return suc;
}

void TexManager::LoadOnce()
{
	lua_getglobal(L, "Iter");
	if (lua_pcall(L, 0, 3, 0) )
	{
		printf(" 尝试调用脚本函数 Iter 错误!\n");
	}
	bool suc = !lua_isnil(L, -3);

	while(suc)
	{
		int tid = lua_tointeger(L, -3);
		const char* path = lua_tostring(L, -2);
		const char* info = lua_isnil(L, -1) ? "None" : lua_tostring(L, -1);
		HTEXTURE tex = hge->Texture_Load(path);
		if(tex==NULL){
			printf("载入纹理失败 %s , %s\n", path, info);
		}else{
			tex_map[tid] = tex;
			info_map[tid] = info;
			printf("载入纹理 %s , %s\n", path, info);
		}
		lua_pop(L, 3);
		lua_getglobal(L, "Iter");
		lua_pcall(L, 0, 3, 0);
		suc = !lua_isnil(L, -3);
	}
}