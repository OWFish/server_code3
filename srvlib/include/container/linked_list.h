#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
/******************************************************************
 *
 *	$ ������ $
 *
 *	ʵ�ֶ�̬��ӡ�����ڵ㡣��Vectorһ����������Ҳ��һ�������࣬����
 *  Vector�Ƚϣ������ڽ���ɾ���ڵ��ʱ���ܹ�����ķ���Ч�ʣ�ȱ�����Ǳ��б�
 *  �����˷��ڴ棨�ڴ濪��Ϊ3~4��������������ʵ�ʱ��Ч�ʼ��͡�
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
* ����ڵ���
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
* �����������
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
	//�������ñ�������
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
	//�Ƴ�һ���ڵ㣬�����ڵ����Ĺ������Ƴ��ڵ�Ӷ��ƻ���������
	inline void remove(LinkedNode<T>* pNode, bool boFree = true)
	{
		if (pNode == enuming_)
			enuming_ = pNode->prev_;

		list_->remove(pNode, boFree);
	}
	//��ͷ��ʼ�����ڵ�
	inline LinkedNode<T>* first()
	{
		return enuming_ = list_->first();
	}
	//������һ���ڵ�
	inline LinkedNode<T>* next()
	{
		return enuming_ = (enuming_ ? enuming_->next_ : list_->first());
	}
	//��ǰ�������Ľڵ�
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
* ������
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
	//��ȡ��һ���ڵ�
	inline LinkedNode<T>* first()
	{
		return first_node_;
	}
	//��ȡ���һ���ڵ�
	inline LinkedNode<T>* last()
	{
		return last_node_;
	}
	//��ȡ�ڵ�����
	inline int count() const
	{
		return count_;
	}
	/* ��pNode�ڵ��ǰ������½ڵ�
	 * ���pNodeΪ�����ʾ���뵽�������ʼλ��
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
	/* ��pNode�ڵ�ĺ�������½ڵ�
	 * ���pNodeΪ�����ʾ���뵽�����ĩβ
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

	/* ��pNode�ڵ��ǰ������½ڵ�
	 * ���pNodeΪ�����ʾ���뵽�������ʼλ��
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

	//����linkAfer������һ�����е�node
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
	//�����ݲ��뵽����ͷ��
	inline LinkedNode<T>* linkAtFirst(const T& data)
	{
		return linkBefore(data, first_node_);
	}
	//��������ӵ�����β��
	inline LinkedNode<T>* linkAtLast(const T& data)
	{
		return linkAfter(data, last_node_);
	}
	inline LinkedNode<T>* TransferAtLast(LinkedNode<T>* pNewNode)
	{
		return Transfer(pNewNode, last_node_);
	}
	//ͨ��������ȡ����ڵ�
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
	/* �Ƴ�һ������ڵ�
	 * ��ע��� �������ͨ�������������������Ƴ�����������õ�������CLinkedListIterator::remove����
	 */
	inline void remove(LinkedNode<T>* node, bool free_flag = true)
	{
		if (node && node->self_ == this)
		{
			//�Ƴ��ڵ�
			if (node->prev_)
				node->prev_->next_ = node->next_;

			if (node->next_)
				node->next_->prev_ = node->prev_;

			if (node == first_node_)
				first_node_ = node->next_;

			if (node == last_node_)
				last_node_ = node->prev_;

			//�����е������в��Բ�������ǰ�����ڵ�
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

			//���ٽڵ�
			if (free_flag)	freeNode(node);

			count_--;
			assert(count_ >= 0);
		}
	}
	//�������
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
	/* ����һ������ڵ����Ĭ�ϵĲ���ʱʹ��new�����ڴ沢����
	 * �����ͨ�����Ǵ˷���ʵ������ڵ���ڴ����
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
	/* ����һ������ڵ����Ĭ�ϵĲ���ʱʹ��delete�������ͷ��ڴ�
	 * �����ͨ�����Ǵ˷���ʵ������ڵ���ڴ����
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

