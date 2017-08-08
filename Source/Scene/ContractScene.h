#pragma once
#include "Scene.h"
#include "../Parameter.h"
#include "../SSPlayer/SS5Player.h"
#include "../Player/Player.h"
#include "../UI/ContractCircle.h"

/*
�_��V�[���N���X
*/
class ContractScene : public Scene {
public:
	ContractScene() :Scene(Parameter::SCENE_CONTRACT) {
		Load();
	}

	void Load();
	void LoadCategoryList(int p, int category);
	void LoadArmsProfile(int p,int category, int id);
	void Process();
	void MoveCircleCursor(int p);
	void ChangeArmsSprite(int p);

	void Drawing();
	void DrawCategoryList(int p, int x, int y);
	void DrawProfile(int p, int x, int y);

private:
	struct ArmsProfile {
		bool exist;
		string name;
		string sName;
		string condition;
		string explain[5];
		int type;
		int rank;
	};

	struct CategoryList {
		string name;
		string sName;
		ArmsProfile armslist[10];
	};

private:
	Controller mController[2];		//���͐���p�R���g���[���[

	int mCounter;					//�ėp�J�E���^�[
	int mCursor[2];					//�J�[�\���ʒu
	int mCategoryCursor[2];
	int mArmsCursor[2];
	int mDecided[2];				//����t���O
	bool mSwitch[2];				//�\���t���O

	int mGraphBackground;			//�w�i�̃O���t�B�b�N�n���h��
	int mGraphCursor;				//�J�[�\���̃O���t�B�b�N�n���h��
	int mGraphCursor2;				//�J�[�\���̃O���t�B�b�N�n���h��2
	int mGraphEmblem[11];			//�G���u�����̃O���t�B�b�N�n���h��
	int mGraphAnime1;				//�w�i�A�j���̃O���t�B�b�N�n���h��
	Player* mPlayer[2];				//�v���C���[
	ss::Player* mSprite[2];			//�X�v���C�g
	ArmsProfile mProfile[2];		//����̃v���t�@�C��
	ContractCircle mCircle[2];		//�_��w
	CategoryList mCategorylist[2];
	Arms *mArms[2];

	int mSoundCursor;				//�J�[�\���ړ��̃T�E���h�n���h��
	int mSoundEnter;				//����SE
	int mSoundCancel;				//�L�����Z��SE
	int mBGM;						//BGM�̃T�E���h�n���h��

};