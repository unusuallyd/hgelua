local texs = 
{
	[ 1001 ] = { "../image/a.jpg"},
	[ 1002 ] = { "../image/key.jpg" , "info"},
}

local index = nil


function GetTex(tid)
	if texs[tid] then
		return texs[tid][1], texs[tid][2]
	else
		return 
	end
end

function Iter()
	local path, info
	index, res = next(texs, index)
	if res == nil then return end
	return index,res[1], res[2]
end



function Test()

	local i,p,info = Iter()
	while i do
		print(i,p,info)
		i,p,info = Iter()
	end
end

