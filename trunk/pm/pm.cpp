// pm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern HGE *hge;
HCHANNEL tmp;
hgeQuad quad;
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

