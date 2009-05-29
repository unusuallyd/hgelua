local texs = 
{
	[ 1001 ] = { "image\\a.jpg"},
	[ 1002 ] = { "image\\key.jpg" , "info"},
}

local index = nil


function GetTex(tid)
	if texs[tid] then
		return texs[tid][1], texs[tid][2]
	else
		return nil, nil
	end
end

function Iter()
	local path, info
	index, res = next(texs, index)
	if res == nil then return nil, nil end
	return res[1], res[2]
end



function Test()

	local p,i = Iter()
	while p do
		print(p, i)
		p, i = Iter()
	end
end

