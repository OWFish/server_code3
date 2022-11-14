#ifndef _BASE_LUA_CONFIG_H_
#define _BASE_LUA_CONFIG_H_

class BaseLuaConfig
	: public BaseLua
{
public:
	typedef BaseLua Inherited;
	typedef misc::RefObjectImpl<String> TableName;
private:
	container::Vector<TableName*>	m_TableStacks;	//已打开表名称列表

public:
	bool ExcuteCjson(const char* funcname, const char* p1, const char* p2, const char* p3);
protected:
	//显示脚本错误内容
	void showError(const char* sError);
	//显示表不存在的错误
	void showTableNotExists(const char* sTableName);
	//显示没有包含有效值的错误
	void showFieldDoesNotContainValue(const char* sFieldName, const char* sValueType);
	//通过const char*字符串构造一个TableName
	static TableName* createTableName(const char* sName);
protected:
	/*	打开脚本内的全局表，成功则返回true，失败会引发showError。
		当不再使用一个已经打开的表的时候必须使用closeTable将表关闭。
	*/
    bool openGlobalTable(const char* sTableName);
	/*	打开当前表中的子成员表，成功则返回true，失败会引发showError。
		当不再使用一个已经打开的表的时候必须使用closeTable将表关闭。
	*/
    bool openFieldTable(const char* sTableName);
	/*	开始遍历当前已经打开的表。
		如果表长度大于0则开始遍历表并返回true。
	*/
    bool enumTableFirst();
	/*  继续遍历当前已经打开的表。
		对一个表的第一次遍历必须使用enumTableFirst，其后的继续遍历则使用enumTableNext。
		如果已经遍历到表的结尾，则函数返回FALSE，此时不得调用enumTableNext，在表枚举结
		束时已经自动将表关闭了。
	*/
    bool enumTableNext();
	/*	终止对当前表的枚举。
		在调用enumTableFirst后开始对表的遍历，在遍历中可以使用enumTableNext持续遍历直到
		其返回false。
		如果在遍历期间需要终止对表的遍历，则应当使用enumTableNext来结束表的遍历。
	*/
    void endTableEnum();
	/*	将当前表中的第IndexStartFromOne索引的个成员当做表打开。成功则返回true，失败会引发showError。
		IndexStartFromOne索引是从1开始的，这遵循lua语言的索引标准。如果表中不存在IndexStartFromOne
		成员或其值不是一个表，则返回FALSE并引发showError。
	*/
    bool getFieldIndexTable(const int IndexStartFromOne);
	/*	测试当前表中是否存在名为sTableName的字成员表，如果存在此名称的成员且值是一个表类型，则返回true。
	*/
    bool feildTableExists(const char* sTableName);
	/*	关闭当前打开的表。	*/
    void closeTable();
	/*	获取当前已经打开的表的完整路径，路径分割符为'.' 
		返回值与Retval相同，即表路径被存储在Retval中并作为返回值。
	*/
    String& getTablePath(String& Retval);
	/*	在表枚举过程中获取当前枚举成员的名称
		函数只在表的枚举过程中有效
	*/
	string::AnsiString& getKeyName(string::AnsiString& Retval);
	/*  获取表枚举程中获取当前枚举成员值的数据类型
		函数只在表的枚举过程中有效
	*/
	inline int getValueType(){ return lua_type(lua_, -1); }
	/*	获取表中名为sFieldName的布尔值。
		如果sFieldName参数值为NULL，则表示读取通过enumTableFirst或enumTableNext进行表枚举的
		当前位置的枚举成员的值。
		如果值存在且值的类型是布尔，则返回脚本中的值并向pIsValid参数中存储true。
		如果值不存在或类型不可转换为布尔，则返回默认值并向pIsValid参数中存储false，如果默认值不存在，则返回false。
	*/
	bool getFieldBoolean(const char* sFieldName, const bool* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	获取表中名为sFieldName的数字值。
		如果sFieldName参数值为NULL，则表示读取通过enumTableFirst或enumTableNext进行表枚举的
		当前位置的枚举成员的值。
		如果值存在且值的类型是数字（整数或浮点数），则返回脚本中的值并向pIsValid参数中存储true。
		如果值不存在或类型不可转换为数字，则返回默认值并向pIsValid参数中存储false，如果默认值不存在，则返回0。
	*/
    double getFieldNumber(const char* sFieldName, const double* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	获取表中名为sFieldName的64位整数值。
		如果sFieldName参数值为NULL，则表示读取通过enumTableFirst或enumTableNext进行表枚举的
		当前位置的枚举成员的值。
		如果值存在且值的类型是数字（整数或浮点数），则返回脚本中的值并向pIsValid参数中存储true，
		如果值中含有小数，将丢弃小数部分。
		如果值不存在或类型不可转换为数字，则返回默认值并向pIsValid参数中存储false，如果默认值不存在，则返回0。
	*/
    int64_t getFieldInt64(const char* sFieldName,const int64_t* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	获取表中名为sFieldName的32位整数值。
		如果sFieldName参数值为NULL，则表示读取通过enumTableFirst或enumTableNext进行表枚举的
		当前位置的枚举成员的值。
		如果值存在且值的类型是数字（整数或浮点数），则返回脚本中的值并向pIsValid参数中存储true，
		如果值中含有小数，将丢弃小数部分。
		如果值不存在或类型不可转换为数字，则返回默认值并向pIsValid参数中存储false，如果默认值不存在，则返回0。
	*/
    int getFieldInt(const char* sFieldName, const int* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	获取表中名为sFieldName的字符串值。
		如果sFieldName参数值为NULL，则表示读取通过enumTableFirst或enumTableNext进行表枚举的
		当前位置的枚举成员的值。
		如果值存在且值的类型可作为字符串值，则返回脚本中的字符串指针并向pIsValid参数中存储true。
		★返回的字符串指只在脚本中的值内容发生改变之前有效，如果脚本内容不会改变，则可以长期使用
		返回的指针，否则在获取字符串指针后必须将内容拷贝到有效的内存地址中以免脚本被修改且进行
		了垃圾回收而使得字符串指针不再有效从而引发内存错误！
		如果值不存在或类型不可转换为字符串，则返回默认值并向pIsValid参数中存储false，如果默认值不存在，则返回NULL。
	*/
    const char* getFieldString(const char* sFieldName, const char* pDefValue = NULL, BOOL* pIsValid = NULL);
	/*	获取表中名为sFieldName的字符串值。
		如果sFieldName参数值为NULL，则表示读取通过enumTableFirst或enumTableNext进行表枚举的
		当前位置的枚举成员的值。
		如果值存在且值的类型可作为字符串值，则将字符串内容拷贝到sBuffer中，并返回拷贝的字符串长度，
		拷贝字符串的长度受dwBufLen参数限制，dwBufLen参数是sBuffer的最大长度，并非缓存区字节长度。
		如果配置中的值的长度超过dwBufLen-1，则只拷贝dwBufLen-1的长度。
		无论如何，只要dwBufLen大于0，均会在拷贝值之后为sBuffer添加终止字符。
		如果值不存在或类型不可转换为字符串，则返回-1，如果Retval的内存地址有效则会填充守字符为0。
	*/
	int getFieldStringBuffer(const char* sFieldName, char* sBuffer, size_t dwBufLen);
public:
	BaseLuaConfig();
	virtual ~BaseLuaConfig();
};

#endif
