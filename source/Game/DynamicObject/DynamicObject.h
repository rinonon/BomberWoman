#pragma once

#include <vector>
#include <memory>

class StaticObject;
class Player;


//abstract class
class DynamicObject {
public:
	DynamicObject();
	virtual ~DynamicObject();

	enum Type {
		TYPE_PLAYER,
		TYPE_ENEMY,

		TYPE_NONE,
	};

	//�������z�֐�
	virtual void move(const std::vector<StaticObject*> so) = 0;
	virtual void draw() = 0;

	//�Փ˔���
	void doCollisionReactionToDynamic(DynamicObject*);
	bool isIntersect(const DynamicObject&) const;
	bool isIntersectWall(int x, int y, int wallCellX, int wallCellY);
	bool isIntersectStatic(int x, int y, int CellX, int CellY); //�����蔻�肠�܂�

	bool isAlive() const;
	void die();
	void getCell(int* x, int* y) const;
	void getPos(int* x, int* y) const;
	void set(int x, int y);
	Type getType() const;
	
protected:

	//���W
	int mX;
	int mY;
	//����
	int mDirectionX;
	int mDirectionY;

	Type mType;
};