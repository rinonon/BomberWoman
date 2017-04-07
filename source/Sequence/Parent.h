#pragma once

namespace Sequence {
class Child;

namespace Game {
class Parent;
}

class Parent {
public:
	enum NextSequence {
		NEXT_TITLE,
		NEXT_GAME,
		NEXT_GAME_OVER,
		NEXT_ENDING,

		NEXT_NONE,
	};

	enum Mode {
		MODE_1P,
		MODE_2P,

		MODE_NONE,
	};

	void update();
	void moveTo(NextSequence);
	Mode getMode() const;
	void setMode(Mode);

	static void create();
	static void destroy();
	static Parent* getInstance();

private:
	Parent();
	~Parent();

	NextSequence mNextSequence;
	Mode mMode;

	Child* mChild;

	static Parent* mInstance;
};

}// namespace Sequense