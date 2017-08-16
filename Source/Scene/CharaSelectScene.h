#pragma once
#include "Scene.h"
#include "../Parameter.h"
#include "../SSPlayer/SS5Player.h"
#include "../Player/Player.h"

/*
�L�����Z���N�g�V�[���N���X
*/
class CharaSelectScene : public Scene {
public:
	CharaSelectScene() :Scene(Parameter::SCENE_TITLE) {
		Load();
	}

	void Load();
	void Process();
	void ChangePlayerSprite(int p,int id);
	void Drawing();
	void DrawProfile(int p,Profile pf, int x, int y);
	void DrawStyles(int p, Styles st, int x, int y);
	void DrawRotaEmblem(int category, int x, int y);

private:
	Controller mController[2];		//���͐���p�R���g���[���[

	int mAnimeCounter[2];			//�e�v���C���[�̃A�j���[�V�����p�J�E���^
	int mCounter;					//�ėp�J�E���^�[
	int mCursor[2];					//�J�[�\���ʒu
	int mColor[2];					//�J���[ID
	int mDecided[2];				//�L��������t���O
	bool mSwitch[2];				//�\���t���O

	int mGraphBackground;			//�w�i�̃O���t�B�b�N�n���h��
	int mGraphCursor[2];			//�J�[�\���̃O���t�B�b�N�n���h��
	int mGraphCursor2[2];			//�J�[�\���̃O���t�B�b�N�n���h��2
	int mGraphFace[11];				//�L�����t�F�C�X�̃O���t�B�b�N�n���h��
	int mGraphStand[11];			//�L���������G�̃O���t�B�b�N�n���h��
	int mGraphEmblem[11];			//�G���u�����̃O���t�B�b�N�n���h��
	int mGraphAnime1;				//�w�i�A�j���̃O���t�B�b�N�n���h��
	int mGraphAnime2;
	int mGraphShadow;				//�e�̃O���t�B�b�N�n���h��
	Player* mPlayer[2];				//�v���C���[
	ss::Player* mSprite[2];			//�v���C���[�̃X�v���C�g
	
	int voice[11][5];				//�I�𒆃{�C�X

	int mSoundCursor;				//�J�[�\���ړ��̃T�E���h�n���h��
	int mSoundMetal;				//�K�`������
	int mSoundEnter;				//����SE
	int mSoundCancel;				//�L�����Z��SE
	int mBGM;						//BGM�̃T�E���h�n���h��
};