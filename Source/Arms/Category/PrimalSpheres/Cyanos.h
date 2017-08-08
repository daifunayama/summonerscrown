#pragma once
#include "../../FollowerArms.h"

class Cyanos : public FollowerArms {
public:
	Cyanos() {
		LoadArmsName();
		mMaxBullet = 5;
		mBullet = mMaxBullet;
	}

	Profile getProfile();
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