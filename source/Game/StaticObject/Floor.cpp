#include "Game\StaticObject\Floor.h"
#include "ResourceLoader.h"
#include "stdCommon.h"

Floor::Floor(int x, int y) :
mBomb(0){
	mType = StaticObject::TYPE_FLOOR;

	mX = x;
	mY = y;
}

Floor::~Floor() {
}

void Floor::draw() const {
	//DxLib::DrawGraph(mX * 32, mY * 32, ResourceLoader::getInstance()->getHdImg(mGraphHd), FALSE);
}

