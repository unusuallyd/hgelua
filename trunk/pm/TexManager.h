#pragma once

#include <hge.h>
#include <lua.hpp>
#include <map>

typedef std::map<int, HTEXTURE> TexMap;
typedef std::map<int, const char* > StrMap;
class TexManager
{
	TexMap tex_map;
	StrMap info_map;
public:
	TexManager(void);
	void Init(const char* srcipt_path);
	~TexManager(void);
};
