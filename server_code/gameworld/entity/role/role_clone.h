#pragma once
#include "entity/entity.h"
#include "entity/creature.h"




//tolua_begin
struct RobotData
{
	int actor_id;
	char* name;
	int level;
	int job;
	int sex;
	int clothesId;
	int weaponId;
	int wingOpenState;
	int wingLevel;
	Attribute attrs;
	int skills[20];
	int headid;
	int holaid;
	int camp;
	int ismirror;

	RobotData(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

//tolua_end
class Role;

class RoleClone:
	public Creature
{

public:
	RoleClone();
	~RoleClone();
	virtual void CreateAppearData(DataPacket& appearPack);
public:
	void LoadFromRole(Role* role, unsigned int scene,int x,int y);
	void LoadFromRobot(RobotData* data, unsigned int scene, int x, int y);
	virtual inline ActorId GetActorId() { return actor_id; }
	virtual int GetId();
	virtual void LogicRun(int64_t curr_t);
	virtual inline char GetJob() { return job; }
	virtual void InitBasicAttribute();
	virtual void CalcAttributes();	//重新所有系统的属性
	virtual void CalcBattleAttributes(); //重新计算战斗系统属性
	virtual void OnDestroy();
	virtual void OnKilled(Creature* killer);
	virtual void SetAllAttrs(Attribute & attrs) { all_attrs_ = attrs; };
	virtual Attribute& GetAllAttrs() { return all_attrs_; };
	virtual void SetBuddy(int roleId, EntityHandle& hdl);
	virtual bool GetBuddy(int roleId, EntityHandle& hdl);
	virtual int getWeaponPeakLv(void) { return isPeak_ ? GodWeaponlevel_ : 0; }
	virtual int getDeathCount(void);
	virtual double GetAtkSum(void);//获取攻击力总和
	virtual int GetYuPeiLv(void) { return yupei_lv_; };
	virtual int64_t GetPrestigeExp(void) { return perstige_exp_; };
	virtual uint64_t GetSummitHandle();
	RoleClone* GetLiveByJob();
	virtual int GetHeadID() { return headid_; }
public:
	virtual bool HasHuShenShield(void) { return has_hushen_shield; }
	void SetAexringMon(int rid, Monster* mon);//关联一个特戒怪物
	void DelAexringMon(int rid);//删除一个特戒怪物,不回收
	void DelAexringMon(Monster* mon);//删除一个特戒怪物,不回收
	int HasAexringMon(Monster* mon);//判断怪物是不是特戒怪物
	void DestroyAllAexringMon(); //回收所有的特戒怪物
	void AddAerMonAttr(int rid, Attribute::AttributeType type, double value);
	void AddAerMonExAttr(int rid, ExAttribute::ExAttributeType type, int value);
	void SetAexringPassivity(bool b);
	void SetAexringTargetNull();
	Attribute *GetAerMonAttr(int rid);
	ExAttribute *GetAerMonExAttr(int rid);
	bool IsActImbaId(int id) { return imba_act_id_.find(id) != imba_act_id_.end(); }
	const std::set<int>* getWeaponIdList(int idx);
	void SetFlameStampLv(int lv) { flamestamp_lv_ = lv; }
	void SetFlameStampSkillLv(int index, int lv) { if (index >= 0 && index < MAX_FLAMESTAMP_SKILL) flamestamp_skill_lv_[index] = lv; }
	int *GetFlameStampData(int &level) { level = flamestamp_lv_; return flamestamp_skill_lv_; }
	void SetLeader() { isLeader = true; }
	inline static void SetShowZhanLingCd(int cd, int delay) { show_zhanling_cd_ = cd; show_zhanling_delay_ = delay; }
	void ShowZhanLing(int64_t curr_t);
	void ResetShowZhanLingT();
	int IsMirror() { return is_mirror; } //是否为镜像

	Attribute* GetBasicAttrs() { return &basic_attrs_cache_; };
private:
	Attribute				basic_attrs_cache_;  // 基础属性缓存
	std::string  name = "";
	//char job1;
	//char sex1;
	ActorId actor_id;
	char job;
	char sex;
	int level;
	int wing_open_state;
	int wing_level;
	int clothes_id;
	int weapon_id;
	int guild_id_ = 0;
	int tid_ = 0;
	int headid_ = 0;
	std::string guild_name_;
	bool has_hushen_shield = false;
	int64_t			show_zhanling_t_;		//上次显示战灵的时间
	static int		show_zhanling_cd_;		//显示战灵的CD
	static int		show_zhanling_delay_;		//延迟显示战灵
	int				zhanling_id_;
	int				zhanling_lv_;			//战灵等级
	int				zhanling_talent_effid_;	//战神附体buff id
	std::map<int, int> zhanling_effids_;  //战灵外显触发的buff列表
	int zhuangban_pos1_ = 0;
	int zhuangban_pos2_ = 0;
	int zhuangban_pos3_ = 0;
	int train_lv_ = 0;
	int yupei_lv_ = 0;
	short weapon_soul_id = 0;
	int64_t perstige_exp_;
	int heirloom[HEIRLOOM_TYPE_MAX];
	Attribute	all_attrs_;
	EntityHandle cloneHdl[MAX_ROLE];
	bool isLeader;
	std::map<int, Monster*> aexring_mon;//特戒召唤怪
	std::map<int, Attribute> aermon_attr;
	std::map<int, ExAttribute> aermon_ex_attr;
	std::set<int> imba_act_id_;
	std::map<int, std::set<int>> weapon_list_;
	bool isPeak_;//是否开启巅峰技能
	int GodWeaponlevel_; //神兵总等级
	int	flamestamp_lv_; //烈焰印记等级
	int	flamestamp_skill_lv_[MAX_FLAMESTAMP_SKILL]; //烈焰印记技能等级
	Timer m_t1s; //1秒定时器
	int zhuansheng_lv;
	int guildpos;
	//bool has_mabi_ring;
	//bool has_hushen_ring;
	int is_mirror; //是否为镜像，区分机器人 0为镜像 , > 0
};