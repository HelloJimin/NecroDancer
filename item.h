#pragma once

enum slotType
{
	BODY,
	ATTACK,
	SHOVEL,
	FEET,
	TORCH,
	ITEM,
	BOMB,
};
struct tagPrice
{
	image* img;
	int frameX;
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

	int _price;

	bool _isGlass;
	bool _isShop;

	int _currentTileIndex;

	vector<tagPrice*> _vPriceImg;
public:
	item();
	~item();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void active();

	virtual int getValue();
	virtual bool getBool();
	virtual void setValue(int num);


	void setItem(slotType type, string name, string description, int x, int y, int price);
	void animation();
	void draw(HDC hdc);

	void setInven(bool inven) { _inInventory = inven; }
	void setRect(POINT xy) { _x = xy.x; _y = xy.y; }
	void rcSet();

	RECT getRc() { return _rc; }

	image* getImg() { return _itemImg; }

	slotType getType() { return _type; }

	string getName() { return _name; }

	int getCurrentTile() { return _currentTileIndex; }

	float getX() { return _x; }
	float getY() { return _y; }

	bool getIsShop() { return _isShop; }
	int getPrice() { return _price; }

	void setPrice(int price);

	void shopCheck();
};

