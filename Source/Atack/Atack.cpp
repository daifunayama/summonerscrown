#include "Atack.h"

/*�U���p�̏�����*/
void Atack::InitAtack() {
	mCounter = 0;
	mAtackHit = false;
}

/*�J�E���^�[��i�߂�*/
void Atack::IncreaseCounter() {
	mCounter++;
}

/*�U���̏I�����`�F�b�N*/
bool Atack::CheckAtackEnd() {
	if (mCounter >= mFrameData.size()){
		return true;
	}
	return false;
}

/*�t���[���f�[�^���v�b�V������*/
void Atack::PushFrameData(FrameData frameData) {
	mFrameData.push_back(frameData);
}

/*�t���[���f�[�^���N���A����*/
void Atack::ClearFrameData() {
	mFrameData.clear();
}