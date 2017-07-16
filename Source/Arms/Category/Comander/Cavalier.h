#pragma once
#include "../../FollowerArms.h"

class Cavalier : public FollowerArms {
public:
	Cavalier() {
		mName = "コマンダー　キャバリエ";
		mCondition = "【コマンダー】魔具の攻撃を１５ｍ以上離れた距離からヒットさせる";
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

	//オーバーライド
	void StartAtack();

private:
	int mMaxBullet;
	int mBullet;
	int mGraphBullet;
};