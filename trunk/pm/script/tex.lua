-- the only thing need to output is datas 
local folder = "image"
datas = 
{
	[ 1001 ] = { "whitestar.BMP", "w",64, 64,0,0},
	[ 1002 ] = { "bluecircle.BMP" , "b", 64,64},
}

table.foreach(datas, function (k,v) v[1] = folder.."/"..v[1] end)

--table.foreach(datas, function (k,v) print(v[1]) end)



