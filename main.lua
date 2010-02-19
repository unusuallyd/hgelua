require("base")
require("const")
require("animation")



hge.System_SetState(HGE_WINDOWED, true);
hge.System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
hge.System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
hge.System_SetState(HGE_LOGFILE, "game.log");
hge.System_SetState(HGE_SCREENBPP, 32);
hge.System_SetState(HGE_FPS, FPS);


GameCtrl.Init()


local sec1 = 
{
	__dat = {},
	InitFunc = function ()
	end,

	EndFunc = function ()
	end,

	FrameFunc = function ()
		return false
	end,

	RenderFunc = function ()	
	end,
}

GameCtrl.AddSection(1, sec1)
GameCtrl.AddSection(2, sec2)
GameCtrl.AddSection(3, sec3)

GameCtrl.Start(1)

