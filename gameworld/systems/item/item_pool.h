#pragma  once

class Item;
struct ItemData;


class ItemPool : public Singleton<ItemPool>
{
public:
	friend Singleton<ItemPool>;
	int64_t allocSeries();

	Item* CreateItem(ItemData* data);
	Item* CreateItem(int id, int count);

	//���÷�����ID��������ID��������Ʒϵ�кŵ�����
	inline void SetServerId(const int sid) { server_id_ = sid; }
private:
	ItemPool();
	~ItemPool();

	Item* NewItem(int type);
private:
	int			series_;	//��Ʒϵ��ֵ
	int			server_id_;	//������ID
	int			last_time_; // ��һ�η���ʱ��
};
