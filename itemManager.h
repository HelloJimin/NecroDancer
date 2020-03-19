#pragma once
#include "shovel.h"
#include "attack.h"
#include"body.h"
#include"feet.h"
#include"torch.h"
#include"coin.h"
#include"dagger.h"
#include "singletonBase.h"
#include"bomb.h"
class itemManager :  public singletonBase<itemManager>
{
private:

public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	item* addItem(string name);
	item* addCoin(int coinValue, int x, int y);

};

