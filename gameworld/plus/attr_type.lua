-- 自动生成attr_type相关的定义
print("auto create attr_type.cc")
local list = {}

local idx = 0
local pat = "(%w+)%s*=%s*(%d+).*<(%w+),(%w+)>"
for line in io.lines("../common/common/attr_type.h") do
	for k,v,t,f in string.gmatch(line, pat) do
		assert(idx == tonumber(v))
		table.insert(list, {k, t, f, idx})
		idx = idx + 1		
	end
end

local fo = io.open("systems/attr/attr_type.cc", "w+")
fo:write("#include \"StdAfx.h\"\n#ifndef _MSC_VER\n#include \"../StdAfx.h\"\n#endif\n\n\nTAttrDataTypes	AttrDataTypes = \n{\n")

for _,t in ipairs(list) do
	fo:write(string.format("%s,\t// %d\n", t[2], t[4]))
end
fo:write("};\n")

fo:write("TAttrNeedCalc AttrNeedCalc =\n{\n")

for _,t in ipairs(list) do
	fo:write(string.format("%s,\t// %d\n", t[3], t[4]))
end

fo:write("};\n")

fo:flush()
fo:close()
