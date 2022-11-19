#ifndef _SQL_H_
#define	_SQL_H_

#ifdef _MSC_VER
#undef bool //config-win.h中会把bool定义为BOOL
#endif
#include "mysql.h"
//#include <windows.h>
#include "os_def.h"
#include "x_lock.h"

using namespace lock;

class SQLConnection
{
private:
	static const int BUFF_SIZE = 4096 * 10;

private:
	MYSQL				MySql_;
	MYSQL_RES*			result_set_;
	my_ulonglong		row_num_;
	MYSQL_ROW			rows_;
	MYSQL_FIELD*		fields_;
	my_ulonglong		field_num_;
	my_ulonglong		affect_rows_;

private:
	char				host_[32];
	int					port_;
	char				user_name_[64];
	char				pw_[64];
	char				db_name_[64];
	size_t				flag_;
	char				buf_[BUFF_SIZE];
	Mutex				lock_;			//SQL查询锁
	bool				connected_;			//是否连接的标志
	bool				mult_thread_;		//是否多线程的标志，如果为TRUE则进行查询是会加锁

	size_t				err_cnt_;			// 执行sql错误的数量,如果过多，则可以报警
	bool				infile_;
	bool				utf8_;
	bool				log_;				// 是否记录sql的日志
private:
	void AfterQueryed(int nError, const char* sql);
	void AfterExeced(int nError, const char* sql);

public:
	SQLConnection();
	~SQLConnection();

	inline const char* GetHost()
	{
		return host_;
	};
	void SetHost(const char* sServerHost);
	inline int GetPort()
	{
		return port_;
	};
	void SetPort(int nServerPort);
	inline const char* GetDbName()
	{
		return db_name_;
	};
	void SetDbName(const char* sDataBaseName);
	inline const char* GetUserName()
	{
		return user_name_;
	};
	void SetUserName(const char* sUserName);
	inline const char* GetPassWord()
	{
		return pw_;
	};
	void SetPassWord(const char* sPassWord);
	inline size_t GetConnectionFlags()
	{
		return flag_;
	};
	void SetConnectionFlags(const size_t nFlags);
	inline bool IsMultiThread()
	{
		return mult_thread_;
	};
	void SetMultiThread(bool boMultiThread);

	BOOL Connect();

	inline BOOL Connected()
	{
		return connected_;
	};
	void Disconnect();

	inline MYSQL* GetMySql()
	{
		return &MySql_;
	}
	//Query和RealQuery用于执行带返回结果的查询操作，
	//查询成功则返回0并且需要在外部调用ResetQuery来释放查询结果集并解锁，
	//如果查询失败则会自动解锁。
	int Query(const char* sQueryFormat, ...);
	int RealQuery(const char* sQueryText, const size_t nTextLen);

	//Exec和RealExec用于执行不带返回结果的查询操作，例如delete,update,create,drop,alter等
	//执行成功则返回0并且需要在外部调用ResetQuery来释放查询结果集并解锁，
	//如果执行失败则会自动解锁。
	int Exec(const char* sQueryFormat, ...);
	int RealExec(const char* sExecText, const size_t nTextLen);

	void ResetQuery();

	int Ping()
	{
		return mysql_ping(&MySql_);
	}

	inline int GetFieldCount()
	{
		return (int)field_num_;
	}
	inline int GetRowCount()
	{
		return (int)row_num_;
	}
	inline int GetRowsAffected()
	{
		return (int)affect_rows_;
	}
	inline MYSQL_ROW CurrentRow()
	{
		return rows_;
	}
	inline MYSQL_ROW NextRow()
	{
		if (result_set_)
		{
			rows_ = mysql_fetch_row(result_set_);
			return rows_;
		}

		return NULL;
	}
	inline unsigned long* GetFieldsLength()
	{
		return mysql_fetch_lengths(result_set_);
	}

	void ClearErrCnt()
	{
		err_cnt_ = 0;
	}
	size_t GetErrCnt()
	{
		return err_cnt_;
	}

	void SetInfileFlag(bool flag)
	{
		infile_ = flag;
	}
	void SetUtf8(bool flag)
	{
		utf8_ = flag;
	}
	void SetLog(bool flag)
	{
		log_ = flag;
	}
};

#endif
