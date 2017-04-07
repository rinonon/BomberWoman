#pragma once

#include "Game\StaticObject\StaticObject.h"

class Wall : public StaticObject {
public:
	Wall(int x, int y);
	~Wall();

	void draw() const;

private:
	int mGraphHd = 10;
};