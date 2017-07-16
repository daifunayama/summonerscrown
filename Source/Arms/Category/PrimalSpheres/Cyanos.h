#pragma once
#include "../../FollowerArms.h"

class Cyanos : public FollowerArms {
public:
	Cyanos() {
		mName = "���n�����@�V�A�m�X";
		mPass = "Data/arms/PrimalSpheres/Cyanos";
		mCondition = "����ɂ�鉓�����U�����P�O��ރq�b�g������";
		mCategoryId = Parameter::PS;
		mMaxBullet = 5;
		mBullet = mMaxBullet;
	}

	void UpdateArmsAnimation();
	void LoadArmsGraphic();
	void LoadArmsSound();

	void CheckCanSummon();
	void ProcessBeforeAtack();
	void ProcessAfterAtack();
	void Draw();
	void DrawUI();

	//�I�[�o�[���C�h
	void StartAtack();

private:
	int mMaxBullet;
	int mBullet;
	int mGraphGauge1;
	int mGraphGauge2;
};