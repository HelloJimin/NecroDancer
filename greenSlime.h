#pragma once
#include"monster.h"
class greenSlime : public monster
{
private:
	int front[4];

	int _rhythm;
public:

	greenSlime();
	~greenSlime();

	virtual HRESULT init(string name, int x, int y, int coin, tagTile * map) override;
	virtual void update() override;
	virtual void render(HDC hdc) override;
	void silhouetteRender(HDC hdc);
};

