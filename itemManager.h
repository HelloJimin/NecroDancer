#pragma once
#include "shovel.h"
#include "singletonBase.h"

class itemManager :  public singletonBase<itemManager>
{
private:
	vector<item*> _vItem;


public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	item* addItem(string name);


};

