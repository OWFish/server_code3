#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

/*************************************************************
*		地图数据读取后将不保存用于显示的图片编号等数据，而仅仅
*	保存用于进行逻辑处理的点阵数据——使用一个字节表示一个坐标。
*	当坐标数据的值为1的时候，表示该坐标可以移动，否则表示该
*	坐标不可移动。
*
************************************************************/

//当前地图版本号
const unsigned int MapFileVersion_Current = 0x0102;
//不可移动标记
const unsigned int MAPFLAG_MOVEABLE = 0x8000;

/*
 * 地图文件头结构
 */
#pragma pack(push, 1)
struct MAPFILE_HEADER_NEW
{
	char hdr_[5];	//"map"
	int ver_;
	unsigned char grid_size_;	// 常量，64像素
	int pxi_width_;		// 地图的像素大小
	int pix_height_;
	int	width_;			//地图宽度
	int	height_;		//地图高度
};

struct MAPFILE_HEADER
{
	unsigned int	version_;		//文件版本0x0101
	int		width_;			//地图宽度
	int		height_;		//地图高度
	int		bg_img_;	//地图背景图片编号
	unsigned int	data_size_;		//地图坐标数据段字节长度
	unsigned char	reseve_[32];
};

// 地图网格的结构
struct MAPGrid
{
	unsigned short	bg_img_;		// 背景图片编号
	unsigned short	ft_img_;		// 前景图片编号
	unsigned short	flag_;			// 地图坐标标志位
	unsigned char	obj_root_;		// 素材分类索引
	unsigned char	reseve_;		// 图片类型

	unsigned short	effect_id_;		// 地图的特效id
	unsigned short  width_;			// 特效的宽度
	unsigned short  height_;		// 特效的高度
} ;

enum GripFlag
{
	gfBlock = 0, //阻挡
	gfCanMove = 1, //行走区
	gfThrough = 2, //透明区
	gfNofly = 3, //阻挡且不能飞跃
};

struct MAPGrid_NEW
{
	unsigned char flag_;	// 0=阻档，1=行走区,2=透明区,3=阻挡且不能飞跃
};

#pragma pack(pop)

class GameMap
{
private:
	static BaseAllocator mapAlloc_;
protected:
	unsigned int width_;		// 地图宽度
	unsigned int height_;		// 地图高度
	int* moveable_index_;		// 每坐标对应的可移动索引，主要是用于省内存的优化，暂时没使用到
	int	moveable_ount_;			// 移动坐标数量
public:
	GameMap();
	virtual ~GameMap();

	/* 从流中加载地图数据 */
	bool LoadFromStream(stream::BaseStream& stream, bool newver);
	/* 从文件中加载地图数据 */
	bool LoadFromFile(const char* fn, bool newver);
	/* 生成一张全部可以移动的地图 */
	void initDefault(unsigned int w, unsigned int h);

	/* 获取地图宽度 */
	inline int getWidth()
	{
		return width_;
	}
	/* 获取地图高度 */
	inline int getHeight()
	{
		return height_;
	}
	/* 获取可移动坐标数量 */
	inline int getMoveableCount()
	{
		return moveable_ount_;
	}

	/* 获取地图中所有单元数目 */
	inline int getUnitCount() const
	{
		return width_ * height_;
	}

	inline int getPosIndex(unsigned int x, unsigned int y)
	{
		if (x >= width_ || y >= height_)
			return -1;

		return y * width_ + x;
	}

	/* 判断地图中x, y坐标位置是否可以移动，返回true表示坐标可以移动 */
	inline bool canMove(unsigned int x, unsigned int y)
	{
		if (x >= width_ || y >= height_)
			return false;

		return moveable_index_[y * width_ + x] != -1;
	}

	int getMapPosValue(unsigned int x, unsigned int y)
	{
		if (x >= width_ || y >= height_)
			return -1;

		return moveable_index_[y * width_ + x] != -1 ? 0 : -1;
	}
};


#endif


