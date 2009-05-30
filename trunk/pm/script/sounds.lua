
local folder = "sound/mp3"
local datas = 
{
	[ 1000 ] = { "0.mid", "鬼塔,铃声"},
	[ 1001 ] = { "1.mid" , "鬼塔,长笛声"},
	[ 1002 ] = { "2.mid" , "鬼塔,小提琴"},
	[ 1003 ] = { "3.mid" , "精灵中心, 治疗"},
	[ 1004 ] = { "4.mid" , "升级"},
	[ 1005 ] = { "5.mid" , "习得技能"},
	[ 1006 ] = { "6.mid" , "战斗胜利1"},
	[ 1007 ] = { "7.mid" , "战斗胜利2"},
	[ 1008 ] = { "8.mid" , "战斗胜利3"},
	[ 1009 ] = { "9.mid" , "战斗胜利4"},
	[ 1010 ] = { "10.mid" , "惊奇"},
	[ 1011 ] = { "11.mid" , "激昂"},
	[ 1012 ] = { "12.mid" , "战斗bgm1"},
	[ 1013 ] = { "13.mid" , "战斗bgm2"},
	[ 1014 ] = { "14.mid" , "欢快bgm"},
	[ 1015 ] = { "15.mid" , "完成任务1"},
	[ 1016 ] = { "16.mid" , "完成任务2"},
	[ 1017 ] = { "17.mid" , "被敌人发现,挑战1"},
	[ 1018 ] = { "18.mid" , "被敌人发现,挑战2"},
	[ 1019 ] = { "19.mid" , "被带领去参观, 欢快"},
	[ 1020 ] = { "20.mid" , ""},
	[ 1021 ] = { "21.mid" , "紧张, 洞穴"},
	[ 1022 ] = { "22.mid" , "激昂, 霸王之路"},
	[ 1023 ] = { "23.mid" , "唱歌, 波波球"},
	[ 1024 ] = { "24.mid" , "挑战天王"},
	[ 1025 ] = { "25.mid" , "激昂,公路"},
	[ 1099 ] = { "0.mid" , ""},
	[ 1099 ] = { "0.mid" , ""},
	[ 1099 ] = { "0.mid" , ""},
	[ 1099 ] = { "0.mid" , ""},
	[ 1099 ] = { "0.mid" , ""},
	[ 1099 ] = { "0.mid" , ""},
	[ 2054 ] = { "54.mp3" , ""},
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
