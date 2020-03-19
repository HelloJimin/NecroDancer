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

	void addItem(item* item);
	void swapItem(int arrNum, item*& item , int itemNum);

	vector<item*> getItemList() { return _vItem; }
	vector<item*>* getItemList_Reference() { return &_vItem; }

	item* getWeapon();
	item* getShovel();
	item* getBomb();

	void throwItem();

	void itemPosionSet();
};

