#pragma once
#include "../Player/Player.h"
#include "../Input/Controller.h"
#include "../Effekseer/EffAnimation.h"
#include "../SSPlayer/SS5Player.h"
#include "../Parameter.h"

class Player;
class Controller;

/*
全魔具のもととなるクラス
Follower,Automata,Spell,Blazeはこのクラスを継承し独自の処理を行う
*/

class Arms {
protected:


	struct Profile {
		int category;
		int id;
		int type;
		float size;
		float speed;
	};

public:
	inline int getState() { return mState; }
	inline int getCounter() { return mCounter; }
	inline int getPositionX() { return mPositionX; }
	inline int getPositionY() { return mPositionY; }
	inline int getDistX() { return mDistX; }
	inline int getDistY() { return mDistY; }
	inline bool getRight() { return mRight; }
	inline string getName() { return mName; }
	inline string getCondition() { return mCondition; }
	inline int getIcon() { return mIcon; }

	inline void setPositionX(int positionX) { mPositionX = positionX; }
	inline void setPositionY(int positionY) { mPositionY = positionY; }
	inline void setState(int state) { mState = state; }
	inline void setRight(bool right) { mRight = right; }
	inline void setCounter(int counter) { mCounter = counter; }

	void ReceivePlayer(Player*, Controller);
	void LoadArmsName();

	virtual Profile getProfile() = 0;
	virtual void InitArms() = 0;
	virtual void LoadArmsData() = 0;
	virtual void LoadArmsGraphic() = 0;
	virtual void LoadArmsSound() = 0;
	virtual void Move() = 0;
	virtual void ResetPosition(){}
	virtual void StartSummon() {};
	virtual void StartAtack() = 0;
	virtual void UpdateArmsAnimation() = 0;
	virtual void Draw() = 0;
	virtual void DrawBack() {}
	virtual void DrawAtackBox() = 0;
	virtual void DrawUI(){}

	virtual void CheckArmsAtackHit(Player&) = 0;

	virtual bool isAtackState() { return false; }

protected:
	Player* mPlayer;				//プレイヤー
	Controller mController;			//操作制御用コントローラー
	int mCategoryId;				//魔具のカテゴリID
	int mArmsId;					//魔具のID
	int mState;						//魔具の状態変数
	int mCounter;					//汎用カウンタ
	int mPositionX;					//X座標
	int mPositionY;					//Y座標
	int mDistX;						//X座標補正
	int mDistY;						//Y座標補正
	bool mRight;					//向き
	ss::Player *mSprite;			//スプライト
	int mIcon;						//魔具アイコンのグラフィックハンドル
	int mSoundAtack[10];			//SEハンドル
	EffAnimation mAnimation[10];	//アニメーション
	//string mPass;					//魔具のディレクトリパス
	string mName;					//魔具の名称
	string mCondition;				//誓約
};