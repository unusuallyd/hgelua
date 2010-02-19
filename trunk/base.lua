
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

function GameCtrl:GetData()
	return self.__dat
end

function GameCtrl:FrameFunc()
	local func
	func = function ()
		if self.__dat.IsEnd then
			return true
		end
		local CurSection = self.CurSection
		if not CurSection then return false end
		return CurSection:FrameFunc()
	end
	return func
end

function GameCtrl:RenderFunc()
	local fun
	func = function ()
		local CurSection = self.CurSection
		if not CurSection then return false end
		CurSection:RenderFunc()
	end
	return func
end

function GameCtrl:Init()
	hge.System_SetState(HGE_FRAMEFUNC, self:FrameFunc());
	hge.System_SetState(HGE_RENDERFUNC, self:RenderFunc());
	hge.System_Init()
end

function GameCtrl:End()
	self:GetData().IsEnd = true
end

function GameCtrl:EndSection(Id)
	self.CurSection:EndFunc()
end

function GameCtrl:AddSection(Id, Section)
	self.__dat[Id] = Section
end

function GameCtrl:InitSection(Id)
	local CurSection
	if not Id then
		CurSection = self.CurSection
	else
		CurSection = self.__dat[Id] 
	end
	CurSection:InitFunc()
end

function GameCtrl:GotoSection(Id)
	local Section = self.__dat[Id]
	if not Section then error("not such game section") end
	self.CurSection = Section
	self.CurId = Id 
end

function GameCtrl:Start(Id)
	self:InitSection(Id)
	self:GotoSection(Id)
	hge.System_MainLoop()
end

