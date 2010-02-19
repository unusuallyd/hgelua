require("base")
require("animation")

local FPS = 24
local SCREEN_WIDTH = 800
local SCREEN_HEIGHT = 600

local function FrameFunc()
	local PressKey = hge.Input_GetKey()
	if PressKey == HGEK_ESCAPE then
		return true
	end

	if PressKey == HGEK_A then
		anim:Play(2, HGEANIM_PINGPONG + HGEANIM_LOOP, 24)
	end

	if PressKey == HGEK_S then
		anim:Play(3, HGEANIM_PINGPONG + HGEANIM_LOOP, 24)
	end

	if PressKey == HGEK_D then
		anim:Play(4, HGEANIM_PINGPONG + HGEANIM_LOOP, 1)
	end

	if PressKey == HGEK_F then
		anim:Play(1, HGEANIM_PINGPONG + HGEANIM_LOOP, 24)
	end

	if PressKey == HGEK_UP then
		anim:Move(0, -5)
	end
	if PressKey == HGEK_DOWN then
		anim:Move(0, 5)
	end
	if PressKey == HGEK_LEFT then
		anim:Move(-5, 0)
	end
	if PressKey == HGEK_RIGHT then
		anim:Move(5, 0)
	end

	anim:Update()
	return false
end


local function RenderFunc()
	hge.Gfx_Clear()
	AnimationGroupRender()
	return false
end

hge.System_SetState(HGE_WINDOWED, true);
hge.System_SetState(HGE_FRAMEFUNC, FrameFunc);
hge.System_SetState(HGE_RENDERFUNC, RenderFunc);
hge.System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
hge.System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
hge.System_SetState(HGE_LOGFILE, "game.log");
hge.System_SetState(HGE_SCREENBPP, 32);
hge.System_SetState(HGE_FPS, FPS);

hge.System_Init()

anim = Animation:New()

anim:Add(1, "Tex/ctrl_1.png", 5, 4, 1, 18)
anim:Add(2, "Tex/ctrl_2.png", 5, 4, 1, 18)
anim:Add(3, "Tex/ctrl_3.png", 5, 4, 1, 17)
anim:Add(4, "Tex/ctrl_4.png", 5, 4, 1, 16)
list = {1, 2, 3, 4}

cb = AnimationList(anim, 24, list)

anim:Play(1, 0, 24, cb)

AddToAnimationGroup(anim, true)

hge.System_MainLoop()
