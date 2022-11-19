#ifndef _ENTITY_SYSTEM_H_
#define _ENTITY_SYSTEM_H_

/***************************************************************
*                     ʵ�����ϵͳ����
* ʵ��Ĺ���ģ��,���������ϵͳ,������ϵͳ���̳��������
* ʵ�����ϵͳʵ��һ���ض��Ĺ��ܣ�����������Ϣ�ķַ�����
* ��Ϸ�еļ���,buff��������ض��Ĺ��ܶ����Ը�һ����ϵͳ����ʵ���һ��
***************************************************************/
class Entity;
/*
	SUBSYSTEMID ��ϵͳ��ID
	SonClass    ����
	EntityClass	����ϵͳ�����ص�ʵ������
*/
template<int SUBSYSTEMID, class SonClass, class EntityClass>
class EntitySystem
{
public:
	EntitySystem() : entity_(NULL), load_data_(false)
	{
		entity_ = NULL;
	}

	virtual ~EntitySystem()
	{
		load_data_ = false;
	}

	/*
	 *��ϵͳ�ĳ�ʼ����
	 *lpEntity ��ϵͳ������ʵ��ָ��
	 *data ��ʼ�������ݣ����û���� NULL
	 *size ��ϵͳ��ʼ�����ݵĳ��ȣ����û��������0
	*/
	inline bool Create(EntityClass* entity, void* data, size_t size)
	{
		entity_ = entity;
		return Initialize(data, size);
	}

	//��ϵͳ��ʼ��,����������Ҫ������ҵĴ�������
	virtual bool Initialize(void* /*data*/, size_t /*size*/)
	{
		return true;
	}

	/*
	* Comments: ���ݿⷵ������
	* Param int nCmd: �����룬�����������
	* Param DataPacketReader reader &: ��д��
	* @Return void:
	*/
	virtual void OnDbRetData(int /*nCmd*/, int /*nErrorCode*/, DataPacketReader& /*reader*/) {}

	/*
	*���̽ӿڣ������Ǵ��̵Ľṹָ��,�������̵�ϵͳ�Ͳ���ס�������ָ��
	*data ��Ҵ�������ָ��
	*/
	virtual void Save(ActorBasicData* /*pData*/) { }

	//����ڴ�
	virtual void Destroy() {};

	//��ȡ��ϵͳ��ID
	inline int GetSystemID() const
	{
		return SUBSYSTEMID;
	}

	/*
	 *�����������ݰ�
	 *nCmd �����ɵ���ϵͳ�������0��ʼ
	 *packet����������
	*/
	virtual void ProcessNetData(int /*nCmd*/, DataPacketReader& /*packet*/) {};

	//��ɫ����ϵͳ��ʼ����ϣ���ͻ��˷��ʹ������ǵ����ݰ��󣬵��øýӿ�
	virtual void OnEnterGame() {};
protected:
	EntityClass* entity_; //�����ϵͳ�������Ǹ�ʵ���,���ֵ���ʵ���ָ��
	bool load_data_;
};

#endif

