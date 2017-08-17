#pragma once
#include "Atack.h"
#include <vector>

/*
Follower�^����̍U�����`����N���X
*/
class FollowerArmsAtack : public Atack {
public:
	inline bool getAllowCancel(int n) { return mAllowCancel[n]; }
	inline bool getContinueAtackAfterDamage() { return mContinueAtackAfterDamage; }

	inline void setAllowCancel(int n, bool t) { mAllowCancel[n] = t; }
	inline void setContinueAtackAfterDamage(bool t) { mContinueAtackAfterDamage = t; }

private:
	bool mAllowCancel[10];				//�L�����Z���\�t���O
	bool mContinueAtackAfterDamage;		//�����ۏ؃t���O
};