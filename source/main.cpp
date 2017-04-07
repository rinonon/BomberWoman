#include "stdCommon.h"
#include "Game/State.h"
#include "File.h"
#include "Sequence/Parent.h"
#include "StringRenderer.h"
#include "ResourceLoader.h"
#include "GameController.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("BomberWoman"); //�^�C�g���̃Z�b�g
	ChangeWindowMode(true); //�E�B���h�E���[�h�ɃZ�b�g
	SetGraphMode(WIDTH, HEIGHT, 16); //�E�B���h�E�T�C�Y�ƃJ���[�r�b�g���̎w��

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//����ʕ`�ʂɂ���
	if (SetDrawScreen(DX_SCREEN_BACK) == -1) return -1;
	//�`�ʃ��[�h���o�C���j�A�@�ɂ���
	if (SetDrawMode(DX_DRAWMODE_BILINEAR) == -1) return -1;
	

	//�e���񂮂�Ƃ�̃C���X�^���X�쐬
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

	// ���b�Z�[�W���[�v
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

	//���񂮂�Ƃ�̃��������
	Sequence::Parent::destroy();
	StringRenderer::destroy();
	ResourceLoader::destroy();
	GameController::destroy();

	DxLib::DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}




