#pragma once
#include "../Player.h"
#include "../Profile.h"

class Ein : public Player {
public:

	Profile getProfile();
	void LoadSound();
	void LoadVoice();
	void LoadData();
	void LoadAtack();
	void UpdateAnimation();

	//オーバーロード
	void StartAtack();
	void StartDash();
	void StartStep();
	void ProcessAtack();
	void DoThrow(Player& another);

private:
	int mSoundDash;
	int mSoundStep;
	int mAnimeDrill;
};