-- the only thing need to output is datas 
local folder = "image"
datas = 
{
	[ 1001 ] = { "a.jpg", "a",400, 300,0,0},
	[ 1002 ] = { "a.jpg" , "info", 400,300},
}

table.foreach(datas, function (k,v) v[1] = folder.."/"..v[1] end)

--table.foreach(datas, function (k,v) print(v[1]) end)



