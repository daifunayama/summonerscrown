#include "DxLib.h"
#include "Application.h"
#include "Parameter.h"
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	SetOutApplicationLogValidFlag(false);

	//��ʂ̐ݒ�
	ChangeWindowMode(true);
	SetMainWindowText("");
	SetWindowSizeChangeEnableFlag(false);
	SetGraphMode(Parameter::WINDOW_WIDTH, Parameter::WINDOW_HEIGHT, 32);
	SetWindowSizeExtendRate(1);

	if (DxLib_Init() == -1)return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	SetDrawMode(DX_DRAWMODE_BILINEAR);

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);

	int t0;

	Application application;

	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		t0 = GetNowCount();   //���[�v�O�̎��Ԃ̎擾

		ClearDrawScreen();    //��ʂ̃N���A


		//���C�����[�v
		application.MainLoop();
		
		//60FPS�ɒ���
		while ((GetNowCount() - t0) <= (double)(1000 / 60)) {} 

		ScreenFlip(); //�X�N���[���ɕ\��
	}

	DxLib_End();// �c�w���C�u�����g�p�̏I������

	return 0;// �\�t�g�̏I�� 

}
