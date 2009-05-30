local folder = "image"
local datas = 
{
	[ 1001 ] = { "a.jpg"},
	[ 1002 ] = { "key.jpg" , "info"},
}

------------------------------------------------
for k, v in pairs(datas) do
	datas[k][1] = folder.."/"..v[1]
end
local index = nil

function GetData(tid)
	if datas[tid] then
		return datas[tid][1], datas[tid][2]
	else
		return 
	end
end

function Iter()
	local path, info
	index, res = next(datas, index)
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

