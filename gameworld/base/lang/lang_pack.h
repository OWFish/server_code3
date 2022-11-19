#ifndef _LANGUAGE_TEXT_PACK_H_
#define _LANGUAGE_TEXT_PACK_H_

class LangPack :
	protected BaseLuaConfig,	//不要继承gameluaconfig
	public LangSection
{
public:
	typedef LangSection Inherited;
	typedef BaseLuaConfig Inherited2;

public:
	LangPack();
	~LangPack();

	//从文件加载语言包
	bool LoadFromFile(const char* fn);
protected:
	void showError(const char* err);
private:
	//将当前脚本表中的语言配置读取到Section中
	bool readLanguagePacket(LangSection& section);
	bool LoadTipMsg(const char* tn);
private:
	MemoryContainer<char>	allocator_;//语言包内存管理器
};

#endif

