
PI = 3.14159265358979323846

function Log(...)
	hge.Log(string.format(...))
end

function RGB(r, g, b)
	return hge.ARGB(255, r, g, b)	
end

function ARGB(a, r, g, b)
	return hge.ARGB(a, r, g, b)	
end

Red = RGB(255, 0, 0)
Blue = RGB(0, 0, 255)
Green = RGB(0, 255, 0)
White = RGB(255, 255, 255)
Black = RGB(0 , 0, 0)
ABlack = ARGB(0, 0 , 0, 0)



GameCtrl = {
	__dat = {} 
}

function GameCtrl:FrameFunc()
	if self.GetData.IsEnd then
		return true
	end
	local CurSection = self.CurSection
	return CurSection.FrameFunc()
end

function GameCtrl:RenderFunc()
	local CurSection = self.CurSection
	CurSection.RenderFunc()
end

function GameCtrl:Init()
	hge.System_SetState(HGE_FRAMEFUNC, self.FrameFunc);
	hge.System_SetState(HGE_RENDERFUNC, self.RenderFunc);
	hge.System_Init()
end

function GameCtrl:GetData()
	return self.__dat
end

function GameCtrl:AddSection(Id, Section)
	self.__dat[Id] = Section
end

function GameCtrl:Start(Id)
	self:InitSection(Id)
	self:GotoSection(Id)
	
	hge.System_MainLoop()
end

function GameCtrl:End()
	self.GetData().IsEnd = true
end

function GameCtrl:InitSection(Id)
	local CurSection
	if not Id then
		CurSection = self.CurSection
	else
		CurSection = 
	end
	CurSection.InitFunc()
end

function GameCtrl:EndSection(Id)
	...
	CurSection.EndFunc()
end

function GameCtrl:GotoSection(Id)
	local Section = self.__dat[Id]
	if not Section then error("not such game section") end
	self.GetData().CurSection = Section
	self.GetData().CurId = Id 
end


