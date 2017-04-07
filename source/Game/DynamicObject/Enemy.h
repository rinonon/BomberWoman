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
	void getVelocity(int* dx, int* dy); //�P�ʎ��ԓ�����̈ړ���
	void getDirection(int* dx, int* dy); //�ړ�����

	const int ENEMY_SPEED = 500;
	const int mHdGraph = 3;
};

