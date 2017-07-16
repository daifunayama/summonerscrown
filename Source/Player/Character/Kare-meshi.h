#pragma once

#include "../Player.h"

class KareMeshi : public Player {
public:
	
	Profile getProfile();
	void LoadGraphic();
	void LoadSound();
	void LoadVoice();
	void LoadData();
	void LoadAtack();
	void UpdateAnimation();

	//オーバーロード

private:
	int mSoundDash;
	int mSoundStep;
}; 
