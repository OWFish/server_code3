#ifndef _LANGUAGE_TEXT_PACK_H_
#define _LANGUAGE_TEXT_PACK_H_

class LangPack :
	protected BaseLuaConfig,	//��Ҫ�̳�gameluaconfig
	public LangSection
{
public:
	typedef LangSection Inherited;
	typedef BaseLuaConfig Inherited2;

public:
	LangPack();
	~LangPack();

	//���ļ��������԰�
	bool LoadFromFile(const char* fn);
protected:
	void showError(const char* err);
private:
	//����ǰ�ű����е��������ö�ȡ��Section��
	bool readLanguagePacket(LangSection& section);
	bool LoadTipMsg(const char* tn);
private:
	MemoryContainer<char>	allocator_;//���԰��ڴ������
};

#endif

