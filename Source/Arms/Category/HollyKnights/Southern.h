#pragma once
#include "../../FollowerArms.h"

class Southern : public FollowerArms {
public:
	Southern() {
		LoadArmsName();
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
	void FollowPlayer(int pX, int pY);
	void StartAtack();
	void Draw();
	void DrawBack();

private:
	ss::Player* mSprite2;
	int mFormation;
};