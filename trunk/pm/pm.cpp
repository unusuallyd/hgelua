// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")
extern HGE *hge;



TexManager tex_manager;
GfxFont* pGfxFont;	
hgeSprite *sprP, *sprA;

void InitFunc()
{
	tex_manager.Init("script/tex.lua");
	pGfxFont		= new GfxFont("宋体",12,FALSE,FALSE,FALSE);// 宋书，非粗体，非斜体，非平滑

	pGfxFont->SetColor(0xFF00FFFF);		// 设置像素字体颜色
	sprP = tex_manager.CreateSprite(1001);
	sprA = tex_manager.CreateSprite(1002);

}

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	switch(hge->Input_GetKey())
	{
	case HGEK_ESCAPE: return true;
	case HGEK_RIGHT:
		break;
	case HGEK_LEFT:
		break;
	}


	return false;
}
bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	const char* lpString = ""
		"Hge lua 演示\n"
		"\n"
		"啦啦啦啦\n";

	pGfxFont->Print(10,10,lpString);

	sprA->Render(50,50);
	sprP->Render(100,100);



	hge->Gfx_EndScene();
	return false;
}

void CleanUpFunc()
{	
	tex_manager.CleanUp();

	hge->System_Shutdown();
	hge->Release();

	delete sprA, sprP;
}
int main()
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_LOGFILE, "game.log");
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_ZBUFFER, false);

	if(! hge->System_Initiate())
	{
		printf("Hge System_Initiate Failed!\n");
	}
	InitFunc();
	hge->System_Start();
	CleanUpFunc();

	return 0;
}

