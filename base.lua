
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

