#pragma once

#include "Game\DynamicObject\DynamicObject.h"


class Enemy : public DynamicObject {
public:
	Enemy(int x, int y);
	~Enemy();
	// virtual = 0
	void move(const std::vector<StaticObject*> soList) override;
	void draw() override;

private:
	void getVelocity(int* dx, int* dy); //単位時間当たりの移動量
	void getDirection(int* dx, int* dy); //移動方向

	const int ENEMY_SPEED = 500;
	const int mHdGraph = 3;
};

