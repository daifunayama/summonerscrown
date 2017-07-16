#pragma once
#include "../../FollowerArms.h"

class Cyanos : public FollowerArms {
public:
	Cyanos() {
		mName = "源創魔球　シアノス";
		mPass = "Data/arms/PrimalSpheres/Cyanos";
		mCondition = "魔具による遠距離攻撃を１０種類ヒットさせる";
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

	//オーバーライド
	void StartAtack();

private:
	int mMaxBullet;
	int mBullet;
	int mGraphGauge1;
	int mGraphGauge2;
};