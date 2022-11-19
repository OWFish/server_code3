#ifndef _CONFIG_DB_DATA_H_
#define _CONFIG_DB_DATA_H_

#define  MAX_NAME_LEN 64

#define MAX_LEN_BUFF 64

#define MAX_LEN_DESC 1024


//礼包数据结构
typedef struct staticaward
{
	int itemid;   		//礼包物品id
	int needgrid;		//需要格子数
	char itemname[MAX_NAME_LEN];
	char itemdesc[MAX_LEN_DESC];
	//int itype; //物品类型
	//int sell_type;
	int icon; //图标id
	//int color;
	//int dura;
	int dup;  //物品可以重叠数量
	//int colGroup;
	//int dealType;
	//int dealPrice;
	int itime;  //使用期限
	unsigned int flag; //插数据库时插入一个已经标好位的
	int grouptype;			//分组类型：没配置或0表示不按掉落组，给全部奖励,1表示按掉落组配
	int cond_cons_id;    	//开启条件，物品id,没有填0
	int cond_cons_count; 	  //开启条件，物品id数量,没有填0
	int cond_money_type;			//开启条件，消耗钱类型，没有填0
	int cond_money_count;	//	开启条件，消耗钱数量，没有填0
	char cond_value[MAX_LEN_BUFF]; //用字符串表示条件， c1=v1&c2=v2&c3=v3采用这种形式
} Staticaward_t;
//礼包配置
typedef struct staticawardconfig
{
	int giftitemid; //	礼包物品id
	int rewardtype;	//奖励类型 1 物品 2 金钱 ... 其余可自定义
	int contenttype;// 奖励内容的类型  目前只用作金钱类型
	int amount;    // 奖励数量 物品数量  或者  金额
	int itemid;		//奖励物的id，或物品id或技能id或
	int bind; 			//是否绑定，0表示非绑，1表示绑定
	int group;  				//	掉落组
	int rate;		//掉落概率
	int noworldrate;		//是否世界经验加成，0加成，1表示物无加成
	int quality;
	int strong;
}Staticawardconfig_t;





#endif

