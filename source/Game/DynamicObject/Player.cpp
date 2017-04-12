#include "Game\DynamicObject\Player.h"
#include "Game\StaticObject\StaticObject.h"
#include "GameController.h"
#include "stdCommon.h"
#include "ResourceLoader.h"

namespace {
int convertCellToInner(int x) {
	return x * 16000 + 8000;
}
//内部単位から画素単位へ
int convertInnerToPixel(int x) {
	return  (x - 8000 + 500) / 1000;
}
} //namespace


Player::Player(int x, int y, int id) :
	mBombPower(1),
	mBombNumber(1),
	mPlayerID(id),
	mSetedBombNumber(0),
	mCount(0),
	mPlayerDirection(4),
	mPrevDirection(2),
	mCurrentHdX(1),
	mPlayerHd(7)
{
	mType = DynamicObject::TYPE_PLAYER;
	mX = convertCellToInner(x);
	mY = convertCellToInner(y);
}

Player::~Player() {
}

void Player::setPlayerID(int pid) {
	mPlayerID = pid;
}

int Player::getPlayerID() const {
	return mPlayerID;
}

int Player::getBombPower() const {
	return mBombPower;
}

int Player::getBombNumber() const {
	return mBombNumber;
}

void Player::incrementBombPower() {
	mBombPower++;
}

void Player::incrementBombNomber() {
	mBombNumber++;
}

void Player::incrementSetedBombNumber() {
	mSetedBombNumber++;
}

void Player::decrementSetedBombNumber() {
	mSetedBombNumber--;
}

bool Player::hasBombButtonPressed() const {
	return GameController::getInstance()->isPressedNow(GameController::A, mPlayerID);
}	

int Player::getSetedBombNumber() const {
	return mSetedBombNumber;
}

void Player::move(const std::vector<StaticObject*> soList) {
	int dx, dy;
	getVelocity(&dx, &dy);

	//移動後の座標
	int movedX = mX + dx;
	int movedY = mY + dy;

	if (mPlayerDirection == 1 || mPlayerDirection == 3) {
		// x軸の移動
		int x, y;
		this->getCell(&x, &y);
		movedY = convertCellToInner(y);
	}
	else if (mPlayerDirection == 0 || mPlayerDirection == 2) {
		// y軸の移動
		int x, y;
		this->getCell(&x, &y);
		movedX = convertCellToInner(x);
	}


	//障害物の座標
	int wallX, wallY;

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
			if (isIntersectWall(movedX, movedY, wallX, wallY)) {
				hit = true;
			}
		}
		if (!hit) {
			mX = movedX;
			mY = movedY;
		}
	}
}


void Player::draw() {

	int dstX = convertInnerToPixel(mX);
	int dstY = convertInnerToPixel(mY);

	//mPlayerHdに　[mPlayerDirection][mCurrentHd]　を格納したい

	if (mPlayerDirection == 4) { //止まっている
		mCount = 0;
		mCurrentHdX = 1;
		mPlayerHd = (mPrevDirection) * 3 + mCurrentHdX;
	}

	else if (mPrevDirection == mPlayerDirection) { //前のフレームと同じ方向に動いている
		mCurrentHdX = static_cast<int>(mCount / CHANGE_GRAPH_TIME);
		if (mCurrentHdX > 2) {
			mCurrentHdX = 0;
			mCount = 0;
		}
		mPlayerHd = (mPlayerDirection) * 3 + mCurrentHdX;
		mPrevDirection = mPlayerDirection;
	}
	else { //動き始め
		mCount = 0;
		mPlayerHd = (mPlayerDirection) * 3 + mCurrentHdX;
		mPrevDirection = mPlayerDirection;
	}

	mCount++;

	if (mPlayerID == 0) {
		DxLib::DrawGraph(dstX * 2, dstY * 2, ResourceLoader::getInstance()->getHdPlayer1(mPlayerHd), true); //解像度が倍になったので2倍
	}
	else if (mPlayerID == 1) {
		DxLib::DrawGraph(dstX * 2, dstY * 2, ResourceLoader::getInstance()->getHdPlayer2(mPlayerHd), true); //解像度が倍になったので2倍
	}
}


void Player::getVelocity(int* dx, int* dy) {

	getDirection(dx, dy);

	*dx *= PLAYER_SPEED;
	*dy *= PLAYER_SPEED;
}

void Player::getDirection(int* dx, int* dy) {
	
	*dx = *dy = 0;

	mDirectionX = 0;
	mDirectionY = 0;

	if (GameController::getInstance()->isPressed(GameController::U, mPlayerID) == GameController::Pressed) {
		*dy = -1;
		mPlayerDirection = 0;
		mDirectionY = -1;
	}
	else if (GameController::getInstance()->isPressed(GameController::R, mPlayerID) == GameController::Pressed) {
		*dx = 1;
		mPlayerDirection = 1;
		mDirectionX = 1;
	}
	else if (GameController::getInstance()->isPressed(GameController::D, mPlayerID) == GameController::Pressed) {
		*dy = 1;
		mPlayerDirection = 2;
		mDirectionY = 1;
	}
	else if (GameController::getInstance()->isPressed(GameController::L, mPlayerID) == GameController::Pressed) {
		*dx = -1;
		mPlayerDirection = 3;
		mDirectionX = -1;
	}
	else {
		mPlayerDirection = 4;
	}
	
}
