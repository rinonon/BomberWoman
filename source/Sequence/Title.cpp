#include "Title.h"
#include "GameController.h"
#include "ResourceLoader.h"
#include "stdCommon.h"
#include "Sequence/Parent.h"
#include "StringRenderer.h"

namespace Sequence {

Title::Title() : mCursorPosition(0) {
	gc = GameController::getInstance();
	rl = ResourceLoader::getInstance();
}

Title::~Title() {}


void Title::update(Parent* parent) {

	if (gc->getKey(KEY_INPUT_UP) == GameController::PressedNow) {
		mCursorPosition--;
		if (mCursorPosition < 0) mCursorPosition = 1;
	}

	else if (gc->getKey(KEY_INPUT_DOWN) == GameController::PressedNow) {
		mCursorPosition++;
		if (mCursorPosition > 1) {
			mCursorPosition = 0;
		}
	}

	if (gc->getKey(KEY_INPUT_SPACE) == GameController::PressedNow) {
		parent->moveTo(Parent::NEXT_GAME);
		if (mCursorPosition == 0) {
			parent->setMode(Parent::MODE_1P);
		}
		else if (mCursorPosition == 1) {
			parent->setMode(Parent::MODE_2P);
		}
	}

	StringRenderer::getInstance()->draw(0, 0, "Bomber Woman");
	StringRenderer::getInstance()->draw(1, 3, "1 player");
	StringRenderer::getInstance()->draw(1, 4, "2 player");

	StringRenderer::getInstance()->draw(0, mCursorPosition+3, ">"); //ÉJÅ[É\Éãï`é 
}

} //namespace Sequence