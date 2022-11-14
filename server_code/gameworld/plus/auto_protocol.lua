








print("auto_protocol begin")


local file_data = nil 



function loadFile(path)
	print("input file: " .. path)
	local file = io.open(path,"r")
	if file == nil then 
		print("not file :" .. path)
		os.exit(-1)
	end
	file_data = file:read("*a")
	file:close()
end



function replace(s,c)
	file_data = string.gsub(file_data,s,c)
end


function writeData(path) 
	print("output file: " .. path)
	local file = io.open(path,"w")
	file:write(file_data)
	file:close()
end


function replaceAll()
	replace('#','--#')
	replace('//','--')
	replace('enum ','-- ')
	replace('};','')
	replace('namespace Protocol {','Protocol')
	replace('{',' ')
	replace('Protocol','Protocol = {')
	replace('\t\t','\t')
	replace('/%*','--[[')
	replace('%*/',']]')
end


function showHelp()

	print("input file output file")
end

if arg[1] == nil then 
	showHelp()
	os.exit(-1)
end
if arg[2] == nil then 
	showHelp()
	os.exit(-1)
end
loadFile(arg[1])
replaceAll()
writeData(arg[2])



print("auto_protocol end")
