#include "Sequence\Parent.h"
#include "Sequence\Title.h"
#include "stdCommon.h"
#include "Sequence\Game\Parent.h"
#include "Sequence\Ending.h"
#include "Sequence\GameOver.h"

namespace Sequence {

Parent* Parent::mInstance = 0;

void Parent::create() {
	if (!mInstance) {
		mInstance = new Parent();
	}
}

void Parent::destroy() {
	if (mInstance) {
		SAFE_DELETE(mInstance);
	}
}

Parent* Parent::getInstance() {
	return mInstance;
}

Parent::Parent() :
	mNextSequence(NEXT_NONE),
	mMode(MODE_NONE),
	mChild(0) {
	mChild = new Title();
}

Parent::~Parent() {
	SAFE_DELETE(mChild);
}

void Parent::update() {
	mChild->update(this);

	switch (mNextSequence) {
	case NEXT_TITLE:
		SAFE_DELETE(mChild);
		mChild = new Title();
		break;

	case NEXT_GAME:
		SAFE_DELETE(mChild);
		mChild = new Game::Parent();
		break;

	case NEXT_GAME_OVER:
		SAFE_DELETE(mChild);
		mChild = new GameOver();
		break;

	case NEXT_ENDING:
		SAFE_DELETE(mChild);
		mChild = new Ending();
		break;
	}
	mNextSequence = NEXT_NONE;
}

void Parent::moveTo(NextSequence next) {
	if (mNextSequence == NEXT_NONE) {
		mNextSequence = next;
	}
}

void Parent::setMode(Mode mode) {
	mMode = mode;
}

Parent::Mode Parent::getMode() const {
	return mMode;
}

} //namespace Sequence