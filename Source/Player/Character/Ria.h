#pragma once

#include "../Player.h"

class Ria : public Player {
public:
	Profile getProfile();
	void LoadSound();
	void LoadVoice();
	void LoadData();
	void LoadAtack();
	void UpdateAnimation();

	//�I�[�o�[���[�h

private:
	int mSoundDash;
	int mSoundStep;
};