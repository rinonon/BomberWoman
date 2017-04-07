#pragma once

#include "Sequence\Game\Child.h"
class GameController;

namespace Sequence {
namespace Game {
class Parent;

class Play : public Child {
public:
	Play();
	~Play();
	void update(Parent*);

private:
	GameController* gc;
};

} //namespace Game
} //namespace Sequence