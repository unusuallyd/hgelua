// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")
extern HGE *hge;



TexManager tex_manager;
GfxFont* pGfxFont;	
hgeSprite *sprP, *sprA;
Predator predator;
Prey prey;

void InitFunc()
{
	tex_manager.Init("script/tex.lua");
	pGfxFont		= new GfxFont("宋体",12,FALSE,FALSE,FALSE);// 宋书，非粗体，非斜体，非平滑

	pGfxFont->SetColor(0xFF00FFFF);		// 设置像素字体颜色
	sprP = tex_manager.CreateSprite(1001);
	sprA = tex_manager.CreateSprite(1002);
	
	predator.randpos(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	prey.randpos(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	prey.set_target(predator);
	prey.set_speed(1);
	predator.set_target(prey);
	predator.set_speed(3);
}

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	switch(hge->Input_GetKey())
	{
	case HGEK_ESCAPE:
		return true;
		break;
	case HGEK_ENTER:
		predator.randpos(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		prey.randpos(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		break;
	case HGEK_RIGHT:
		break;
	case HGEK_LEFT:
		break;
	}

	prey.move();
	predator.move();

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

	sprA->Render(prey.get_x(), prey.get_y());
	sprP->Render(predator.get_x(), predator.get_y());



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
	hge->System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
	hge->System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
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

