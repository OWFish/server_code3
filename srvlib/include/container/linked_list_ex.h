#ifndef _LINKED_LIST_EX_H_
#define _LINKED_LIST_EX_H_


#include <set>
/*
	使用内存管理器扩展了一下List链表,
*/
namespace container
{
template<typename DATA,int ONE_TIME_COUNT=1024>
class LinkedListEx:
	public BaseLinkedList<DATA>
{
public:
	typedef ObjPool<LinkedNode<DATA>, ONE_TIME_COUNT> LinkNodeMgr;

	virtual ~LinkedListEx()
	{
		this->clear();
	}
protected:
	virtual LinkedNode<DATA>* allocNode()
	{
		LinkedNode<DATA>* result = node_pool_->Alloc();
		return result;
	}

	virtual void freeNode(LinkedNode<DATA> *pNode)
	{
		node_pool_->Free(pNode);//放回内存池
	}
public:
	static LinkNodeMgr*	node_pool_;	
};
}


#endif


