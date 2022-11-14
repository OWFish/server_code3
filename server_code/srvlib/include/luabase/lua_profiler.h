#ifndef _LUA_PROFILER_H_
#define _LUA_PROFILER_H_

/************************************************************************
*
*                    LUA 脚本函数调用性能统计类
*
*    函数通过lua_hook的方式实现了记录并统计脚本中函数调用时间消耗的功能。对函数调用时间
* 消耗的默认计算方式为计算函数调用前与调用好的时间差。因此误差可能比较大，但足以找出调用
* 消耗的时间较大的函数。同时实现了将统计信息保存为文本流的功能，默认的输出格式为树形统计信
* 息。
*
*    可以通过派生此类并覆盖HandleDebugHook方法来重新实现对函数调用信息的记录和性能的统
* 计规则。
*
*    可以通过派生此类并覆盖Save方法来重新实现对统计信息保存为文本流的输出格式。
*
************************************************************************/

class LuaProfiler
{
public:
	typedef misc::RefObject<LuaPreProcessor::LineRangeList> SourceLineList;

public:
	LuaProfiler();
	virtual ~LuaProfiler();

	/*
	* Comments:设置性能统计对象
	* Param lua_State * L:
	* Param CSourceLineList * pLRList: 用于取得
	* @Return bool:如果目标对象已经被安装过性能统计，则函数返回false
	*/
	bool SetState(lua_State* L, SourceLineList* pLRList = NULL);
	/*
	* 将函数调用性能统计保存到流中
	* 函数返回向流中写入多少字节
	*/
	size_t Save(stream::BaseStream& stm);
	/*
	* Comments: 获取调用时间最长的一个函数栈的时间
	* @Return int64_t:
	*/
	int64_t GetMaxTotalTime();

protected:
	//在lua中存储当前性能统计调试器对象的值名称
	static const char PerStaticDebuggerName[];
	//静态hook处理函数
	static void StaticCallTimeHook(lua_State* L, lua_Debug* ar);

protected:
	/** 处理调试HOOK回调 **/
	virtual void HandleDebugHook(lua_State* L, lua_Debug* ar);
public:
	/** Lua函数调用性能记录 **/
	class LuaCallRcd
	{
	public:
		char		sName[40];		//函数名称
		int			nLineNo;		//行号
		int64_t		dwLastTime;	//上次调用时间
		int64_t		dwMaxTime;		//最大调用时间
		int64_t		dwMinTime;		//最小调用时间
		int64_t		dwCallCount;	//调用次数
		int64_t		dwTotalTime;	//本函数总计调用耗时
		void*		pSubCallList;	//子级调用函数表，类型为SubCallTable
	public:
		~LuaCallRcd();
	};
	//子级调用函数表
	typedef StrHashTable<LuaCallRcd> SubCallTable;
	//当前调用堆栈表
	typedef container::Vector<LuaCallRcd*> CallStack;

protected:
	lua_State*		lua_;
	CallStack		callStack_;		//当前调用堆栈
	SubCallTable	rootCallTable_;	//根调用记录表
	int64_t			igoreRecordTime_;//在保存函数调用性能记录时忽略总时间低于此值的记录
	SourceLineList	LRList_;//行范围记录器，用于格式化函数统计时取得代码的文件名和行号
};

#endif
