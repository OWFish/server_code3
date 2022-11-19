#ifndef _BASE_LUA_H_
#define _BASE_LUA_H_

/*****************************************************************
*                     LUA�ű����������
*	�ṩ�Խű��ļ��ء�������ע�ᡢ��������Լ��������õĹ����塣
*	���ڴ�������Ĳ�������Ӧ������showError�����Ա������δ���
*	�ű�������в����Ĵ���
*****************************************************************/
#include "memory/buffer_allocator.h"

class DataPacket;

class BaseLua
{
protected:
	//�������������
	virtual lua_State* createLuaVM();
	//�򿪻����⡣Ĭ�ϻ��base��string��math�Լ�table�⡣����true��ʾ�ɹ���
	virtual bool openBaseLibs();
	//ע�᱾�غ����⡣����true��ʾ�ɹ���
	virtual bool registLocalLibs();
	//���ýű��ĳ�ʼ����������������true��ʾû�д�����������δ�ṩ���ó�ʼ��������ʵ�ʹ��ܡ�
	virtual bool callInit();
	//���ýű���ж�غ�������������true��ʾû�д�����������δ�ṩ����ж�غ�����ʵ�ʹ��ܡ�
	virtual bool callFinal();
	//��ʾ�ű���������
	virtual void showError(const char* err);

	void SetErrDesc(const char* err);
protected:
	//��ʽ���������ݲ���ʾ����ʽ������������ַ����ĳ��ȱ�����Ϊ1024���ַ���
	void showErrorFormat(const char* fmt, ...);

	/*	�ű����ú���
		�ڽ������Լ�����������ջ����ôӺ����������ֱ�ӵ���lua_pcall����Ϊ�Ա㼯�д�����
		�����а����Ե��ú���ǰ��Ķ�ջƽ���顣
		��������true��ʾû�д���
	*/
	bool pcall(const int args, const int results, const int errfunc);

	//���ű����÷���ֵ�����nError��Ϊ�ɹ�ֵ�������������ݲ�����false����nError��ֵ��������m_nLastError�С�
	inline bool lcCheck(int err);

	/*
	* Comments: ����ű�Ϊ�ֽ���
	* Param lua_State * L:
	* Param const char * szContent: �ı���ʽ��lua�ű�����
	* Param DataPacket & packet: �����������
	* @Return bool:�ɹ�����true��ʧ�ܷ���false
	* @Remark:
	*/
	bool CompileLua(lua_State* L, const char* content, DataPacket& packet);

	/*
	* Comments: �����������Writer
	* Param lua_State * L: Lua״̬��
	* Param const void * p: ��д��Ķ���������
	* Param size_t size: ���������ݳ���
	* Param void * u: userData�� ������CDataPacket*
	* @Return int: �ɹ�����0��ʧ�ܷ�0
	* @Remark:
	*/
	static int StreamWriter(lua_State* L, const void* p, size_t size, void* u);

public:
	BaseLua();
	virtual ~BaseLua();

	/* ���ýű����ݣ���������º��Ĳ�����
	   1�����õ�ǰ�ű���ж�غ���
	   2��ɾ����ǰ�����������
	   3�����´��������
	   4���򿪻���������
	   5��ע�᱾�غ�����
	   6�����ó�ʼ������
	   �������sTextΪNULL��Ϊ���ַ���������ٵ�ǰ������Ҳ��������������
	   ��������true��ʾ���ýű��ɹ�������ֵ��ʾ��������
	*/
	bool setScript(const char* txt);

	/*
	* Comments: ���ö����ƽű����ݣ���ɴ󲿷ֲ���ͬsetScript(const char* sText)��ָʾ�ű������Ǳ�����Ķ������ֽ���
	* Param const char* szScript: �ű����ı���ʽ��
	* Param DataPacket& packet: ���bCompileΪtrue�����Ǳ����Ķ�����������������Ƕ�����������
	* Param const char* name: ��������ƣ�һ��ָ�ű��ļ�����
	* Param bool bCompile: Ϊtrue���ȱ���ű�Ϊ�����ƣ�Ȼ����ض����ƣ�����ֱ�Ӽ��ض���������
	* @Return bool: �ɹ�����true��ʧ�ܷ���false
	* @Remark:
	*/
	bool setBinScript(const char* script, DataPacket& packet, const char* name = NULL, bool compile = false);

	/*
	* Comments: ���ö����ƽű�
	* Param DataPacket & packet: �ű�����������
	* @Return bool:
	* @Remark:
	*/
	bool resetBinScript(DataPacket& packet);

	//��ȡ��������ڴ�ʹ��������λ���ֽ�
	int getAvaliableMemorySize();
	//�����������գ��ͷ��ڴ档�������ػ����˶����ֽڵ��ڴ�
	int gc();
	//��ȡ�����
	inline int getLastErrorNo()
	{
		return errno_;
	}
	//��ȡ��������
	inline const char* getLastErrorDesc() const
	{
		return err_desc_;
	}
	void SetLastFunc(const char* name)
	{
		STATIC_ASSERT(sizeof(last_fn_) > 8);	// ȷ�����Ͳ���char*
		if (name)
		{
			_STRNCPY_A(last_fn_, name);
		}
		else
		{
			last_fn_[0] = 0;
		}
	}
	//�жϽű����Ƿ������ΪsFnName�ĺ���
	bool FunctionExists(const char* fn);
protected:
	lua_State*		lua_;			//LUA���������
	int				errno_;		//��һ�������
	char*			err_desc_;		//��һ�����������
	char			last_fn_[128];	//��һ�ε��õĺ�������
};

#endif

