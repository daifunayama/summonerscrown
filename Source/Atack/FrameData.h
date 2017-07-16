#pragma once
#include "../HitBox/HitBox.h"
#include "../HitBox/BoxData.h"

/*攻撃の1F内のデータ*/
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
	int mSoundId;				//SEのID
	HitBox mHitBox;				//プレイヤーの当たり判定
	HitBox mDamageBox[10];		//プレイヤーの食らい判定
	HitBox mAtackBox[20];		//攻撃範囲
	BoxData mAtackBoxData[5];	//攻撃のボックスデータ
	bool mAllowCancel;			//このフレーム中キャンセル可能か
};