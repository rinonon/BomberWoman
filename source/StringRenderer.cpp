#include "StringRenderer.h"
#include "stdCommon.h"
#include "sstream"
#include "ResourceLoader.h"

//static変数はcppに実体が必要
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
	//書き込み先を初期化
	int dstX = x * CHAR_WIDTH;
	int dstY = y * CHAR_HEIGHT;

	//範囲外チェック(Yが外れたら問答無用で抜ける)
	if (dstY < 0 || dstY >= HEIGHT) {
		return;
	}
	//画像幅
	for (int i = 0; s[i] != '\0'; ++i) {
		//X範囲判定
		if (dstX >= 0 && (dstX + CHAR_WIDTH) < WIDTH) {
			//文字範囲チェック
			int t = s[i];
			if (t < 32 || t >= 128) {
				t = 127; //範囲外は四角に変換
			}
			t -= 32; //フォント画像の左上が32番なので、32を引く
			int srcX = (t % 16) * CHAR_WIDTH; //Xは幅で割った余り
			int srcY = (t / 16) * CHAR_HEIGHT; //Yは幅で割った商
											 
			DxLib::DrawGraph(dstX, dstY, rl->getInstance()->getHdFont(t), TRUE);
		}
		dstX += CHAR_WIDTH;
	}
}