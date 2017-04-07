#pragma once

#include "Game\StaticObject\StaticObject.h"

class Brick : public StaticObject {
public:
	Brick(int x, int y);
	~Brick();

	void draw() const;
	void update() override;

private:
	int mGraphHd[2] = {1 , 2};
	int mCount;
	static const int EXPLOSION_LIFE = 60; //1•b
};