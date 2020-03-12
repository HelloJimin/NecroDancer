#pragma once
class inventory
{
private:
	vector<item*> _vItem;
	bool _weapon;

public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addItem(item* item);
	void swapItem(int arrNum, item*& item);

	vector<item*> getItemList() { return _vItem; }
	vector<item*>* getItemList_Reference() { return &_vItem; }

	bool getWeapon() { return _weapon; }
};

