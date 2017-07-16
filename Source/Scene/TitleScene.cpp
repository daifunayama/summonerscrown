#include "TitleScene.h"
#include "../Application.h"
#include "../Input/Input.h"
#include "../Effekseer/AnimationController.h"

/*���\�[�X�̃��[�h�Ə�����*/
void TitleScene::Load() {
	mGraphAnime1 = LoadGraph("Data/graphic/charaselect/l.png");

	//�v���C���[�̍쐬
	mSprite = ss::Player::create();

	//�A�j���f�[�^�����\�[�X�ɒǉ�
	Application::resman->addData("Data/sprite_logo/logo.ssbp");

	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite->setData("logo");// ssbp�t�@�C����

	mSprite->play("logo/anime_1");// �A�j���[�V���������w��

	//�\���ʒu��ݒ�
	mSprite->setPosition(640, 360);
	//�X�P�[���ݒ�
	mSprite->setScale(0.6f, 0.6f);

	mSprite->setStep(0.6);

	mSoundEnter = LoadSoundMem("Data/se/decision16.mp3");

	mController.SetPlayerId(0);
}

/*�X�V*/
void TitleScene::Process() {
	mController.ConvertInput();

	if (mController.getKey(9) == 1) {
		Application::mNextSceneId = Parameter::SCENE_CHARASELECT;
		PlaySoundMem(mSoundEnter, DX_PLAYTYPE_BACK);
	}
	mSprite->update((float)30 / 1000);

	if (mSprite->getFrameNo() == 38)
		AnimationController::getInstance().Create(mGraphAnime1, 1, 0, 350, 1024, 620, 1.25, 0, 4, 4, 204, 204, 0, 0);

	if (mSprite->getFrameNo() == 119)mSprite->setFrameNo(78);

	//�A�j���[�V�����̃v���Z�X
	AnimationController::getInstance().Process();
}

/*�`��*/
void TitleScene::Drawing() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//�A�j���[�V�����̕`��
	AnimationController::getInstance().DrawLayer1();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	mSprite->draw();

	if (mSprite->getFrameNo() > 38)DrawStringToHandle(480, 600, "<Press Start>", Parameter::COLOR_WHITE, Parameter::FONT_80_FERRUM, 0, 0);
}
