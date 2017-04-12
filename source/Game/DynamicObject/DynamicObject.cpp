#include "Game\DynamicObject\DynamicObject.h"
#include "stdCommon.h"

namespace {

static const int HALF_SIZE = 5000; //衝突判定用（ちょうどいいさいず）

int convertCellToInner(int x) {
	return x * 16000 + 8000;
}
//内部単位から画素単位へ
int convertInnerToPixel(int x) {
	return  (x - 8000 + 500) / 1000;
}

} //namespace

DynamicObject::DynamicObject() : 
mX(0),
mY(0),
mType(TYPE_NONE)
{}

DynamicObject::~DynamicObject() {

}

void DynamicObject::set(int x, int y) {
	//1画素 -> 1000
	//内部座標値に変換
	mX = convertCellToInner(x);
	mY = convertCellToInner(y);
}

void DynamicObject::getCell(int* x, int* y) const {
	*x = mX / 16000;
	*y = mY / 16000;
}

void DynamicObject::getPos(int* x, int* y) const {
	*x = mX;
	*y = mY;
}

void DynamicObject::doCollisionReactionToDynamic(DynamicObject* another) {
	//相手が死んでいればするー
	if (!another->isAlive()) {
		return;
	}

	DynamicObject& o1 = *this;
	DynamicObject& o2 = *another;
	if (o1.isIntersect(o2)) { //衝突判定

		//プレイヤーの死亡はんてい
		if ((o1.getType() == TYPE_PLAYER) && (o2.getType() == TYPE_ENEMY)) {
			o1.die();
		}
		else if ((o1.getType() == TYPE_ENEMY) && (o2.getType() == TYPE_PLAYER)) {
			o2.die();
		}
	}
}

bool DynamicObject::isIntersect(const DynamicObject& o) const {
	int al = mX - HALF_SIZE; //left A
	int ar = mX + HALF_SIZE; //right A
	int bl = o.mX - HALF_SIZE; //left B
	int br = o.mX + HALF_SIZE; //right B
	if ((al < br) && (ar > bl)) {
		int at = mY - HALF_SIZE; //top A
		int ab = mY + HALF_SIZE; //bottom A
		int bt = o.mY - HALF_SIZE; //top B
		int bb = o.mY + HALF_SIZE; //bottom B
		if ((at < bb) && (ab > bt)) {
			return true;
		}
	}
	return false;
}


bool DynamicObject::isIntersectWall(int x, int y, int wallX, int wallY) {
	int wx = convertCellToInner(wallX);
	int wy = convertCellToInner(wallY);

	int al = x - HALF_SIZE; //left A
	int ar = x + HALF_SIZE; //right A

	if (mDirectionX != 0) {
		al = x - 8000;
		ar = x + 8000;
	}

	int bl = wx - 8000; //left B
	int br = wx + 8000; //right B
	if ((al < br) && (ar > bl)) {
		int at = y - HALF_SIZE; //top A
		int ab = y + HALF_SIZE; //bottom A

		if (mDirectionY != 0) {
			at = y - 8000;
			ab = y + 8000;
		}
		int bt = wy - 8000; //top B
		int bb = wy + 8000; //bottom B
		if ((at < bb) && (ab > bt)) {
			return true;
		}
	}
	return false;
}

bool DynamicObject::isIntersectStatic(int x, int y, int cellX, int cellY) {
	int wx = convertCellToInner(cellX);
	int wy = convertCellToInner(cellY);

	int al = x - HALF_SIZE; //left A
	int ar = x + HALF_SIZE; //right A
	int bl = wx - HALF_SIZE; //left B
	int br = wx + HALF_SIZE; //right B
	if ((al < br) && (ar > bl)) {
		int at = y - HALF_SIZE; //top A
		int ab = y + HALF_SIZE; //bottom A
		int bt = wy - HALF_SIZE; //top B
		int bb = wy + HALF_SIZE; //bottom B
		if ((at < bb) && (ab > bt)) {
			return true;
		}
	}
	return false;
}


void DynamicObject::die() {
	mType = TYPE_NONE;
}

bool DynamicObject::isAlive() const{
	if (mType == TYPE_NONE) {
		return false;
	}
	return true;
}

DynamicObject::Type DynamicObject::getType() const {
	return mType;
}
