#include "Sequence\GameOver.h"
#include "Sequence\Parent.h"
#include "ResourceLoader.h"
#include "stdCommon.h"
#include "StringRenderer.h"

namespace Sequence {

GameOver::GameOver() : mCount(0){
	rl = ResourceLoader::getInstance();
}

GameOver::~GameOver(){}

void GameOver::update(Parent* parent) {
	if (mCount == 60) {
		parent->moveTo(Parent::NEXT_TITLE);
	}

	//DxLib::DrawGraph(0, 0, rl->getHdTitle, TRUE);

	StringRenderer::getInstance()->draw(0, 0, "Game Over");

	mCount++;
}

}// namespace Sequence