#pragma once
#include "../../FollowerArms.h"

class Alpha : public FollowerArms {
public:
	Alpha() {
		mName = "人口魔具α";
		mCondition = "なし";
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

	//オーバーライド
	void StartAtack();

private:

};