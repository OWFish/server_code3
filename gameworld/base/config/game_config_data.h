#ifndef _GAME_CONFIG_DATA_H_
#define _GAME_CONFIG_DATA_H_


/*******************************************************
*
*					�߼����������ṩ��
*
   ����ʵ�ֶ���Ϸ�߼���������������Ҫ�ĸ�����Ϸ�������ݵĶ�ȡ�Լ���
* ����������ȼ����������������ã������������ã������������õȡ�
*******************************************************/

class GameConfigData :
	public GameLuaConfig,
	ConfigLoader<GameConfigData>
{
public:
	typedef GameLuaConfig Inherited;
	GameConfigData();
	~GameConfigData();

	//�������л�������
	bool LoadConfig();
	static const char IncludeFileName[];
protected:
	void showError(const char* err);

private:
	MemoryContainer<char>	alloc_;
};

#endif

