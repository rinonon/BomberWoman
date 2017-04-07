#include "Sequence\Ending.h"
#include "ResourceLoader.h"
#include "Sequence\Parent.h"
#include "StringRenderer.h"

namespace Sequence {

Ending::Ending() : mCount(0) {
	rl = ResourceLoader::getInstance();
}

Ending::~Ending(){}

void Ending::update(Parent* parent) {
	if (mCount == 120) {
		parent->moveTo(Parent::NEXT_TITLE);
	}

	StringRenderer::getInstance()->draw(0, 0, "Game Clear");

	mCount++;
}

} //namespace Sequence