#ifndef _SERVER_DEF_H_
#define _SERVER_DEF_H_

/*****************************************************
*
*	�����ͨ�ö����ļ�
*
*****************************************************/
#include "os_def.h"


#define TAG_VALUE 0xCCEE		   //Ĭ�ϵİ��Ŀ�ͷ��2���ֽ�
#define SMALL_HEAD

#pragma pack(push,4)
typedef struct
{
	int tag;
	int len;
	struct 
	{
		uint16_t dataSum;
		uint16_t hdrSum;
	} EncodePart;
#ifndef SMALL_HEAD
	union
	{
		struct
		{
			int recvTime;	// ���ؽ�������ʱ��
			int sendTime;	// ���ط�������ʱ��
		}s;
		int64_t reserve; // ʱ��㣬�������ؽ��ܵ��ͻ������ݺ���ϵ�ʱ�����
	}u;
#endif
}DATAHEADER;


typedef struct
{
	uint64_t socket_;
	uint16_t index_;
	uint16_t gate_id_;
}NetId;

#pragma pack(pop)

typedef int ActorId;
typedef int64_t FuBenUId;

// ���ڲ������紫�����ܵ�����id

#define 	TEST_GATEAY_CODE  0xfabc1254adee
#define		TEST_SERVER_CODE  0xffbb56facedd
#define		TEST_SERVER_CODE1 0x12698745200d
namespace SrvDef
{
	/* ���������Ͷ��� */
	typedef enum tagServerType
	{
		InvalidServer = 0,	//δ�������������
		LogServer = 2,		//��־������
		SessionServer = 4,	//�Ự������
		T_DBServer = 5,		//���ݷ�����
		T_GameServer = 6,	//��Ϸ������	
		GateServer = 1,		//���ط�����
	}SERVERTYPE;

	
	/* ��ȡ���������������ַ��� */
	inline const char* getServerTypeName(int eServerType)
	{
		switch(eServerType)
		{
		case GateServer: return ("gateway");
		case LogServer: return ("log");
		case SessionServer: return ("login");
		case T_DBServer: return ("db");
		case T_GameServer: return ("game");
		default: return ("unknow");
		}
	}

	/******
	 * ������ע��ṹ�������������ӵ���һ����������
	 * ��Ҫ����ע������������ݽṹ�Ա�ע���������
	 * ע��������ɹ���ſ�����ͨ�š�
	****************************************************/
	typedef struct tagServerRegistData
	{
		static const int GT_ID = 0x12AA66CA;
		int			GameType;		//��ϷID���̶�Ϊ0x12AA66CA
		int			ServerType;		//���������ͣ�ֵΪSERVERTYPEö�������е�ö��ֵ
		int			ServerIndex;	//������Ψһ��ţ���������Ž�����Ϸ�����������壩
		int			Recv1;
		char		ServerName[64];	//���������ƣ������0��ֹ��
	}SERVER_REGDATA, *PSERVER_REGDATA;


	//�����ַ������ݳ���
	static const int MAX_ACCOUNT_NAME_LENGTH  = 80;	//�����˻����ֳ���
	static const int ACCOUNT_LENGTH = 81;  //�˻���buff����

	typedef char ACCOUNT[ACCOUNT_LENGTH];

	static const int MAX_ACTOR_NAME_LENGTH  = 32;   //����������ֵĳ���
	static const int ACTOR_NAME_BUFF_LENGTH = 33;   //������ֵ�buff����
	
	typedef char ACTORNAME[ACTOR_NAME_BUFF_LENGTH]; //��ҵ�����

	static const int MAX_PASSWD_LENGTH		= 32;    //�������볤��
	static const int MAX_GUILD_NAME_LENGTH	= 32;    //���Ĺ��������

	
	/***
	*  ��Ϸ����·�ɱ�ṹ
	*******************************************/
	typedef struct tagGameServerRoute
	{
		int		nServerIndex;	//������ID
		int		nRouteCount;	//·�ɵ�ַ����
		struct
		{
			char	sHost[124];	//��������ַ��֧��������
			int		nPort;		//�������˿�
		}	RouteTable[16];		//·�ɵ�ַ��
	}GAMESERVERROUTE, *PGAMESERVERROUTE;

}


	
#endif
