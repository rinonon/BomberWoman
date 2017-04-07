#pragma once

#include "Sequence\Game\Child.h"
class ResourceLoader;

namespace Sequence {
namespace Game {
class Parent;

class Failure : public Child {
public:
	Failure();
	~Failure();
	void update(Parent*);

private:
	int mCount;
	ResourceLoader* rl;
};

} //namespace Game
} //namespace Sequence