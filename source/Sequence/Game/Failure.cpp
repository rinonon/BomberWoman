#include "Sequence\Game\Failure.h"
#include "Sequence\Game\Parent.h"
#include "ResourceLoader.h"
#include "StringRenderer.h"
#include "Game\State.h"
#include "stdCommon.h"

namespace Sequence {
namespace Game {

Failure::Failure() : mCount(0) {
	rl = ResourceLoader::getInstance();
}

Failure::~Failure(){}

void Failure::update(Parent* parent) {
	if (mCount == 60) {

		if (parent->getLifeNumber() == 0) {
			parent->moveTo(Parent::NEXT_GAME_OVER);
		}
		else {
			parent->moveTo(Parent::NEXT_READY);
		}
	}

	parent->getState()->draw();

	//”¼“§–¾‚Ì•‚¢‰æ–Ê
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawBox(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	StringRenderer::getInstance()->draw(0, 0, "failure");

	mCount++;
}
} //namespace Game
} //namespace Sequence