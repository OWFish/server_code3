#pragma once

#include <vector>


/***********************************************************
* ��Ʒ ����������
* �򻯰棬ֻ���˵�ǰ��Ҫ�Ĺ���
***********************************************************/


struct ItemData;
class Item;

class BaseContainer
{
public:
	BaseContainer();
	virtual ~BaseContainer();

	static const int MAX_ITEM_COUNT = 1 << 30;

	int GetCountById(int id) const;
	int GetCountById(int64_t uid) const;

protected:
	bool AddItem(Item* item, bool notify = true, bool showTip = true);		//����������Ʒ���
	bool AddItem(ItemData* data, bool notify = true);	//������Ʒ������� 
	bool AddItem(int id, int count, bool showTip = true);					//��������id���

	bool TakeOutItem(Item* item);
	bool DeleteItem(int64_t uid, int count);

	size_t Count() { return item_list_.size(); }

protected:
	virtual void NotifyDelete(int64_t uid, int count){}
	virtual void NotifyAdd(Item *item, bool showTip = true){}	//���ͻ��˼ӵ��Ƿ���ʾ��ʾ(��װ���)
	virtual void NotifyUpdate(int64_t uid, int count, bool showTip = true){}

	virtual void OnAddItem(Item *item) {}

private:
	bool RemoveItem(int index);
	
protected:
	std::vector<Item*> item_list_;
	bool			need_save_;
};