#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

/*************************************************************
*		��ͼ���ݶ�ȡ�󽫲�����������ʾ��ͼƬ��ŵ����ݣ�������
*	�������ڽ����߼�����ĵ������ݡ���ʹ��һ���ֽڱ�ʾһ�����ꡣ
*	���������ݵ�ֵΪ1��ʱ�򣬱�ʾ����������ƶ��������ʾ��
*	���겻���ƶ���
*
************************************************************/

//��ǰ��ͼ�汾��
const unsigned int MapFileVersion_Current = 0x0102;
//�����ƶ����
const unsigned int MAPFLAG_MOVEABLE = 0x8000;

/*
 * ��ͼ�ļ�ͷ�ṹ
 */
#pragma pack(push, 1)
struct MAPFILE_HEADER_NEW
{
	char hdr_[5];	//"map"
	int ver_;
	unsigned char grid_size_;	// ������64����
	int pxi_width_;		// ��ͼ�����ش�С
	int pix_height_;
	int	width_;			//��ͼ���
	int	height_;		//��ͼ�߶�
};

struct MAPFILE_HEADER
{
	unsigned int	version_;		//�ļ��汾0x0101
	int		width_;			//��ͼ���
	int		height_;		//��ͼ�߶�
	int		bg_img_;	//��ͼ����ͼƬ���
	unsigned int	data_size_;		//��ͼ�������ݶ��ֽڳ���
	unsigned char	reseve_[32];
};

// ��ͼ����Ľṹ
struct MAPGrid
{
	unsigned short	bg_img_;		// ����ͼƬ���
	unsigned short	ft_img_;		// ǰ��ͼƬ���
	unsigned short	flag_;			// ��ͼ�����־λ
	unsigned char	obj_root_;		// �زķ�������
	unsigned char	reseve_;		// ͼƬ����

	unsigned short	effect_id_;		// ��ͼ����Чid
	unsigned short  width_;			// ��Ч�Ŀ��
	unsigned short  height_;		// ��Ч�ĸ߶�
} ;

enum GripFlag
{
	gfBlock = 0, //�赲
	gfCanMove = 1, //������
	gfThrough = 2, //͸����
	gfNofly = 3, //�赲�Ҳ��ܷ�Ծ
};

struct MAPGrid_NEW
{
	unsigned char flag_;	// 0=�赵��1=������,2=͸����,3=�赲�Ҳ��ܷ�Ծ
};

#pragma pack(pop)

class GameMap
{
private:
	static BaseAllocator mapAlloc_;
protected:
	unsigned int width_;		// ��ͼ���
	unsigned int height_;		// ��ͼ�߶�
	int* moveable_index_;		// ÿ�����Ӧ�Ŀ��ƶ���������Ҫ������ʡ�ڴ���Ż�����ʱûʹ�õ�
	int	moveable_ount_;			// �ƶ���������
public:
	GameMap();
	virtual ~GameMap();

	/* �����м��ص�ͼ���� */
	bool LoadFromStream(stream::BaseStream& stream, bool newver);
	/* ���ļ��м��ص�ͼ���� */
	bool LoadFromFile(const char* fn, bool newver);
	/* ����һ��ȫ�������ƶ��ĵ�ͼ */
	void initDefault(unsigned int w, unsigned int h);

	/* ��ȡ��ͼ��� */
	inline int getWidth()
	{
		return width_;
	}
	/* ��ȡ��ͼ�߶� */
	inline int getHeight()
	{
		return height_;
	}
	/* ��ȡ���ƶ��������� */
	inline int getMoveableCount()
	{
		return moveable_ount_;
	}

	/* ��ȡ��ͼ�����е�Ԫ��Ŀ */
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

	/* �жϵ�ͼ��x, y����λ���Ƿ�����ƶ�������true��ʾ��������ƶ� */
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


