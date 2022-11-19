#pragma once


enum DBCacheType
{
	DBCacheType_Undefined = -1, // ���ش�������

	DBCacheType_ActorBasic = 0,	// ��ɫ��������
	DBCacheType_RoleData,		// �ӽ�ɫ����
	DBCacheType_ScriptData,
	DBCacheType_ItemBag,		// ���߰�
	DBCacheType_EquipBag,		// װ����
	DBCacheType_Mail,			// �ʼ�
	DBCacheType_Store,			// �̳�
	DBCacheType_Depot,			// �ֿ�
	DBCacheType_Guild,			// ����
	DBCacheType_TogHitEquip,	// �ϻ�װ��
	DBCacheType_CsScriptData,   //�����lua
	DBCacheType_ActorCache,   //���������

	DBCacheType_Max,
};

// ��ɫCache�������� (�ɵ� ���� ��ʱ������ ������̫��)
enum enActorCacheDataType
{	
	enCT_ActorBasicData,					// ��ɫ��������
	enCT_BagItemData,						// ��ɫ��������
	enCT_EquipItemData,						// ��ɫװ������
	enCT_DepotItemData,						// ��ɫ�ֿ�����		
	enCT_SkillData,							// ��������
	enCT_QuestData,							// ��������
	enCT_GuildData,							// ��������
	enCT_MiscData,							// ��������
	enCT_ScriptData,						// �ű�����������
	enCT_GemData,							// ��������
	enCT_MountData,							// ��������
	enCT_DmkjItemData,						//���οռ�ֿ�
	enCT_WingData,							//�������
	enCT_BuffData,							//buff����
	enCT_AchieveData,						// �ɾ�
	enCT_CaleData,							//����ͳ������
	enCT_FbCountData,						//ÿ����븱������
	enCT_PlotData,							// ����(�����ã�
	enCT_MiscStruct,						// �����Ӱ�����(�����ã�
	enCT_PetSkill,						// ���＼��
	enCT_EntrustItemData,				// ����ί�вֿ�
	enCT_PetItemData,						//����װ��
	enCT_PetCrossItem,					//���ﴳ�زֿ�
	enCT_CrossScriptData,				// ���ս�ű�����
	enCT_TongTianTaData,				//ͨ��������
	enCT_MijiItem,                    //�ؼ�����
	enCT_PetBase,						//����ϵͳ
	enCT_MarryBase,				  //����ϵͳ
	enCT_Max,						 // ����ɫCache��������
};