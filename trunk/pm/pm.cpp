// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern HGE *hge;
int _tmain(int argc, _TCHAR* argv[])
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_WINDOWED, true);
	if(! hge->System_Initiate())
	{
		printf("Hge System_Initiate Failed!\n");
		return 1;
		
	}

	TexManager tex_mgr;
	tex_mgr.SetLoadMode(false);
	tex_mgr.Init("script/tex.lua");
	tex_mgr.GetTexture(1001);
	tex_mgr.GetTexture(1003);
	tex_mgr.GetTexture(1002);


	hge->Release();

	return 0;
}

