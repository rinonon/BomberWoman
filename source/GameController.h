#pragma once

namespace {
	const int frameInterval = 16; //16ms 62.5fps
	const int keyKindNum = 256;
	const int padButtonNum = 28;
}


class GameController {
public:
	enum KeyState {
		NotPressed = 0,
		Pressed = 1,
		PressedNow = 2
	};

	static GameController* getInstance();

	static void create();
	static void destroy();

	char getKey(int input) const;
	int getAllKeyPressed();
	void control();
	void adjustKeyState();

	//Pad�p
	enum Button {
		A, //0�{�^�� 
		B, //1�{�^��
		U, //up
		D, //down
		L, //left
		R, //right
		Q, //quit
	};
	char getPadInput(int input, int pid) const;
	int getAllPadPressed();
	void adjustPadState();
	bool isPressed(Button, int playerID = 0);
	bool isPressedNow(Button, int playerID = 0);

private:
	static GameController* mInstance;
	// �R���X�g���N�^�E�R�s�[�R���X�g���N�^�Ő�����R�s�[����
	GameController();
	GameController(GameController&);
	~GameController();

	void graphFps();
	void controlFps();

	void increaseCount();

	unsigned mFrameInterval10;
	unsigned mCurrentTime;
	unsigned mPrevTime[10];
	int mCounter;

	char mKey[keyKindNum];
	char mPrevKey[keyKindNum];

	//Pad�p 28�̃t���O���K�v
	char padInput1P[padButtonNum];
	char padInput2P[padButtonNum];

	char padPrevInput1P[padButtonNum];
	char padPrevInput2P[padButtonNum];
};