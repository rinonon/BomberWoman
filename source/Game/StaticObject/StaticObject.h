#pragma once

class Bomb;

class StaticObject {
public:
	enum Type {
		TYPE_WALL, //���Ȃ���
		TYPE_BRICK , //�����
		TYPE_FIRE, //����
		TYPE_BOMB,
		TYPE_ITEM,
		TYPE_FLOOR,

		TYPE_NONE,
	};

	StaticObject();
	virtual ~StaticObject();
	virtual void draw() const = 0;
	virtual void update();
	virtual bool getCollisionFlag() const; //���e�p
	void getCell(int* x, int* y) const;
	bool isExist() const;
	StaticObject::Type getType() const;
	void setBurnFlag(bool f);
	bool getBurnFlag() const;

protected:
	//���W
	int mX;
	int mY;

	bool mBurnFlag; //�A�C�e���A���e�A�����K�p
	Type mType;
};