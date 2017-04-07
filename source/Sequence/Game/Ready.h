#pragma once

#include "Sequence\Game\Child.h"
class ResourceLoader;

namespace Sequence {
namespace Game {

class Parent;

class Ready : public Child{
public:
	Ready();
	~Ready();
	void update(Parent*);

private:
	int mCount;
	bool mStarted;
	ResourceLoader* rl;
};


} //namespace Game
} //namespace Sequence