#pragma once

#include <hge.h>
#include <lua.hpp>
#include <map>

// typedef
typedef std::map<int, HTEXTURE> TexMap;
typedef std::map<int, const char* > StrMap;

// help function


// class def
class TexManager
{
	TexMap tex_map;
	StrMap info_map;
	bool is_load_once; //一次性载入纹理
	bool AssertExist(int tid); //判定纹理是否在map中, 如果不存在并且 is_load_once 为 flase, 尝试载入
	bool TryAddTexture(int tid); //尝试载入编号为tid的纹理
	bool LoadOnce(); //尝试一次性载入
	// 状态
	lua_State *L;
public:
	TexManager(void);
	void Init(const char* srcipt_path);
	~TexManager(void);
	void SetLoadMode(bool load_once); //设置载入方式
	HTEXTURE GetTexture(int tid);
	const char* GetInfo(int tid);
};
