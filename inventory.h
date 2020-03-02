#pragma once
class inventory
{
private:
	vector<item*> _vItem;
public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addItem(item* item) { item->setInven(true); _vItem.push_back(item); }
};

