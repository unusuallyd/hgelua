// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern HGE *hge;
int _tmain(int argc, _TCHAR* argv[])
{
	hge = hgeCreate(HGE_VERSION);
	TexManager tex_mgr;
	tex_mgr.SetLoadMode(false);
	tex_mgr.Init("script/tex.lua");
	tex_mgr.GetTexture(1001);
	return 0;
}

