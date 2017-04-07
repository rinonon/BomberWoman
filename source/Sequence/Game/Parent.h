#pragma once

#include "Sequence\Child.h"
class State;

namespace Sequence {
class Parent;

namespace Game {
class Child;

class Parent : public Sequence::Child {
public:
	typedef Sequence::Parent GrandParent;

	enum NextSequence{
		NEXT_CLEAR,
		NEXT_READY,
		NEXT_PAUSE,
		NEXT_PLAY,
		NEXT_FAILURE,
		NEXT_JUDGE,
		NEXT_ENDING,
		NEXT_GAME_OVER,
		NEXT_TITLE,
		
		NEXT_NONE,
	};
	enum Mode {
		MODE_1P,
		MODE_2P,

		MODE_NONE,
	};

	Parent();
	~Parent();
	void update(GrandParent*);
	void moveTo(NextSequence);

	State* getState();
	bool hasFinalStageCleared() const;
	int getLifeNumber() const;
	Parent::Mode getMode() const;
	void startLoading();
	
private:
	State* mState;
	int mStageID;
	int mLife;

	static const int FINAL_STAGE = 2;
	static const int INITIAL_LIFE_NUMBER = 2;

	NextSequence mNextSequence;

	Sequence::Game::Child* mChild;
};

}// namespace Game
}// namespace Sequence