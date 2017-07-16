#pragma once
#include "../../FollowerArms.h"

class Cavalier : public FollowerArms {
public:
	Cavalier() {
		mName = "�R�}���_�[�@�L���o���G";
		mCondition = "�y�R�}���_�[�z����̍U�����P�T���ȏ㗣�ꂽ��������q�b�g������";
		mPass = "Data/arms/Comander/Cavalier";
		mCategoryId = Parameter::CM;
		mMaxBullet = 5;
		mBullet = mMaxBullet;
	}

	void UpdateArmsAnimation();
	void LoadArmsGraphic();
	void LoadArmsSound();

	void CheckCanSummon();
	void Process();
	void ProcessAfterAtack();
	void DrawUI();

	//�I�[�o�[���C�h
	void StartAtack();

private:
	int mMaxBullet;
	int mBullet;
	int mGraphBullet;
};