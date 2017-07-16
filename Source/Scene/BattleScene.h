#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include "../BackGround/BackGround.h"
#include "../UI/HPGauge.h"
#include "../UI/EXGauge.h"
#include "../UI/Chain.h"
#include "../UI/ContractCircle.h"
#include "../Parameter.h"

/*
�퓬�V�[���N���X
�퓬���K�v�ȏ��������ׂĊǗ�����
*/
class BattleScene : public Scene {
public:
	BattleScene() :Scene(Parameter::SCENE_TITLE) {
		Load();
	}

	void Load();
	virtual void Process();
	virtual void Drawing();

private:
	Player* mPlayer[2];						//�퓬�v���C���[
	HPGauge mHPGauge[2];					//HP�Q�[�W
	EXGauge mEXGauge[2];					//EX�Q�[�W
	Chain mChain[2];						//�`�F�[��
	ContractCircle mContractCircle[2];		//�_��w
	BackGround mBackGround;					//�w�i

	int mBGM;								//BGM�̃T�E���h�n���h��
};