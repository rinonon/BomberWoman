#include "Sequence\Game\Ready.h"
#include "Sequence\Game\Parent.h"
#include "stdCommon.h"
#include "Game\State.h"
#include "StringRenderer.h"
#include "ResourceLoader.h"

namespace Sequence {
namespace Game {

Ready::Ready() : mCount(0), mStarted(false) {
	rl = ResourceLoader::getInstance();
}

Ready::~Ready(){}

void Ready::update(Parent* parent) {

	char* s = "";

	if (!mStarted) {
		parent->startLoading();
		mStarted = true;
	}

	if (mCount == 120) {
		parent->moveTo(Parent::NEXT_PLAY);
	}
	else if (mCount >= 60) {
		s = "Go!";
	}
	else {
		s = "Ready...";
	}

	parent->getState()->draw();

	//”¼“§–¾‚Ì•‚¢‰æ–Ê
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DxLib::DrawBox(0, 0, WIDTH, HEIGHT, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	StringRenderer::getInstance()->draw(0, 0, "[READY] : ");
	StringRenderer::getInstance()->draw(0, 1, s);

	mCount++;
}

}
}