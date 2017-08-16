#pragma once
#include "../../Blaze.h"

class Hercules : public Blaze {
public:
	Hercules() {
		LoadArmsName();
	}

	Profile getProfile();
	void UpdateArmsAnimation();
	void LoadArmsGraphic();
	void LoadArmsSound();

	void CheckCanSummon();
	void Process();
	void ProcessAfterAtack();

	//�I�[�o�[���C�h
	void StartAtack();


private:
};