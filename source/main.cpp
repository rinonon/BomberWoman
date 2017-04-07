#include "stdCommon.h"
#include "Game/State.h"
#include "File.h"
#include "Sequence/Parent.h"
#include "StringRenderer.h"
#include "ResourceLoader.h"
#include "GameController.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("BomberWoman"); //タイトルのセット
	ChangeWindowMode(true); //ウィンドウモードにセット
	SetGraphMode(WIDTH, HEIGHT, 16); //ウィンドウサイズとカラービット数の指定

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//裏画面描写にする
	if (SetDrawScreen(DX_SCREEN_BACK) == -1) return -1;
	//描写モードをバイリニア法にする
	if (SetDrawMode(DX_DRAWMODE_BILINEAR) == -1) return -1;
	

	//各しんぐるとんのインスタンス作成
	if (!Sequence::Parent::getInstance()) {
		Sequence::Parent::create();
	}

	if (!StringRenderer::getInstance()) {
		StringRenderer::create();
	}

	if (!GameController::getInstance()) {
		GameController::create();
	}

	if (!ResourceLoader::getInstance()) {
		ResourceLoader::create();
	}

	ResourceLoader* rl = ResourceLoader::getInstance();
	GameController* gc = GameController::getInstance();

	if (rl->load() == -1) {
		OutputDebugString("can not load file");
	}

	// メッセージループ
	while (DxLib::ProcessMessage() == 0
		&& DxLib::ClearDrawScreen() == 0
		&& gc -> getAllKeyPressed() == 0
		&& gc -> getAllPadPressed() == 0
		&& gc -> getKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		gc->adjustKeyState();
		gc->adjustPadState();
		Sequence::Parent::getInstance()->update();
		gc->control();
		DxLib::ScreenFlip();
	}

	//しんぐるとんのメモリ解放
	Sequence::Parent::destroy();
	StringRenderer::destroy();
	ResourceLoader::destroy();
	GameController::destroy();

	DxLib::DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}




