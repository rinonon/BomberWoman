#include "Game\DynamicObject\Enemy.h"
#include "Game\StaticObject\StaticObject.h"
#include "ResourceLoader.h"
#include "stdCommon.h"

namespace {
int convertCellToInner(int x) {
	return x * 16000 + 8000;
}
//内部単位から画素単位へ
int convertInnerToPixel(int x) {
	return  (x - 8000 + 500) / 1000;
}
} //namespace

Enemy::Enemy(int x, int y) {
	mType = DynamicObject::TYPE_ENEMY;
	mX = convertCellToInner(x);
	mY = convertCellToInner(y);

	mDirectionX = mDirectionY = 0;
	switch (DxLib::GetRand(3)) {
	case 0: mDirectionX = 1; break;
	case 1: mDirectionX = -1; break;
	case 2: mDirectionY = 1; break;
	case 3: mDirectionY = -1; break;
	}
}

Enemy::~Enemy(){
}

void Enemy::move(const std::vector<StaticObject*> soList) {
	int dx, dy;
	getVelocity(&dx, &dy);

	//移動後の座標
	int movedX = mX + dx;
	int movedY = mY + dy;

	int wallX, wallY; //障害物の座標

	bool hitX = false; //ｘだけ移動したときあたるか
	bool hitY = false; //ｙだけ移動したときあたるか
	bool hit = false;

	for (size_t i = 0; i < soList.size(); i++) {
		soList[i]->getCell(&wallX, &wallY); 
		if (isIntersectWall(movedX, mY, wallX, wallY)) {
			hitX = hit = true;
		}
		else if (isIntersectWall(mX, movedY, wallX, wallY)) {
			hitY = hit = true;
		}
	}

	if (hitX && !hitY) {
		mY = movedY;
	}
	else if (!hitX && hitY) {
		mX = movedX;
	}
	else {
		for (size_t i = 0; i < soList.size(); i++) {
			soList[i]->getCell(&wallX, &wallY);
			if (isIntersectWall(movedX, movedY, wallX, wallY)){
				hit = true;
			}
		}
		if (!hit) {
			mX = movedX;
			mY = movedY;
		}
	}
	//敵なら向き変え
	if (hit) {
		mDirectionX = mDirectionY = 0;
		switch (DxLib::GetRand(3)) {
		case 0: mDirectionX = 1; break;
		case 1: mDirectionX = -1; break;
		case 2: mDirectionY = 1; break;
		case 3: mDirectionY = -1; break;
		}
	}
}

void Enemy::draw() {
	int dstX = convertInnerToPixel(mX);
	int dstY = convertInnerToPixel(mY);

	DxLib::DrawGraph(dstX * 2, dstY * 2, ResourceLoader::getInstance()->getHdImg(mHdGraph), true); //解像度が倍になったので2倍
}


void Enemy::getVelocity(int* dx, int* dy) {
	getDirection(dx, dy);

	*dx *= ENEMY_SPEED;
	*dy *= ENEMY_SPEED;
}

void Enemy::getDirection(int* dx, int* dy) {

	*dx = mDirectionX;
	*dy = mDirectionY;
}

