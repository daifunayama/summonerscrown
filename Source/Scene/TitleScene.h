#pragma once
#include "Scene.h"
#include "../Parameter.h"
#include "../SSPlayer/SS5Player.h"
#include "../Input/Controller.h"

/*
�^�C�g����ʂ̃V�[���N���X
*/
class TitleScene : public Scene {
public:
	TitleScene():Scene(Parameter::SCENE_TITLE) {
		Load();
	}

	void Load();
	void Process();
	void Drawing();

private:
	Controller mController;
	int mCounter;
	ss::Player *mSprite;		//���S�A�j���[�V�����p�X�v���C�g
	int mGraphAnime1;			//�w�i�A�j��
	int mGraphBack;

	int mSoundEnter;			//����SE
	int mSE1;
	int mSE2;
	int mSE3;
};