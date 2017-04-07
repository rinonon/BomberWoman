#include "Sequence\Game\Pause.h"
#include "stdCommon.h"
#include "Sequence\Game\Parent.h"
#include "ResourceLoader.h"
#include "GameController.h"
#include "Game\State.h"
#include "StringRenderer.h"

namespace Sequence {
namespace Game {

Pause::Pause() : mCursorPosition(0) {
	rl = ResourceLoader::getInstance();
	gc = GameController::getInstance();
}

Pause::~Pause() {}

void Pause::update(Parent* parent) {

	//1:やりなおし 2:面セレクト 3:タイトル画面 4:ゲームに戻る

	if (gc->getKey(KEY_INPUT_UP) == GameController::PressedNow) {
		mCursorPosition--;
		if (mCursorPosition < 0) {
			mCursorPosition = 1;
		}
	}
	else if (gc->getKey(KEY_INPUT_DOWN) == GameController::PressedNow) {
		mCursorPosition++;
		if (mCursorPosition > 1) {
			mCursorPosition = 0;
		}
	}
	else if (gc->getKey(KEY_INPUT_SPACE) == GameController::PressedNow) {
		if (mCursorPosition == 0) { //ゲームに戻る
			parent->moveTo(Parent::NEXT_PLAY);
		}
		else if (mCursorPosition == 1) { //タイトルへ戻る
			parent->moveTo(Parent::NEXT_TITLE);
		}
	}

	//ゲーム画面の上に描写
	parent->getState()->draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawBox(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	StringRenderer::getInstance()->draw(0, 0, "pause");

	StringRenderer::getInstance()->draw(3, 4, "continue");
	StringRenderer::getInstance()->draw(3, 5, "title");

	//カーソル描写
	StringRenderer::getInstance()->draw(2, 4 + mCursorPosition, ">");

}
} //namespace Game
} //namespace Sequence