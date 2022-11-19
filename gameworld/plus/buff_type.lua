-- 自动生成buff_type相关的定义
print("auto create buff_type.cc")
local list = {}

local idx = 0
local pat = "(%w+)%s*=%s*(%d+)"
for line in io.lines("script/interface/buff_type.h") do
	for k,v,t,f in string.gmatch(line, pat) do
		assert(idx == tonumber(v))
		local attr, type
		for p, t in string.gmatch(line, ".*<(%w+),(%w+)>") do
			attr = p
			type = t
		end
		if not attr then attr = "aUndefined" end
		if not type then type = "adInt" end
		table.insert(list, {k, attr, type, idx})
		idx = idx + 1
	end
end

local fo = io.open("script/export/buff_type.cc", "w+")
fo:write("#include \"StdAfx.h\"\n#ifndef _MSC_VER\n#include \"../StdAfx.h\"\n#endif\n\n\nGAMEATTRTYPE Buff2Attr[GameBuffCount] = \n{\n")

for _,t in ipairs(list) do
	fo:write(string.format("%s,\t// %d\n", t[2], t[4]))
end

fo:write("};\n")

fo:write("eAttribueTypeDataType BuffDataType[GameBuffCount] =\n{\n")
for _,t in ipairs(list) do
	fo:write(string.format("%s,\t// %d\n", t[3], t[4]))
end
fo:write("};\n")

fo:flush()
fo:close()
