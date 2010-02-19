require("base")
require("const")
require("animation")



hge.System_SetState(HGE_WINDOWED, true);
hge.System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
hge.System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
hge.System_SetState(HGE_LOGFILE, "game.log");
hge.System_SetState(HGE_SCREENBPP, 32);
hge.System_SetState(HGE_FPS, FPS);

GameCtrl:Init()

local sec1 = 
{
	__dat = {},
	InitFunc = function (self)
		print("InitFunc sec1")
		self.__dat.fnt = hge.NewFont("tex/font1.fnt")
		self.__dat.fnt:SetColor(RGB(255, 0, 0))
	end,

	EndFunc = function (self)
		print("Game End")
		GameCtrl:End()
	end,

	FrameFunc = function (self)
		local PressKey = hge.Input_GetKey()
		if PressKey == HGEK_ESCAPE then
			GameCtrl:EndSection()
		end

		if PressKey == HGEK_N then
			GameCtrl:InitSection(2)
			GameCtrl:GotoSection(2)
		end
		return false
	end,

	RenderFunc = function (self)
		hge.Gfx_Clear()
		self.__dat.fnt:Render(400, 300, 0, string.format("Current Time: %g", hge.Timer_GetTime()))
	end,
}

local sec2 = 
{
	__dat = {},
	InitFunc = function (self)
		print("InitFunc sec2")
		self.__dat.fnt = hge.NewFont("tex/font1.fnt")
		self.__dat.fnt:SetColor(RGB(0, 255, 0))
	end,

	EndFunc = function (self)
		print("Game End")
		GameCtrl:End()
	end,

	FrameFunc = function (self)
		local PressKey = hge.Input_GetKey()
		if PressKey == HGEK_ESCAPE then
			GameCtrl:EndSection()
		end
		
		if PressKey == HGEK_N then
			GameCtrl:InitSection(3)
			GameCtrl:GotoSection(3)
		end
		return false
	end,

	RenderFunc = function (self)
		hge.Gfx_Clear()
		self.__dat.fnt:Render(10, 10, 0, "Now loading...")
	end,
}

local sec3 = 
{
	__dat = {},
	InitFunc = function (self)
		print("InitFunc sec3")
		self.__dat.fnt = hge.NewFont("tex/font1.fnt")
		self.__dat.fnt:SetColor(RGB(0, 0, 255))
	end,

	EndFunc = function (self)
		print("Game End")
		GameCtrl:End()
	end,

	FrameFunc = function (self)
		local PressKey = hge.Input_GetKey()
		if PressKey == HGEK_ESCAPE then
			GameCtrl:EndSection()
		end
		
		return false
	end,

	RenderFunc = function (self)
		hge.Gfx_Clear()
		self.__dat.fnt:Render(10, 10, 0, "Fin")
	end,
}

GameCtrl:AddSection(1, sec1)
GameCtrl:AddSection(2, sec2)
GameCtrl:AddSection(3, sec3)

GameCtrl:Start(1)

