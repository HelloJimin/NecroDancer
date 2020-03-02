#pragma once

enum itemType
{
	SHOVEL,
	ATTACK,
	BODY,
	FEET,
	TORCH,
	ITEM,
	BOMB,
};
class item
{

protected:
	string _name;
	string _description;
	image* _slotImg;
	image* _itemImg;
	RECT _rc;
	itemType _type;

	bool _inInventory;
	bool _upDown;
	//bool _silhouette;
	float _x, _y;
	int _waveCnt;

	int price;
	int diamondPrice;
public:
	item();
	~item();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual int getInfo();


	void setItem(itemType type, string name, string description);
	void setInven(bool inven) { _inInventory = inven; }
	void animation();
	void draw(HDC hdc);
	string getName() { return _name; }
	void setRect(POINT xy) { _x = xy.x; _y = xy.y; }
	void setRect(RECT tile) { _rc = tile; }
	RECT getRc() { return _rc; }

	image* getImg() { return _itemImg; }
};

