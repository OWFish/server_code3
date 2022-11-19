#pragma once

/***************************************************************
*
*					��Բ�ͬ�汾�Լ���Ӫ�̶���ͬ�ĺ궨�����ö�ȡ��
*
*   ��VSPDef.txt�ж�����Բ�ͬ��Ϸ�汾����Ϸ��Ӫ�̶���ͬ������ֵ��ʹ������
* ��Ϸ�ڱ��ְ汾����һ�µ�����¿�����������ļ��еĶ�������ز�ͬ�������ļ���
* ����ĳЩ�����Ƿ����ȵȡ�
*   VSP����ͬʱҲ��Ϊ��Ϸ�е�һ�ֳ�������ֵ�ṩ����
*
***************************************************************/

class CVSPDefinition
{
public:
	/* �����������ݽṹ���� */
	typedef struct Definition
	{
		char* sDefName;	//��������
		char* sDefValue;	//����ֵ
	}*PDEFINITION;

public:
	CVSPDefinition();
	~CVSPDefinition();

	/*
	* Comments: ͨ�����ƻ�ȡ����ֵ
	* Param const char* sDefName: ����
	* @Return const char*: �������ָ�����Ƶĳ����򷵻س�������ֵ���򷵻�NULL
	*/
	const char* GetDefinition(const char* sDefName) const;
	/*
	* Comments: �����еĶ�����Ϊ�����ӵ��ű�Ԥ��������
	* Param LuaPreProcessor & preProcessor:
	* @Return void:
	*/
	void RegisteToPreprocessor(LuaPreProcessor &pp);
	/*
	* Comments: ���ļ����س�������
	* Param const char* sFilePath: �ļ�·���������ǻ��ڹ���Ŀ¼�����·��Ҳ�����Ǿ���·��
	* @Return bool: ���سɹ��򷵻�true���򷵻�false��
	*/
	bool LoadDefinitions(const char* sFilePath);
	/*
	* Comments: ����һ���������壬������ӡ�ɾ���Լ��޸Ķ���
	* Param const char* sDefName: �������ƣ�����Ϊ�գ�
	* Param const char* sDefValue:����ֵ��Ϊ�����ʾɾ���˶�����򵱶����������¶��壬����������Ӷ���
	* @Return void:
	*/
	void SetDefinition(const char* sDefName, const char* sDefValue);

protected:
	/*
	* Comments: ������ж�������ͷ��ڴ�
	* @Return void:
	*/
	void ClearDefinitions();

private:
	container::Vector<Definition> m_Defines;
};

