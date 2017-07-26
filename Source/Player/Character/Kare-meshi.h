#pragma once

#include "../Player.h"

class KareMeshi : public Player {
public:
	
	Profile getProfile();
	void LoadSound();
	void LoadVoice();
	void LoadData();
	void LoadAtack();
	void UpdateAnimation();

	//�I�[�o�[���[�h
	void ProcessAtack();

private:
	int mSoundDash;
	int mSoundStep;
}; 
