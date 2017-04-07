#include "Game\State.h"
#include "Game\StaticObject\StaticObject.h"
#include "stdCommon.h"
#include "Game\DynamicObject\Player.h"
#include "Game\DynamicObject\Enemy.h"
#include "Game\StaticObject\Bomb.h"
#include <algorithm>
#include "Game\StaticObject\Wall.h"
#include "Game\StaticObject\Brick.h"
#include "Game\StaticObject\Fire.h"
#include "Game\StaticObject\Floor.h"
#include "Game\StaticObject\Item.h"

#include "ResourceLoader.h"
#include "GameController.h"

namespace { //名前なし空間

//マップサイズ
const int sWIDTH = 19;
const int sHEIGHT = 15;

struct StageData {
	int mEnemyNumber; //敵の数
	int mBrickRate; //煉瓦率(パーセント)
	int mItemPowerNumber; //爆風アイテムの数
	int mItemBombNumber; //爆弾アイテムの数
};

StageData gStageData[] = {
	{ 0, 50, 3, 4, },
	{ 3, 20, 5, 6, },
	{ 6, 30, 1, 2, },
};

//グリッド探索用　上下左右
int dx[4] = {0, 0, -1, 1}; 
int dy[4] = { -1, 1, 0, 0 };

} //namespace


void State::addBombList(BombRef& o) {
	mBombList.push_back(o);
}

void State::addFireList(FireRef& o) {
	mFireList.push_back(o);
}

void State::addPlayerList(PlayerRef& o) {
	mPlayerList.push_back(o);
}

void State::addEnemyList(EnemyRef& o) {
	mEnemyList.push_back(o);
}

void State::addItemList(ItemRef& o) {
	mItemList.push_back(o);
}

State::State(int stageID) : mStageID(stageID), mDynamicObjectNumber(0) {

	const StageData& stageData = gStageData[mStageID];

	//配列確保
	int floorNum = (sWIDTH * sHEIGHT - (((sWIDTH - 1) / 2) * ((sHEIGHT - 1) / 2)));
	int brickNumber = floorNum * stageData.mBrickRate / 100;
	int itemNumber = stageData.mItemBombNumber + stageData.mItemPowerNumber;
	int brickCount = 0;
	mSoList.setSize(sWIDTH, sHEIGHT);
	mFireList.reserve(sWIDTH* sHEIGHT * 2); //重なる可能性があるため
	mBombList.reserve(sWIDTH*sHEIGHT);
	mItemList.reserve(itemNumber);

	for (int y = 0; y < sHEIGHT; y++) {
		for (int x = 0; x < sWIDTH; x++) {
			if (x == 0 || y == 0 || (x == sWIDTH - 1) || (y == sHEIGHT - 1)) {
				mSoList(x, y) = new Wall(x, y);
			}
			else if ((x % 2 == 0) && (y % 2 == 0)) {
				mSoList(x, y) = new Wall(x, y);
			}
			else if ((x + y) < 4) {
				//左上3マスは床
				mSoList(x, y) = new Floor(x, y);
			}
			else if ((mStageID == 0) && (y + x > (sWIDTH + sHEIGHT - 6))) {
				//二人用なら右下3マスは床
				mSoList(x, y) = new Floor(x, y);
			}
			else {
				if (DxLib::GetRand(100) < stageData.mBrickRate) {
					mSoList(x, y) = new Brick(x, y);
					brickCount++;
				}
				else {
					//レンガじゃなければ床
					mSoList(x, y) = new Floor(x, y);
				}
			}
		}
	}

	//アイテム配置
	for (int i = 0; i < stageData.mItemPowerNumber;) {
		int x = DxLib::GetRand(sWIDTH - 3) + 1;
		int y = DxLib::GetRand(sHEIGHT - 3) + 1;

		if (mSoList(x, y)->getType() == StaticObject::TYPE_BRICK) {
			ItemRef item(new Item(x, y, Item::TYPE_POWER));
			addItemList(item);
			i++;
		}
		else {
			continue;
		}
	}
	for (int i = 0; i < stageData.mItemBombNumber;) {
		int x = DxLib::GetRand(sWIDTH - 3) + 1;
		int y = DxLib::GetRand(sHEIGHT - 3) + 1;

		if (mSoList(x, y)->getType() == StaticObject::TYPE_BRICK) {
			ItemRef item(new Item(x, y, Item::TYPE_BOMB));
			addItemList(item);
			i++;
		}
		else {
			continue;
		}
	}

	//配列確保
	int playerNumber = (mStageID == 0) ? 2 : 1;
	int enemyNumber = stageData.mEnemyNumber;
	mEnemyList.reserve(enemyNumber);
	mPlayerList.reserve(playerNumber);

	//Player配置
	PlayerRef p1(new Player(1, 1, 0));
	addPlayerList(p1);
	if (mStageID == 0) {
		PlayerRef p2(new Player(sWIDTH - 2, sHEIGHT - 2, 1));
		addPlayerList(p2);
	}

	//敵配置
	for (int i = 0; i < enemyNumber;) {
		int x = DxLib::GetRand(sWIDTH - 3) + 1;
		int y = DxLib::GetRand(sHEIGHT - 3) + 1;

		if ((mSoList(x, y)->getType() == StaticObject::TYPE_FLOOR) && (x+y) >= 4) {
			EnemyRef enemy(new Enemy(x, y));
			addEnemyList(enemy);
			i++;
		}
		else {
			continue;
		}
	}
}

State::~State() {
}

void State::draw() const {

	//背景描写
	DxLib::DrawBox(0, 0, WIDTH, HEIGHT, GetColor(256, 100, 100), FALSE);

	//床描写
	for (int x = 0; x < sWIDTH; x++) {
		for (int y = 0; y < sHEIGHT; y++) {	
			DxLib::DrawGraph(x * 32, y * 32, ResourceLoader::getInstance()->getHdFloor(), FALSE);
		}
	}

	//アイテム描写
	for (size_t i = 0; i < mItemList.size(); i++) {
		mItemList[i]->draw();
	}

	//StaticObject描写
	for (int x = 0; x < sWIDTH; x++) {
		for (int y = 0; y < sHEIGHT; y++) {
			if (mSoList(x, y) != 0) {
				mSoList(x, y)->draw();
			}
		}
	}

	//前景描写
	for (size_t i = 0; i < mBombList.size(); i++) {
		mBombList[i]->draw();
	}

	for (size_t i = 0; i < mPlayerList.size(); i++) {
		mPlayerList[i]->draw();
	}

	for (size_t i = 0; i < mEnemyList.size(); i++) {
		mEnemyList[i]->draw();
	}

	//爆風描写
	for (size_t i = 0; i < mFireList.size(); i++) {
		mFireList[i]->draw();
	}


#ifdef _DEBUG
	//アイテム描写
	if(GameController::getInstance()->getKey(KEY_INPUT_7) == GameController::Pressed){
		for (size_t i = 0; i < mItemList.size(); i++) {
			mItemList[i]->draw();
		}
	}
#endif

}

void State::update() {

	//爆弾更新
	for (size_t i = 0; i < mBombList.size(); i++) {
		mBombList[i]->update();
		int x, y;
		mBombList[i]->getCell(&x, &y);

		//爆発処理
		if (mBombList[i]->isExplosion()) {
			setFire(x, y, mBombList[i]->getPower()); //炎設置
			mBombList[i]->getOwner()->decrementSetedBombNumber();
			mSoList(x, y) = new Floor(x, y);
		}

		//衝突判定処理
		if (mBombList[i]->getCollisionFlag() == false) {
			bool cFlag = true; //一人でも衝突していればfalse
			for (size_t j = 0; j < mPlayerList.size(); j++) {
				int px, py; //プレイヤーの内部座標
				mPlayerList[j]->getPos(&px, &py);
				if ((mPlayerList[j]->isIntersectWall(px, py, x, y))) { //衝突していなければフラグをたてる
					cFlag = false;
				}
			}
			if (cFlag) { //誰も衝突していない
				mBombList[i]->setCollisionFlag(true);
			}
		}
	}

	//StaticObject（レンガのみ）更新
	for (int x = 0; x < sWIDTH; x++) {
		for (int y = 0; y < sHEIGHT; y++) {
			mSoList(x, y)->update();
		}
	}

    //炎更新
	for (size_t i = 0; i < mFireList.size(); i++) {
		mFireList[i]->update();
	}

	//DynamicObjectの処理
	//敵の処理
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		if (!mEnemyList[i]->isAlive()) {
			continue; //しんでいたらcontinue
		}
		int x, y;

		mEnemyList[i]->getCell(&x, &y); //座標を格納

		std::vector<StaticObject*> objects; //いる場所の上下左右のオブジェクト情報
		objects.reserve(4);

		for (int i = 0; i < 4; i++) {
			//壁かれんが
			if ((mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_BRICK) || (mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_WALL)) {
				objects.push_back(mSoList(x + dx[i], y + dy[i])); //上下左右の順
			}
			//衝突フラグがたっている爆弾
			else if (mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_BOMB && mSoList(x + dx[i], y + dy[i])->getCollisionFlag()) {
				objects.push_back(mSoList(x + dx[i], y + dy[i]));
			}
		}
		mEnemyList[i]->move(objects);

		int ex, ey;
		mEnemyList[i]->getPos(&ex, &ey); //えねみーの内部座標

		//Fireとの当たり判定
		for (size_t j = 0; j < mFireList.size(); j++) {
			int fx, fy;
			mFireList[j]->getCell(&fx, &fy);
			if (mEnemyList[i]->isIntersectStatic(ex, ey, fx, fy)) {
				mEnemyList[i]->die();
			}
		}
	}

	//Playerの処理
	for (size_t i = 0; i < mPlayerList.size(); i++) {
		if (!mPlayerList[i]->isAlive()) {
			continue;
		}
		//移動処理
		int x, y;
		mPlayerList[i]->getCell(&x, &y); //座標を格納
		std::vector<StaticObject*> objects; //いる場所の上下左右のオブジェクト情報
		objects.reserve(4);
		for (int i = 0; i < 4; i++) {
			//壁かれんが
			if ((mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_BRICK) || (mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_WALL)) { 
				objects.push_back(mSoList(x + dx[i], y + dy[i])); //上下左右の順
			}
			//衝突フラグがたっている爆弾
	    	else if (mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_BOMB && mSoList(x + dx[i], y + dy[i])->getCollisionFlag()) {
				objects.push_back(mSoList(x + dx[i], y + dy[i]));
			}
		}
		mPlayerList[i]->move(objects);

		mPlayerList[i]->getCell(&x, &y); //移動後

		//爆弾おく処理
		if (mPlayerList[i]->hasBombButtonPressed()) {
			if (mPlayerList[i]->getSetedBombNumber() < mPlayerList[i]->getBombNumber()) {
			
				 if (mSoList(x, y)->getType() == StaticObject::TYPE_FLOOR) { //床なら
					BombRef bomb(new Bomb(x, y, mPlayerList[i].get()));
					addBombList(bomb);
					mPlayerList[i]->incrementSetedBombNumber();
					SAFE_DELETE(mSoList(x, y));
					mSoList(x, y) = bomb.get();
				}
			}
		}

		int px, py;
		mPlayerList[i]->getPos(&px, &py); //プレイヤーの内部座標

		//アイテム取得判定
		for (size_t j = 0; j < mItemList.size(); j++) {
			int ix, iy;
			mItemList[j]->getCell(&ix, &iy);
			if (mPlayerList[i]->isIntersectStatic(px, py, ix, iy)) {
				mItemList[j]->remove();
				if (mItemList[j]->getItemType() == Item::TYPE_BOMB) {
					mPlayerList[i]->incrementBombNomber();
				}

				else if (mItemList[j]->getItemType() == Item::TYPE_POWER) {
					mPlayerList[i]->incrementBombPower();
				}
			}
		}

		//Fireとの当たり判定
		for (size_t j = 0; j < mFireList.size(); j++) {
			int fx, fy;
			mFireList[j]->getCell(&fx, &fy);
			if (mPlayerList[i]->isIntersectStatic(px, py, fx, fy)) {
				mPlayerList[i]->die();
			}
		}

		//Enemyとの当たり判定
		for (size_t j = 0; j < mEnemyList.size(); j++) {
				mPlayerList[i]->doCollisionReactionToDynamic(mEnemyList[j].get());
			}
		}
	

	//アイテム燃えはんてい
	for (size_t i = 0; i < mItemList.size(); i++) {
		int ix, iy;
		mItemList[i]->getCell(&ix, &iy);
		for (size_t j = 0; j < mFireList.size(); j++) {
			int fx, fy;
			mFireList[j]->getCell(&fx, &fy);
			if (ix == fx && iy == fy) {
				mItemList[i]->remove();
			}
		}
	}


	//しんだものを配列から削除し（上の行）、配列を詰める（下の行）
	std::vector<PlayerRef>::iterator pend = std::remove_if(mPlayerList.begin(), mPlayerList.end(), [](PlayerRef& o) {return !o->isAlive(); });
	mPlayerList.erase(pend, mPlayerList.end());
	std::vector<EnemyRef>::iterator eend = std::remove_if(mEnemyList.begin(), mEnemyList.end(), [](EnemyRef& o) {return !o->isAlive(); });
	mEnemyList.erase(eend, mEnemyList.end());
	std::vector<BombRef>::iterator bend = std::remove_if(mBombList.begin(), mBombList.end(), [](BombRef& o) {return !o->isExist(); });
	mBombList.erase(bend, mBombList.end());
	std::vector<FireRef>::iterator fend = std::remove_if(mFireList.begin(), mFireList.end(), [](FireRef& o) {return !o->isExist(); });
	mFireList.erase(fend, mFireList.end());
	std::vector<ItemRef>::iterator iend = std::remove_if(mItemList.begin(), mItemList.end(), [](ItemRef& o) {return !o->isExist(); });
	mItemList.erase(iend, mItemList.end());

	for (int x = 0; x < sWIDTH; x++) {
		for (int y = 0; y < sHEIGHT; y++) {
			if (mSoList(x, y)->getType() == StaticObject::TYPE_NONE) {
				SAFE_DELETE(mSoList(x, y));
				mSoList(x, y) = new Floor(x, y);
			}
		}
	}
}

void State::setFire(int x, int y, int power) {

	int end;

	//中央
	FireRef fire(new Fire(x, y, Fire::TYPE_CENTER));
	addFireList(fire);

	//左
	end = (x - power < 0) ? 0 : (x - power);
	for (int i = x - 1; i >= end; i--) {
		StaticObject* to = mSoList(i, y);
		StaticObject::Type type = to->getType();
		if (type == StaticObject::TYPE_WALL || type == StaticObject::TYPE_BRICK || type == StaticObject::TYPE_BOMB) { //火が止まる条件
			to->setBurnFlag(true);
			break;
		}
		else {
			FireRef fire(new Fire(i, y, Fire::TYPE_X));
			addFireList(fire);
		}
	}

	//右
	end = (x + power >= sWIDTH) ? (sWIDTH - 1) : (x + power);
	for (int i = x + 1; i <= end; i++) {
		StaticObject* to = mSoList(i, y);
		StaticObject::Type type = to->getType();
		if (type == StaticObject::TYPE_WALL || type == StaticObject::TYPE_BRICK || type == StaticObject::TYPE_BOMB) { //火が止まる条件
			to->setBurnFlag(true);
			break;
		}
		else {
			FireRef fire(new Fire(i, y, Fire::TYPE_X));
			addFireList(fire);
		}
	}

	//上
	end = (y - power < 0) ? 0 : (y - power);
	for (int i = y - 1; i >= end; i--) {
		StaticObject* to = mSoList(x, i);
		StaticObject::Type type = to->getType();
		if (type == StaticObject::TYPE_WALL || type == StaticObject::TYPE_BRICK || type == StaticObject::TYPE_BOMB) { //火が止まる条件
			to->setBurnFlag(true);
			break;
		}
		else {
			FireRef fire(new Fire(x, i, Fire::TYPE_Y));
			addFireList(fire);
		}
	}

	//下
	end = (y + power >= sHEIGHT) ? (sHEIGHT - 1) : (y + power);
	for (int i = y + 1; i <= end; i++) {
		StaticObject* to = mSoList(x, i);
		StaticObject::Type type = to->getType();
		if (type == StaticObject::TYPE_WALL || type == StaticObject::TYPE_BRICK || type == StaticObject::TYPE_BOMB) { //火が止まる条件
			to->setBurnFlag(true);
			break;
		}
		else {
			FireRef fire(new Fire(x, i, Fire::TYPE_Y));
			addFireList(fire);
		}
	}
}


bool State::hasCleared() const {
	//敵がいなければくりあ
	if(mEnemyList.size() > 0){
			return false;
	}
	return true;
}

bool State::isAlive(int playerID) const {
	for(size_t i = 0; i < mPlayerList.size(); i++){
		if (mPlayerList[i]->getPlayerID() == playerID) {
			return true;
		}
	}
	return false;
}