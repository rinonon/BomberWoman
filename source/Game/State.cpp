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

namespace { //���O�Ȃ����

//�}�b�v�T�C�Y
const int sWIDTH = 19;
const int sHEIGHT = 15;

struct StageData {
	int mEnemyNumber; //�G�̐�
	int mBrickRate; //������(�p�[�Z���g)
	int mItemPowerNumber; //�����A�C�e���̐�
	int mItemBombNumber; //���e�A�C�e���̐�
};

StageData gStageData[] = {
	{ 0, 50, 3, 4, },
	{ 3, 20, 5, 6, },
	{ 6, 30, 1, 2, },
};

//�O���b�h�T���p�@�㉺���E
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

	//�z��m��
	int floorNum = (sWIDTH * sHEIGHT - (((sWIDTH - 1) / 2) * ((sHEIGHT - 1) / 2)));
	int brickNumber = floorNum * stageData.mBrickRate / 100;
	int itemNumber = stageData.mItemBombNumber + stageData.mItemPowerNumber;
	int brickCount = 0;
	mSoList.setSize(sWIDTH, sHEIGHT);
	mFireList.reserve(sWIDTH* sHEIGHT * 2); //�d�Ȃ�\�������邽��
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
				//����3�}�X�͏�
				mSoList(x, y) = new Floor(x, y);
			}
			else if ((mStageID == 0) && (y + x > (sWIDTH + sHEIGHT - 6))) {
				//��l�p�Ȃ�E��3�}�X�͏�
				mSoList(x, y) = new Floor(x, y);
			}
			else {
				if (DxLib::GetRand(100) < stageData.mBrickRate) {
					mSoList(x, y) = new Brick(x, y);
					brickCount++;
				}
				else {
					//�����K����Ȃ���Ώ�
					mSoList(x, y) = new Floor(x, y);
				}
			}
		}
	}

	//�A�C�e���z�u
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

	//�z��m��
	int playerNumber = (mStageID == 0) ? 2 : 1;
	int enemyNumber = stageData.mEnemyNumber;
	mEnemyList.reserve(enemyNumber);
	mPlayerList.reserve(playerNumber);

	//Player�z�u
	PlayerRef p1(new Player(1, 1, 0));
	addPlayerList(p1);
	if (mStageID == 0) {
		PlayerRef p2(new Player(sWIDTH - 2, sHEIGHT - 2, 1));
		addPlayerList(p2);
	}

	//�G�z�u
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

	//�w�i�`��
	DxLib::DrawBox(0, 0, WIDTH, HEIGHT, GetColor(256, 100, 100), FALSE);

	//���`��
	for (int x = 0; x < sWIDTH; x++) {
		for (int y = 0; y < sHEIGHT; y++) {	
			DxLib::DrawGraph(x * 32, y * 32, ResourceLoader::getInstance()->getHdFloor(), FALSE);
		}
	}

	//�A�C�e���`��
	for (size_t i = 0; i < mItemList.size(); i++) {
		mItemList[i]->draw();
	}

	//StaticObject�`��
	for (int x = 0; x < sWIDTH; x++) {
		for (int y = 0; y < sHEIGHT; y++) {
			if (mSoList(x, y) != 0) {
				mSoList(x, y)->draw();
			}
		}
	}

	//�O�i�`��
	for (size_t i = 0; i < mBombList.size(); i++) {
		mBombList[i]->draw();
	}

	for (size_t i = 0; i < mPlayerList.size(); i++) {
		mPlayerList[i]->draw();
	}

	for (size_t i = 0; i < mEnemyList.size(); i++) {
		mEnemyList[i]->draw();
	}

	//�����`��
	for (size_t i = 0; i < mFireList.size(); i++) {
		mFireList[i]->draw();
	}


#ifdef _DEBUG
	//�A�C�e���`��
	if(GameController::getInstance()->getKey(KEY_INPUT_7) == GameController::Pressed){
		for (size_t i = 0; i < mItemList.size(); i++) {
			mItemList[i]->draw();
		}
	}
#endif

}

void State::update() {

	//���e�X�V
	for (size_t i = 0; i < mBombList.size(); i++) {
		mBombList[i]->update();
		int x, y;
		mBombList[i]->getCell(&x, &y);

		//��������
		if (mBombList[i]->isExplosion()) {
			setFire(x, y, mBombList[i]->getPower()); //���ݒu
			mBombList[i]->getOwner()->decrementSetedBombNumber();
			mSoList(x, y) = new Floor(x, y);
		}

		//�Փ˔��菈��
		if (mBombList[i]->getCollisionFlag() == false) {
			bool cFlag = true; //��l�ł��Փ˂��Ă����false
			for (size_t j = 0; j < mPlayerList.size(); j++) {
				int px, py; //�v���C���[�̓������W
				mPlayerList[j]->getPos(&px, &py);
				if ((mPlayerList[j]->isIntersectWall(px, py, x, y))) { //�Փ˂��Ă��Ȃ���΃t���O�����Ă�
					cFlag = false;
				}
			}
			if (cFlag) { //�N���Փ˂��Ă��Ȃ�
				mBombList[i]->setCollisionFlag(true);
			}
		}
	}

	//StaticObject�i�����K�̂݁j�X�V
	for (int x = 0; x < sWIDTH; x++) {
		for (int y = 0; y < sHEIGHT; y++) {
			mSoList(x, y)->update();
		}
	}

    //���X�V
	for (size_t i = 0; i < mFireList.size(); i++) {
		mFireList[i]->update();
	}

	//DynamicObject�̏���
	//�G�̏���
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		if (!mEnemyList[i]->isAlive()) {
			continue; //����ł�����continue
		}
		int x, y;

		mEnemyList[i]->getCell(&x, &y); //���W���i�[

		std::vector<StaticObject*> objects; //����ꏊ�̏㉺���E�̃I�u�W�F�N�g���
		objects.reserve(4);

		for (int i = 0; i < 4; i++) {
			//�ǂ����
			if ((mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_BRICK) || (mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_WALL)) {
				objects.push_back(mSoList(x + dx[i], y + dy[i])); //�㉺���E�̏�
			}
			//�Փ˃t���O�������Ă��锚�e
			else if (mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_BOMB && mSoList(x + dx[i], y + dy[i])->getCollisionFlag()) {
				objects.push_back(mSoList(x + dx[i], y + dy[i]));
			}
		}
		mEnemyList[i]->move(objects);

		int ex, ey;
		mEnemyList[i]->getPos(&ex, &ey); //���˂݁[�̓������W

		//Fire�Ƃ̓����蔻��
		for (size_t j = 0; j < mFireList.size(); j++) {
			int fx, fy;
			mFireList[j]->getCell(&fx, &fy);
			if (mEnemyList[i]->isIntersectStatic(ex, ey, fx, fy)) {
				mEnemyList[i]->die();
			}
		}
	}

	//Player�̏���
	for (size_t i = 0; i < mPlayerList.size(); i++) {
		if (!mPlayerList[i]->isAlive()) {
			continue;
		}
		//�ړ�����
		int x, y;
		mPlayerList[i]->getCell(&x, &y); //���W���i�[
		std::vector<StaticObject*> objects; //����ꏊ�̏㉺���E�̃I�u�W�F�N�g���
		objects.reserve(4);
		for (int i = 0; i < 4; i++) {
			//�ǂ����
			if ((mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_BRICK) || (mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_WALL)) { 
				objects.push_back(mSoList(x + dx[i], y + dy[i])); //�㉺���E�̏�
			}
			//�Փ˃t���O�������Ă��锚�e
	    	else if (mSoList(x + dx[i], y + dy[i])->getType() == StaticObject::TYPE_BOMB && mSoList(x + dx[i], y + dy[i])->getCollisionFlag()) {
				objects.push_back(mSoList(x + dx[i], y + dy[i]));
			}
		}
		mPlayerList[i]->move(objects);

		mPlayerList[i]->getCell(&x, &y); //�ړ���

		//���e��������
		if (mPlayerList[i]->hasBombButtonPressed()) {
			if (mPlayerList[i]->getSetedBombNumber() < mPlayerList[i]->getBombNumber()) {
			
				 if (mSoList(x, y)->getType() == StaticObject::TYPE_FLOOR) { //���Ȃ�
					BombRef bomb(new Bomb(x, y, mPlayerList[i].get()));
					addBombList(bomb);
					mPlayerList[i]->incrementSetedBombNumber();
					SAFE_DELETE(mSoList(x, y));
					mSoList(x, y) = bomb.get();
				}
			}
		}

		int px, py;
		mPlayerList[i]->getPos(&px, &py); //�v���C���[�̓������W

		//�A�C�e���擾����
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

		//Fire�Ƃ̓����蔻��
		for (size_t j = 0; j < mFireList.size(); j++) {
			int fx, fy;
			mFireList[j]->getCell(&fx, &fy);
			if (mPlayerList[i]->isIntersectStatic(px, py, fx, fy)) {
				mPlayerList[i]->die();
			}
		}

		//Enemy�Ƃ̓����蔻��
		for (size_t j = 0; j < mEnemyList.size(); j++) {
				mPlayerList[i]->doCollisionReactionToDynamic(mEnemyList[j].get());
			}
		}
	

	//�A�C�e���R���͂�Ă�
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


	//���񂾂��̂�z�񂩂�폜���i��̍s�j�A�z����l�߂�i���̍s�j
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

	//����
	FireRef fire(new Fire(x, y, Fire::TYPE_CENTER));
	addFireList(fire);

	//��
	end = (x - power < 0) ? 0 : (x - power);
	for (int i = x - 1; i >= end; i--) {
		StaticObject* to = mSoList(i, y);
		StaticObject::Type type = to->getType();
		if (type == StaticObject::TYPE_WALL || type == StaticObject::TYPE_BRICK || type == StaticObject::TYPE_BOMB) { //�΂��~�܂����
			to->setBurnFlag(true);
			break;
		}
		else {
			FireRef fire(new Fire(i, y, Fire::TYPE_X));
			addFireList(fire);
		}
	}

	//�E
	end = (x + power >= sWIDTH) ? (sWIDTH - 1) : (x + power);
	for (int i = x + 1; i <= end; i++) {
		StaticObject* to = mSoList(i, y);
		StaticObject::Type type = to->getType();
		if (type == StaticObject::TYPE_WALL || type == StaticObject::TYPE_BRICK || type == StaticObject::TYPE_BOMB) { //�΂��~�܂����
			to->setBurnFlag(true);
			break;
		}
		else {
			FireRef fire(new Fire(i, y, Fire::TYPE_X));
			addFireList(fire);
		}
	}

	//��
	end = (y - power < 0) ? 0 : (y - power);
	for (int i = y - 1; i >= end; i--) {
		StaticObject* to = mSoList(x, i);
		StaticObject::Type type = to->getType();
		if (type == StaticObject::TYPE_WALL || type == StaticObject::TYPE_BRICK || type == StaticObject::TYPE_BOMB) { //�΂��~�܂����
			to->setBurnFlag(true);
			break;
		}
		else {
			FireRef fire(new Fire(x, i, Fire::TYPE_Y));
			addFireList(fire);
		}
	}

	//��
	end = (y + power >= sHEIGHT) ? (sHEIGHT - 1) : (y + power);
	for (int i = y + 1; i <= end; i++) {
		StaticObject* to = mSoList(x, i);
		StaticObject::Type type = to->getType();
		if (type == StaticObject::TYPE_WALL || type == StaticObject::TYPE_BRICK || type == StaticObject::TYPE_BOMB) { //�΂��~�܂����
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
	//�G�����Ȃ���΂��肠
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