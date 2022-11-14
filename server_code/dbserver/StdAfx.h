#define DB_UTF8
//#include <vld.h>

//#define _TIME_STATE_CHECK_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DB_TYPEDIRTY   //是否编译进去，以类型为单位判断是否保存
#include "os_def.h"
#include <_ast.h>

#include <x_thread.h>
#include <net/base_socket.h>
#include <x_lock.h>
#include <x_tick.h>
#include <container/queue_list.h>
#include "share_util.h"
#include "memory/buffer_allocator.h"
#include "memory/memory_container.hpp"
#include "appitnmsg.h"
#include "db/sql_connection.h"
#include "data_packet.hpp"
#include "data_packet_reader.hpp"
#include "net/send_packet_pool.h"
#include "net/work_socket.h"
#include "net/net_client.h"
#include "net/net_session.h"
#include "net/server_socket.h"
#include "server_def.h"
#include "gate/gate_proto.h"

#include <stream.h>

#ifdef _MSC_VER
#include "statistic/time_stat.h"
#endif

#include "InterServerComm.h"
#include "db_proto.h"
#include "utils/watch_thread.h"
#include "common/property_id_def.h"
#include "common/property_set.h"

#include "db_pvm_cache.h"
#include "db/table_defs.h"
#include "db/actor_cache_def.h"
#include "db/actor_db_data.h"
#include "db_cache.h"
#include "db_session_mgr.h"
#include "db_server.h"
//#include "common/attr_type.h"
//#include "common/attr_def.h"
//#include "../gameworld/config/gem_def.h"
#include "../common/db/msg.h"
#include "encrypt/CRC.h"
#include "encrypt/Encrypt.h"
#include "flog/file_logger.h"
#include "log/log_sender.h"
#include "log/log_def.h"
#include "common/system_param_def.h"

#include "second_time.h" //时间用的
#include "container/static_hash_table.h"

#include "db/skill_data.h"
#include "db/item_data.h"
#include "db/fight_data.h"
#include "db/wing_data.h"
#include "db/pet_data.h"
#include "db/friend_data.h"
#include "db/achieve_data.h"
#include "db/rank_data.h"
#include "db/config_db_data.h"
#include "datahandle/db_handle_def.h"

#include "dbserver_utils.h"
#include <ref_class.hpp>
#include <ref_string.hpp>
#include <time.h>

#include "encrypt/EDPass.h"

extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "luabase/base_lua.h"
#include "luabase/base_lua_config.h"
#include "luabase/script_value.hpp"
#include "luabase/script_value_list.h"
#include "luabase/lua_pre_process.h"
#include "luabase/vsp_def.h"
#include "db_config.h"
#include "luabase/base_script.h"
#include "db_executor.h"
#include "db_tables.h"

#include "db_session.h"
#include <tolua++.h>

#define SP_ZX_TX		// 定义SP宏，用来区分不同的运营商，比如SP_ZX_TX表示斩仙在腾讯运营，SP_ZX_TW表示斩仙台服
