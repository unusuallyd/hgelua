local Texs = 
{
	[ 1001 ] = { "a.jpg"},
}



function GetTex(tid)
	if Texs[tid] then
		return Texs[tid][1], Texs[tid][2]
	else
		return nil, nil
	end
end
