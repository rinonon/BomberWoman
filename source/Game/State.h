#pragma once

#include <memory>
#include <vector>
#include "Array2D.h"

class StaticObject;
class Fire;
class Bomb;
class Player;
class Enemy;
class Item;

typedef std::shared_ptr<Enemy> EnemyRef;
typedef std::shared_ptr<Fire> FireRef;
typedef std::shared_ptr<Bomb> BombRef;
typedef std::shared_ptr<Player> PlayerRef;
typedef std::shared_ptr<Item> ItemRef;

class State {

public:
	static const int STAGE_ID_2PLAYERS = 0;
	State(int stageID); //��l�p��0, ��l�p�̓X�e�[�WID���^������
	~State();
	void update(); //���͏����͓���
	void draw() const;

	bool hasCleared() const;
	bool isAlive(int playerID) const;

private:
	void setFire(int x, int y, int power);

	void addFireList(FireRef& o);
	void addBombList(BombRef& o);
	void addPlayerList(PlayerRef& o);
	void addEnemyList(EnemyRef& o);
	void addItemList(ItemRef& o);
	Array2D< StaticObject* > mSoList;
	std::vector<FireRef> mFireList;
	std::vector<BombRef> mBombList;
	std::vector<PlayerRef> mPlayerList;
	std::vector<EnemyRef> mEnemyList;
	std::vector<ItemRef> mItemList;
	int mDynamicObjectNumber;
	int mStageID;
};