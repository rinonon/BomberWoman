#include "Sequence\Game\Parent.h"
#include "stdCommon.h"
#include "Sequence\Parent.h"
#include "Sequence\Game\Play.h"
#include "Sequence\Game\Clear.h"
#include "Sequence\Game\Pause.h"
#include "Sequence\Game\Ready.h"
#include "Sequence\Game\Failure.h"
#include "Sequence\Game\Judge.h"
#include "File.h"
#include "Game\State.h"

namespace Sequence {
namespace Game {

Parent::Parent() : mState(0), mStageID(1), mNextSequence(NEXT_NONE), mLife(INITIAL_LIFE_NUMBER), mChild(0) {
	mChild = new Ready();
}

Parent::~Parent() {
	SAFE_DELETE(mState);
	SAFE_DELETE(mChild);
}

void Parent::update(GrandParent* parent) {

	mChild->update(this);

	switch ( mNextSequence ){
	case NEXT_CLEAR:
		SAFE_DELETE(mChild);
		mChild = new Clear();
		++mStageID; //次のステージへ
		break;
	case NEXT_READY:
		SAFE_DELETE(mChild);
		mChild = new Ready();
		break;
	case NEXT_PAUSE:
		SAFE_DELETE(mChild);
		mChild = new Pause();
		break;
	case NEXT_PLAY:
		SAFE_DELETE(mChild);
		mChild = new Play();
		break;
	case NEXT_FAILURE:
		SAFE_DELETE(mChild);
		mChild = new Failure();
		--mLife;
		break;
	case NEXT_JUDGE:
		SAFE_DELETE(mChild);
		mChild = new Judge();
		break;
	case NEXT_ENDING:
		SAFE_DELETE(mChild);
		parent->moveTo(GrandParent::NEXT_ENDING);
		break;
	case NEXT_GAME_OVER:
		SAFE_DELETE(mChild);
		parent->moveTo(GrandParent::NEXT_GAME_OVER);
		break;
	case NEXT_TITLE:
		SAFE_DELETE(mChild);
		parent->moveTo(GrandParent::NEXT_TITLE);
		break;
	}
	mNextSequence = NEXT_NONE;
}


void Parent::moveTo(NextSequence next) {
	if (mNextSequence == NEXT_NONE) {
		mNextSequence = next;
	}
}

State* Parent::getState() {
	return mState;
}

bool Parent::hasFinalStageCleared() const {
	return (mStageID > FINAL_STAGE);
}

int Parent::getLifeNumber() const {
	return mLife;
}

Parent::Mode Parent::getMode() const {
	Parent::Mode m = MODE_NONE;

	//GrandParent::Mode　を　Parent::Mode　に変換
	switch (GrandParent::getInstance()->getMode()) {
	case GrandParent::MODE_1P: m = Parent::MODE_1P; break;
	case GrandParent::MODE_2P: m = Parent::MODE_2P; break;
	default: break;
	}

	return m;
}

void Parent::startLoading() {
	SAFE_DELETE(mState);
	if (getMode() == Parent::MODE_2P) {
		mStageID = 0;
	}
	mState = new State(mStageID);
}


} //namespace Game
} //namespace Sequence