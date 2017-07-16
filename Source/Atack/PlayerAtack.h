#pragma once
#include "Atack.h"
#include "DxLib.h"

/*
プレイヤーの攻撃を定義するクラス
*/
class PlayerAtack : public Atack {
public:
	inline bool getAllowCancel(int n) { return mAllowCancel[n]; }

	inline void setAllowCancel(int n, bool t) { mAllowCancel[n] = t; }
	inline void setVoiceHandle(int handle) { mVoice = handle; }
	void PlayVoice() { PlaySoundMem(mVoice, DX_PLAYTYPE_BACK); }

private: 
	int mVoice;				//攻撃時ボイス
	bool mAllowCancel[15];	//キャンセル可能フラグ
};