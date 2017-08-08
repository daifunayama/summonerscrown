#pragma once
#include "../../FollowerArms.h"

class Aries : public FollowerArms {
public:
	Aries() {
		LoadArmsName();
	}
	
	Profile getProfile();
	void UpdateArmsAnimation();
	void LoadArmsGraphic();
	void LoadArmsSound();

	void CheckCanSummon();
	void Process();
	void ProcessAfterAtack();

	//オーバーライド
	void StartAtack();

	
private:
};