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

private: 
	bool mAllowCancel[15];	//�L�����Z���\�t���O
};