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

	//純粋仮想関数
	virtual void move(const std::vector<StaticObject*> so) = 0;
	virtual void draw() = 0;

	//衝突判定
	void doCollisionReactionToDynamic(DynamicObject*);
	bool isIntersect(const DynamicObject&) const;
	bool isIntersectWall(int x, int y, int wallCellX, int wallCellY);
	bool isIntersectStatic(int x, int y, int CellX, int CellY); //当たり判定あまめ

	bool isAlive() const;
	void die();
	void getCell(int* x, int* y) const;
	void getPos(int* x, int* y) const;
	void set(int x, int y);
	Type getType() const;
	
protected:

	//座標
	int mX;
	int mY;
	//向き
	int mDirectionX;
	int mDirectionY;

	Type mType;
};