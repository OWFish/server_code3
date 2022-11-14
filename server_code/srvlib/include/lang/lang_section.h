#ifndef _LANG_SECTION_H_
#define _LANG_SECTION_H_
/************************************************************************
*                           语言包配置节点类
*
*            配置节点可以是一个字符串或者是文字包，这取决于getType的类型。
*
*   此类的内存管理方式为使用MemoryContainer<char>进行，因此意味着内存将不会被释放，
* 除非构造时传递的内存管理器已经被释放。
*
************************************************************************/
class LangSection;
class LangSectionTable;

class LangSection
{
public:
	enum ElementType
	{
	    eInvalid,
	    ePacket,	//类型是一个分类
	    eText,		//类型是一个文字包
	};

public:
	LangSection();
	LangSection(MemoryContainer<char>*);
	~LangSection();

	//获取节点类型
	inline ElementType getType()
	{
		return type_;
	}
	//获取字符串值
	inline const char* getText()
	{
		return data_.str_;
	}
	//获取名为sName的文字包节点
	LangSection* getSection(const char* name);
	//设置节点为字符串
	void setText(const char* str);
	//设置节点为文字包
	void setPacket(size_t len);
	//添加一个节点，此前必须调用setPacket设置当前节点类型为文字包
	LangSection* addSection(const char* name);

protected:
	//清空节点数据
	void clear();
	//内存申请函数，作用与c函数中的realloc实现相同，实现申请、扩展以及释放内存
	void* Realloc(void* p, size_t s);

protected:
	ElementType type_;	//节点的类型
	union
	{
		char*			str_;
		LangSectionTable*	pack_;
	}			data_;		//节点的数据
	MemoryContainer<char>*	alloctor_ptr_;
};

class LangSectionTable :
	public BZHashTable<LangSection>
{
public:
	typedef BZHashTable<LangSection> Inherited;

public:
	LangSectionTable(size_t len);
	~LangSectionTable();
};

#endif


