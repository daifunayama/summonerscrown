#pragma once
#include "FrameData.h"
#include <vector>

/*
������U���̒�`������N���X
*/
class Atack {
public:
	inline int getCounter() { return mCounter; }
	inline int getAtackHit() { return mAtackHit; }
	inline FrameData getFrameData(int n) { return mFrameData[n]; }

	inline void setAtackHit(bool atackHit) { mAtackHit = atackHit; }
	
	void PushFrameData(FrameData);
	void ClearFrameData();
	void InitAtack();
	void IncreaseCounter();
	bool CheckAtackEnd();

protected:
	int mCounter;						//�ėp�J�E���^
	bool mRight;
	bool mAtackHit;						//�U���̃q�b�g�t���O
	std::vector<FrameData> mFrameData;	//�U���̃t���[���f�[�^�z��
};