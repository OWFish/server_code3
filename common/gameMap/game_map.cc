#include <stdio.h>
#include "os_def.h"
#include "_ast.h"

#include <zlib.h>
#include "stream.h"
#include "zstream.h"
#include "game_map.h"

#include "memory/base_allocator.hpp"

#ifndef _MSC_VER
#include <arpa/inet.h>
#endif

using namespace stream;
using namespace zstream;

BaseAllocator GameMap::mapAlloc_("mapAlloc");

GameMap::GameMap()
{
	width_ = 0;
	height_ = 0;
	moveable_index_ = NULL;
	moveable_ount_ = 0;
}

GameMap::~GameMap()
{
	if (moveable_index_)
		mapAlloc_.FreeBuffer(moveable_index_);
}


bool GameMap::LoadFromStream(BaseStream& stream, bool newver)
{
	MAPFILE_HEADER hdr;
	MAPGrid* map_grid, *grid_ptr;

	MAPFILE_HEADER_NEW hdr_n;
	MAPGrid_NEW* map_grid_n, *grid_ptr_n;

	if (!newver)
	{
		//读取并检查文件头
		if (stream.read(&hdr, sizeof(hdr)) != sizeof(hdr))
			return false;

		if (hdr.version_ != MapFileVersion_Current)
			return false;
	}

	//将压缩过的坐标数据段读取到内存流
	MemoryStream ms(NULL);
	if (newver)
		ms.copyFrom(stream, stream.getSize());
	else
		ms.copyFrom(stream, hdr.data_size_);

	ms.setPosition(0);

	//从内存流中创建解压流，以便解压坐标数据
	ZDecompressionStream deStream(ms, NULL);
	
	if (newver)
	{
		//读取并检查文件头
		if (deStream.read(&hdr_n, sizeof(hdr_n)) != sizeof(hdr_n))
			return false;
		// 地图打包文件，按照大头的字节序打包了
		hdr_n.width_ = ntohl(hdr_n.width_);
		hdr_n.height_ = ntohl(hdr_n.height_);
	}

	int max = 0;
	if (newver)
	{
		size_t grid_count = sizeof(MAPGrid_NEW) * hdr_n.width_ * hdr_n.height_;

		grid_ptr_n = map_grid_n = (MAPGrid_NEW*)mapAlloc_.AllocBuffer(grid_count);

		if (grid_count != (const size_t)deStream.read(map_grid_n, (const int)grid_count))
			return false;

		max = hdr_n.width_ * hdr_n.height_;
	}
	else
	{
		size_t grid_count = sizeof(MAPGrid) * hdr.width_ * hdr.height_;

		grid_ptr = map_grid = (MAPGrid*)mapAlloc_.AllocBuffer(grid_count);

		if (grid_count != (const size_t)deStream.read(map_grid, (const int)grid_count))
			return false;

		max = hdr.width_ * hdr.height_;
	}

	moveable_ount_ = 0;
	int* index_ptr = moveable_index_ = (int*)mapAlloc_.ReAllocBuffer(moveable_index_, max * sizeof(*index_ptr));
	memset(index_ptr, -1, max * sizeof(*index_ptr));		// 如果是memset其他值会有问题

	//保存地图宽度以及高度数据
	if (newver)
	{
		// 这个索引值跟旧版本的不一样
		for (int i = 0; i < max; ++i)
		{
			if (grid_ptr_n->flag_ != gfBlock /*&& grid_ptr_n->flag_ != gfNofly*/)//不是明确的不可走点,都认为可走就行了
			{
				int x = i / hdr_n.height_;
				int y = i % hdr_n.height_;

				(*(index_ptr + (y * hdr_n.width_ + x))) = moveable_ount_;
				moveable_ount_++;
			}

			//index_ptr++;
			grid_ptr_n++;
		}

		width_ = hdr_n.width_;
		height_ = hdr_n.height_;

		mapAlloc_.FreeBuffer(map_grid_n);
	}
	else
	{
		for (int i = 0; i < max; ++i)
		{
			if ((grid_ptr->flag_ & MAPFLAG_MOVEABLE) != 0)
			{
				(*index_ptr) = moveable_ount_;
				moveable_ount_++;
			}

			index_ptr++;
			grid_ptr++;
		}
		width_ = hdr.width_;
		height_ = hdr.height_;

		mapAlloc_.FreeBuffer(map_grid);
	}

	return true;
}

bool GameMap::LoadFromFile(const char* fn, bool newver)
{
	FileStream fs(fn, FileStream::faRead || FileStream::faShareRead, NULL);
	return LoadFromStream(fs, newver);
}

void GameMap::initDefault(unsigned int w, unsigned int h)
{
	// 特定地方才会用到这个函数，全部网格设置成可以走动
	//生成抽象灰度地图
	int max = w * h;

	moveable_ount_ = 0;
	int* index_ptr = moveable_index_ = (int*)mapAlloc_.ReAllocBuffer(moveable_index_, max * sizeof(*index_ptr));

	for (int i = 0; i < max; ++i)
	{
		(*index_ptr) = moveable_ount_;
		moveable_ount_++;
		index_ptr++;
	}

	//保存地图宽度以及高度数据
	width_ = w;
	height_ = h;
}


