#include "StringRenderer.h"
#include "stdCommon.h"
#include "sstream"
#include "ResourceLoader.h"

//static�ϐ���cpp�Ɏ��̂��K�v
StringRenderer* StringRenderer::mInstance = 0;

StringRenderer::StringRenderer() {
}

StringRenderer::~StringRenderer() {}

void StringRenderer::create() {
	mInstance = new StringRenderer();
}

void StringRenderer::destroy() {
	SAFE_DELETE(mInstance);
}

StringRenderer* StringRenderer::getInstance() {
	return mInstance;
}


void StringRenderer::draw(int x, int y, const char* s, unsigned c) const {


	const int CHAR_WIDTH = 8;
	const int CHAR_HEIGHT = 16;
	//�������ݐ��������
	int dstX = x * CHAR_WIDTH;
	int dstY = y * CHAR_HEIGHT;

	//�͈͊O�`�F�b�N(Y���O�ꂽ��ⓚ���p�Ŕ�����)
	if (dstY < 0 || dstY >= HEIGHT) {
		return;
	}
	//�摜��
	for (int i = 0; s[i] != '\0'; ++i) {
		//X�͈͔���
		if (dstX >= 0 && (dstX + CHAR_WIDTH) < WIDTH) {
			//�����͈̓`�F�b�N
			int t = s[i];
			if (t < 32 || t >= 128) {
				t = 127; //�͈͊O�͎l�p�ɕϊ�
			}
			t -= 32; //�t�H���g�摜�̍��オ32�ԂȂ̂ŁA32������
			int srcX = (t % 16) * CHAR_WIDTH; //X�͕��Ŋ������]��
			int srcY = (t / 16) * CHAR_HEIGHT; //Y�͕��Ŋ�������
											 
			DxLib::DrawGraph(dstX, dstY, rl->getInstance()->getHdFont(t), TRUE);
		}
		dstX += CHAR_WIDTH;
	}
}