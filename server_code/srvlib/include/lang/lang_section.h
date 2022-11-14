#ifndef _LANG_SECTION_H_
#define _LANG_SECTION_H_
/************************************************************************
*                           ���԰����ýڵ���
*
*            ���ýڵ������һ���ַ������������ְ�����ȡ����getType�����͡�
*
*   ������ڴ����ʽΪʹ��MemoryContainer<char>���У������ζ���ڴ潫���ᱻ�ͷţ�
* ���ǹ���ʱ���ݵ��ڴ�������Ѿ����ͷš�
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
	    ePacket,	//������һ������
	    eText,		//������һ�����ְ�
	};

public:
	LangSection();
	LangSection(MemoryContainer<char>*);
	~LangSection();

	//��ȡ�ڵ�����
	inline ElementType getType()
	{
		return type_;
	}
	//��ȡ�ַ���ֵ
	inline const char* getText()
	{
		return data_.str_;
	}
	//��ȡ��ΪsName�����ְ��ڵ�
	LangSection* getSection(const char* name);
	//���ýڵ�Ϊ�ַ���
	void setText(const char* str);
	//���ýڵ�Ϊ���ְ�
	void setPacket(size_t len);
	//���һ���ڵ㣬��ǰ�������setPacket���õ�ǰ�ڵ�����Ϊ���ְ�
	LangSection* addSection(const char* name);

protected:
	//��սڵ�����
	void clear();
	//�ڴ����뺯����������c�����е�reallocʵ����ͬ��ʵ�����롢��չ�Լ��ͷ��ڴ�
	void* Realloc(void* p, size_t s);

protected:
	ElementType type_;	//�ڵ������
	union
	{
		char*			str_;
		LangSectionTable*	pack_;
	}			data_;		//�ڵ������
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


