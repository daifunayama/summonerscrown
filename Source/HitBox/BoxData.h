#pragma once

/*
衝突判定用ボックス内データの定義クラス
*/
class BoxData {
public:
	BoxData(){
		mAtackType = 0;
		mEffectType = 0;
		mSEType = 0;
		mGuardType = 0;
		mAllowMultiHit = 0;
		mHitStop = 0;
		mDecHitStop = 0;
		mBindTime = 0;
		mContinueAtackAfterOffset = 0;
		mForceDown = 0;
		mFloorBound = 0;
		mWallBound = 0;
		mShakeWindow = 0;
		mVectorX = 0;
		mVectorY = 0;
		mAirVectorX = 0;
		mAirVectorY = 0;
		mPower = 0;
		mEXGain = 0;
	}
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
	int mAtackType;                  //攻撃タイプ(上中下段)
	int mEffectType;                 //エフェクトタイプ
	int mSEType;                     //SEタイプ
	int mGuardType;                  //ガードタイプ(通常・ガー不・空ガー不)
	bool mAllowMultiHit;			 //多段ヒットを許可するかどうか
	int mHitStop;					 //ヒットストップ
	int mDecHitStop;				 //ヒットストップ減衰補正
	int mBindTime;					 //その場拘束時間
	bool mContinueAtackAfterOffset;  //相殺後攻撃継続フラグ
	bool mForceDown;				 //ダウン誘発フラグ
	bool mFloorBound;				 //床バウンド
	bool mWallBound;				 //壁叩きつけ
	int mShakeWindow;				 //画面揺らし(弱中強)
	int mVectorX;					 //吹き飛ばしXベクトル
	int mVectorY;					 //吹き飛ばしYベクトル
	int mAirVectorX;				 //空中吹き飛ばしXベクトル
	int mAirVectorY;				 //空中吹き飛ばしYベクトル
	int mPower;						 //威力
	int mEXGain;					 //EX回復
};