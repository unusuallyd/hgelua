#include "StdAfx.h"
#include "TexManager.h"

TexManager::TexManager(void)
{
}

TexManager::~TexManager(void)
{
}

void TexManager::Init(const char *srcipt_path)
{
	lua_State *L = lua_open();
	luaL_openlibs(L);
	if (luaL_dofile(L, srcipt_path))
	{
		printf("Œ∆¿ÌΩ≈±æ‘ÿ»Î¥ÌŒÛ!!\n");
	}
}
