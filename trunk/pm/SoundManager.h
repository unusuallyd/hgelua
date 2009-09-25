#pragma once

class SoundManager
{
	ResMap sound_map;
	StrMap info_map;
	IntMap width_map, hight_map, left_map, top_map;
	bool IsExist(int sid); //判定纹理是否在map中
	void LoadOnce(lua_State *L); //尝试一次性载入
public:
	void Init(const char* srcipt_path);
	void CleanUp();
	HEFFECT GetSound(int sid);
	HCHANNEL PlaySound(int sid);
	const char* GetInfo(int sid);
};
