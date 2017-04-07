#pragma once

#include "Sequence\Child.h"

class ResourceLoader;

namespace Sequence {
class Parent;

class Ending : public Child {
public:
	Ending();
	~Ending();
	void update(Parent*);

private:
	int mCount;
	ResourceLoader* rl;
};

} //namespace Sequence