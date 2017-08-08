#pragma once
#include "../../FollowerArms.h"

class Cavalier : public FollowerArms {
public:
	Cavalier() {
		LoadArmsName();
		mMaxBullet = 5;
		mBullet = mMaxBullet;
	}
	Profile getProfile();
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