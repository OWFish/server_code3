#include <stdio.h>
#ifdef _MSC_VER
#include <config-win.h>
#endif
#include "db/sql_connection.h"
#include <x_tick.h>
#include <string_ex.h>
#include "share_util.h"

SQLConnection::SQLConnection()
{
	ZeroMemory(&MySql_, sizeof(MySql_));

	result_set_ = NULL;
	row_num_ = 0;
	rows_ = NULL;
	fields_ = NULL;
	field_num_ = 0;

	host_[0] = 0;
	port_ = 3306;
	user_name_[0] = 0;
	pw_[0] = 0;
	db_name_[0] = 0;
	flag_ = CLIENT_FOUND_ROWS | CLIENT_MULTI_RESULTS;

	buf_[0] = 0;

	connected_ = FALSE;
	mult_thread_ = FALSE;

	err_cnt_ = 0;
	infile_ = false;
	utf8_ = false;
	log_ = true;
}

SQLConnection::~SQLConnection()
{
	Disconnect();
}

void SQLConnection::SetHost(const char* sServerHost)
{
	ZeroMemory(host_, sizeof(host_));
	_STRNCPY_S(host_, sServerHost, sizeof(host_) - 1);
}

void SQLConnection::SetPort(int nServerPort)
{
	port_ = nServerPort;
}

void SQLConnection::SetDbName(const char* sDataBaseName)
{
	ZeroMemory(db_name_, sizeof(db_name_));
	_STRNCPY_S(db_name_, sDataBaseName, sizeof(db_name_) - 1);
}

void SQLConnection::SetUserName(const char* sUserName)
{
	ZeroMemory(user_name_, sizeof(user_name_));
	_STRNCPY_S(user_name_, sUserName, sizeof(user_name_) - 1);
}

void SQLConnection::SetPassWord(const char* sPassWord)
{
	ZeroMemory(pw_, sizeof(pw_));
	_STRNCPY_S(pw_, sPassWord, sizeof(pw_) - 1);
}

void SQLConnection::SetConnectionFlags(const size_t nFlags)
{
	flag_ = nFlags;
}

void SQLConnection::SetMultiThread(bool boMultiThread)
{
	mult_thread_ = boMultiThread;
}


BOOL SQLConnection::Connect()
{
	bool Result = TRUE;

	if (!connected_)
	{
		if (mysql_init(&MySql_))
		{
			//MySql_.reconnect = TRUE;
			if (infile_)
			{
				unsigned int def = 1;
				mysql_options(&MySql_, MYSQL_OPT_LOCAL_INFILE, (const char*)&def);
				OutputMsg(rmError, "mysql_options:MYSQL_OPT_LOCAL_INFILE ok");
			}
			if (utf8_)
			{
				mysql_options(&MySql_, MYSQL_SET_CHARSET_NAME, "utf8");
			}

			if (mysql_real_connect(&MySql_, host_, user_name_, pw_, db_name_, (UINT)port_, NULL, (UINT)flag_))
			{
				connected_ = TRUE;
				//ResetQuery();
			}
			else
			{
				Result = FALSE;
				OutputMsg(rmError, ("can not connect to mysql：%s"), mysql_error(&MySql_));
				mysql_close(&MySql_);
			}
		}
		else
		{
			OutputMsg(rmError, ("mysql_init fail"));
			Result	= FALSE;
		}
	}

	return	Result;
}

void SQLConnection::Disconnect()
{
	if (connected_)
	{
		connected_ = FALSE;
		ResetQuery();
		mysql_close(&MySql_);
	}
}

void SQLConnection::AfterQueryed(int nError, const char* sql)
{
	if (!nError)
	{
		result_set_ = mysql_store_result(&MySql_);

		if (result_set_)
		{
			mysql_data_seek(result_set_, 0);
			mysql_field_seek(result_set_, 0);
			row_num_	= mysql_num_rows(result_set_);
			field_num_	= mysql_num_fields(result_set_);
			rows_    = mysql_fetch_row(result_set_);
		}
		else
		{
			field_num_ = 0;
			fields_ = NULL;
			row_num_ = 0;
			rows_ = NULL;
			buf_[128] = 0;
			//OutputMsg(rmError, ("%s(%s)"), mysql_error(&MySql_), buf_);
		}
	}
	else
	{
		field_num_ = 0;
		fields_ = NULL;
		row_num_ = 0;
		rows_ = NULL;
		result_set_ = NULL;

		OutputMsg(rmError, "%s:%s:%s", __FUNCTION__, mysql_error(&MySql_), sql);

		if (mult_thread_) lock_.Unlock();
	}
}

void SQLConnection::AfterExeced(int nError, const char* sql)
{
	if (!nError)
	{
		result_set_ = NULL;
		affect_rows_ = mysql_affected_rows(&MySql_);
	}
	else
	{
		field_num_ = 0;
		fields_ = NULL;
		row_num_ = 0;
		rows_ = NULL;
		result_set_ = NULL;
		affect_rows_ = 0;

		OutputMsg(rmError, "%s:%s:%s", __FUNCTION__, mysql_error(&MySql_), sql);

		if (mult_thread_) lock_.Unlock();
	}
}

int SQLConnection::Query(const char* sQueryFormat, ...)
{
	va_list	args;

	if (mult_thread_) lock_.Lock();

	va_start(args, sQueryFormat);
	int Result = vsprintf(buf_, sQueryFormat, args);
	va_end(args);

	Result = mysql_real_query(&MySql_, buf_, Result);
	AfterQueryed(Result, buf_);

	if (Result)
	{
		if (Result == 2006)
		{
			Disconnect();
		}
	}
	if (Result != 0) err_cnt_++;

	if (log_)
	{
		OutputMsg(rmError, "__SQL__:%s", buf_);
	}

	return Result;
}

int SQLConnection::RealQuery(const char* sQueryText, const size_t nTextLen)
{
	if (mult_thread_) lock_.Lock();

	int Result = mysql_real_query(&MySql_, sQueryText, (UINT)nTextLen);
	AfterQueryed(Result, sQueryText);

	if (Result)
	{
		if (Result == 2006)
		{
			Disconnect();
		}
	}
	if (Result != 0) err_cnt_++;

	if (log_)
	{
		OutputMsg(rmError, "__SQL__:%s", sQueryText);
	}

	return	Result;
}

int SQLConnection::Exec(const char* sQueryFormat, ...)
{
	va_list	args;

	if (mult_thread_) lock_.Lock();

	va_start(args, sQueryFormat);
	int Result = vsprintf(buf_, sQueryFormat, args);
	va_end(args);

	Result = mysql_real_query(&MySql_, buf_, Result);
	AfterExeced(Result, buf_);

	if (Result)
	{
		if (Result == 2006)
		{
			Disconnect();
		}
	}
	if (Result != 0) err_cnt_++;

	if (log_)
	{
		OutputMsg(rmError, "__SQL__:%s", buf_);
	}

	return	Result;
}

int SQLConnection::RealExec(const char* sExecText, const size_t nTextLen)
{
	int	Result;

	if (mult_thread_) lock_.Lock();

	Result = mysql_real_query(&MySql_, sExecText, (UINT)nTextLen);
	AfterExeced(Result, sExecText);

	if (Result)
	{
		if (Result == 2006)
		{
			Disconnect();
		}
	}
	if (Result != 0) err_cnt_++;

	if (log_)
	{
		OutputMsg(rmError, "__SQL__:%s", sExecText);
	}

	return	Result;
}

void SQLConnection::ResetQuery()
{
	if (result_set_)
	{
		mysql_free_result(result_set_);

		//Commands out of sync; you can't run this command now
		//get back all results
		while (!mysql_next_result(&MySql_));
	}

	field_num_ = 0;
	fields_ = NULL;
	row_num_ = 0;
	rows_ = NULL;
	result_set_ = NULL;

	if (mult_thread_) lock_.Unlock();
}


