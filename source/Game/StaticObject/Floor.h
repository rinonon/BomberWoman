#pragma once

#include "Game\StaticObject\StaticObject.h"
class Bomb;

class Floor : public StaticObject {
public:
	Floor(int x, int y);
	~Floor();
	void draw() const;

private:
	Bomb* mBomb;
};