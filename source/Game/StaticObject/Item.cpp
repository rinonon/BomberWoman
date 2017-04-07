#include "Game\StaticObject\Item.h"
#include "stdCommon.h"
#include "ResourceLoader.h"

Item::Item(int x, int y, Item::Type type) :
mItemType(type){

	mType = StaticObject::TYPE_ITEM;

	mX = x;
	mY = y;
}

Item::~Item() {
}

Item::Type Item::getItemType() const {
	return mItemType;
}

void Item::remove() {
	mType = StaticObject::TYPE_NONE;
}

void Item::draw() const {
	if (mItemType != TYPE_NONE) {
		DxLib::DrawGraph(mX * 32, mY * 32, ResourceLoader::getInstance()->getHdImg(mGraphHd[mItemType]), TRUE);
	}
}