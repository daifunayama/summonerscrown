#pragma once
#include "FrameData.h"
#include <vector>

/*
������U���̒�`������N���X
*/
class Atack {
public:
	Atack() {
		mCounter = 0;
		mExist = 0;
	}
	inline bool getExist() { return mExist; }
	inline int getCounter() { return mCounter; }
	inline int getAtackHit() { return mAtackHit; }
	inline FrameData getFrameData(int n) { return mFrameData[n]; }

	inline void setExist(bool exist) { mExist = exist; }
	inline void setAtackHit(bool atackHit) { mAtackHit = atackHit; }
	
	void PushFrameData(FrameData);
	void ClearFrameData();
	void InitAtack();
	void IncreaseCounter();
	bool CheckAtackEnd();

protected:
	bool mExist;
	int mCounter;						//�ėp�J�E���^
	bool mRight;
	bool mAtackHit;						//�U���̃q�b�g�t���O
	std::vector<FrameData> mFrameData;	//�U���̃t���[���f�[�^�z��
};