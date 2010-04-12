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
		local dat = self.__dat
		dat.fnt = hge.NewFont("tex/font1.fnt")
		dat.gui = hge.NewGUI();
		for j = 1, 1 do
			for i = 0, 255 do
				local id = i * j
				dat.gui:AddCtrl(hge.NewGUIText(id, id % 800, id / 600, 200, 40, dat.fnt))
				dat.gui:GetCtrl(id):SetMode(0)
				if j == 1 then
					dat.gui:GetCtrl(id):SetColor(RGB(i, 0, 0))
				else
					if j == 2 then
						dat.gui:GetCtrl(id):SetColor(RGB(0, i, 0))
					else
						if j == 3 then
							dat.gui:GetCtrl(id):SetColor(RGB(0, 0, i))
						end
					end
				end
				dat.gui:GetCtrl(id):SetText("1")
			end
		end
		self.__dat = dat
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
		lastid = 1
		local gui = self.__dat.gui
		local id = gui:Update(hge.Timer_GetDelta())

		return false
	end,

	RenderFunc = function (self)
		hge.Gfx_Clear()
		self.__dat.gui:Render()
	end,
}
GameCtrl:AddSection(1, sec1)

GameCtrl:Start(1)

