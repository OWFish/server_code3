int_t = 1
int64_t = 2
string_t = 3
bin_t = 4
byte_t = 5
ushort_t = 6

--这几个是固定变量
c_srvid = 999
c_actid = 998

typename = 
{
	[int_t] = "int",
	[int64_t] = "int64_t",
	[string_t] = "const char*",
	--[bin_t] = "const char*",
	[byte_t] = "BYTE",
	[ushort_t] = "unsigned short",
}

conf = 
{
	{
		cmd = "dcDeleteMsg",
		func = "DeleteMsg",
		
		sql = "call deletecharmsg(%d,%I64d)",
		-- in_count = true,
		in_list = {	int64_t },
		sql_arg = {	c_actid, c_srvid,1,2 },
		src_out = {1},
		
		-- mul_count = 0,	-- 超过这个数量会报错
		-- sql_out = 
		-- {
		-- },
	},
	
	{
		cmd = "old",
		func = "old_func",
		inc = "old_func.hpp",
	}
}