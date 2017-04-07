#pragma once

#include "Sequence\Child.h"

class GameController;
class ResourceLoader;

namespace Sequence {
class Parent;

class Title : public Child {
public:
	Title();
	~Title();
	void update(Parent*);
private:
	GameController* gc;
	ResourceLoader* rl;
	
	int mCursorPosition;
};

} //namespace Sequence