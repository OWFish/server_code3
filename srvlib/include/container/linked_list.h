#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
/******************************************************************
 *
 *	$ 链表类 $
 *
 *	实现动态添加、插入节点。与Vector一样，链表类也是一个容器类，但与
 *  Vector比较，链表在进行删除节点的时候能够更大的发挥效率，缺点则是比列表
 *  更加浪费内存（内存开销为3~4倍）且在随机访问的时候效率极低。
 *
 *****************************************************************/
#include <assert.h>
#include "memory/objpool.hpp"

namespace container
{
template <typename T>
class BaseLinkedList;

template <typename T>
class ListIterator;

/*************************
* 链表节点类
**************************/
template <typename T>
class LinkedNode
{
public:
	LinkedNode() {}
	inline operator T& ()
	{
		return data_;
	}
	T				data_;
public:
	LinkedNode<T>*	prev_;
	LinkedNode<T>* next_;
	BaseLinkedList<T>* self_;
};

/*************************
* 链表迭代器类
**************************/
template <typename T>
class ListIterator
{
	friend class BaseLinkedList<T>;
public:
	ListIterator()
	{
		list_ = NULL;
		enuming_ = NULL;
		prev_ = next_ = NULL;
	}
	ListIterator(BaseLinkedList<T>& list)
	{
		//list_ = NULL;
		//enuming_ = NULL;
		//prev_ = next_ = NULL;
		//setList(list);

		//wuzhihong edit
		list_ = &list;
		enuming_ = NULL;
		next_ = NULL;
		prev_ = list.iterator_;

		if (prev_) prev_->next_ = this;

		list.iterator_ = this;
	}
	~ListIterator()
	{
		if (list_)
		{
			if (prev_) prev_->next_ = next_;

			if (next_) next_->prev_ = prev_;

			if (this == list_->iterator_)
				list_->iterator_ = prev_;

			list_ = NULL;
			enuming_ = NULL;
			prev_ = next_ = NULL;
		}
	}
	//重新设置遍历对象
	inline void setList(BaseLinkedList<T>& list)
	{
		this->~ListIterator();
		list_ = &list;
		enuming_ = NULL;
		next_ = NULL;
		prev_ = list.iterator_;

		if (prev_) prev_->next_ = this;

		list.iterator_ = this;
	}
	//移除一个节点，方便在迭代的过程中移除节点从而破坏迭代过程
	inline void remove(LinkedNode<T>* pNode, bool boFree = true)
	{
		if (pNode == enuming_)
			enuming_ = pNode->prev_;

		list_->remove(pNode, boFree);
	}
	//从头开始遍历节点
	inline LinkedNode<T>* first()
	{
		return enuming_ = list_->first();
	}
	//遍历下一个节点
	inline LinkedNode<T>* next()
	{
		return enuming_ = (enuming_ ? enuming_->next_ : list_->first());
	}
	//当前遍历到的节点
	inline LinkedNode<T>* current()
	{
		return enuming_;
	}
private:
	LinkedNode<T>*		enuming_;
	BaseLinkedList<T>*	list_;
	ListIterator<T>* prev_;
	ListIterator<T>* next_;
};

/*************************
* 链表类
**************************/
template <typename T>
class BaseLinkedList
{
	friend class ListIterator<T>;
public:
	typedef T InstancesType;
	typedef LinkedNode<T> NodeType;
	typedef ListIterator<T> Iterator;
public:
	BaseLinkedList(ObjPool< LinkedNode<T> >* alloc = NULL)
	{
		first_node_ = last_node_ = NULL;
		iterator_ = NULL;
		count_ = 0;
		allocator_ = alloc;
	}
	virtual ~BaseLinkedList()
	{
		clear();
	}
	//获取第一个节点
	inline LinkedNode<T>* first()
	{
		return first_node_;
	}
	//获取最后一个节点
	inline LinkedNode<T>* last()
	{
		return last_node_;
	}
	//获取节点数量
	inline int count() const
	{
		return count_;
	}
	/* 在pNode节点的前面插入新节点
	 * 如果pNode为空则表示插入到链表的起始位置
	 */
	LinkedNode<T>* linkBefore(const T& data, LinkedNode<T>* node = NULL)
	{
		assert(!node || node->self_ == this);

		if (!node) node = first_node_;

		LinkedNode<T>* pPrev = node ? node->prev_ : NULL;
		LinkedNode<T>* new_node = allocNode();

		new_node->data_ = data;
		new_node->prev_ = pPrev;
		new_node->next_ = node;

		if (pPrev)
			pPrev->next_ = new_node;
		else first_node_ = new_node;

		if (node)
			node->prev_ = new_node;
		else last_node_ = new_node;

		new_node->self_ = this;
		count_++;
		return new_node;
	}
	/* 在pNode节点的后面插入新节点
	 * 如果pNode为空则表示插入到链表的末尾
	 */
	LinkedNode<T>* linkAfter(const T& data, LinkedNode<T>* pNode = NULL)
	{
		assert(!pNode || pNode->self_ == this);

		if (!pNode) pNode = last_node_;

		LinkedNode<T>* pNext = pNode ? pNode->next_ : NULL;
		LinkedNode<T>* pNewNode = allocNode();

		pNewNode->data_ = data;
		pNewNode->prev_ = pNode;
		pNewNode->next_ = pNext;

		if (pNext)
			pNext->prev_ = pNewNode;
		else last_node_ = pNewNode;

		if (pNode)
			pNode->next_ = pNewNode;
		else first_node_ = pNewNode;

		pNewNode->self_ = this;
		count_++;
		return pNewNode;
	}

	/* 在pNode节点的前面插入新节点
	 * 如果pNode为空则表示插入到链表的起始位置
	 */
	LinkedNode<T>* linkBefore(LinkedNode<T>* new_node, LinkedNode<T>* node = NULL)
	{
		assert(!node || node->self_ == this);

		if (!node) node = first_node_;

		LinkedNode<T>* pPrev = node ? node->prev_ : NULL;

		new_node->prev_ = pPrev;
		new_node->next_ = node;

		if (pPrev)
			pPrev->next_ = new_node;
		else first_node_ = new_node;

		if (node)
			node->prev_ = new_node;
		else last_node_ = new_node;

		new_node->self_ = this;
		count_++;
		return new_node;
	}

	//重载linkAfer，插入一个已有的node
	LinkedNode<T>* Transfer(LinkedNode<T>* pNewNode, LinkedNode<T>* pNode = NULL)
	{
		assert(!pNode || pNode->self_ == this);
		assert(pNewNode->self_ == NULL);

		if (!pNode) pNode = last_node_;

		LinkedNode<T>* pNext = pNode ? pNode->next_ : NULL;

		pNewNode->prev_ = pNode;
		pNewNode->next_ = pNext;

		if (pNext)
			pNext->prev_ = pNewNode;
		else last_node_ = pNewNode;

		if (pNode)
			pNode->next_ = pNewNode;
		else first_node_ = pNewNode;

		pNewNode->self_ = this;
		count_++;
		return pNewNode;
	}
	//将数据插入到链表头部
	inline LinkedNode<T>* linkAtFirst(const T& data)
	{
		return linkBefore(data, first_node_);
	}
	//将数据添加到链表尾部
	inline LinkedNode<T>* linkAtLast(const T& data)
	{
		return linkAfter(data, last_node_);
	}
	inline LinkedNode<T>* TransferAtLast(LinkedNode<T>* pNewNode)
	{
		return Transfer(pNewNode, last_node_);
	}
	//通过索引获取链表节点
	LinkedNode<T>* getNodeAt(int nIndex)
	{
		for (LinkedNode<T>* pNode = first_node_; pNode; pNode = pNode->next_)
		{
			if (nIndex <= 0)
				return pNode;

			nIndex--;
		}

		return NULL;
	}
	/* 移除一个链表节点
	 * ★注意★ 如果正在通过迭代器遍历链表，则移除操作必须调用迭代器的CLinkedListIterator::remove函数
	 */
	inline void remove(LinkedNode<T>* node, bool free_flag = true)
	{
		if (node && node->self_ == this)
		{
			//移除节点
			if (node->prev_)
				node->prev_->next_ = node->next_;

			if (node->next_)
				node->next_->prev_ = node->prev_;

			if (node == first_node_)
				first_node_ = node->next_;

			if (node == last_node_)
				last_node_ = node->prev_;

			//从所有迭代器中测试并修正当前遍历节点
			if (iterator_)
			{
				Iterator* it = iterator_;

				while (it)
				{
					if (node == it->enuming_)
						it->enuming_ = node->prev_;

					it = it->prev_;
				}
			}

			node->self_ = NULL;

			//销毁节点
			if (free_flag)	freeNode(node);

			count_--;
			assert(count_ >= 0);
		}
	}
	//清空链表
	virtual void clear()
	{
		LinkedNode<T>* pNode = first_node_, *pNextNode;

		while (pNode)
		{
			pNextNode = pNode->next_;
			freeNode(pNode);
			pNode = pNextNode;
		}

		first_node_ = last_node_ = NULL;
		count_ = 0;
	}
protected:
	/* 申请一个链表节点对象，默认的操作时使用new申请内存并构造
	 * 子类可通过覆盖此方法实现链表节点的内存管理
	 */
	virtual LinkedNode<T>* allocNode()
	{
		if (allocator_)
		{
			return allocator_->Alloc();
		}
		else
		{
			return new LinkedNode<T>;
		}
	}
	/* 销毁一个链表节点对象，默认的操作时使用delete析构并释放内存
	 * 子类可通过覆盖此方法实现链表节点的内存管理
	 */
	virtual void freeNode(LinkedNode<T>* pNode)
	{
		if (allocator_)
		{
			allocator_->Free(pNode);
		}
		else
		{
			delete pNode;
		}
	}
private:
	LinkedNode<T>* first_node_;
	LinkedNode<T>* last_node_;
	Iterator*   	iterator_;
	int			count_;
	ObjPool< LinkedNode<T> >*	allocator_;
};
};

#endif

