#include "Sequence\Game\Judge.h"
#include "Sequence\Game\Parent.h"
#include "ResourceLoader.h"
#include "GameController.h"
#include "Game\State.h"
#include "stdCommon.h"
#include "StringRenderer.h"

namespace Sequence {
namespace Game {

Judge::Judge() : mCursorPosition(0){
	gc = GameController::getInstance();
	rl = ResourceLoader::getInstance();
}

Judge::~Judge() {}

void Judge::update(Parent* parent) {

	// カーソル位置処理
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
		if (mCursorPosition == 0) {
			parent->moveTo(Parent::NEXT_READY); //続ける
		}
		else if (mCursorPosition == 1) {
			parent->moveTo(Parent::NEXT_TITLE); //タイトル画面へ
		}
	}

	parent->getState()->draw();

	//半透明の黒い画面
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawBox(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	StringRenderer::getInstance()->draw(0, 0, "result");
	StringRenderer::getInstance()->draw(0, 1, "1P win");

	StringRenderer::getInstance()->draw(3, 4, "continue");
	StringRenderer::getInstance()->draw(3, 5, "title");

	//カーソル描写
	StringRenderer::getInstance()->draw(2, 4 + mCursorPosition, ">");
}

}
}