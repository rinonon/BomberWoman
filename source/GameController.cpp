#include "GameController.h"
#include "stdCommon.h"

GameController* GameController::mInstance = 0;

GameController::GameController(){}
GameController::~GameController(){}

void GameController::create() {
	mInstance = new GameController();
}

void GameController::destroy() {
	SAFE_DELETE(mInstance);
}

GameController* GameController::getInstance() {
	static GameController instance;
	return &instance;
}


void GameController::increaseCount() {
	mCounter++;
}


//FPS制御関数
void GameController::controlFps() {

	while ((DxLib::GetNowCount() - mPrevTime[9]) < frameInterval) {
		Sleep(1);
	}

	mCurrentTime = DxLib::GetNowCount();
	mFrameInterval10 = mCurrentTime - mPrevTime[0];

	for (int i = 0; i < 9; ++i) {
		mPrevTime[i] = mPrevTime[i + 1];
	}
	mPrevTime[9] = mCurrentTime;
}



//FPS表示関数
void GameController::graphFps() {
	if (mFrameInterval10 != 0) { //0割り禁止
		DxLib::DrawFormatString(620, 0, GetColor(255, 255, 255), "FPS:%.1f", 10 * 1000 / static_cast<double>(mFrameInterval10));
	}
}


//mainで呼ぶ
void GameController::control() {
	controlFps();
#ifdef _DEBUG
	graphFps();
#endif
	increaseCount();
}

//入力制御関数
int GameController::getAllKeyPressed()
{
	return DxLib::GetHitKeyStateAll(mKey);
}

int GameController::getAllPadPressed()
{
	int input1P, input2P;
	if(input1P = DxLib::GetJoypadInputState(DX_INPUT_PAD1) != 0) return -1;
	if(input2P = DxLib::GetJoypadInputState(DX_INPUT_PAD2) != 0) return -1;

	for (int i = 0; i < padButtonNum; i++) {   
		if(input1P & (1 << i)) {
			padInput1P[i] = 1;
		}
		if (input2P & (1 << i)) {
			padInput2P[i] = 1;
		}
	}

	return 0;
}

char GameController::getKey(int input) const
{
	return mKey[input];
}

char GameController::getPadInput(int input, int pid) const {
	if (pid == 0) {
		return padInput1P[input];
	}
	else {
		return padInput2P[input];
	}
}


void GameController::adjustKeyState()
{
	for (int i = 0; i < keyKindNum; i++)
	{
		// 前に押してなくて、今押していたら
		if (mPrevKey[i] == NotPressed && mKey[i] == Pressed)
		{
			mKey[i] = PressedNow;     // 今の瞬間押されたという意味の2を代入。
		}
		mPrevKey[i] = mKey[i];        // 今の入力状態を過去に入力されたデータとしてコピー
	}
}

void GameController::adjustPadState() {

	for (int i = 0; i < padButtonNum; i++) {
		// 前に押してなくて、今押していたら
		if (padPrevInput1P[i] == NotPressed && padInput1P[i] == Pressed)
		{
			padInput1P[i] = PressedNow;     // 今の瞬間押されたという意味の2を代入。
		}
		padPrevInput1P[i] = padInput1P[i];        // 今の入力状態を過去に入力されたデータとしてコピー


		if (padPrevInput2P[i] == NotPressed && padInput2P[i] == Pressed)
		{
			padInput2P[i] = PressedNow;     // 今の瞬間押されたという意味の2を代入。
		}
		padPrevInput2P[i] = padInput2P[i];        // 今の入力状態を過去に入力されたデータとしてコピー
	}
}


bool GameController::isPressed(Button b, int pid) {
	bool res = false;
	if (pid == 0) {
		int table[] = { KEY_INPUT_Q, KEY_INPUT_E, KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_A,
			KEY_INPUT_D, KEY_INPUT_ESCAPE };
		res = (getKey(table[b]) == GameController::Pressed);
	}
	else {
		int table[] = { KEY_INPUT_U, KEY_INPUT_O, KEY_INPUT_I, KEY_INPUT_K, KEY_INPUT_J,
			KEY_INPUT_L, KEY_INPUT_ESCAPE };
		res = (getKey(table[b]) == GameController::Pressed);
	}

	if (DxLib::GetJoypadNum() > pid) { //一人用の時は1個　二人用の時は2個か確認
		int table[] = {
			PAD_INPUT_1,
			PAD_INPUT_2,
			PAD_INPUT_UP,
			PAD_INPUT_DOWN,
			PAD_INPUT_LEFT,
			PAD_INPUT_RIGHT,
			PAD_INPUT_9,
		};
		res = (getPadInput(table[b], pid) == GameController::Pressed);
	}
	return res;
}

bool GameController::isPressedNow(Button b, int pid) {
	bool res = false;
	if (pid == 0) {
		int table[] = { KEY_INPUT_Q, KEY_INPUT_E, KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_A,
			KEY_INPUT_D, KEY_INPUT_ESCAPE };
		res = (getKey(table[b]) == GameController::PressedNow);
	}
	else {
		int table[] = { KEY_INPUT_U, KEY_INPUT_O, KEY_INPUT_I, KEY_INPUT_K, KEY_INPUT_J,
			KEY_INPUT_L, KEY_INPUT_ESCAPE };
		res = (getKey(table[b]) == GameController::PressedNow);
	}

	if (DxLib::GetJoypadNum() > pid) { //一人用の時は1個　二人用の時は2個か確認
		int table[] = {
			PAD_INPUT_1,
			PAD_INPUT_2,
			PAD_INPUT_UP,
			PAD_INPUT_DOWN,
			PAD_INPUT_LEFT,
			PAD_INPUT_RIGHT,
			PAD_INPUT_9,
		};
		res = (getPadInput(table[b], pid) == GameController::PressedNow);
	}
	return res;
}