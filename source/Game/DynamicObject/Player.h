#pragma once

#include "Game\DynamicObject\DynamicObject.h"

class Player : public DynamicObject {
public:
	Player(int x, int y, int id);
	~Player();

	//virtural = 0
	void move(const std::vector<StaticObject*> soList) override;
	void draw() override;

	void setPlayerID(int);
	int getPlayerID() const;
	int getBombPower() const;
	int getBombNumber() const;
	int getSetedBombNumber() const;

	void incrementBombPower();
	void incrementBombNomber();
	void incrementSetedBombNumber();
	void decrementSetedBombNumber();
	bool hasBombButtonPressed() const;	//���e�{�^���������ꂽ�����ׂ�

private:
	void getVelocity(int* dx, int* dy); //�P�ʎ��ԓ�����̈ړ���
	void getDirection(int* dx, int* dy); //�ړ�����

	int mBombPower; //������
	int mBombNumber; //���e��

    //�A�j���[�V�����p
	int mCount;
	int mPlayerDirection; //up:0 right:1 down:2 left:3 stop:4
	int mPrevDirection;
	int mCurrentHdX;
	int mPlayerHd;
	const int CHANGE_GRAPH_TIME = 10; //

	int mPlayerID;
	int mSetedBombNumber;
	const int PLAYER_SPEED = 1000;
};