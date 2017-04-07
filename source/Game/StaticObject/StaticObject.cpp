#include "Game\\StaticObject\StaticObject.h"
#include "stdCommon.h"

//èâä˙ílÇÕï«
StaticObject::StaticObject() :
	mType(TYPE_NONE),
	mX(0),
	mY(0),
	mBurnFlag(false)
{ 
}

StaticObject::~StaticObject() {

}

StaticObject::Type StaticObject::getType() const {
	return mType;
}

void StaticObject::getCell(int* x, int* y) const {
	*x = mX;
	*y = mY;
}

bool StaticObject::isExist() const {
	if (mType == StaticObject::TYPE_NONE) {
		return false;
	}
	return true;
}

void StaticObject::setBurnFlag(bool f) {
	mBurnFlag = f;
}

bool StaticObject::getBurnFlag() const {
	return mBurnFlag;
}

void StaticObject::update() {
	return;
}

bool StaticObject::getCollisionFlag() const {
	return false;
}