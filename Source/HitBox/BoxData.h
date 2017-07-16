#pragma once

/*
�Փ˔���p�{�b�N�X���f�[�^�̒�`�N���X
*/
class BoxData {
public:
	BoxData(){}
	~BoxData(){}

	inline int getAtackType() { return mAtackType; }
	inline int getEffectType() { return mEffectType; }
	inline int getSEType() { return mSEType; }
	inline int getGuardType() { return mGuardType; }
	inline bool getAllowMultHit() { return mAllowMultiHit; }
	inline int getHitStop() { return mHitStop; }
	inline int getdecHitStop() { return mDecHitStop; }
	inline int getBindTime() { return mBindTime; }
	inline bool getContinueAtackAfterOffset() { return mContinueAtackAfterOffset; }
	inline bool getForceDown() { return mForceDown; }
	inline bool getFloorBound() { return mFloorBound; }
	inline bool getWallBound() { return mWallBound; }
	inline int getShakeWindow() { return mShakeWindow; }
	inline int getVectorX() { return mVectorX; }
	inline int getVectorY() { return mVectorY; }
	inline int getAirVectorX() { return mAirVectorX; }
	inline int getAirVectorY() { return mAirVectorY; }
	inline int getPower() { return mPower; }
	inline int getEXGain() { return mEXGain; }

	inline void setAtackType(int atackType) { mAtackType = atackType; }
	inline void setEffectType(int effectType){ mEffectType = effectType; }
	inline void setSEType(int SEType){ mSEType = SEType; }
	inline void setGuardType(int guardType){ mGuardType = guardType; }
	inline void setAllowMultHit(bool allowMultiHit) { mAllowMultiHit = allowMultiHit; }
	inline void setHitStop(int hitStop){ mHitStop = hitStop; }
	inline void setDecHitStop(int decHitStop){ mDecHitStop = decHitStop; }
	inline void setBindTime(int bindTime){ mBindTime = bindTime; }
	inline void setContinueAtackAfterOffset(bool continueAtackAfterOffset){ mContinueAtackAfterOffset = continueAtackAfterOffset; }
	inline void setForceDown(bool forceDown){ mForceDown = forceDown; }
	inline void setFloorBound(bool floorBound){ mFloorBound = floorBound; }
	inline void setWallBound(bool wallBound){ mWallBound = wallBound; }
	inline void setShakeWindow(int shakeWindow){ mShakeWindow = shakeWindow; }
	inline void setVectorX(int vectorX){ mVectorX = vectorX; }
	inline void setVectorY(int vectorY){ mVectorY = vectorY; }
	inline void setAirVectorX(int airVectorX){ mAirVectorX = airVectorX; }
	inline void setAirVectorY(int airVectorY){ mAirVectorY = airVectorY; }
	inline void setPower(int power){ mPower = power; }
	inline void setEXGain(int EXGain){ mEXGain = EXGain; }

private:
	int mAtackType;                  //�U���^�C�v(�㒆���i)
	int mEffectType;                 //�G�t�F�N�g�^�C�v
	int mSEType;                     //SE�^�C�v
	int mGuardType;                  //�K�[�h�^�C�v(�ʏ�E�K�[�s�E��K�[�s)
	bool mAllowMultiHit;			 //���i�q�b�g�������邩�ǂ���
	int mHitStop;					 //�q�b�g�X�g�b�v
	int mDecHitStop;				 //�q�b�g�X�g�b�v�����␳
	int mBindTime;					 //���̏�S������
	bool mContinueAtackAfterOffset;  //���E��U���p���t���O
	bool mForceDown;				 //�_�E���U���t���O
	bool mFloorBound;				 //���o�E���h
	bool mWallBound;				 //�ǒ@����
	int mShakeWindow;				 //��ʗh�炵(�㒆��)
	int mVectorX;					 //������΂�X�x�N�g��
	int mVectorY;					 //������΂�Y�x�N�g��
	int mAirVectorX;				 //�󒆐�����΂�X�x�N�g��
	int mAirVectorY;				 //�󒆐�����΂�Y�x�N�g��
	int mPower;						 //�З�
	int mEXGain;					 //EX��
};