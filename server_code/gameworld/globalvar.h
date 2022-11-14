#ifndef _GLOBAL_VAR_H_
#define _GLOBAL_VAR_H_


struct GlobalVar
{
	//Vector<int> prior_attack_list_;
	FriendAlloc friend_alloctor_;	//用于好友系统的内存分配器

	GridAlloc entity_grid_alloc_;	// 用于地图网格放entity handle的vector的分配器
	SceneGridAlloc scene_grid_alloc_;	// 场景网格类需要用的分配器
	SceneTeleAlloc scene_tele_alloc_;	// 场景的传送门配置用到的

	VisiHandleList	visible_list_;
	VisiHandleList	fb_visible_list_;
	VisiHandleList	ai_visible_list_;
	VisiHandleList	range_visible_list_;		// 周围玩家列表
	VisiHandleList	skill_hit_list_;	//技能命中列表

	ObjList<VisiHandleList, 4096 * 8> obser_entity_list_alloc_;
	QuestAlloc quest_alloc_;

	ObjList<AnyVector, 4096 * 8> any_list_alloc_;
	ObjList<DataPackList, 4096 * 8>	dp_list_alloc_;
//	ObjList<MailDataVector, 4096>	mail_data_list_alloc_;
	ObjList<ItemList,4096> item_list_alloc_;
	//ObjList<AttriCalc,4096> attricalc_list_alloc_;
	TimerCallAlloc time_caller_alloc_;
	//ObjList<BuffSystem::DenyBuffList, 4096> buff_deny_alloc_;
	//ObjList<BuffSystem::AfterBuffList, 4096> after_buff_alloc_;
	GEAlloc ge_alloc_;

	GlobalVar():/*prior_attack_list_(),*/ friend_alloctor_("friend_alloctor_"), entity_grid_alloc_("entity_grid_alloc")
		, scene_grid_alloc_("scene_grid_alloc"), scene_tele_alloc_("scene_tele_alloc_"), visible_list_(), fb_visible_list_(), ai_visible_list_(),range_visible_list_()
		, obser_entity_list_alloc_("obser_entity_list", "obser_alloc")
		, quest_alloc_("quest_alloc"), any_list_alloc_("any_list_alloc", "any_alloc")
		, dp_list_alloc_("dp_list_alloc_", "db_alloc")
//		, mail_data_list_alloc_("mail_data_list_alloc_", "mail_data_alloc_")
		, item_list_alloc_("item_list_alloc_", "item_alloc_")
		//, attricalc_list_alloc_("attricalc_list_alloc_", "attricalc_alloc_")
		, time_caller_alloc_("time_caller_alloc_")
		, ge_alloc_("ge_alloc_")
		//buff_deny_alloc_("buff_deny_alloc_", "buff_deny_alloc"),
		//after_buff_alloc_("after_buff_alloc_","after_buff_alloc")
	{
		friend_alloctor_.SetMultiThread(false);
		entity_grid_alloc_.SetMultiThread(false);
		scene_grid_alloc_.SetMultiThread(false);
		scene_tele_alloc_.SetMultiThread(false);
		quest_alloc_.SetMultiThread(false);
		time_caller_alloc_.SetMultiThread(false);
		ge_alloc_.SetMultiThread(false);
	}
};

#endif


