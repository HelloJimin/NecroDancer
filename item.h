#pragma once

enum slotType
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
	slotType _type;

	bool _inInventory;
	bool _upDown;
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

	virtual void active();

	virtual int getValue();


	void setItem(slotType type, string name, string description);
	void animation();
	void draw(HDC hdc);

	void setInven(bool inven) { _inInventory = inven; }
	void setRect(POINT xy) { _x = xy.x; _y = xy.y; }
	void rcSet();

	RECT getRc() { return _rc; }

	image* getImg() { return _itemImg; }

	slotType getType() { return _type; }

	string getName() { return _name; }
};

