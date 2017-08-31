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

private: 
	bool mAllowCancel[15];	//キャンセル可能フラグ
};