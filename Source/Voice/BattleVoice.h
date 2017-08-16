#pragma once
#include <vector>
#include <map>

class BattleVoice {
public:
	void PlayVoice(int state, int id);
	void PlayVoiceOver(int state, int id);
	void PlayVoiceIf(int state, int id);
	void StopVoice();
	virtual void Load(){}

protected:
	std::map <int, std::vector<int>> mVoice;

	/*
	std::vector<int> voiceSummon;
	std::vector<int> voiceSummon2;
	std::vector<int> voiceSummon3;
	int voiceBeforeUltimate;
	int voiceUltimate;


 
	std::vector<int> voicePAtack;
	std::vector<int> voiceMAtack;
	std::vector<int> voiceMCharge;

	std::vector<int> voiceThrow;
	std::vector<int> voiceEscape;

	std::vector<int> voiceDamage1;
	std::vector<int> voiceDamage2;

	std::vector<int> voiceAfterCombo;
	std::vector<int> voiceAfterDown;
	std::vector<int> voiceReversal;

	std::vector<int> voiceGuard;
	std::vector<int> voicBurst;

	int voiceJump;

	std::vector<int> voiceDash;
	std::vector<int> voiceBackStep;

	std::vector<int> voiceWait;
	std::vector<int> voiceChangeDirection;
	*/

};