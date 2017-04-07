#include "Game\StaticObject\Brick.h"
#include "stdCommon.h"
#include "ResourceLoader.h"

Brick::Brick(int x, int y) :
mCount(0) {

	mType = StaticObject::TYPE_BRICK;

	mX = x;
	mY = y;
}

Brick::~Brick() {
}

void Brick::draw() const {
	DxLib::DrawGraph(mX * 32, mY * 32, ResourceLoader::getInstance()->getHdImg(mGraphHd[mBurnFlag]), FALSE); //ŠëŒ¯‚©‚à
}

void Brick::update() {
	if (mBurnFlag) {
		if (mCount == EXPLOSION_LIFE) {
			mType = TYPE_NONE;
		}
		else {
			mCount++;
		}
	}
}