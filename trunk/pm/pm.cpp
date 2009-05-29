// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern HGE *hge;
int main()
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_WINDOWED, true);
	
	if(! hge->System_Initiate())
	{
		printf("Hge System_Initiate Failed!\n");
		return 1;
		
	}

	TexManager tex_mgr;
	tex_mgr.Init("script/tex.lua");


	hge->Release();

	return 0;
}

