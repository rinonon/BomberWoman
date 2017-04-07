#include "Game\StaticObject\Bomb.h"
#include "stdCommon.h"
#include "ResourceLoader.h"
#include "Game\DynamicObject\Player.h"

Bomb::Bomb(int x, int y, Player* player) : 
	mBombOwner(player),
	mCount(0),
	mExplosionFlag(false),
	mPower(0),
	mCollisionFlag(false){
	mType = StaticObject::TYPE_BOMB;
	mX = x;
	mY = y;
	mPower = player->getBombPower();
}

Bomb::~Bomb() {
}

void Bomb::move(int* wallsX, int* wallsY, int wallNumber) {
	//キックアイテム追加用
	return;
}

void Bomb::draw() const {
	//床の上に描写
	DxLib::DrawGraph(mX * 32, mY * 32, ResourceLoader::getInstance()->getHdFloor(), TRUE); 
	DxLib::DrawGraph(mX * 32, mY * 32, ResourceLoader::getInstance()->getHdImg(mGraphHd), TRUE);
}

bool Bomb::isExplosion() const {
	return mExplosionFlag;
}

void Bomb::update() {

	if (mCount == EXPLOSION_TIME || mBurnFlag) {
		mExplosionFlag = true;
		mType = TYPE_NONE;
	}

	mCount++;
}

Player* Bomb::getOwner() const {
	return mBombOwner;
}

int Bomb::getPower() const {
	return mPower;
}

void Bomb::setCollisionFlag(bool f) {
	mCollisionFlag = f;
}

bool Bomb::getCollisionFlag() const {
	return mCollisionFlag;
}