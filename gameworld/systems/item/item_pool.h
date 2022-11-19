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

	//设置服务器ID，服务器ID将参与物品系列号的生成
	inline void SetServerId(const int sid) { server_id_ = sid; }
private:
	ItemPool();
	~ItemPool();

	Item* NewItem(int type);
private:
	int			series_;	//物品系列值
	int			server_id_;	//服务器ID
	int			last_time_; // 上一次分配时间
};
