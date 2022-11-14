#pragma once
#ifndef _ACTOR_DB_DATA_H_
#define _ACTOR_DB_DATA_H_

#include "common.h"
#include "common/datalist.h"
#include "common/property_set.h"

#pragma  pack(push,4)

/*
    �����Ҫ���̵����ݽṹ��
*/

using namespace SrvDef;

//tolua_begin ��ҽ�ɫ����
struct ActorBasicData
{
	unsigned int account_id; //�˻���ID
	//ACCOUNT account_name;       //�˻�����
	char account_name[ACCOUNT_LENGTH];       //�˻�����
	int actor_id;  //��ɫid
	//ACTORNAME actor_name;  //����
	char actor_name[ACTOR_NAME_BUFF_LENGTH];  //����
	unsigned int server_idnex;

	unsigned char job; // ��һ����ɫְҵ
	unsigned char sex; // ��һ����ɫ�Ա�
	unsigned int headimage; //ͷ��id 
	unsigned int level;		
	unsigned int exp;
	long long int fb_uid; //������uid
	unsigned int fb_scene_id; //�����ڵĳ���id

	unsigned int create_time; //������ʱ��
	unsigned int last_online_time; //�������ʱ��
	unsigned long long last_login_ip;//�ϴε�¼��ip,��û֧��

	unsigned int total_online;	//�ܵ�����ʱ��
	unsigned int daily_online;	//��������ʱ��

	unsigned int bag_grid;	// ������������
	long long int gold;
	long long int yuanbao;
	long long int total_power;	// ��ս��
	long long int rank_power;	//�������а��ս��
	unsigned int recharge;		// ��ֵԪ����
	unsigned int paid;			// ����Ԫ����
	unsigned int chapter_level; // ���ڹؿ���  ͬʱ����ѡ��̬�������ڵĳ���
	unsigned int vip_level;		// vip�ȼ�
	int essence;		// ����
	int zhuansheng_lv; // ת���ȼ�
	int zhuansheng_exp; // ת����Ϊ
	unsigned char monthcard; //0Ϊû����1,Ϊû����,2Ϊ����
	int tianti_level; //���ݼ���
	int tianti_dan; //���ݶ�λ
	int tianti_win_count; //���ݾ�ʤ
	int tianti_week_refres; //������ˢ��


	long long int total_wing_power; //�����ս��
	long long int warrior_power; //սʿս��
	long long int mage_power; //��ʦս��
	long long int taoistpriest_power; //��ʿս��
	int train_level; //��(��λ)�ȼ�
	int train_exp; //��(��λ)����
	int total_stone_level; //��ʯ(����)�ܵȼ�
	int total_zhuling_level;//�����ܵȼ�
	int guild_id_; //����ID
	char guild_name_[32];//������

	int zhan_ling_star; //
	int zhan_ling_stage; //
	int total_loongsoul_level;

	int prestige_exp;     //����ֵ
	long long int feats;  // ��ѫ

	unsigned int ex_ring_lv[8];//�ؽ�ȼ�,���λΪ1ʱ���ս

	long long int shatter; //������Ƭ
	long long int spcshatter; //���������Ƭ

	unsigned int knighthood_lv;//ѫ�µȼ�

	long long int togeatter;//�ϻ���Ƭ
	int total_wing_lv; //����ܽ׼�
	long long int total_tujian_power;//ͼ����ս��
	long long int total_equip_power;//װ��������
	long long int togeatterhigh;//�߼��ϻ���Ƭ

	unsigned char privilege_monthcard; //��Ȩ�¿��� δ������ѹ���Ϊ0,1Ϊû����
	int reincarnate_lv; // �ֻصȼ�
	int reincarnate_exp; // �ֻ���Ϊ
	int field_chapter_level; //Ұ�⸱��ͨ�صȼ�
	int field_chapter_progress;//Ұ�⸱����սboss����ֵ
	int field_pk_mode;			//��ҵ�pkģʽ 0 ��ƽģʽ  1�л�ģʽ 2ȫ�幥��ģʽ
	int field_last_fuben_id;	//���һ��Ұ�⸱��id
	int	field_last_pos_x;		//���Ұ���ͼ����
	int field_last_pos_y;		//���Ұ���ͼ����
};

inline ActorBasicData* toActorBasicData(void* data) { return (ActorBasicData*)data; }
//tolua_end

struct ActorCsData {
	unsigned int actor_id;  //��ɫid

							// �������
	unsigned long long cw_fbhdl_sid_;	// ���ս��λ����Ϣ,��4λ��fuben��handle����4λ��ս������sid
	unsigned long long cw_scene_xy_;	// ���ս��λ����Ϣ,��4λ�ǳ���id����4λ�еĵ͸���λ�ֱ���x��y
	unsigned long long cw_static_pos_;	// ���븱��ǰ������ͨ������λ�ã���4λ�ǳ���id����4λ�еĵ͸���λ�ֱ���x��y

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
#pragma message("todo ��װ���ݿ�����")
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
	//�м������� appid��pfid
	GetRowString(62, actor_data.guild_name_);
	GetRowInt(63, actor_data.headimage);
	GetRowInt(64, actor_data.field_chapter_level);
	GetRowInt(65, actor_data.field_chapter_progress);
	GetRowInt(66, actor_data.field_pk_mode);
	}


#endif

/*
//����ǣ���ǰն�ɣ���dbͨ�ŵİ�
typedef struct tagActorDbData:
ActorProperty
{
ACTORNAME name;  //����
unsigned nFbHandle; //�����ľ���������0��ʾ����ͨ�ĳ���
unsigned nScenceID; //����id
unsigned nEnterFbScenceID;
int       nEnterFbPos; //X ��y������һ��

unsigned int nCreateTime; //������ʱ��
unsigned long long lLastLoginIp ;//�ϴε�¼��ip,��û֧��
unsigned int nLastLogoutTime; //�ϴε�����ʱ��,�����ʾ�ϴ����߼�������������ʱ��,minidate��ʽ
unsigned int nFbTeamId; // ���˻���(����)
ACCOUNT accountName;       //�˻�����

unsigned int achieveTime;  //�ɾʹ��ʱ��

unsigned int nAccountId; //�˻���ID

int64_t csrevivepoint; //��ͨ�����ĸ���㣬�ǳ���id,x,y�����
int64_t fbrevivepoint; //���������ĸ���㣬�ǳ���id,x,y�����
int64_t cityrevivepoint; //����ĸ���㣬�ǳ���id,x,y�����
int free_baptize_;    // ���ϴ���Ĵ���
int one_key_time_; // ʣ��һ�����ѵĴ���
int mount_score_; // ��������
int friend_cong_;  // ����ף�ص�����
int reserve_data_;  // �����ֶ����ݣ���ʹ��
unsigned int spirit_score_;   //��ҵľ�����ܷ�
int	lianfuTeamId; //��������id
// �������
unsigned long long cw_fbhdl_sid_;	// ���ս��λ����Ϣ,��4λ��fuben��handle����4λ��ս������sid
unsigned long long cw_scene_xy_;	// ���ս��λ����Ϣ,��4λ�ǳ���id����4λ�еĵ͸���λ�ֱ���x��y
unsigned long long cw_static_pos_;	// ���븱��ǰ������ͨ������λ�ã���4λ�ǳ���id����4λ�еĵ͸���λ�ֱ���x��y

int war_team_id_; // ս��ID
int cross_honor_; // �������ֵ
unsigned int upgrade_time_; //��ҵȼ�������ʱ��

unsigned int total_online_;	//�ܵ�����ʱ��
unsigned int daily_online_;	//��������ʱ��

char quest[1000]; //���������

char mis_for_php_[128]; //����̨��ѯ��һЩ����

tagActorDbData()
{
memset(this, 0, sizeof(tagActorDbData));
}
} ACTORDBDATA, *PACTORDBDATA;
*/
