#include "Game\DynamicObject\Enemy.h"
#include "Game\StaticObject\StaticObject.h"
#include "ResourceLoader.h"
#include "stdCommon.h"

namespace {
int convertCellToInner(int x) {
	return x * 16000 + 8000;
}
//“à•”’PˆÊ‚©‚ç‰æ‘f’PˆÊ‚Ö
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

	//ˆÚ“®Œã‚ÌÀ•W
	int movedX = mX + dx;
	int movedY = mY + dy;

	int wallX, wallY; //áŠQ•¨‚ÌÀ•W

	bool hitX = false; //‚˜‚¾‚¯ˆÚ“®‚µ‚½‚Æ‚«‚ ‚½‚é‚©
	bool hitY = false; //‚™‚¾‚¯ˆÚ“®‚µ‚½‚Æ‚«‚ ‚½‚é‚©
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
	//“G‚È‚çŒü‚«•Ï‚¦
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

	DxLib::DrawGraph(dstX * 2, dstY * 2, ResourceLoader::getInstance()->getHdImg(mHdGraph), true); //‰ğ‘œ“x‚ª”{‚É‚È‚Á‚½‚Ì‚Å2”{
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

