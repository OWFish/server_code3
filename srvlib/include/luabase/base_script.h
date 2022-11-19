#ifndef _ROBOT_SCRIPT_H_
#define _ROBOT_SCRIPT_H_

class BaseScript :
	public BaseLua
{
public:
	typedef BaseLua Inherited;
	typedef misc::RefObject<LuaPreProcessor::LineRangeList> SourceLineList;

	//脚本初始化函数名称
	static const char* ScriptInitFnName;
	//脚本析构函数名称
	static const char* ScriptUninitFnName;
	//向脚本中保存此脚本对象指针的名称
	static const char* ScriptInstanceKeyName;
public:
	BaseScript();
	~BaseScript();
	
	/* 调用脚本函数，如果脚本调用成功，则函数返回true，否则返回false。
	 * 当调用脚本失败时，函数返回false并在返回值列表中存储1个错误描述内容的字符串值
	 * args				脚本参数列表
	 * results			脚本返回值列表
	 * nResultCount		期望的返回值数量，LUA_MULTRET表示不限制
	 */
	virtual bool Call(const char* fn, ScriptValueList *args, ScriptValueList *results, int ret_count = LUA_MULTRET);
	
	bool LoadScript(const char* fn);

	void SetVspDef(CVSPDefinition* vsp);
	/*
	* Comments: 覆盖父类设置脚本内容的函数，增加对代码原始行记录器的保存
	* Param const char* sText:
	* Param const CSourceLineList * pLRList:
	* @Return bool:
	*/
	bool setScript(const char* sText, SourceLineList* pLRList);
protected:
	//脚本调用错误处理分派函数
	static int ScriptCallErrorDispatcher(lua_State *L);

	virtual void ScriptCallError(const char* sFnName);
	virtual int HandleCallError();
	virtual lua_State* createLuaVM();
	virtual bool openBaseLibs();
	virtual bool registLocalLibs();
	virtual bool callInit();
	virtual bool onCallInit();
	virtual bool callFinal();
	virtual bool onCallFinal();
	virtual void showError(const char* err);
	virtual void onCallEnd(bool ret);
protected:
	SourceLineList		src_;		//原始代码行记录表，用于获取更精确的函数代码位置
	CVSPDefinition*		vsp_;
};

#endif

