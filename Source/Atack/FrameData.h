#pragma once
#include "../HitBox/HitBox.h"
#include "../HitBox/BoxData.h"

/*�U����1F���̃f�[�^*/
class FrameData {
public:
	inline int getSoundId() { return mSoundId; }
	inline HitBox getHitBox() { return mHitBox; }
	inline HitBox getDamageBox(int n) { return mDamageBox[n]; }
	inline HitBox getAtackBox(int n) { return mAtackBox[n]; }
	inline BoxData getAtackBoxData(int n) { return mAtackBoxData[n]; }
	inline bool getAllowCancel() { return mAllowCancel; }

	inline void setSoundId(int soundId) { mSoundId = soundId; }
	inline void setHitBox(HitBox hitBox) { mHitBox = hitBox; }
	inline void setDamageBox(int n, HitBox damageBox) { mDamageBox[n] = damageBox; }
	inline void setAtackBox(int n, HitBox atackBox) { mAtackBox[n] = atackBox; }
	inline void setAtackBoxData(int n, BoxData atackBoxData) { mAtackBoxData[n] = atackBoxData; }
	inline void setAllowCancel(bool allowCancel) { mAllowCancel = allowCancel; }

private:
	int mSoundId;				//SE��ID
	HitBox mHitBox;				//�v���C���[�̓����蔻��
	HitBox mDamageBox[10];		//�v���C���[�̐H�炢����
	HitBox mAtackBox[20];		//�U���͈�
	BoxData mAtackBoxData[5];	//�U���̃{�b�N�X�f�[�^
	bool mAllowCancel;			//���̃t���[�����L�����Z���\��
};