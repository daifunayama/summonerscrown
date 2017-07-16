#pragma once
#include "Atack.h"
#include "DxLib.h"

/*
�v���C���[�̍U�����`����N���X
*/
class PlayerAtack : public Atack {
public:
	inline bool getAllowCancel(int n) { return mAllowCancel[n]; }

	inline void setAllowCancel(int n, bool t) { mAllowCancel[n] = t; }
	inline void setVoiceHandle(int handle) { mVoice = handle; }
	void PlayVoice() { PlaySoundMem(mVoice, DX_PLAYTYPE_BACK); }

private: 
	int mVoice;				//�U�����{�C�X
	bool mAllowCancel[15];	//�L�����Z���\�t���O
};