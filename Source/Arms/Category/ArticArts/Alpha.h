#pragma once
#include "../../FollowerArms.h"

class Alpha : public FollowerArms {
public:
	Alpha() {
		mName = "�l�����";
		mCondition = "�Ȃ�";
		mPass = "Data/arms/ArticArts/alpha";
		mCategoryId = Parameter::AA;
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

};