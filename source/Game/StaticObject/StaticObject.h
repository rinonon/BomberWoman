#pragma once

class Bomb;

class StaticObject {
public:
	enum Type {
		TYPE_WALL, //壊れない壁
		TYPE_BRICK , //壊れる壁
		TYPE_FIRE, //爆風
		TYPE_BOMB,
		TYPE_ITEM,
		TYPE_FLOOR,

		TYPE_NONE,
	};

	StaticObject();
	virtual ~StaticObject();
	virtual void draw() const = 0;
	virtual void update();
	virtual bool getCollisionFlag() const; //爆弾用
	void getCell(int* x, int* y) const;
	bool isExist() const;
	StaticObject::Type getType() const;
	void setBurnFlag(bool f);
	bool getBurnFlag() const;

protected:
	//座標
	int mX;
	int mY;

	bool mBurnFlag; //アイテム、爆弾、レンガ用
	Type mType;
};