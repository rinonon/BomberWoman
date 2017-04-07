#pragma once

#include "Sequence\Game\Child.h"
class ResourceLoader;
class GameController;

namespace Sequence {
namespace Game {
class Parent;

class Pause : public Child{
public:
	Pause();
	~Pause();
	void update(Parent*);

private:
	ResourceLoader* rl;
	GameController* gc;
	int mCursorPosition;
};

}// namespace Game
}// namespace Sequence