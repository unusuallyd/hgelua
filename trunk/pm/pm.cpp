// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma comment(linker, "/NODEFAULTLIB:libc.lib")
extern HGE *hge;
HCHANNEL tmp;
hgeQuad quad;


GfxFont* pGfxFont		= NULL;	// 普通模式
GfxFont* pBlodFont		= NULL;	// 粗体模式
GfxFont* pItalicFont	= NULL;	// 斜体模式
GfxFont* pNotAntialias	= NULL; // 非平滑模式
GfxFont* pAntialias		= NULL; // 平滑模式

void Init()
{

	pGfxFont		= new GfxFont("宋体",12,FALSE,FALSE,FALSE);// 宋书，非粗体，非斜体，非平滑
	pBlodFont		= new GfxFont("宋体",18,TRUE,FALSE,FALSE);// 宋书，粗体，非斜体，非平滑
	pItalicFont		= new GfxFont("黑体",26,TRUE,TRUE,FALSE);// 黑书，粗体，斜体，非平滑
	pNotAntialias	= new GfxFont("隶书",36,TRUE,FALSE,FALSE);// 隶书，粗体，非斜体，非平滑
	pAntialias		= new GfxFont("隶书",36,TRUE,FALSE,TRUE);// 隶书，粗体，非斜体，平滑

	pGfxFont->SetColor(0xFF00FFFF);		// 设置像素字体颜色
	pBlodFont->SetColor(0xFFFF0FF0);	// 设置像素字体颜色
	pItalicFont->SetColor(0xFF0FF0FF);	// 设置像素字体颜色
	pNotAntialias->SetColor(0xFFFFF00F);// 设置像素字体颜色
	pAntialias->SetColor(0xFF0FFF0F);	// 设置像素字体颜色
}

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	switch(hge->Input_GetKey())
	{
	case HGEK_ESCAPE: return true;
	case HGEK_RIGHT:
		hge->Channel_Resume(tmp);
		break;
	case HGEK_LEFT:
		hge->Channel_Pause(tmp);
		break;
	case HGEK_UP:
		hge->Channel_SetVolume(tmp,50);
		break;
	}
	float x = 400;
	float y = 300;
	// Set up quad's screen coordinates
	quad.v[0].x=x-16; quad.v[0].y=y-16;
	quad.v[1].x=x+16; quad.v[1].y=y-16;
	quad.v[2].x=x+16; quad.v[2].y=y+16;
	quad.v[3].x=x-16; quad.v[3].y=y+16;

	return false;
}
bool RenderFunc()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	hge->Gfx_RenderQuad(&quad);

	const char* lpString = ""
		"演示中文显示新方案，支持平滑(无锯齿)模式\n"
		"\n"
		"不需要依赖任何图片字模，丰富多样的显示方法。\n"
		"\n"
		"使用方法很简单，请参阅 <CN> 目录下的 Readme.txt 文件。\n";

	// 使用像素字体输出
	pGfxFont->Print(10,10,lpString);

	pBlodFont->Print(10,100,"中文显示方案 演示“粗体”");		
	pItalicFont->Print(10,150,"中文显示方案 演示“斜体”");
	pNotAntialias->Print(10,200,"中文显示方案 演示“非平滑模式”");
	pAntialias->Print(10,250,"中文显示方案 演示“平滑反锯齿模式”");


	HpBar bar(100,20,2);
	bar.Render();

	hge->Gfx_EndScene();
	return false;
}
int main()
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_LOGFILE, "game.log");
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(! hge->System_Initiate())
	{
		printf("Hge System_Initiate Failed!\n");
		return 1;		
	}
	Init();
	TexManager tex_manager;
	tex_manager.Init("script/tex.lua");
	SoundManager sound_manager;
	sound_manager.Init("script/sounds.lua");
	tmp = hge->Effect_PlayEx(sound_manager.GetSound(2054),100,100,2,true);
	hge->Channel_Pause(tmp);
	quad.tex = tex_manager.GetTexture(1003);


	// Set up quad which we will use for rendering sprite
	//quad.blend=BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;

	for(int i=0;i<4;i++)
	{
		// Set up z-coordinate of vertices
		quad.v[i].z=0.5f;
		// Set up color. The format of DWORD col is 0xAARRGGBB
		quad.v[i].col=0xFFFFA000;
	}

	// Set up quad's texture coordinates.
	// 0,0 means top left corner and 1,1 -
	// bottom right corner of the texture.
	quad.v[0].tx=96.0/128.0; quad.v[0].ty=64.0/128.0; 
	quad.v[1].tx=128.0/128.0; quad.v[1].ty=64.0/128.0; 
	quad.v[2].tx=128.0/128.0; quad.v[2].ty=96.0/128.0; 
	quad.v[3].tx=96.0/128.0; quad.v[3].ty=96.0/128.0; 
	//////////////////////////////////////////////////////////////////////////
	hge->System_Start();

	tex_manager.CleanUp();
	sound_manager.CleanUp();
	hge->System_Shutdown();
	hge->Release();

	return 0;
}

