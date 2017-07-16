#pragma once
#include "Atack.h"
#include <vector>

/*
Follower型魔具の攻撃を定義するクラス
*/
class FollowerArmsAtack : public Atack {
public:
	inline bool getAllowCancel(int n) { return mAllowCancel[n]; }
	inline bool getContinueAtackAfterDamage() { return mContinueAtackAfterDamage; }

	inline void setAllowCancel(int n, bool t) { mAllowCancel[n] = t; }
	inline void setContinueAtackAfterDamage(bool t) { mContinueAtackAfterDamage = t; }

private:
	bool mRight;						//攻撃の向き
	bool mAllowCancel[10];				//キャンセル可能フラグ
	bool mContinueAtackAfterDamage;		//発生保証フラグ
};