#pragma once
#include "shovel.h"
#include "attack.h"
#include"body.h"
#include"feet.h"
#include"coin.h"
#include"dagger.h"
#include "singletonBase.h"
#include"bomb.h"
#include"tileNode.h"
#include"torch.h"
#include"hpSlot.h"
#include"apple.h"
class itemManager :  public singletonBase<itemManager>
{
private:
	tagTile* _map;

	vector<item*> _vItem;
public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	item* addItem(string name, int x, int y);
	void addCoin(int coinValue, int x, int y);

	void setMap();
	vector<item*> getItemList() { return _vItem; }
	vector<item*>& getItemList_ref() { return _vItem; }

	void removeItem(int arrNum);

	void addItemList(string name,int x, int y);

	void shopKeeperDie();
};

