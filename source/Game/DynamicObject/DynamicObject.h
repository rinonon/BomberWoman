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

	//ƒˆ‰¼‘zŠÖ”
	virtual void move(const std::vector<StaticObject*> so) = 0;
	virtual void draw() = 0;

	//Õ“Ë”»’è
	void doCollisionReactionToDynamic(DynamicObject*);
	bool isIntersect(const DynamicObject&) const;
	bool isIntersectWall(int x, int y, int wallCellX, int wallCellY);
	bool isIntersectStatic(int x, int y, int CellX, int CellY); //“–‚½‚è”»’è‚ ‚Ü‚ß

	bool isAlive() const;
	void die();
	void getCell(int* x, int* y) const;
	void getPos(int* x, int* y) const;
	void set(int x, int y);
	Type getType() const;
	
protected:

	//À•W
	int mX;
	int mY;
	//Œü‚«
	int mDirectionX;
	int mDirectionY;

	Type mType;
};