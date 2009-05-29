// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	TexManager tex_mgr;
	tex_mgr.Init("tex.lua");
	return 0;
}

