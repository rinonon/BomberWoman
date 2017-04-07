#pragma once

#include "Sequence\Game\Child.h"
class ResourceLoader;

namespace Sequence {
namespace Game {
class Parent;

class Clear : public Child {
public:
	Clear();
	~Clear();
	void update(Parent*);

private:
	int mCount;
	ResourceLoader* rl;
};

}//namespace Game
}//namespace Sequence