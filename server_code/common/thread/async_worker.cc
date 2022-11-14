#include <stdlib.h>
#include <stdio.h>
#include "os_def.h"
#include "_ast.h"
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "ltm.h"
}
#include "x_thread.h"
#include "x_tick.h"
#include "x_lock.h"
#include "ref_string.hpp"
#include "stream.h"
#include "share_util.h"
#include "container/str_hash_table.h"
#include "container/queue_list.h"
#include "memory/buffer_allocator.h"
#include "luabase/base_lua.h"
#include "luabase/base_lua_config.h"
#include "luabase/lua_pre_process.h"
#include "luabase/clvariant.h"
#include "luabase/lua_clvariant.h"
#include "luabase/lua_profiler.h"
#include "luabase/script_value.hpp"
#include "luabase/script_value_list.h"
#include "luabase/vsp_def.h"
#include "luabase/base_script.h"
#include "async_worker.h"

AsyncWorker::AsyncWorker(const char* lua_file) : Inherited(),
	alloc_("AsyncWorker"), wcb_(NULL), reload_(false)
{
	cb_list_.setLock(&cb_list_lock_);

	LoadScript(lua_file);

	_STRNCPY_A(lua_file_, lua_file);
}

AsyncWorker::~AsyncWorker()
{
	cb_list_.flush();
	int count = cb_list_.count();

	for (int i = 0; i < count; ++i)
	{
		CBData* cb = cb_list_[i];
		if (!cb) continue;

		if (cb->params_ && cb->free_func_)
		{
			cb->free_func_(cb);
		}

		alloc_.FreeBuffer(cb);
	}

	cb_list_.clear();
}

int AsyncWorker::Run()
{
	if (reload_)
	{
		reload_ = false;
		LoadScript(lua_file_);
	}

	if (cb_list_.appendCount() <= 0) return 0;

	cb_list_.flush();
	int count = cb_list_.count();

	for (int i = 0; i < count; ++i)
	{
		CBData* cb = cb_list_[i];
		cb->work_func_(cb);

		this->wcb_(cb);
	}

	cb_list_.clear();
	return count;
}

void AsyncWorker::OnRoutine()
{
	OnStart();

	while (!terminated())
	{
		if (Run() <= 0)
			Sleep(1);
	}

	OnStop();
}

void AsyncWorker::OnStart()
{
	OutputMsg(rmNormal, "AsyncWorker start!");
}

void AsyncWorker::OnStop()
{
	OutputMsg(rmNormal, "AsyncWorker stop!");
}

void AsyncWorker::AppendWork(CBData* cb)
{
	cb_list_.append(cb);
}

void AsyncWorker::LoadScript(const char* lua_file)
{
	if (lua_file)
	{
		CVSPDefinition vsp_def;
		vsp_def.LoadDefinitions("./data/vspdef.txt");
		script_.SetVspDef(&vsp_def);

		if (!script_.LoadScript(lua_file))
		{
			OutputMsg(rmError, "load AsyncWorker script fail!!!file:%s", lua_file);
		}
	}
}

unsigned int AsyncWorker::SendLuaMessage(ScriptValueList& req, WordFunc func)
{
	id_++;

	if (id_ == 0) id_++;

	CBData* cb = (CBData*)alloc_.AllocBuffer(sizeof(*cb));
	new(cb)CBData(this, id_);

	cb->worker_ = this;
	cb->work_func_ = &AsyncWorker::ExecuteLua;
	cb->after_func_ = func;
	cb->free_func_ = &AsyncWorker::FreeLuaParams;
	cb->params_ = alloc_.AllocBuffer(sizeof(LuaParams));
	new(cb->params_)LuaParams();

	LuaParams* p = (LuaParams*)cb->params_;
	p->req_ = req;
	p->result_ << cb->guid_;
	AppendWork(cb);
	return cb->guid_;
}

void AsyncWorker::FreeLuaParams(void* callback)
{
	CBData* cb = (CBData*)callback;

	if (cb->params_)
	{
		((LuaParams*)cb->params_)->~LuaParams();
		cb->worker_->GetAlloc().FreeBuffer(cb->params_);
		cb->params_ = NULL;
	}
}

void AsyncWorker::ExecuteLua(void* cb)
{
	CBData* c = (CBData*)cb;
	LuaParams* p = (LuaParams*)c->params_;
	c->worker_->script_.Call("main", &p->req_, &p->result_);
}

