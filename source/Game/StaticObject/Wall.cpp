#include "Game\StaticObject\Wall.h"
#include "ResourceLoader.h"
#include "stdCommon.h"

Wall::Wall(int x, int y) {
	mType = StaticObject::TYPE_WALL;

	mX = x;
	mY = y;
}

Wall::~Wall() {
}

void Wall::draw() const { 
	DxLib::DrawGraph(mX * 32, mY * 32, ResourceLoader::getInstance()->getHdImg(mGraphHd), FALSE);
}