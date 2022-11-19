#ifdef _MSC_VER
/* tolua
** Support code for Lua bindings.
** Written by Waldemar Celes
** TeCGraf/PUC-Rio
** Aug 2003
** $Id: tolua.c 1141 2006-05-18 23:58:45Z lindquist $
*/

/* This code is free software; you can redistribute it and/or modify it.
** The software provided hereunder is on an "as is" basis, and
** the author has no obligation to provide maintenance, support, updates,
** enhancements, or modifications.
*/


extern "C"
{
#include "tolua++.h"
#include "toluabind.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <vld.h>

#include <afx.h>
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

static void help (void)
{
	fprintf(stderr,"\n"
		"usage: tolua++ [options] input_file\n"
		"\n"
		"Command line options are:\n"
		"  -v       : print version information.\n"
		"  -o  file : set output file; default is stdout.\n"
		"  -H  file : create include file.\n"
		"  -n  name : set package name; default is input file root name.\n"
		"  -p       : parse only.\n"
		"  -P       : parse and print structure information (for debug).\n"
		"  -S       : disable support for c++ strings.\n"
		"  -1       : substract 1 to operator[] index (for compatibility with tolua5).\n"
		"  -L  file : run lua file (with dofile()) before doing anything.\n"
		"  -D       : disable automatic exporting of destructors for classes that have\n"
		"             constructors (for compatibility with tolua5)\n"
		"  -W       : disable warnings for unsupported features (for compatibility\n"
		"             with tolua5)\n"
		"  -C       : disable cleanup of included lua code (for easier debugging)\n"
		"  -E  value[=value] : add extra values to the luastate\n"
		"  -t       : export a list of types asociates with the C++ typeid name\n"
		"  -h       : print this message.\n"
		"Should the input file be omitted, stdin is assumed;\n"
		"in that case, the package name must be explicitly set.\n\n"
		);
}

static void version (void)
{
	fprintf(stderr, "%s (written by W. Celes, A. Manzur)\n",TOLUA_VERSION);
}

static void setfield (lua_State* L, int table, char* f, char* v)
{
	lua_pushstring(L,f);
	lua_pushstring(L,v);
	lua_settable(L,table);
}

static void add_extra (lua_State* L, char* value) {
	int len;
	lua_getglobal(L, "_extra_parameters");
	len = luaL_getn(L, -1);
	lua_pushstring(L, value);
	lua_rawseti(L, -2, len+1);
	lua_pop(L, 1);
};

static void error (char* o)
{
	fprintf(stderr,"tolua: unknown option '%s'\n",o);
	help();
	exit(1);
}


#include <stdlib.h>
#include <stdio.h>
#include "crc32c.h"


__time64_t GetDirTime(CString  strFullPath) 
{ 
	//查找指定目录大小的归递函数 
	__time64_t dir_t,sub_t; 
	CFileFind finder; 

	dir_t=sub_t=0; 
	strFullPath+= "\\*.*"; 
	if (finder.FindFile(strFullPath)) 
	{ 
		while (1) 
		{ 
			BOOL bFound; 

			bFound=finder.FindNextFile();	
			if (finder.IsDirectory()) 
			{ 
				if (!finder.IsDots()) 
				{ 
					sub_t=GetDirTime(finder.GetFilePath()); 
					dir_t+=sub_t; 
				} 
			} 
			else 
			{ 
				CFile file; 
				CFileStatus state;
				if (file.Open(finder.GetFilePath(),CFile::modeRead)) 
				{
					file.GetStatus(state);
					dir_t += state.m_mtime.GetTime();
					file.Close(); 
				}	
			} 
			if (bFound==FALSE) 
				break; 
		}	
	} 
	finder.Close(); 
	return dir_t; 

}

bool get_crc(const char* f, unsigned int* crc)
{
	FILE* inf;
	inf = fopen(f, "r");
	if (!inf) 
	{ 
		fprintf(stderr, "file is not exists!%s", f); 
		return false;
	}
	char inbuf[512 * 1024];
	size_t inl;
	inl = fread(inbuf, 1, sizeof(inbuf), inf);
	if (inl >= sizeof(inbuf)) 
	{ 
		fprintf(stderr, "big file!%s\n", f); 
		fclose(inf);
		return false;
	}

	*crc = leveldb::crc32c::Value(inbuf, inl);
	fclose(inf);
	return true;
}

unsigned int crc[1024];
unsigned int newcrc[1024];
size_t fc = 0;

void check_chg(const char* f)
{
	// array crc 不用初始化了
	fc = 0;
	FILE* cf = fopen("cf", "rb");
	size_t cl = 0;
	if (cf)
	{
		cl = fread(crc, sizeof(unsigned int), sizeof(crc)/sizeof(crc[0]), cf);
		fclose(cf);
	}

	if (get_crc(f, newcrc)) fc++;

	FILE* inf;
	inf = fopen(f, "r");
	if (!inf) 
	{ 
		fprintf(stderr, "file is not exists!%s", f); 
		exit(1);
	}

	char src[10 * 1024];
	size_t sl = fread(src, 1, sizeof(src), inf);
	src[sl] = 0;
	fclose(inf);

	const char* line = src;
	char* lpos = (char*)strchr(line, '\n');
	while(*line)
	{
		if (lpos) *lpos = 0;
		if (*line)
		{
			if (strncmp(line, "$cfile", 6) == 0 || strncmp(line, "$pfile", 6) == 0)
			{
				const char* l = strchr(line, '"');
				if (l) 
				{
					char* r = (char*)strchr(l+1, '"');
					const char* fn = l;
					if (r) *r = 0;					
					if (r && get_crc(fn+1, newcrc + fc)) fc++;
				}
			}

		}


		if(!lpos) break;
		line = lpos + 1;
		lpos = (char*)strchr(line, '\n');
	}

	if (fc == cl && fc > 0)
	{
		bool chg = false;
		for (size_t i = 0; i < fc; i++)
		{
			if (newcrc[i] != crc[i]) 
			{
				fprintf(stderr, "%d,%d,%d",i, newcrc[i], crc[i]);
				chg = true;			
				break;
			}
		}

		if (!chg)
		{
			fprintf(stderr, "no change!");
			exit(0);// no change 
		}
	}

	// 新的crc写入文件
	cf = fopen("cf", "wb");
	if (cf)
	{
		size_t wc = fwrite(newcrc, sizeof(unsigned int), fc, cf);
		fclose(cf);
		if (wc != fc)
		{
			fprintf(stderr, "file write error!");
		}
	}
	fprintf(stderr, "file change!,%d,%d..", fc, cl);
	return;
}

const char* check_dir = "..";
const char* save_file = "c:\\cf";

void check_dir_chg()
{
	FILE* cf = fopen(save_file, "rb");
	__time64_t rt = 0;
	if (cf)
	{
		fread(&rt, sizeof(__time64_t), 1, cf);
		fclose(cf);
	}

	__time64_t nt = GetDirTime(check_dir);
	if (nt == rt)
	{
		fprintf(stderr, "no change!");
		exit(0);// no change 
	}
	fprintf(stderr, "file change!,%lld,%lld..", rt, nt);
	return;
}

void save_time()
{
	__time64_t nt = GetDirTime(check_dir);
	FILE* cf = fopen(save_file, "wb");
	if (cf)
	{
		size_t wc = fwrite(&nt, sizeof(__time64_t), 1, cf);
		fclose(cf);
	}
}


int main (int argc, char* argv[])
{
#ifdef LUA_VERSION_NUM /* lua 5.1 */
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
#else
	lua_State* L = lua_open();
	luaopen_base(L);
	luaopen_io(L);
	luaopen_string(L);
	luaopen_table(L);
	luaopen_math(L);
	luaopen_debug(L);
#endif

	lua_pushstring(L,TOLUA_VERSION); lua_setglobal(L,"TOLUA_VERSION");
	lua_pushstring(L,LUA_VERSION); lua_setglobal(L,"TOLUA_LUA_VERSION");

	if (argc==1)
	{
		help();
		return 0;
	}
	else
	{
		int i, t;
		lua_newtable(L);
		lua_setglobal(L, "_extra_parameters");
		lua_newtable(L);
		lua_pushvalue(L,-1);
		lua_setglobal(L,"flags");
		t = lua_gettop(L);
		for (i=1; i<argc; ++i)
		{
			if (*argv[i] == '-')
			{
				switch (argv[i][1])
				{
				case 'v': version(); return 0;
				case 'h': help(); return 0;
				case 'p': setfield(L,t,"p",""); break;
				case 'P': setfield(L,t,"P",""); break;
				case 'o': setfield(L,t,"o",argv[++i]); break;
				case 'n': setfield(L,t,"n",argv[++i]); break;
				case 'H': setfield(L,t,"H",argv[++i]); break;
				case 'S': setfield(L,t,"S",""); break;
				case '1': setfield(L,t,"1",""); break;
				case 'L': setfield(L,t,"L",argv[++i]); break;
				case 'D': setfield(L,t,"D",""); break;
				case 'W': setfield(L,t,"W",""); break;
				case 'C': setfield(L,t,"C",""); break;
				case 'E': add_extra(L,argv[++i]); break;
				case 't': setfield(L,t,"t",""); break;
				default: error(argv[i]); break;
				}
			}
			else
			{
				setfield(L,t,"f",argv[i]);
				// revision:zac in 2012-1-5
				check_dir_chg();
				break;
			}
		}
		lua_pop(L,1);
	}
#define TOLUA_SCRIPT_RUN
#ifndef TOLUA_SCRIPT_RUN
	{
		int tolua_tolua_open (lua_State* L);
		tolua_tolua_open(L);

		save_time();
	}
#else
	{
		char* p;
		char  path[BUFSIZ];
		strcpy(path,argv[0]);
		p = strrchr(path,'/');
		if (p==NULL) p = strrchr(path,'\\');
		p = (p==NULL) ? path : p+1;
		sprintf(p,"%s","lua/");
		lua_pushstring(L,path); 
		lua_setglobal(L,"path");
		strcat(path,"all.lua");
		lua_dofile(L,path);

		save_time();
	}
#endif
	return 0;
}
#endif
