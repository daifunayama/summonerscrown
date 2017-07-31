#pragma once
#include "Scene.h"
#include "../Parameter.h"
#include "../SSPlayer/SS5Player.h"
#include "../Input/Controller.h"

/*
�퓬�O�A�C�L���b�`�̃V�[���N���X
*/
class Player;

class EyecatchScene : public Scene {
public:
	EyecatchScene() :Scene(Parameter::SCENE_TITLE) {
		Load();
	}

	void Load();
	void Process();
	void Drawing();

private:
	struct CharaGraph {
		int positionX;
		int positionY;
		int graph;
	};

	Controller mController;
	int mCounter;
	int mBright;
	CharaGraph mCharaGraph[2];
	Player *mPlayer[2];
	int mNameX[2];

	ss::Player *mSprite;		//���S�A�j���[�V�����p�X�v���C�g
	int mGraphBackground;		//�w�i
	int mGraphAnime1;			//�w�i�A�j��
	int mSoundEnter;			//����SE
	int mBGM;					//BGM
};

