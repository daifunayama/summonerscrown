#include "BattleVoice.h"
#include "DxLib.h"

void BattleVoice::PlayVoice(int state, int id) {
	PlaySoundMem(mVoice[state][id], DX_PLAYTYPE_BACK);
}

void BattleVoice::PlayVoiceOver(int state, int id) {
	StopVoice();
	PlaySoundMem(mVoice[state][id],DX_PLAYTYPE_BACK);
}

void BattleVoice::PlayVoiceIf(int state, int id) {
	bool t = false;
	for (int i = 0; i < 21; i++) {
		for (int l = 0; l < mVoice[i].size(); l++) {
			if (CheckSoundMem(mVoice[i][l]))t = true;

			if (t) {
				int a;
				a = 1;
				a++;
			}
		}
	}
	if (!t)PlaySoundMem(mVoice[state][id], DX_PLAYTYPE_BACK);
}

void BattleVoice::StopVoice() {
	for (int i = 0; i < 21; i++) {
		for (int l = 0; l < mVoice[i].size(); l++) {
			if (CheckSoundMem(mVoice[i][l]))StopSoundMem(mVoice[i][l]);
		}
	}
}