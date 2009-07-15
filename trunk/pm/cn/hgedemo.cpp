#include <windows.h>
#include ".\cn\GfxFont.h"

#pragma comment(lib,"./HGE16/lib/hge.lib")
#pragma comment(lib,"./HGE16/lib/hgehelp.lib")
#pragma comment(linker, "/NODEFAULTLIB:libcmt.lib")

HGE *hge=0;

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

void Done()
{
	// 销毁像素字体指针
	delete pGfxFont;
}

bool FrameFunc()
{
	return false;
}

bool RenderFunc()
{
	hge->Gfx_Clear(0);
	hge->Gfx_BeginScene();


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

	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_INIFILE, "hgedemo.ini");
	hge->System_SetState(HGE_LOGFILE, "hgedemo.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "HGE 中文显示解决方案 : 微妙的平衡 HTTP://BOGY.CN");
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	hge->System_SetState(HGE_USESOUND, false);

	if(hge->System_Initiate())
	{
		Init();
		hge->System_Start();
	}
	else MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	Done();

	hge->System_Shutdown();
	hge->Release();
	return 0;
}
