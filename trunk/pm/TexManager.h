#pragma once

#include <hge.h>

class TexManager
{
	ResMap tex_map;
	StrMap info_map;
	IntMap height_map, width_map, top_map, left_map;
	bool IsExist(int tid); 
	void AssertExist(int tid);
	void LoadOnce(lua_State* L);
public:
	void Init(const char* srcipt_path);
	void CleanUp();
	HTEXTURE GetTexture(int tid);
	const char* GetInfo(int tid);
	int GetHeight(int tid);
	int GetWidth(int tid);
	int GetTop(int tid);
	int GetLeft(int tid);
	hgeSprite* CreateSprite(int tid);
};
