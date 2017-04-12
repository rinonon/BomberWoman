#include "Game\StaticObject\Fire.h"
#include "stdCommon.h"
#include "ResourceLoader.h"

Fire::Fire(int x, int y, Fire::Type type) :
	mFireType(type),
	mCount(0) {

	mType = StaticObject::TYPE_FIRE;
	mX = x;
	mY = y;
}

Fire::~Fire() {

}

void Fire::update() {
	if (mCount == EXPLOSION_LIFE) {
		mType = StaticObject::TYPE_NONE;
	}
	mCount++;
}

void Fire::draw() const {

	if (mFireType == TYPE_NONE) {
		return;
	}

	DxLib::DrawGraph(mX * 32, mY * 32, ResourceLoader::getInstance()->getHdImg(mGraphHd[static_cast<int>(mFireType)]), TRUE);
}

void Fire::setFireType(Fire::Type type)
{
	mFireType = type;
}

Fire::Type Fire::getFireType()
{
	return mFireType;
}