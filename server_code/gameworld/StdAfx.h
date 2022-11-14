#define DB_UTF8

#define NEW_BUFF

#ifdef _MSC_VER
#define _UNIT_TEST_
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "os_def.h"
#include "_ast.h"

#include "x_thread.h"
#include "net/base_socket.h"
#include "net/lua_socket.hpp"

#include "x_lock.h"
#include "x_tick.h"
#include "ref_string.hpp"
#include "stream.h"
#include "wrand.h"
#include "bzhash.h"
#include <math.h>
#include <algorithm>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "ltm.h"
#include "tolua++.h"
}
//#include <md5.h>
#include "container/binary_list.h"
#include "container/static_array_list.h"
#include "container/queue_list.h"
#include "container/linked_list.h"
#include "container/static_hash_table.h"
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "memory/align_allocator.h"
#include "common/datalist.h"
#include "alloc.h"
#include "version.h"

#include "appitnmsg.h"
#include "data_packet.hpp"
#include "memory/objpool.hpp"
#include "memory/memory_container.hpp"
#include "container/linked_list_ex.h"
#include "memory/handle_mgr.h"

#include "utils/fdop.h"
#include "utils/watch_thread.h"
#include "utils/singleton.h"
#include "container/bz_hash_table.h"
#include "container/str_hash_table.h"
#include "container/obj_list.h"

#include "encrypt/EDPass.h"
#ifdef _MSC_VER
#include "except/DefExceptHander.h"
#endif
#include "net/send_packet_pool.h"
#include "net/work_socket.h"
#include "net/net_client.h"
#include "net/net_session.h"
#include "net/server_socket.h"
#include "luabase/base_lua.h"
#include "luabase/base_lua_config.h"
#include "luabase/lua_pre_process.h"
#include "luabase/clvariant.h"
#include "luabase/lua_clvariant.h"
#include "luabase/lua_profiler.h"
#include "luabase/script_value.hpp"
#include "luabase/script_value_list.h"

#include "lang/lang_section.h"
#include "lang/lua_lang_section.h"
#include "second_time.h"
#include "time/time_caller.h"
#include "statistic/time_stat_log.h"

#ifdef _MSC_VER
#include "statistic/time_stat.h"
#endif

#include "server_def.h"
#include "InterServerComm.h"
#include "protocol/system_cmd_def.h"
//#include "protocol/proto_cmd_old.h"
//#include "protocol/proto_data_def.h"
#include "gate/gate_proto.h"
#include "gate/gate_user.h"
#include "gate/gate_session.h"
#include "gate/gate_manager.h"
#include "fastFT/mbcs_def.h" //关键字过滤用的
#include "encrypt/CRC.h"
#include "encrypt/Encrypt.h"
#include "game_world_def.h"
#include "log/log_def.h"
#include "log/log_sender.h"
#include "flog/file_logger.h"

//#include "common/attr_type.h"
//#include "common/attr_def.h"

//#include "script/interface/buff_type.h"
//#include "script/interface/achieve_event.h" //成就事件的定义
#include "script/interface/actor_event_def.h"
//#include "script/interface/map_area_attribute.h"
#include "script/interface/log_def.h"
//#include "script/interface/item_export_fun.h"
//#include "script/interface/lua_help_export_fun.h"


#include "db/sql_connection.h"
#include "db/actor_db_data.h"
#include "db/skill_data.h"
#include "db/guild_data.h"
#include "db/msg.h"
#include "db/achieve_data.h"
#include "db/fight_data.h"
#include "db/config_db_data.h"
#include "db/pet_data.h"
#include "db/item_data.h"
//#include "db/mount_data.h"
//#include "db/wing_data.h"
#include "db/db_client.h"
#include "db/db_client_mgr.h"

//#include "redis/RedisConnect.h"

#include "crossservice/game_conn_mgr.h"
#include "crossservice/game_client.h"
#include "crossservice/game_conn.h"

#include "base/time_span.h"      //时间管理器
#include "base/timer.h"      //时间管理器
#include "base/game_lua_config.h"
#include "base/ref_object.h"
#include "base/entity_attri_flag.h"
#include "base/act_msg.h"
#include "base/TipMsgId.h"
#include "base/global_var_mgr.h"		//给脚本保存数据用的
#include "base/act_msg.h"
#include "guild/guild_mgr.h"  //公会管理器
//#include "base/consignment_mgr.h"	//寄卖管理器
//#include "base/db_rank_mgr.h"	//头衔管理器
//#include "base/misc_mgr.h"		//杂七杂八的管理器
#include "base/msg_mgr.h"		// 信息管理
//#include "base/fight_mgr.h"		//竞技场管理器
#include "base/system_var_mgr.h"
//#include "base/ranking.h"
#include "base/act_msg.h"
//#include "base/netmsg_mgr.h"
//#include "base/guild.h"


#include "gate/game_gate.h"
#include "gate/game_gate_mgr.h"

#include "config/tip_msg_conf.h"
#include "lang/lang_pack.h"

#include "script/hlp/lua_hlp.h"
#include "common/system_param_def.h"

//#include "attr/attr_calc.h"
//#include "attr/attr_eval.h"
//#include "attr/attr_config.h"


//#include "plus/file_up_check.h"

#include "config/config_loader.h"

//配置文件
#include "config/game_server_config.h"
#include "common/property_id_def.h"
#include "common/property_set.h"

//#include "item/std_item.h"
//#include "item/item_conf_pool.h"

//#include "config/camp_config.h"
//#include "config/quest_config.h"
//#include "config/quest_conf_pool.h"

//#include "config/guild_conf_pool.h"
//#include "config/pk_provider.h"
//#include "config/pet_config.h"
//#include "config/enhance_provider.h"
//#include "config/action_provider.h"
//#include "config/rand_quest_conf.h"
//#include "config/fight_conf_pool.h"
//#include "config/artifact_config.h"
//#include "config/miji_config.h"
//#include "config/scene_def.h"
//#include "misc/area_region.h"
//#include "config/monster_config.h"
//#include "config/vocation_config.h"
//#include "config/envir_config.h"
//#include "config/global_config.h"
//#include "config/skill_config.h"
//#include "config/skill_conf_pool.h"
//#include "config/monster_conf_pool.h"
//#include "config/ai_config.h"
//#include "config/ai_conf_pool.h"
//#include "config/achieve_conf_pool.h"
//#include "config/buff_config.h"

//#include "misc/actor_name_color.h"

#include "config/game_config_data.h"

#include "script/ext/lua_memory.h"
#include "luabase/vsp_def.h"
#include "luabase/base_script.h"
#include "script/game_script.h"
#include "thread/async_worker.h"


//实体的列表
#include "entity/entity.h"
#include "entity/entity_op_collect.h"
#include "entity/entity_system.h"
//#include "entity/non_live.h"
#include "entity/creature.h"
//#include "entity/animal.h"
//#include "entity/transfer.h"
#include "entity/drop_bag.h"

#include "entity/actor/actor_ex.h"
#include "entity/actor/actor.h"
#include "entity/monster/monster.h"
#include "entity/role/role.h"
#include "entity/npc.h"
//#include "entity/moving_npc.h"
#include "entity/script_npc.h"
#include "entity/role/role_clone.h"
#include "entity/monster/gather_monster.h"
#include "entity/entity_mgr.h" //实体管理器


//#include "item/suit_cal.h"
//#include "item/item_allocator.h"
///#include "item/cnt/item_container.h"
///#include "item/cnt/depot_base.h"
///#include "item/cnt/user_bag.h"
//#include "item/cnt/guild_depot.h"

#include "center/center_client.h"

//#include "crosswar/game_session_mgr.h"
//#include "crosswar/game_client.h"
//#include "crosswar/game_session.h"
//#include "crosswar/corss_war_def.h"
//#include "crosswar/war_team.h"
//#include "crosswar/game_war_mgr.h"


#include "gameMap/game_map.h"


//子系统的列表
//#include "buff/dynamic_buff.h"
//#include "buff/buff_system.h"    //buff子系统

//#include "quest/quest_def.h"
//#include "observer/observer_system.h" //观察者子系统
//#include "move/move_system.h" //移动子系统
//#include "property/property_system.h" //玩家的属性子系统

//#include "item/cnt/equip_vessel.h"  //装备子系统

#include "lianfu/lianfu_defs.h"
#include "lianfu/lianfu_rank.h"
//#include "lianfu/lianfu_guild.h"
#include "lianfu/lianfu_mgr.h"

//#include "item/cnt/user_equip.h"  //装备子系统
//#include "item/cnt/branch_equip.h"
//#include "item/cnt/pet_equip.h"
//#include "item/cnt/mount_equip.h"
//#include "item/cnt/wing_equip.h"

//#include "quest/quest_system.h"   //任务子系统
//#include "skill/skill_condition.h"
//#include "skill/skill_result.h"
//#include "skill/effect_system.h"
//#include "skill/skill_system.h" //技能子系统
//#include "skill/miji_effect.h"

//#include "deal/deal_system.h"  //交易子系统
//#include "guild/guild_system.h"		//帮派子系统
//#include "loot/loot_system.h" //拾取子系统
//#include "mount/mount_system.h"	//坐骑子系统
//#include "offlinemsg/msg_system.h"
//#include "pk/pk_system.h"
//#include "pet/pet_system.h"
//#include "war/war_system.h"

//#include "misc/misc_system.h"  //杂乱子系统

#include "lua_var_system.h"
#include "cswar/war_system.h"
//#include "dress/dress_system.h"
//#include "pet/petcross_system.h"
//#include "depot/depot_mgr_system.h"
//#include "rank/rank_system.h"

#include "common/gem_def.h"
//#include "spirit/spirit_system.h"
//#include "fight/fight_system.h"

//#include "wing/wing_system.h"
//#include "attr/attr_system.h"
//#include "marry/marry_system.h"

//#include "ai/config/ai_config.h"
//#include "ai/config/ai_conf_pool.h"
//#include "ai/ai.h"
//#include "ai/ai_condition.h"
//#include "ai/ai_event.h"
//#include "ai/ai_state.h"
//#include "ai/ai_mgr.h"
//#include "ai/ai_state/ai_back.h"
//#include "ai/ai_state/ai_battle.h"
//#include "ai/ai_state/ai_born.h"
//#include "ai/ai_state/ai_dead.h"
//#include "ai/ai_state/ai_idle.h"

//#include "other/txlog/dcapi_mgr.h"
//#include "other/txlog/tlog_mgr.h"

#include "dkmlog/dkm_log_mgr.h"


//#include "config/dym_item_conf.h"   //用于管理从数据读取的配置

#include "scene/scene_def.h"
#include "scene/scene_grid.h"
#include "scene/scene.h"
#include "scene/fuben.h"
#include "scene/fuben_mgr.h"

#include "actormgr/rand_name_list.h"
#include "actormgr/actor_mgr.h"

//#include "camp/camp_mgr.h"

#include "game_engine.h"
#include "game_server.h"
#include "globalvar.h"
/*
#ifdef _MSC_VER
#include <vld.h>
#endif
*/
//!!!是否开启try_catch,在需要跟问题的时候把下面的屏蔽
//开启try_catch 主要用捕获一些偶然出现的异常，如果出现异常并无法找到原因，就把下面的定义屏蔽，生成dump
//服务器将停止运行

#define SP_X6_TX		// 定义SP宏，用来区分不同的运营商，比如SP_ZX_TX表示斩仙在腾讯运营，SP_ZX_TW表示斩仙台服

#define TEST_CROSS_MEM  

#define OPENLOGDKMLOG // 开启DKMLOG

