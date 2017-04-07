#include "Sequence\Game\Clear.h"
#include "ResourceLoader.h"
#include "Sequence\Game\Parent.h"
#include "stdCommon.h"
#include "Game\State.h"
#include "StringRenderer.h"


namespace Sequence {
namespace Game {

Clear::Clear() : mCount(0) {
	rl = ResourceLoader::getInstance();
}

Clear::~Clear() {}

void Clear::update(Parent* parent) {
	if (mCount == 60) {
		if (parent->hasFinalStageCleared()) {
			parent->moveTo(Parent::NEXT_ENDING);
		}
		else {
			parent->moveTo(Parent::NEXT_READY);
		}
	}

	//ƒQ[ƒ€‰æ–Ê‚Ìã‚É•`ŽÊ
	parent->getState()->draw();
	//DxLib::DrawGraph(0, 0, rl->getHdClear(), true)

	//”¼“§–¾‚Ì•‚¢‰æ–Ê
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawBox(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	StringRenderer::getInstance()->draw(0, 0, "Stage Clear!");

	mCount++;
}
}// namespace Game
}// namespace Sequence