#ifndef _ENTITY_OP_COLLECT_H_
#define _ENTITY_OP_COLLECT_H_

/************************************************************************
* 
*                            实体对象操作汇总收集系统
*
*    实体对象操作汇总处理用于优化处理性能，将在一次逻辑循环中需要多次处理的相同事情集中
* 到例行逻辑函数即将返回前执行。
* 例如：
*  1) 刷新属性，在一次例行逻辑中可能需要多次刷新属性，而使用集中标记则可以只将需要刷新属
*     性的标志置为真，并在例行函数即将返回前判断标记并刷新属性）
*
*  2) 刷新外观，在一次例行逻辑中可能需要多次刷新外观，外观包括衣服、物品的形象，名称、名称
*     颜色，是否组队等标志
*
************************************************************************/

class EntityOPCollector
{
	friend class Creature;
public:
	enum CollecteOPType
	{
		coRefAbility = 0,	//重新计算属性
		coRefFeature,		//重新计算外观
		coTransport,       //传送标记，传送以后要向新出生地点旁边的玩家发一个消息
		coResetMaxHPMP,		// 重置最大血量和法力值，用于升级后的更新
		coRefMonsterDynProp,	// 刷新怪物动态属性
		coDenaturation,		//变性
		coEndHide,		// 现身
		coActordataerr,	// 从db读取道具的数据出错
		coSpeed,		// 速度改变
		coCheckProp,	// 下发属性变化
		//定义标记数量
		MaxCollectedOp
	};

	STATIC_ASSERT(MaxCollectedOp < 32);
public:
	EntityOPCollector()
	{
		Reset();
	}

	//重设汇总标记掩码
	inline void Reset()
	{
		operations_ = 0;
	}

	//设置汇总标记掩码
	inline void Collect(const CollecteOPType eOPType)
	{
		if (eOPType >= 0 && eOPType < MaxCollectedOp)
			operations_ |= (1 << (eOPType & 31));
	}

	inline bool IsCollected() { return operations_ != 0; }

	//判断某个标记掩码是否被设置
	inline bool IsCollected(const CollecteOPType eOPType)
	{
		if (eOPType >= 0 && eOPType < MaxCollectedOp)
			return (operations_ & (1 << (eOPType & 31))) != 0;
		else return false;
	}
protected:
	int	operations_;
};


#endif

