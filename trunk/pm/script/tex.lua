-- the only thing need to output is datas 
local folder = "image"
datas = 
{
	[ 1001 ] = { "big.jpg", "w",2848, 2136,0,0},
}

table.foreach(datas, function (k,v) v[1] = folder.."/"..v[1] end)

--table.foreach(datas, function (k,v) print(v[1]) end)



