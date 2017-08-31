#include <fstream>
#include "../../Application.h"
#include "../../SSPlayer/SS5Player.h"
#include "../../Utility.h"
#include "../../Atack/FrameData.h"
#include "../../Effekseer/AnimationController.h"
#include "Carol.h"
#include "../../Voice/Character/VoiceCarol.h"

Profile Carol::getProfile() {
	Profile p;
	p.name = "キャロル = ブラックフォード";
	p.eName = "Carol Blackford";
	p.pass = "carol";

	p.size = 0.34f;
	p.speed = 0.5f;
	p.distX = 0;
	p.distY = 0;

	p.cAtack = 5;
	p.lAtack = 1;
	p.aut = 1;
	p.pAtack = 5;
	p.sAtack = 1;
	return p;
}

/*サウンドのロード*/
void Carol::LoadSound() {
	mAnimeDrill = LoadGraph("Data/graphic/animation/dorill2.png");

	mSoundDash = LoadSoundMem("Data/se/highspeed-movement1.mp3");
	mSoundStep = mSoundDash;

	mSoundPlayerAtack[1] = LoadSoundMem("Data/se/手足・空振り04.mp3");
	mSoundPlayerAtack[2] = LoadSoundMem("Data/se/ロボット・殴る、蹴る02.mp3");
	mSoundPlayerAtack[3] = mSoundDash;

	ChangeVolumeSoundMem(128, mSoundDash);
	ChangeVolumeSoundMem(128, mSoundStep);
	ChangeVolumeSoundMem(128, mSoundPlayerAtack[2]);
}

/*ボイスのロード*/
void Carol::LoadVoice() {
	mVoice = new VoiceCarol();
	mVoice->Load();
}

/*プレイヤーデータをロード*/
void Carol::LoadData() {
	ifstream ifs;
	string tmp;

	string statebox[15] =
	{ "normal","walk","back","squat","jump",
		"damage_u","damage_d","damage_air","damage_air2",
		"damage_squat","summon","dash","step","guard","guar_squat" };

	//ボックスの初期化
	for (int i = 0; i<15; i++) {
		mHitBox[i].setExist(0);

		for (int j = 0; j < 10; j++) {
			mDamageBox[i][j].setExist(0);
		}
	}

	//ダメージボックスの読み込み

	ifs.clear();
	ifs.open("Data/character/carol/DamageBoxData.txt");

	if (ifs) {
		ifs >> mHeight;//高さ
		ifs >> mSquatY;//しゃがみ時Y座標補正
		ifs >> mDownY;//ダウン時Y座標補正

		ifs >> tmp;

		for (int i = 1; i < 15; i++) {
			for (int j = 0; j < 10; j++) {
				ifs >> tmp;
				if (tmp == statebox[i])break;
				mDamageBox[i][j].setPositionX(Utility::StringToInt(tmp));
				ifs >> tmp;
				mDamageBox[i][j].setPositionY(Utility::StringToInt(tmp));
				ifs >> tmp;
				mDamageBox[i][j].setWidth(Utility::StringToInt(tmp));
				ifs >> tmp;
				mDamageBox[i][j].setHeight(Utility::StringToInt(tmp));

				mDamageBox[i][j].setExist(1);
			}
		}
	}
	ifs.close();

	//プレイヤーの当たり判定の読み込み

	ifs.clear();
	ifs.open("Data/character/carol/HitBoxData.txt");

	if (ifs) {
		for (int i = 1; i < 15; i++) {
			ifs >> tmp;
			ifs >> tmp;
			mHitBox[i].setPositionX(Utility::StringToInt(tmp));
			ifs >> tmp;
			mHitBox[i].setPositionY(Utility::StringToInt(tmp));
			ifs >> tmp;
			mHitBox[i].setWidth(Utility::StringToInt(tmp));
			ifs >> tmp;
			mHitBox[i].setHeight(Utility::StringToInt(tmp));

			mHitBox[i].setExist(1);
		}
	}
	ifs.close();

	for (int i = 15; i < 40; i++) {
		mHitBox[i].setPositionX(mHitBox[0].getPositionX());
		mHitBox[i].setPositionY(mHitBox[0].getPositionY());
		mHitBox[i].setWidth(mHitBox[0].getWidth());
		mHitBox[i].setHeight(mHitBox[0].getHeight());
		mHitBox[i].setExist(1);
	}
}

/*アニメーションの更新*/
void Carol::UpdateAnimation() {
	string name;
	name = getProfile().pass + Utility::IntToString(getColor()) + "/";

	//振り向き
	if (mRight)mSprite->setScale(0.34, 0.34);
	else mSprite->setScale(-0.34, 0.34);

	//通常時（待機・前進・後退・ジャンプ）
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//プレイヤーが地面にいる
		if (mGround) {

			//プレイヤーが静止している
			if (mAcceleX == 0) {
				if (mSprite->getPlayAnimeName() != "idle" && mSprite->getPlayAnimeName() != "wait") {
					mSprite->play(name + "idle");
					mSprite->setStep(0.8f);
				}
				if (mIdleCounter == 300 && mPlayerId == 0) {
					//mSprite->play(name + "wait");
					//mSprite->setStep(0.5f);
				}
				if (mIdleCounter == 400 && mPlayerId == 0)mSprite->play(name + "idle");
			}
			//プレイヤーが右に進んでいる
			else if (mAcceleX > 0) {
				//プレイヤーが右向き
				if (mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play(name + "walk");
						mSprite->setStep(0.6f);
					}
				}
				//プレイヤーが左向き
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play(name + "back");
					mSprite->setStep(0.6f);
				}
			}
			//プレイヤーが左に進んでいる
			else {
				//プレイヤーが左向き
				if (!mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play(name + "walk");
						mSprite->setStep(0.6f);
					}
				}
				//プレイヤーが右向き
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play(name + "back");
					mSprite->setStep(0.6f);
				}
			}
		}
		//プレイヤーが空中にいる
		else {
			if (mAcceleY == 36 || mAcceleY == 28) {
				mSprite->play(name + "jump");
				mSprite->setStep(0.6f);
			}
		}

	}
	//ダッシュ
	else if (mState == Parameter::S_PLAYER_DASH) {
		if (mSprite->getPlayAnimeName() != "dash") {
			mSprite->play(name + "dash");
			mSprite->setStep(1.2f);
		}
	}
	//バックステップ
	else if (mState == Parameter::S_PLAYER_STEP) {
		if (mSprite->getPlayAnimeName() != "backstep") {
			mSprite->play(name + "backstep");
			mSprite->setStep(1.2f);
		}
	}
	//プレイヤーがしゃがんでいる
	else if (mState == Parameter::S_PLAYER_SQUAT) {
		if (mSprite->getPlayAnimeName() != "squat") {
			mSprite->play(name + "squat");
			mSprite->setStep(0.4f);
		}
	}
	//上段ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_U && mDamageCounter == 1) {
		mSprite->play(name + "damage_u");
		mSprite->setStep(0.7f);
	}
	//下段ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_D && mDamageCounter == 1) {
		mSprite->play(name + "damage_d");
		mSprite->setStep(0.7f);
	}
	//空中ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_AIR2 && mDamageCounter == 1) {
		mSprite->play(name + "damage_air");
		mSprite->setStep(1.0f);
	}
	//空中ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_AIR && mDamageCounter == 1) {
		mSprite->play(name + "damage_air");
		mSprite->setStep(1.0f);
		mSprite->setLoop(1);
	}
	//ダウン状態
	else if (mState == Parameter::S_PLAYER_DOWN && mCounter == 59) {
		mSprite->play(name + "down");
		mSprite->setStep(0.9f);
	}
	//しゃがみダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_S && mDamageCounter == 1) {
		mSprite->play(name + "damage_s");
	}
	//受け身状態
	else if (mState == Parameter::S_PLAYER_REVERSAL) {
		if (mSprite->getPlayAnimeName() != "reversal") {
			mSprite->play(name + "reversal");
			mSprite->setStep(0.7f);
		}
	}
	//つかまれ状態
	else if (mState == Parameter::S_PLAYER_CAUGHT) {
		if (mSprite->getPlayAnimeName() != "caught") {
			mSprite->play(name + "caught");
			mSprite->setStep(0.5f);
		}
	}
	//投げぬけ状態
	else if (mState == Parameter::S_PLAYER_ESCAPE) {
		if (mSprite->getPlayAnimeName() != "escape") {
			mSprite->play(name + "escape");
			mSprite->setStep(1.2f);
		}
	}
	//立ちガード状態
	else if (mState == Parameter::S_PLAYER_GUARD) {
		if (mSprite->getPlayAnimeName() != "guard_u") {
			mSprite->play(name + "guard_u");
		}
	}
	//しゃがみガード状態
	else if (mState == Parameter::S_PLAYER_GUARD_S) {
		if (mSprite->getPlayAnimeName() != "guard_d") {
			mSprite->play(name + "guard_d");
		}
	}
	//バースト
	else if (mState == Parameter::S_PLAYER_BURST) {
		if (mSprite->getPlayAnimeName() != "burst") {
			mSprite->play(name + "burst");
			mSprite->setStep(0.5f);
		}
	}
	//A攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_A &&
		mPlayerAtack[Parameter::P_ATACK_A].getCounter() == 1)
	{
		mSprite->play(name + "a");
		//mSprite->setStep(0.7f);
	}
	//A下攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_2A &&
		mPlayerAtack[Parameter::P_ATACK_2A].getCounter() == 1)
	{
		mSprite->play(name + "2a");
		//mSprite->setStep(0.7f);
	}
	//B攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_B &&
		mPlayerAtack[Parameter::P_ATACK_B].getCounter() == 1)
	{
		mSprite->play(name + "b");
		mSprite->setStep(0.7f);
	}
	
	//6B攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_6B &&
		mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 1)
	{
		mSprite->play(name + "6b");
		mSprite->setStep(0.8f);
	}
	/*
	//B下攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_2B &&
		mPlayerAtack[Parameter::P_ATACK_2B].getCounter() == 1)
	{
		mSprite->play(name + "2b");
		mSprite->setStep(0.6);
	}
	//3B攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_3B &&
		mPlayerAtack[Parameter::P_ATACK_3B].getCounter() == 1)
	{
		mSprite->play(name + "3b");
		mSprite->setStep(0.8);
	}
	//6B攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_6B &&
		mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 1)
	{
		mSprite->play(name + "6b");
		mSprite->setStep(0.6);
	}
	//JB攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_JA &&
		mPlayerAtack[Parameter::P_ATACK_JA].getCounter() == 1)
	{
		mSprite->play(name + "ja");
		mSprite->setStep(1.0);
	}
	//JB攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_JB &&
		mPlayerAtack[Parameter::P_ATACK_JB].getCounter() == 1)
	{
		mSprite->play(name + "jb");
		mSprite->setStep(1.2);
	}
	*/
	//つかみ
	else if (mState == Parameter::S_PLAYER_CATCH) {
		if (mSprite->getPlayAnimeName() != "catch") {
			mSprite->play(name + "catch");
		}
	}
	//投げ
	else if (mState == Parameter::S_PLAYER_THROW) {
		if (mSprite->getPlayAnimeName() != "throw") {
			mSprite->play(name + "throw");
			mSprite->setStep(0.6f);
		}
	}

	//表示位置の更新
	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
		Parameter::GROUND_LINE - mPositionY + 10 + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	//プレイヤーの更新、引数は前回の更新処理から経過した時間
	mSprite->update((float)30 / 1000);
}


//オーバーロード

/*攻撃を始める*/
void Carol::StartAtack() {
	//A攻撃
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		!mController.getDown() && mGround && isCanCancelTiming(Parameter::P_ATACK_A))
	{
		mState = Parameter::S_PLAYER_ATACK_A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_A].InitAtack();
	}
	//A下攻撃
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		mController.getDown() && mGround && isCanCancelTiming(Parameter::P_ATACK_2A))
	{
		mState = Parameter::S_PLAYER_ATACK_2A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2A].InitAtack();
	}
	//B攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() && !mController.getDown() && !mController.getRight() && !mController.getLeft()
		&& mGround && isCanCancelTiming(Parameter::P_ATACK_B))
	{
		mState = Parameter::S_PLAYER_ATACK_B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_B].InitAtack();
	}
	//B下攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && !mController.getRight() && !mController.getLeft() && mGround &&
		isCanCancelTiming(Parameter::P_ATACK_2B))
	{
		mState = Parameter::S_PLAYER_ATACK_2B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2B].InitAtack();
	}
	//3B攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && (mRight && mController.getRight() || !mRight && mController.getLeft()) && mGround &&
		isCanCancelTiming(Parameter::P_ATACK_3B))
	{
		mState = Parameter::S_PLAYER_ATACK_3B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_3B].InitAtack();
	}
	//6B攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() && !mController.getDown() && (mRight && mController.getRight() || !mRight && mController.getLeft()) && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_6B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_6B].InitAtack();
	}
}

/*ダッシュを始める*/
void Carol::StartDash() {
	mState = Parameter::S_PLAYER_DASH;
	mCounter = 15;
	PlaySoundMem(mSoundDash, DX_PLAYTYPE_BACK);
}

/*ステップを始める*/
void Carol::StartStep() {
	mState = Parameter::S_PLAYER_STEP;
	mCounter = 15;
	PlaySoundMem(mSoundStep, DX_PLAYTYPE_BACK);
}

void Carol::ProcessAtack() {
	static int animeKey;

	if (mState == Parameter::S_PLAYER_ATACK_6B) {
		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 10) {
			animeKey = AnimationController::getInstance().Create(mAnimeDrill, 2, 0, 0, 500, 300, 2.5, 0, 4, 1, 30, -1, mRight, true);
		}

		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() >= 10 && mPlayerAtack[Parameter::P_ATACK_6B].getCounter() < 30) {
			if (mRight)mAcceleX = 30;
			else mAcceleX = -30;
		}
		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() >= 25) {
			if (mRight) {
				mAcceleX -= 4;
				if (mAcceleX < 0)mAcceleX = 0;
			}
			else {
				mAcceleX += 4;
				if (mAcceleX > 0)mAcceleX = 0;
			}
		}
		AnimationController::getInstance().SetPosition(animeKey, mPositionX + (mRight ? -200 : 200), mPositionY - 20);
	}
}

/*投げる*/
void Carol::DoThrow(Player& another) {

	if (mCounter == 39 || mCounter == 34 || mCounter == 29 || mCounter == 24 || mCounter == 19)PlaySoundMem(mSoundPlayerAtack[1], DX_PLAYTYPE_BACK);

	if (mCounter == 15) {
		if (mRight)another.setAcceleX(mThrowDirection ? 5.0 : -5.0);
		else another.setAcceleX(mThrowDirection ? -5.0 : 5.0);
		another.setAcceleY(50.0);
		another.setGround(false);
		another.setState(Parameter::S_PLAYER_DAMAGE_AIR);
		another.setDamageCounter(0);
		another.setCounter(30);

		PlaySoundMem(mSoundPlayerAtack[2], DX_PLAYTYPE_BACK);
		AnimationController::getInstance().Create(mGraphDamage, 1, mRight?mPositionX+100:mPositionX-100, mPositionY, 600, 400, 2, GetRand(359), 4, 2, 48, 0, true, true);
	}
}