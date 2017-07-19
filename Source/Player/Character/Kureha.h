#pragma once
#include "../Player.h"
#include "../Profile.h"

class Kureha : public Player {
public:

	Profile getProfile();
	void LoadSound();
	void LoadVoice();
	void LoadData();
	void LoadAtack();
	void UpdateAnimation();

	//�I�[�o�[���[�h
	void StartAtack();
	void StartDash();
	void StartStep();
	void ProcessAtack();

private:
	int mSoundDash;
	int mSoundStep;
};