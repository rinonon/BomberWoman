#pragma once

#include "Game\StaticObject\StaticObject.h"

class Fire : public StaticObject {
public:
	enum Type {
		TYPE_X,
		TYPE_Y,
		TYPE_CENTER,

		TYPE_NONE,
	};
	Fire(int x, int y, Fire::Type type);
	~Fire();
	void draw() const;
	void update();

private:
	int mGraphHd[3] = { 5, 6, 4 };
	Fire::Type mFireType;
	int mCount;
	static const int EXPLOSION_LIFE = 60; //1�b
};