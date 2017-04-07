#pragma once

#include "Sequence\Game\Child.h"
class ResourceLoader;
class GameController;

namespace Sequence {
namespace Game {

class Parent;

class Judge : public Child{
public:
	Judge();
	~Judge();
	void update(Parent*);

private:
	int mCursorPosition;
	ResourceLoader* rl;
	GameController* gc;
};
} //namespace Game
} //namespace Sequence