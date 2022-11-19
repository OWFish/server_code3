#ifndef _DB_PROTO_H_
#define _DB_PROTO_H_


//数据引擎版本号
#define DBEGN_KN_VERION			MAKEFOUR(2, 10, 11, 20)
//数据引擎的数据结构版本
#define	DB_KRN_VERSION				0x0101


/* 定义数据服务器关于角色创建、删除、查询等的数据包格式
*************************************/
//以下是包的类型定义


//查询角色列表的请求包
typedef  struct  tagQueryActorListReq
{
	uint16_t		CmdId;			//数据包的类型
	int			AccountId;		//帐户id
} QUERYACTORLISTREQ, *PQUERYACTORLISTREQ;

typedef struct
{
	UINT 	ActorId;//角色id
	//以下是该角色的属性值，暂定
	char	ActorName[SrvDef::ACTOR_NAME_BUFF_LENGTH];
	int		Icon;
	int		Sex;				//性别
	int		Level;			//等级
	int 	Job;			//职业的编码
	int		Zy;				//阵营编码
} Actors;

//查询角色列表的回应包包
typedef  struct  tagQueryActorListResp
{
	uint16_t  CmdId;			//数据包的类型
	int		AccountId;		//帐户id
	char 	Count;             //角色数量,小于0表示查询失败
	// 后面是Count个Actors包
	//Actors[Count];
} QUERYACTORLISTRESP, *PQUERYACTORLISTRESP;

//创建角色的请求包
typedef  struct  tagCreateActorDataReq
{
	uint16_t	CmdId;			//数据包的类型   uint16_t
	char	Namelen;
	char	ActorName[SrvDef::ACTOR_NAME_BUFF_LENGTH];		//角色名称
	char	Sex;				//性别
	char 	Job;			//职业的编码
	char	Icon;              //头像
	uint8_t	Zy;
	//其他属性不加到数据包中，采用默认值
} CREATEACTORDATAREQ, *PCREATEACTORDATAREQ;

//创建角色的回应包
typedef  struct  tagCreateActorDataResp
{
	uint16_t			CmdId;			//数据包的类型
	UINT 			ActorId;	// 如果ret 为0,则该字段表示新创建的角色id，否则本字段结果没意义
	char			Ret;//创建角色的结果，0 表示成功，否则为错误码
} CREATEACTORDATARESP, *PCREATEACTORDATARESP;

//删除角色的请求包
typedef  struct  tagDeleteActorDataReq
{
	uint16_t	CmdId;			//数据包的类型
	UINT 	Actoid;//角色id
} DELETEACTORDATAREQ, *PDELETEACTORDATAREQ;

//删除角色的回应包
typedef  struct  tagDeleteActorDataResp
{
	uint16_t		CmdId;			//数据包的类型
	UINT 		Actorid;//角色id
	char		Ret;//删除角色的结果，0表示删除成功，否则为错误码
} DELETEACTORDATARESP, *PDELETEACTORDATARESP;

//	进入游戏通知包
typedef  struct  tagEnteyGameReq
{
	uint16_t	CmdId;					//数据包的类型, ENTRYGAMEREQ_CMD
	UINT	Actorid;			//进入的角色id
} ENTRYGAMEREQ, *PENTRYGAMEREQ;

//逻辑服务器信息包
typedef  struct  tagEnteyGameResq
{
	uint16_t	CmdId;			//数据包的类型, ENTRYGAMERESP_CMD
	char 	szIP[128];		//0 结尾的字符串
	int 	Port;
	char	Ret;				//回应的结果，是否可以进入游戏，0表示正确
} ENTRYGAMERESP, *PENTRYGAMERESP;


/************************************/

/*  SQL查询语句定义
 *******************************************/
//从数据库中加载角色名称过滤表

#define szSQLSP_GetFilterNames					"call getdenycharnames()" //查询名称屏蔽此列表
//客户端相关数据的SQL查询
#define szSQLSP_CheckCreateCharCountryFlag		"call checkcreatecharcountryflag(%d)"//查询允许创建的国家列表（标志位作为允许创建的国家表）
#define  szSQLSP_ClientQueryChar					"call clientquerycharactors(%d,\"%s\")"//查询角色在特定服务器的账号列表
#define  szSQLSP_GetAvailableCharactorCountInServer "call getavailablecharactorcountinserver(%d, \"%s\")" //查询角色在特定服务器的角色数量
#define  szSQLSP_GetCharactorIdByName				"call getcharactoridbyname(\"%s\",%d)"//通过角色名称查询角色ID

#define  szSQLSP_UpdateActorScriptData			"update actorvariable set `variable`="//更新角色的2进制数据
#define  szSQLSP_LoadActorScriptData             "select variable from actorvariable where actorid=%d" //获取玩家的二进制数

//数据客户端角色通知相关数据的SQL查询
#define  szSQLSP_LoadCharNotify					"call loadcharnotify(%d)"//查询角色下一个通知数据
#define  szSQLSP_AddCharNotify						"call addcharnotify(%d,\"%s\",\"%s\")"//添加一个角色通知数据(EXEC)
#define  szSQL_DelCharNotify						"delete from charnotify where idx=%d"//删除一个角色通知数据(EXEC)

#define  szSQLSP_RenameCharactor					"call renamecharactor(%d,\"%s\")"//执行角色重命名

#define  szSQLSP_DeleteCharMsg						"call deletecharmsg(%d,%lld)"	//删除角色的一条消息

//消息系统
#define  addcharmsg								"call addcharmsg(%d,%d,%s,%s,"
#define  loadcharmsglist							"call loadcharmsglist(%d,%lld)"//读取角色的所有消息

#define  szSQLSP_CleanGemItemData					"call cleangemitems(%d)"
#define  szSQLSP_SaveGemItemData					"insert into actorgemitem(actorid, uid, gemid, level, exp, ss, grade, quality, scattack, scdefence, scagility, schp, smithcount, smith1, smith2, smith3, smith4, gemscore, wish, reserve1) values"
#define  szSQLSP_CleanGemSuitData					"call cleangemsuit(%d)"

#define  sql_updatevariable				"update actorvariable set %s ="		// 更新二进制数据
#define  sql_loadvariable				"select %s from actorvariable where actorid=%d"	// 获取玩家二进制数据

#define  updateglobalvariable				"update globalvariable set %s ="		// 更新二进制数据
#define  loadglobalvariable				"select %s from globalvariable where serverid=%d"	// 获取二进制数据

#define  loadgmcmd						"call loadgmcmd(%d);"
#define	delgmcmd						"call delgmcmd(%d);"

#define loadgiftitem					"call loadgiftitem()"
#define loadgiftconfig					"call loadgiftitemconfig()"


#define updateactorlogout	    	"update actors set actorname=\"%s\", totalpower=%lld, rankpower=%lld where actorid=%d;"
#define updateactorlogin			"update actors set status = (status | 8) where actorid = %d;"

#define loadgmquestions   "call loadgmquestions(%d)" //获取gm问题
#define loadgmquestion     "call loadgmquestion(%lld)"

#define updategmquestion  "call updategmquestion(%lld)"


#define initdb "call initdb(%d)" //初始化数据库
#define saveactormisc "update actormisc set %s=%d where actorid=%d"
#define loadactormisc "select %s from actormisc where actorid=%d"
#define insertmisc	  "insert into actormisc(actorid) values(%d)"


//新开始定义
#define sql_updateactor "call updateactor(%d,%d,%d,%d,%d,%d,%d,%d,%d,%lld,%lld,%d,%d,%d,%d,%d,%d,%d,%d,%d)"
#define sql_loadactorbasic "select * from actors where actorid=%d and (status & 2)=2" //查询角色基本数据
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
#define  loadguildmgrdata "call loadguildmgrdata(%d)" // 获取帮派的管理信息
#define  loadguildallname "call loadguildallname(%d)" // 获取帮派的管理信息

#define  loadguildmembers "call loadguildmembers(%d)" //查询公会成员数据
#define  addguildmember							"call addguildmember(%d,%d,%d)"//添加公会成员(EXEC)
#define  delguildmember							"call delguildmember(%d)"//删除公会成员(EXEC)
#define  updateguildmember						"call updateguildmember(%d,%d,%d,%d,%d)"//更新公会成员(EXEC)
#define  loadcharguild							"call loadcharguild(%d)" //读取公会成员信息
#define  createguild							"call createguild(%d,\"%s\",%d)"//创建公会
#define  deleteguild							"call deleteguild(%d)"//删除公会
#define  updateguildbasedata					"call updateguildbasedata(%d,%d,\"%s\")"//更新公会基本数据
#define  updateguildvar							"call updateguildvar(%d,%d,\""
#define	 loadguildlog							"call loadguildlog(%d)" //获取公会事件
#define  addguildlog							"call addguildlog(%d,%d,%d,%d,%d,%d,\"%s\",\"%s\")" //添加公会事件
#define  delguildlog							"call delguildlog(%d,%d)" //删除公会事件
#define sql_cleanguildchat "update guildchat set `guildid` = 0 where `guildid` = %d" //删除公会聊天记录
#define sql_saveguildchat "insert into guildchat(guildid, type, date, actorid, content) values " //保存公会聊天记录

#define sql_saveguildstorelog "insert ignore into guildstorelog(logdate, guildid, actorid, itemid) values " //保存公会商店记录

#define addauctionitem "insert into auction(id,addtime,guildendtime,globalendtime,owners,guildid,auctionid,serverid,flag) values(%d,%d,%d,%d,'%s',%d,%d,%d,%d)"
#define delauctionitem "delete from auction where id=%d"
#define updateauctionitem "update auction set `guildendtime`=%d,`globalendtime`=%d,`bid`=%d,`bidder`=%d,`gbidder`=%d,`flag`=%d,`hylimit`=%d,`yblimit`=%d where `id`=%d"

#define  loadfriends					"call loadfriends(%d)"	// 读取好友的数据
#define  updatefriends				"call updatefriend(%d,%d,%d,%d,%d)"	// 增加或修改好友类型
#define  delfriend					    "call delfriend(%d,%d,%d)"	// 删除好友

/*************************************************************    私聊数据      ***********************************************************************/
#define  LoadPrivateChat			"call loadprivatechat(%d)"					// 读取私聊的数据 ( 自己id ， 目标id )
#define  AddPrivateChat				"call addprivatechatdata(%d,%d,%d,'%s',%d)"	// 增加私聊数据 ( 自己id ，好友id ， 聊天时间 ， 聊天内容 ， 是否是自己发送)
#define  DelPrivateChat				"call delprivatechatdata(%d,%d,%d)"				// 删除私聊数据
#define  BatchDelPrivateChat		"call batchdelprivatechatdata(%d,%d)"				// 批量删除私聊数据
/*************************************************************    私聊数据      ***********************************************************************/

/*************************************************************    竞技场玩家数据      ***********************************************************************/
#define  LoadLoadPVMlayer			"call loadpvmplayerdata(%d)"					// 读取竞技场玩家数据
#define  UpdatePVMlayer				"call updatepvmplayerdata(%d,%d,%d,%d)"					// 更新竞技场玩家数据
#define sql_replacechallengerecord  "REPLACE INTO pvmchallengerecord (actorid,recorddata) VALUES " //更新竞技场挑战记录
#define LoadChallengeRecord			"select * from pvmchallengerecord where actorid=(%d)"	//加载玩家竞技场挑战记录
#define UpdateRecord				"call UpdateChallengeRecord(%d,\"%s\")"
/*************************************************************    竞技场玩家数据      ***********************************************************************/

/*************************************************************    挂机练功玩家数据      ***********************************************************************/
#define saveplayerafkdata				"call updateplayerafkdata(%d,%d,'%s')"
#define loadplayerafkdata				"call loadplayerafkdata(%d)"
/*************************************************************    挂机练功玩家数据      ***********************************************************************/

//消息系统
#define  addcharmsg								"call addcharmsg(%d,%d,%s,%s)"
#define  loadcharmsglist							"call loadcharmsglist(%d,%lld)"//读取角色的所有消息
#define addchatmonitoring                         "call addchatmonitoring(%d,%d,%d,%d,\"%s\",\"%s\",\"%s\",%d,%d)"

#endif
