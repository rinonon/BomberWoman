#pragma once

#include "Sequence\Child.h"

class ResourceLoader;

namespace Sequence {
class Parent;

class GameOver : public Child {
public:
	GameOver();
	~GameOver();
	void update(Parent*);

private:
	ResourceLoader* rl;
	int mCount;
};

} // namespace Sequence