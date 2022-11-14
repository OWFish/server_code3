#pragma once
#ifndef _ACTOR_DB_DATA_H_
#define _ACTOR_DB_DATA_H_

#include "common.h"
#include "common/datalist.h"
#include "common/property_set.h"

#pragma  pack(push,4)

/*
    玩家需要存盘的数据结构体
*/

using namespace SrvDef;

//tolua_begin 玩家角色数据
struct ActorBasicData
{
	unsigned int account_id; //账户的ID
	//ACCOUNT account_name;       //账户名字
	char account_name[ACCOUNT_LENGTH];       //账户名字
	int actor_id;  //角色id
	//ACTORNAME actor_name;  //名字
	char actor_name[ACTOR_NAME_BUFF_LENGTH];  //名字
	unsigned int server_idnex;

	unsigned char job; // 第一个角色职业
	unsigned char sex; // 第一个角色性别
	unsigned int headimage; //头像id 
	unsigned int level;		
	unsigned int exp;
	long long int fb_uid; //副本的uid
	unsigned int fb_scene_id; //副本内的场景id

	unsigned int create_time; //创建的时间
	unsigned int last_online_time; //最后在线时间
	unsigned long long last_login_ip;//上次登录的ip,还没支持

	unsigned int total_online;	//总的在线时长
	unsigned int daily_online;	//单日在线时长

	unsigned int bag_grid;	// 背包开启数量
	long long int gold;
	long long int yuanbao;
	long long int total_power;	// 总战力
	long long int rank_power;	//用于排行榜的战力
	unsigned int recharge;		// 充值元宝数
	unsigned int paid;			// 消费元宝数
	unsigned int chapter_level; // 所在关卡数  同时用于选择静态场景所在的场景
	unsigned int vip_level;		// vip等级
	int essence;		// 精魄
	int zhuansheng_lv; // 转生等级
	int zhuansheng_exp; // 转生修为
	unsigned char monthcard; //0为没购买1,为没过期,2为过期
	int tianti_level; //天梯级别
	int tianti_dan; //天梯段位
	int tianti_win_count; //天梯净胜
	int tianti_week_refres; //天梯周刷新


	long long int total_wing_power; //翅膀总战力
	long long int warrior_power; //战士战力
	long long int mage_power; //法师战力
	long long int taoistpriest_power; //道士战力
	int train_level; //神工(爵位)等级
	int train_exp; //神工(爵位)经验
	int total_stone_level; //宝石(精炼)总等级
	int total_zhuling_level;//铸造总等级
	int guild_id_; //公会ID
	char guild_name_[32];//工会名

	int zhan_ling_star; //
	int zhan_ling_stage; //
	int total_loongsoul_level;

	int prestige_exp;     //威望值
	long long int feats;  // 功勋

	unsigned int ex_ring_lv[8];//特戒等级,最高位为1时候出战

	long long int shatter; //符文碎片
	long long int spcshatter; //特殊符文碎片

	unsigned int knighthood_lv;//勋章等级

	long long int togeatter;//合击碎片
	int total_wing_lv; //翅膀总阶级
	long long int total_tujian_power;//图鉴总战力
	long long int total_equip_power;//装备总评分
	long long int togeatterhigh;//高级合击碎片

	unsigned char privilege_monthcard; //特权月卡， 未购买或已过期为0,1为没过期
	int reincarnate_lv; // 轮回等级
	int reincarnate_exp; // 轮回修为
	int field_chapter_level; //野外副本通关等级
	int field_chapter_progress;//野外副本挑战boss能量值
	int field_pk_mode;			//玩家的pk模式 0 和平模式  1行会模式 2全体攻击模式
	int field_last_fuben_id;	//最后一次野外副本id
	int	field_last_pos_x;		//最后野外地图坐标
	int field_last_pos_y;		//最后野外地图坐标
};

inline ActorBasicData* toActorBasicData(void* data) { return (ActorBasicData*)data; }
//tolua_end

struct ActorCsData {
	unsigned int actor_id;  //角色id

							// 跨服数据
	unsigned long long cw_fbhdl_sid_;	// 跨服战的位置信息,低4位是fuben的handle，高4位是战斗服的sid
	unsigned long long cw_scene_xy_;	// 跨服战的位置信息,低4位是场景id，高4位中的低高两位分别是x，y
	unsigned long long cw_static_pos_;	// 进入副本前，在普通场景的位置，低4位是场景id，高4位中的低高两位分别是x，y

	ActorCsData() {
		memset(this, 0, sizeof(ActorCsData));
	}
};

#pragma  pack(pop)

inline void ReadActorBasicData(ActorBasicData& actor_data, MYSQL_ROW &pRow, unsigned long *fieldLength)
{
	/*select level, exp, baggridcount, gold, yuanbao, totalpower, paid, fbhandle, sceneid,
	createtime, lastlogouttime, totalonline, dailyonline
	from actors
	where actorid = nactorid and(status & 2) = 2;
	*/
#define GetRowInt(i, data) sscanf(pRow[i], "%d", &(data))
#define GetRowUChar(i, data) int temp##i; sscanf(pRow[i], "%d", &(temp##i)); data = temp##i;
#define GetRowLInt(i, data) sscanf(pRow[i], "%lld", &(data))
#define GetRowString(i, data) sscanf(pRow[i], "%s", (data))
#define GetRowData(i,data) if(pRow[i]!=NULL) memcpy(&(data),pRow[i],fieldLength[i])


#ifdef _MSC_VER
#pragma message("todo 封装数据库流程")
#endif
	GetRowInt(0, actor_data.account_id);
	GetRowString(1, actor_data.account_name);
	GetRowInt(2, actor_data.actor_id);
	GetRowString(3, actor_data.actor_name);
	GetRowUChar(4, actor_data.job);
	GetRowUChar(5, actor_data.sex);
	
	//GetRowInt(6, actor_data.status);
	GetRowInt(7, actor_data.level);
	GetRowInt(8, actor_data.exp);
	GetRowInt(9, actor_data.server_idnex);

	//GetRowInt(10, actor_data.create_time);
	tm t;
	memset(&t, 0, sizeof(t));
	sscanf(pRow[10], "%d-%d-%d %d:%d:%d",
		&t.tm_year,
		&t.tm_mon,
		&t.tm_mday,
		&t.tm_hour,
		&t.tm_min,
		&t.tm_sec
		);
	t.tm_year -= 1900;
	t.tm_mon -= 1;
	actor_data.create_time = (unsigned int)mktime(&t);
	//GetRowInt(11, actor_data.updatetime);
	GetRowInt(12, actor_data.last_online_time);
	GetRowLInt(13, actor_data.last_login_ip);
	GetRowInt(14, actor_data.bag_grid);
	GetRowLInt(15, actor_data.gold);
	GetRowLInt(16, actor_data.yuanbao);
	GetRowLInt(17, actor_data.total_power);
	GetRowInt(18, actor_data.recharge);
	GetRowInt(19, actor_data.paid);
	GetRowLInt(20, actor_data.fb_uid);
	GetRowInt(21, actor_data.fb_scene_id);
	GetRowInt(22, actor_data.total_online);
	GetRowInt(23, actor_data.daily_online);
	GetRowInt(24, actor_data.chapter_level);
	GetRowInt(25, actor_data.vip_level);
	GetRowInt(26, actor_data.essence);
	GetRowInt(27, actor_data.zhuansheng_lv);
	GetRowInt(28, actor_data.zhuansheng_exp);
	GetRowUChar(29, actor_data.monthcard);
	GetRowInt(30, actor_data.tianti_level);
	GetRowInt(31, actor_data.tianti_dan);
	GetRowInt(32, actor_data.tianti_win_count);
	GetRowInt(33, actor_data.tianti_week_refres);


	GetRowLInt(34, actor_data.total_wing_power);
	GetRowLInt(35, actor_data.warrior_power);
	GetRowLInt(36, actor_data.mage_power);
	GetRowLInt(37, actor_data.taoistpriest_power);
	GetRowInt(38, actor_data.train_level);
	GetRowInt(39, actor_data.train_exp);
	GetRowInt(40, actor_data.total_stone_level);

	GetRowInt(41, actor_data.guild_id_);

	GetRowInt(42, actor_data.zhan_ling_star);
	GetRowInt(43, actor_data.zhan_ling_stage);
	GetRowInt(44, actor_data.total_loongsoul_level);
	GetRowLInt(45, actor_data.feats);
	GetRowData(46, actor_data.ex_ring_lv);
	GetRowLInt(47, actor_data.shatter);
	GetRowLInt(48, actor_data.spcshatter);
	GetRowInt(49, actor_data.knighthood_lv);
	GetRowLInt(50, actor_data.togeatter);
	GetRowLInt(51, actor_data.rank_power);
	GetRowInt(52, actor_data.total_wing_lv);
	GetRowLInt(53, actor_data.total_tujian_power);
	GetRowLInt(54, actor_data.total_equip_power);
	GetRowLInt(55, actor_data.togeatterhigh);
	GetRowInt(56, actor_data.total_zhuling_level);
	GetRowInt(57, actor_data.prestige_exp);
	GetRowInt(58, actor_data.reincarnate_lv);
	GetRowInt(59, actor_data.reincarnate_exp);
	//中间有两个 appid和pfid
	GetRowString(62, actor_data.guild_name_);
	GetRowInt(63, actor_data.headimage);
	GetRowInt(64, actor_data.field_chapter_level);
	GetRowInt(65, actor_data.field_chapter_progress);
	GetRowInt(66, actor_data.field_pk_mode);
	}


#endif

/*
//这个是（以前斩仙）和db通信的包
typedef struct tagActorDbData:
ActorProperty
{
ACTORNAME name;  //名字
unsigned nFbHandle; //副本的句柄，如果是0表示是普通的场景
unsigned nScenceID; //场景id
unsigned nEnterFbScenceID;
int       nEnterFbPos; //X 和y放在了一起

unsigned int nCreateTime; //创建的时间
unsigned long long lLastLoginIp ;//上次登录的ip,还没支持
unsigned int nLastLogoutTime; //上次的下线时间,这个表示上次在逻辑服务器的下线时间,minidate格式
unsigned int nFbTeamId; // 个人积分(无用)
ACCOUNT accountName;       //账户名字

unsigned int achieveTime;  //成就达成时间

unsigned int nAccountId; //账户的ID

int64_t csrevivepoint; //普通场景的复活点，是场景id,x,y的组合
int64_t fbrevivepoint; //副本场景的复活点，是场景id,x,y的组合
int64_t cityrevivepoint; //城镇的复活点，是场景id,x,y的组合
int free_baptize_;    // 免费洗炼的次数
int one_key_time_; // 剩余一键征友的次数
int mount_score_; // 坐骑评分
int friend_cong_;  // 好友祝贺的数据
int reserve_data_;  // 保留字段数据，可使用
unsigned int spirit_score_;   //玩家的精灵的总分
int	lianfuTeamId; //连服队伍id
// 跨服数据
unsigned long long cw_fbhdl_sid_;	// 跨服战的位置信息,低4位是fuben的handle，高4位是战斗服的sid
unsigned long long cw_scene_xy_;	// 跨服战的位置信息,低4位是场景id，高4位中的低高两位分别是x，y
unsigned long long cw_static_pos_;	// 进入副本前，在普通场景的位置，低4位是场景id，高4位中的低高两位分别是x，y

int war_team_id_; // 战队ID
int cross_honor_; // 跨服荣誉值
unsigned int upgrade_time_; //玩家等级升级的时间

unsigned int total_online_;	//总的在线时长
unsigned int daily_online_;	//单日在线时长

char quest[1000]; //任务的数据

char mis_for_php_[128]; //供后台查询的一些数据

tagActorDbData()
{
memset(this, 0, sizeof(tagActorDbData));
}
} ACTORDBDATA, *PACTORDBDATA;
*/
