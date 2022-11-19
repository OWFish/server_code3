#ifndef _DB_PROTO_H_
#define _DB_PROTO_H_


//��������汾��
#define DBEGN_KN_VERION			MAKEFOUR(2, 10, 11, 20)
//������������ݽṹ�汾
#define	DB_KRN_VERSION				0x0101


/* �������ݷ��������ڽ�ɫ������ɾ������ѯ�ȵ����ݰ���ʽ
*************************************/
//�����ǰ������Ͷ���


//��ѯ��ɫ�б�������
typedef  struct  tagQueryActorListReq
{
	uint16_t		CmdId;			//���ݰ�������
	int			AccountId;		//�ʻ�id
} QUERYACTORLISTREQ, *PQUERYACTORLISTREQ;

typedef struct
{
	UINT 	ActorId;//��ɫid
	//�����Ǹý�ɫ������ֵ���ݶ�
	char	ActorName[SrvDef::ACTOR_NAME_BUFF_LENGTH];
	int		Icon;
	int		Sex;				//�Ա�
	int		Level;			//�ȼ�
	int 	Job;			//ְҵ�ı���
	int		Zy;				//��Ӫ����
} Actors;

//��ѯ��ɫ�б�Ļ�Ӧ����
typedef  struct  tagQueryActorListResp
{
	uint16_t  CmdId;			//���ݰ�������
	int		AccountId;		//�ʻ�id
	char 	Count;             //��ɫ����,С��0��ʾ��ѯʧ��
	// ������Count��Actors��
	//Actors[Count];
} QUERYACTORLISTRESP, *PQUERYACTORLISTRESP;

//������ɫ�������
typedef  struct  tagCreateActorDataReq
{
	uint16_t	CmdId;			//���ݰ�������   uint16_t
	char	Namelen;
	char	ActorName[SrvDef::ACTOR_NAME_BUFF_LENGTH];		//��ɫ����
	char	Sex;				//�Ա�
	char 	Job;			//ְҵ�ı���
	char	Icon;              //ͷ��
	uint8_t	Zy;
	//�������Բ��ӵ����ݰ��У�����Ĭ��ֵ
} CREATEACTORDATAREQ, *PCREATEACTORDATAREQ;

//������ɫ�Ļ�Ӧ��
typedef  struct  tagCreateActorDataResp
{
	uint16_t			CmdId;			//���ݰ�������
	UINT 			ActorId;	// ���ret Ϊ0,����ֶα�ʾ�´����Ľ�ɫid�������ֶν��û����
	char			Ret;//������ɫ�Ľ����0 ��ʾ�ɹ�������Ϊ������
} CREATEACTORDATARESP, *PCREATEACTORDATARESP;

//ɾ����ɫ�������
typedef  struct  tagDeleteActorDataReq
{
	uint16_t	CmdId;			//���ݰ�������
	UINT 	Actoid;//��ɫid
} DELETEACTORDATAREQ, *PDELETEACTORDATAREQ;

//ɾ����ɫ�Ļ�Ӧ��
typedef  struct  tagDeleteActorDataResp
{
	uint16_t		CmdId;			//���ݰ�������
	UINT 		Actorid;//��ɫid
	char		Ret;//ɾ����ɫ�Ľ����0��ʾɾ���ɹ�������Ϊ������
} DELETEACTORDATARESP, *PDELETEACTORDATARESP;

//	������Ϸ֪ͨ��
typedef  struct  tagEnteyGameReq
{
	uint16_t	CmdId;					//���ݰ�������, ENTRYGAMEREQ_CMD
	UINT	Actorid;			//����Ľ�ɫid
} ENTRYGAMEREQ, *PENTRYGAMEREQ;

//�߼���������Ϣ��
typedef  struct  tagEnteyGameResq
{
	uint16_t	CmdId;			//���ݰ�������, ENTRYGAMERESP_CMD
	char 	szIP[128];		//0 ��β���ַ���
	int 	Port;
	char	Ret;				//��Ӧ�Ľ�����Ƿ���Խ�����Ϸ��0��ʾ��ȷ
} ENTRYGAMERESP, *PENTRYGAMERESP;


/************************************/

/*  SQL��ѯ��䶨��
 *******************************************/
//�����ݿ��м��ؽ�ɫ���ƹ��˱�

#define szSQLSP_GetFilterNames					"call getdenycharnames()" //��ѯ�������δ��б�
//�ͻ���������ݵ�SQL��ѯ
#define szSQLSP_CheckCreateCharCountryFlag		"call checkcreatecharcountryflag(%d)"//��ѯ�������Ĺ����б���־λ��Ϊ�������Ĺ��ұ�
#define  szSQLSP_ClientQueryChar					"call clientquerycharactors(%d,\"%s\")"//��ѯ��ɫ���ض����������˺��б�
#define  szSQLSP_GetAvailableCharactorCountInServer "call getavailablecharactorcountinserver(%d, \"%s\")" //��ѯ��ɫ���ض��������Ľ�ɫ����
#define  szSQLSP_GetCharactorIdByName				"call getcharactoridbyname(\"%s\",%d)"//ͨ����ɫ���Ʋ�ѯ��ɫID

#define  szSQLSP_UpdateActorScriptData			"update actorvariable set `variable`="//���½�ɫ��2��������
#define  szSQLSP_LoadActorScriptData             "select variable from actorvariable where actorid=%d" //��ȡ��ҵĶ�������

//���ݿͻ��˽�ɫ֪ͨ������ݵ�SQL��ѯ
#define  szSQLSP_LoadCharNotify					"call loadcharnotify(%d)"//��ѯ��ɫ��һ��֪ͨ����
#define  szSQLSP_AddCharNotify						"call addcharnotify(%d,\"%s\",\"%s\")"//���һ����ɫ֪ͨ����(EXEC)
#define  szSQL_DelCharNotify						"delete from charnotify where idx=%d"//ɾ��һ����ɫ֪ͨ����(EXEC)

#define  szSQLSP_RenameCharactor					"call renamecharactor(%d,\"%s\")"//ִ�н�ɫ������

#define  szSQLSP_DeleteCharMsg						"call deletecharmsg(%d,%lld)"	//ɾ����ɫ��һ����Ϣ

//��Ϣϵͳ
#define  addcharmsg								"call addcharmsg(%d,%d,%s,%s,"
#define  loadcharmsglist							"call loadcharmsglist(%d,%lld)"//��ȡ��ɫ��������Ϣ

#define  szSQLSP_CleanGemItemData					"call cleangemitems(%d)"
#define  szSQLSP_SaveGemItemData					"insert into actorgemitem(actorid, uid, gemid, level, exp, ss, grade, quality, scattack, scdefence, scagility, schp, smithcount, smith1, smith2, smith3, smith4, gemscore, wish, reserve1) values"
#define  szSQLSP_CleanGemSuitData					"call cleangemsuit(%d)"

#define  sql_updatevariable				"update actorvariable set %s ="		// ���¶���������
#define  sql_loadvariable				"select %s from actorvariable where actorid=%d"	// ��ȡ��Ҷ���������

#define  updateglobalvariable				"update globalvariable set %s ="		// ���¶���������
#define  loadglobalvariable				"select %s from globalvariable where serverid=%d"	// ��ȡ����������

#define  loadgmcmd						"call loadgmcmd(%d);"
#define	delgmcmd						"call delgmcmd(%d);"

#define loadgiftitem					"call loadgiftitem()"
#define loadgiftconfig					"call loadgiftitemconfig()"


#define updateactorlogout	    	"update actors set actorname=\"%s\", totalpower=%lld, rankpower=%lld where actorid=%d;"
#define updateactorlogin			"update actors set status = (status | 8) where actorid = %d;"

#define loadgmquestions   "call loadgmquestions(%d)" //��ȡgm����
#define loadgmquestion     "call loadgmquestion(%lld)"

#define updategmquestion  "call updategmquestion(%lld)"


#define initdb "call initdb(%d)" //��ʼ�����ݿ�
#define saveactormisc "update actormisc set %s=%d where actorid=%d"
#define loadactormisc "select %s from actormisc where actorid=%d"
#define insertmisc	  "insert into actormisc(actorid) values(%d)"


//�¿�ʼ����
#define sql_updateactor "call updateactor(%d,%d,%d,%d,%d,%d,%d,%d,%d,%lld,%lld,%d,%d,%d,%d,%d,%d,%d,%d,%d)"
#define sql_loadactorbasic "select * from actors where actorid=%d and (status & 2)=2" //��ѯ��ɫ��������
#define sql_loadrole "select * from roles where actorid=(%d)"
#define sql_cleanrole "update roles set `actorid` = 0 where `actorid` = %d"
#define sql_saverole "insert into roles(actorid,roleid,job,sex,power,skill_data,wing_data,equips_data,ex_rings_data,jingmai_data,loogsoul_data,fuwen_data,heirloom,weapon_soul_id) values "
#define sql_cleanitem "update items set `actorid` = 0 where `actorid` = %d and `bag_type` = %d"
#define sql_realcleanitem "delete from items  where `actorid` = 0;"
#define sql_saveitem "insert into items(uid, actorid, bag_type, id, count, attrs) values "
#define sql_loaditem "select * from items where actorid=(%d) and bag_type=(%d)"

#define sql_cleanmail "update mails set actorid = 0 where actorid = %d"
#define sql_savemail "insert into mails(uid, actorid, readstatus, sendtime, head, context, award, awardstatus) values "
#define sql_loadmail "select * from mails where actorid=(%d)"
#define sql_realcleanmail "delete from mails  where `actorid` = 0;"

// 
#define  loadguildmgrdata "call loadguildmgrdata(%d)" // ��ȡ���ɵĹ�����Ϣ
#define  loadguildallname "call loadguildallname(%d)" // ��ȡ���ɵĹ�����Ϣ

#define  loadguildmembers "call loadguildmembers(%d)" //��ѯ�����Ա����
#define  addguildmember							"call addguildmember(%d,%d,%d)"//��ӹ����Ա(EXEC)
#define  delguildmember							"call delguildmember(%d)"//ɾ�������Ա(EXEC)
#define  updateguildmember						"call updateguildmember(%d,%d,%d,%d,%d)"//���¹����Ա(EXEC)
#define  loadcharguild							"call loadcharguild(%d)" //��ȡ�����Ա��Ϣ
#define  createguild							"call createguild(%d,\"%s\",%d)"//��������
#define  deleteguild							"call deleteguild(%d)"//ɾ������
#define  updateguildbasedata					"call updateguildbasedata(%d,%d,\"%s\")"//���¹����������
#define  updateguildvar							"call updateguildvar(%d,%d,\""
#define	 loadguildlog							"call loadguildlog(%d)" //��ȡ�����¼�
#define  addguildlog							"call addguildlog(%d,%d,%d,%d,%d,%d,\"%s\",\"%s\")" //��ӹ����¼�
#define  delguildlog							"call delguildlog(%d,%d)" //ɾ�������¼�
#define sql_cleanguildchat "update guildchat set `guildid` = 0 where `guildid` = %d" //ɾ�����������¼
#define sql_saveguildchat "insert into guildchat(guildid, type, date, actorid, content) values " //���湫�������¼

#define sql_saveguildstorelog "insert ignore into guildstorelog(logdate, guildid, actorid, itemid) values " //���湫���̵��¼

#define addauctionitem "insert into auction(id,addtime,guildendtime,globalendtime,owners,guildid,auctionid,serverid,flag) values(%d,%d,%d,%d,'%s',%d,%d,%d,%d)"
#define delauctionitem "delete from auction where id=%d"
#define updateauctionitem "update auction set `guildendtime`=%d,`globalendtime`=%d,`bid`=%d,`bidder`=%d,`gbidder`=%d,`flag`=%d,`hylimit`=%d,`yblimit`=%d where `id`=%d"

#define  loadfriends					"call loadfriends(%d)"	// ��ȡ���ѵ�����
#define  updatefriends				"call updatefriend(%d,%d,%d,%d,%d)"	// ���ӻ��޸ĺ�������
#define  delfriend					    "call delfriend(%d,%d,%d)"	// ɾ������

/*************************************************************    ˽������      ***********************************************************************/
#define  LoadPrivateChat			"call loadprivatechat(%d)"					// ��ȡ˽�ĵ����� ( �Լ�id �� Ŀ��id )
#define  AddPrivateChat				"call addprivatechatdata(%d,%d,%d,'%s',%d)"	// ����˽������ ( �Լ�id ������id �� ����ʱ�� �� �������� �� �Ƿ����Լ�����)
#define  DelPrivateChat				"call delprivatechatdata(%d,%d,%d)"				// ɾ��˽������
#define  BatchDelPrivateChat		"call batchdelprivatechatdata(%d,%d)"				// ����ɾ��˽������
/*************************************************************    ˽������      ***********************************************************************/

/*************************************************************    �������������      ***********************************************************************/
#define  LoadLoadPVMlayer			"call loadpvmplayerdata(%d)"					// ��ȡ�������������
#define  UpdatePVMlayer				"call updatepvmplayerdata(%d,%d,%d,%d)"					// ���¾������������
#define sql_replacechallengerecord  "REPLACE INTO pvmchallengerecord (actorid,recorddata) VALUES " //���¾�������ս��¼
#define LoadChallengeRecord			"select * from pvmchallengerecord where actorid=(%d)"	//������Ҿ�������ս��¼
#define UpdateRecord				"call UpdateChallengeRecord(%d,\"%s\")"
/*************************************************************    �������������      ***********************************************************************/

/*************************************************************    �һ������������      ***********************************************************************/
#define saveplayerafkdata				"call updateplayerafkdata(%d,%d,'%s')"
#define loadplayerafkdata				"call loadplayerafkdata(%d)"
/*************************************************************    �һ������������      ***********************************************************************/

//��Ϣϵͳ
#define  addcharmsg								"call addcharmsg(%d,%d,%s,%s)"
#define  loadcharmsglist							"call loadcharmsglist(%d,%lld)"//��ȡ��ɫ��������Ϣ
#define addchatmonitoring                         "call addchatmonitoring(%d,%d,%d,%d,\"%s\",\"%s\",\"%s\",%d,%d)"

#endif
