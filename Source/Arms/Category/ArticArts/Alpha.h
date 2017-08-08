#pragma once
#include "../../FollowerArms.h"

class Alpha : public FollowerArms {
public:
	Alpha() {
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

	//�I�[�o�[���C�h
	void StartAtack();

private:

};