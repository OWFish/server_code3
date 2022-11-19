-- auto Generated lang define for c++
local f = nil
local update = 0
local crcsave = "tipmsgcrc"
function init()
	f = io.open(arg[2], "w");
end

function w(data)
	if f ~= nil then
		f:write(data)
	end
end


function getUpdate()
	update = 0
	local pos = 1
	for line in io.lines(arg[1]) do
		local len = string.len(line)
		for i = 1, len do
			local ch = string.byte(line, i, i)
			update = update + (ch * pos % 100)
			pos = pos + 1
		end
	end
end

function checkUpdate()
	local crcf = io.open(crcsave)
	if crcf == nil then return true end
	c = crcf:read("*l")
	crcf:close()
	getUpdate()
	if tonumber(c) == tonumber(update) then 
		return false
	else
		--print(c)
		--print(update)
	end
	return true
end


function gen()
	w("/*\n** Generated automatically by lua .\n*/")
	w("\n\n#ifndef _TIP_MSG_ID_H_\n#define _TIP_MSG_ID_H_\n\n\n\n")
	w("enum tagTipmsgID\n{\n")
	
	for line in io.lines(arg[1]) do
		if string.sub(line, 1, 1) == '"' then 
			local i, j = string.find(line, "\".-\"")
			if (i ~= nil) then
				--print(string.sub(line, i, j))
				local k, d = string.find(line, "%-%-.-,")
				k = k + 2
				local s = string.sub(line, k, d)
				-- print(s)
				w("\t"..s.."\n")
			end
		end
	end
	
	w("\n\n\ttpMax,\n};\n\n#endif\n\n\n")
	f:flush()
	
	
end

if checkUpdate() then
	init()
	gen()
	f:close()
	getUpdate()
	--Ð´µ½ÎÄ¼þ
	io.open(crcsave,"w"):write(tostring(update))
else
	print("no change!")
end


--[[
f = io.lines("f:/1.txt")
f1 = io.lines("f:/2.txt")
f3 = io.open("f:/3.txt", "w")
local i = 1
for line in f do
	f3:write(line.."\t\t\t\t--".. f1().."\n")
	i = i + 1
end
--]]