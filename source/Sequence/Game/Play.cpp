#include "Sequence\Game\Play.h"
#include "Game\State.h"
#include "GameController.h"
#include "stdCommon.h"
#include "Sequence\Game\Parent.h"
#include "StringRenderer.h"

namespace Sequence {
namespace Game {

Play::Play() {
	gc = GameController::getInstance();
}

Play::~Play() {
}

void Play::update(Parent* parent) {

	State* state = parent->getState();

	bool cleared = state->hasCleared();
	bool die1P = !state->isAlive(0);
	bool die2P = !state->isAlive(1);

#ifdef _DEBUG
	//1:1P die, 2:2P die, c:clear
	StringRenderer::getInstance()->draw(0, 0, "1:1P die, 2:2P die, c:clear");
	if (gc->getKey(KEY_INPUT_1) == GameController::PressedNow) {
		die1P = true;
	}
	else if (gc->getKey(KEY_INPUT_2) == GameController::PressedNow) {
		die2P = true;
	}
	else if (gc->getKey(KEY_INPUT_C) == GameController::PressedNow) {
		cleared = true;
	}
#endif

	if (parent->getMode() == Parent::MODE_1P) {
		if (cleared && !die1P) {
			parent->moveTo(Parent::NEXT_CLEAR);
		}
		else if (die1P) {
			parent->moveTo(Parent::NEXT_FAILURE);
		}
	}
	else if (parent->getMode() == Parent::MODE_2P) {
		if (die1P || die2P) {
			parent->moveTo(Parent::NEXT_JUDGE);
		}
	}

	if (gc->getKey(KEY_INPUT_SPACE) == GameController::PressedNow) {
		parent->moveTo(Parent::NEXT_PAUSE);
	}

	state->update();
	state->draw();
}

} //namespace Geme
} //namespace Sequence