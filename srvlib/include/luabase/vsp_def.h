#pragma once

/***************************************************************
*
*					针对不同版本以及运营商而不同的宏定义配置读取类
*
*   在VSPDef.txt中定义针对不同游戏版本或游戏运营商而不同的配置值，使得整个
* 游戏在保持版本数据一致的情况下可以针对配置文件中的定义而加载不同的配置文件、
* 决定某些功能是否开启等等。
*   VSP定义同时也作为游戏中的一种常量配置值提供对象。
*
***************************************************************/

class CVSPDefinition
{
public:
	/* 常量对象数据结构定义 */
	typedef struct Definition
	{
		char* sDefName;	//常量名称
		char* sDefValue;	//常量值
	}*PDEFINITION;

public:
	CVSPDefinition();
	~CVSPDefinition();

	/*
	* Comments: 通过名称获取定义值
	* Param const char* sDefName: 名称
	* @Return const char*: 如果存在指定名称的常量则返回常量定义值否则返回NULL
	*/
	const char* GetDefinition(const char* sDefName) const;
	/*
	* Comments: 将所有的定义作为宏增加到脚本预处理器中
	* Param LuaPreProcessor & preProcessor:
	* @Return void:
	*/
	void RegisteToPreprocessor(LuaPreProcessor &pp);
	/*
	* Comments: 从文件加载常量定义
	* Param const char* sFilePath: 文件路径，可以是基于工作目录的相对路径也可以是绝对路径
	* @Return bool: 加载成功则返回true否则返回false。
	*/
	bool LoadDefinitions(const char* sFilePath);
	/*
	* Comments: 设置一个常量定义，可以添加、删除以及修改定义
	* Param const char* sDefName: 定义名称（不能为空）
	* Param const char* sDefValue:定义值，为空则表示删除此定义否则当定义存在则更新定义，不存在则添加定义
	* @Return void:
	*/
	void SetDefinition(const char* sDefName, const char* sDefValue);

protected:
	/*
	* Comments: 清空所有定义对象并释放内存
	* @Return void:
	*/
	void ClearDefinitions();

private:
	container::Vector<Definition> m_Defines;
};

