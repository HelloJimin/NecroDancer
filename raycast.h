#pragma once

struct ray
{
	POINT center;
	POINT end;
	float angle;
	int power;
};
class raycast
{
private:
	ray _ray;
public:
	raycast();
	~raycast();

	void update();
	void render(HDC hdc);

	void reset();
};

