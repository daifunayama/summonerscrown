#pragma once
#include "../SSPlayer/SS5Player.h"
#include "../HitBox/HitBox.h"
#include "../Atack/PlayerAtack.h"
#include "../Arms/Arms.h"
#include "../Input/Controller.h"
#include "../Camera/Camera.h"
#include "Profile.h"

class Arms;
class Camera;

/*
バトル中のプレイヤーを制御するクラス
各キャラクターはこのクラスを継承し独自の処理を追加する
*/
class Player {
public:
	inline Controller getController() { return mController; }
	inline int getPlayerId() { return mPlayerId; }
	inline int getColor() { return mColor; }
	inline string getName() { return mName; }
	inline int getState() { return mState; }
	inline int getCounter() { return mCounter; }
	inline int getHitStop() { return mHitStop; }
	inline int getHP() { return mHP; }
	inline int getEX() { return mEXP; }
	inline int getChain() { return mChain; }
	inline int getPositionX() { return mPositionX; }
	inline int getPositionY() { return mPositionY; }
	inline bool getRight() { return mRight; }
	inline bool getOpenCircle() { return mOpenCircle; }
	inline Arms* getArms(int n) { return mArms[n]; }
	inline bool getArmsExist(int n) { return mArmsExist[n]; }
	inline int getArmsId() { return mArmsId; }
	inline int getCircleCursor() { return mCircleCursor; }
	inline HitBox getDamageBox(int n1, int n2) { return mDamageBox[n1][n2]; }

	inline void setPlayerId(int playerId) { mPlayerId = playerId; }
	inline void setChain(int chain) { mChain = chain; }
	inline void setArmsExist(int n,bool t) { mArmsExist[n] = t; }

	void Init(int);
	virtual Profile getProfile() = 0;
	virtual void LoadGraphic();
	void LoadCommonSound();
	virtual void LoadSound() = 0;
	virtual void LoadVoice() = 0;
	virtual void LoadData() = 0;
	virtual void LoadAtack() = 0;
	void LoadArms(int);

	void Move(Player&);
	void DoJump();
	void StartSummon();
	void DoSummon();
	virtual void StartAtack();
	void DoAtack();
	virtual void ProcessAtack(){}
	virtual void StartDash();
	void DoDash();
	virtual void StartStep();
	void DoStep();
	void DoDamaged();
	void DecrementCounter(Player&);
	void DecrementHitStop();
	void ChangeDirection(Player&);
	void EatAtack(bool,BoxData);
	void EatDamage(Player&);
	void IncleaseChain() { mChain++ ; }

	void MoveArms();
	void DrawArms();
	void DrawArmsBack();
	void MoveCircleCursor();

	void CheckPlayersHit(Player&);
	void CheckWallHit();
	void CheckVirtualWallHit(Player &);
	void CheckPlayersAtackHit(Player&);

	virtual void UpdateAnimation() = 0;
	void Draw();
	void DrawShadow();
	void DrawHitBox();
	void DrawDamageBox();
	void DrawAtackBox();

	bool isAcceledState();
	bool isAtackState();
	bool isDamageState();
	bool isCanArmsAtackState();
	bool isCanCancelTiming(int atackId);

protected:
	Controller mController;			//コントローラー

	int mPlayerId;					//プレイヤーID
	int mCharaID;					//キャラID
	int mColor;						//カラーID
	string mName;					//キャラの名前
	int mState;						//状態変数
	int mCounter;					//汎用カウンタ
	int mDamageCounter;				//ダメージカウンタ
	int mHitStop;
	int mPositionX;					//X座標
	int mPositionY;					//Y座標
	double mPositionDX;				//X座標(double)
	double mPositionDY;				//Y座標(double)
	double mAcceleX;				//X加速度
	double mAcceleY;				//Y加速度
	bool mBarrier;					//バリアを展開しているかのフラグ
	bool mOpenCircle;				//契約陣を開いているかどうかのフラグ
	int mRightCounter;				//右キーのカウンター
	int mLeftCounter;				//左キーのカウンター
	int mHeight;					//プレイヤーの高さ
	int mSquatY;					//しゃがみ時Y座標補正
	int mDownY;						//ダウン時Y座標補正
	int mHP;						//ヒットポイント
	int mEXP;						//EXポイント
	bool mRight;					//プレイヤーの向き
	bool mGround;					//プレイヤーの接地フラグ
	PlayerAtack mPlayerAtack[15];	//プレイヤーの攻撃データ
	HitBox mHitBox[15];				//プレイヤーの当たり判定用ヒットボックス
	HitBox mDamageBox[15][10];		//プレイヤーのダメージ食らい判定用のヒットボックス
	bool mEatAtackFlag;				//攻撃を食らったかどうかのフラグ
	bool mEatAtackRight;			//攻撃を食らった向き
	BoxData mEatAtackData;			//食らった攻撃を保存しておくボックスデータ
	ss::Player *mSprite;			//プレイヤーのスプライト
	Arms* mArms[8];					//魔具8種
	bool mArmsExist[8];				//魔具の存在フラグ
	int mArmsId;					//召喚中魔具
	int mCircleCursor;				//契約陣のカーソル位置
	int mChain;						//チェーン
	int mBarrierId;					//バリアのアニメID

	int mGraphShadow;				//影のグラフィックハンドル
	int mGraphSummonEffect1;		//召喚陣のグラフィックハンドル1
	int mGraphSummonEffect2;		//召喚陣のグラフィックハンドル2
	int mGraphDamage;				//ダメージエフェクトのグラフィックハンドル
	int mAnimeBarrier;				//バリアのグラフィックハンドル

	int mSoundOpenCircle;			//契約陣を開くSE
	int mSoundSummon;				//召喚SE
	int mSoundDamage;				//ダメージSE
	int mSoundGuard;				//ガードSE
	int mSoundPlayerAtack[10];		//攻撃用SE
};