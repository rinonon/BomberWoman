#pragma once

#include "Game\StaticObject\StaticObject.h"
#include <vector>
#include <memory>

class Player;

class Bomb : public StaticObject{
public:
	Bomb(int x, int y, Player* player);
	~Bomb();

	void move(int* wallsX, int* wallsY, int wallNumber);
	void draw() const;
	void update();
	int getPower() const;
	bool isExplosion() const;
	Player* getOwner() const;
	void setCollisionFlag(bool f);
	bool getCollisionFlag() const override;

private:
	int mCount;

	//îöíeÉpÉâÉÅÅ[É^
	static const int EXPLOSION_TIME = 300; //5ïb
	Player* mBombOwner;
	int mPower;
	bool mExplosionFlag;
	bool mCollisionFlag;
	int mGraphHd = 0;
};