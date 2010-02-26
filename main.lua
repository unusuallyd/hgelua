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
		self.__dat.gui = hge.NewGUI();
		self.__dat.text = hge.NewGUIText(1, 0, 0, 200, 48, self.__dat.fnt)
		gui:AddCtrl(self.__dat.text)
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
			--GameCtrl:InitSection(2)
			--GameCtrl:GotoSection(2)
		end
		return false
	end,

	RenderFunc = function (self)
		hge.Gfx_Clear()
		self.__dat.fnt:Render(400, 300, 0, string.format("Current Time: %g", hge.Timer_GetTime()))
	end,
}
GameCtrl:AddSection(1, sec1)

GameCtrl:Start(1)

