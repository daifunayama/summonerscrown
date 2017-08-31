#include <fstream>
#include "../../Application.h"
#include "../../SSPlayer/SS5Player.h"
#include "../../Utility.h"
#include "../../Atack/FrameData.h"
#include "../../Effekseer/AnimationController.h"
#include "../../SSEffect/SSEffectController.h"
#include "Ein.h"
#include "../../Voice/Character/VoiceEin.h"

Profile Ein::getProfile() {
	Profile p;

	p.name = "アイン";
	p.eName = "Ein";
	p.pass = "ein";

	p.size = 0.25f;
	p.speed = 1.0f;
	p.distX = 0;
	p.distY = 0;

	p.cAtack = 3;
	p.lAtack = 5;
	p.aut = 2;
	p.pAtack = 3;
	p.sAtack = 3;

	return p;
}

/*サウンドのロード*/
void Ein::LoadSound() {
	mAnimeDrill = LoadGraph("Data/graphic/animation/dorill.png");

	mSoundDash = LoadSoundMem("Data/se/highspeed-movement1.mp3");
	mSoundStep = mSoundDash;
	
	mSoundPlayerAtack[1] = LoadSoundMem("Data/se/Cyber06-1.mp3");
	mSoundPlayerAtack[2] = LoadSoundMem("Data/se/ロボット・殴る、蹴る02.mp3");
	mSoundPlayerAtack[3] = mSoundDash;

	ChangeVolumeSoundMem(128, mSoundDash);
	ChangeVolumeSoundMem(128, mSoundStep);
	ChangeVolumeSoundMem(128, mSoundPlayerAtack[2]);
}

/*ボイスのロード*/
void Ein::LoadVoice() {
	mVoice = new VoiceEin();
	mVoice->Load();
}

/*プレイヤーデータをロード*/
void Ein::LoadData() {
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
	ifs.open("Data/character/ein/DamageBoxData.txt");

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
	ifs.open("Data/character/ein/HitBoxData.txt");

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
}

/*アニメーションの更新*/
void Ein::UpdateAnimation() {
	string name;
	name = getProfile().pass + Utility::IntToString(getColor()) + "/";

	//振り向き
	if (mRight)mSprite->setScale(0.26, 0.26);
	else mSprite->setScale(-0.26, 0.26);

	//通常時（待機・前進・後退・ジャンプ）
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//プレイヤーが地面にいる
		if (mGround) {

			//プレイヤーが静止している
			if (mAcceleX == 0) {
				if (mSprite->getPlayAnimeName() != "idle" && mSprite->getPlayAnimeName() != "wait") {
					mSprite->play(name + "idle");
				}
				if (mIdleCounter == 300 && mPlayerId == 0) {
					mSprite->play(name + "wait");
					mSprite->setStep(0.5f);
				}
				if (mIdleCounter == 400 && mPlayerId == 0)mSprite->play(name + "idle");
			}
			//プレイヤーが右に進んでいる
			else if (mAcceleX > 0) {
				//プレイヤーが右向き
				if (mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play(name + "walk");
					}
				}
				//プレイヤーが左向き
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play(name + "back");
				}
			}
			//プレイヤーが左に進んでいる
			else {
				//プレイヤーが左向き
				if (!mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play(name + "walk");
					}
				}
				//プレイヤーが右向き
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play(name + "back");
				}
			}
		}
		//プレイヤーが空中にいる
		else {
			if (mAcceleY == 36 || mAcceleY == 28) {
				mSprite->play(name + "jump");
			}
		}

	}
	//ダッシュ
	else if (mState == Parameter::S_PLAYER_DASH) {
		if (mSprite->getPlayAnimeName() != "dash") {
			mSprite->play(name + "dash");
		}
	}
	//バックステップ
	else if (mState == Parameter::S_PLAYER_STEP) {
		if (mSprite->getPlayAnimeName() != "backstep") {
			mSprite->play(name + "backstep");
		}
	}
	//プレイヤーがしゃがんでいる
	else if (mState == Parameter::S_PLAYER_SQUAT) {
		if (mSprite->getPlayAnimeName() != "squat") {
			mSprite->play(name + "squat");
		}
	}
	//上段ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_U && mDamageCounter == 1) {
		mSprite->play(name + "damage_u");
		mSprite->setStep(0.9f);
	}
	//下段ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_D && mDamageCounter == 1) {
		mSprite->play(name + "damage_d");
		mSprite->setStep(0.9f);
	}
	//空中ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_AIR && mDamageCounter == 1) {
		mSprite->play(name + "damage_air");
		mSprite->setStep(0.9f);
	}
	//ダウン状態
	else if (mState == Parameter::S_PLAYER_DOWN && mCounter == 59) {
		mSprite->play(name + "down");
		mSprite->setStep(0.7f);
	}
	//しゃがみダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_S && mDamageCounter == 1) {
		mSprite->play(name + "damage_squat");
	}
	//受け身状態
	else if (mState == Parameter::S_PLAYER_REVERSAL) {
		if (mSprite->getPlayAnimeName() != "reversal") {
			mSprite->play(name + "reversal");
			mSprite->setStep(1.2f);
		}
	}
	//つかまれ状態
	else if (mState == Parameter::S_PLAYER_CAUGHT) {
		if (mSprite->getPlayAnimeName() != "caught") {
			mSprite->play(name + "caught");
			mSprite->setStep(0.9f);
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
	}
	//A下攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_2A &&
		mPlayerAtack[Parameter::P_ATACK_2A].getCounter() == 1)
	{
		mSprite->play(name + "2a");
	}
	//B攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_B &&
		mPlayerAtack[Parameter::P_ATACK_B].getCounter() == 1)
	{
		mSprite->play(name + "b");
	}
	//6B攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_6B &&
		mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 1)
	{
		mSprite->play(name + "6b");
	}
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
	//JA攻撃
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
			mSprite->setStep(0.55f);
		}
	}

	//表示位置の更新
	mSprite->setPosition(mPositionX -(Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 
		Parameter::GROUND_LINE - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	//プレイヤーの更新、引数は前回の更新処理から経過した時間
	mSprite->update((float)30 / 1000);
}


//オーバーロード

/*攻撃を始める*/
void Ein::StartAtack() {
	//A攻撃
	if (mController.getKey(1) == 3 && !mController.getUp() &&
		!mController.getDown() && mGround && isCanCancelTiming(Parameter::P_ATACK_A) && mPlayerAtack[Parameter::P_ATACK_A].getExist())
	{
		mState = Parameter::S_PLAYER_ATACK_A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_A].InitAtack();
		mVoice->PlayVoiceIf(Parameter::VOICE_PATACK, 0);
	}
	//A下攻撃
	if (mController.getKey(1) == 3 && !mController.getUp() &&
		mController.getDown() && mGround && isCanCancelTiming(Parameter::P_ATACK_2A) && mPlayerAtack[Parameter::P_ATACK_2A].getExist())
	{
		mState = Parameter::S_PLAYER_ATACK_2A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2A].InitAtack();
		mVoice->PlayVoiceIf(Parameter::VOICE_PATACK, 0);
	}
	//B攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() && !mController.getDown() && !mController.getRight() && !mController.getLeft()
		&& mGround && isCanCancelTiming(Parameter::P_ATACK_B) && mPlayerAtack[Parameter::P_ATACK_B].getExist())
	{
		mState = Parameter::S_PLAYER_ATACK_B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_B].InitAtack();
		mVoice->PlayVoiceOver(Parameter::VOICE_PATACK, 6);
	}
	//B下攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && !mController.getRight() && !mController.getLeft() && mGround &&
		isCanCancelTiming(Parameter::P_ATACK_2B) && mPlayerAtack[Parameter::P_ATACK_2B].getExist())
	{
		mState = Parameter::S_PLAYER_ATACK_2B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2B].InitAtack();
		mVoice->PlayVoiceOver(Parameter::VOICE_PATACK, 5);
	}
	//3B攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && (mRight && mController.getRight() || !mRight && mController.getLeft()) && mGround &&
		isCanCancelTiming(Parameter::P_ATACK_3B) && mPlayerAtack[Parameter::P_ATACK_3B].getExist())
	{
		mState = Parameter::S_PLAYER_ATACK_3B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_3B].InitAtack();
		mVoice->PlayVoiceOver(Parameter::VOICE_PATACK, 8);
	}
	//6B攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() && !mController.getDown() && (mRight && mController.getRight() || 
		!mRight && mController.getLeft()) && mGround && mPlayerAtack[Parameter::P_ATACK_6B].getExist())
	{
		mState = Parameter::S_PLAYER_ATACK_6B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_6B].InitAtack();
		mVoice->PlayVoiceOver(Parameter::VOICE_PATACK, 7);
	}

	//JA攻撃
	if (mController.getKey(1) == 1 && !mController.getDown() && !mGround && mPlayerAtack[Parameter::P_ATACK_JA].getExist())
	{
		mState = Parameter::S_PLAYER_ATACK_JA;

		mPlayerAtack[Parameter::P_ATACK_JA].InitAtack();
		mVoice->PlayVoiceOver(Parameter::VOICE_PATACK, 1);
	}

	//JB攻撃
	if (mController.getKey(2) == 1 && !mController.getDown() && !mGround && mPlayerAtack[Parameter::P_ATACK_JB].getExist())
	{
		mState = Parameter::S_PLAYER_ATACK_JB;
		
		mPlayerAtack[Parameter::P_ATACK_JB].InitAtack();
		mVoice->PlayVoiceOver(Parameter::VOICE_PATACK, 0);
	}
}

/*ダッシュを始める*/
void Ein::StartDash() {
	mState = Parameter::S_PLAYER_DASH;
	mCounter = 15;
	PlaySoundMem(mSoundDash, DX_PLAYTYPE_BACK);

	mVoice->PlayVoiceIf(Parameter::VOICE_DASH, 0);
}

/*ステップを始める*/
void Ein::StartStep() {
	mState = Parameter::S_PLAYER_STEP;
	mCounter = 15;
	PlaySoundMem(mSoundStep, DX_PLAYTYPE_BACK);

	mVoice->PlayVoiceIf(Parameter::VOICE_BACKSTEP, GetRand(1));
}

void Ein::ProcessAtack() {
	static int animeKey;
	if (mState == Parameter::S_PLAYER_ATACK_6B) {
		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 2) {
			animeKey = AnimationController::getInstance().Create(mAnimeDrill, 2, 0,0, 500, 300, 3, 0, 4, 1, 30, -1, mRight, true);
		}

		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() >= 2 && mPlayerAtack[Parameter::P_ATACK_6B].getCounter() < 20) {
			if (mRight)mAcceleX = 25;
			else mAcceleX = -25;
		}
		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() >= 20) {
			if (mRight) {
				mAcceleX -= 5;
				if (mAcceleX < 0)mAcceleX = 0;
			}
			else {
				mAcceleX += 5;
				if (mAcceleX > 0)mAcceleX = 0;
			}
		}
		AnimationController::getInstance().SetPosition(animeKey, mPositionX + (mRight? -100:+100) , mPositionY - 20);
	}

	if (mState == Parameter::S_PLAYER_ATACK_JA || mState == Parameter::S_PLAYER_ATACK_JB) {
		if (mGround) {
			mState = Parameter::S_PLAYER_NORMAL;
			mAcceleY = 0;
		}
		else if (mState == Parameter::S_PLAYER_ATACK_JA && mChain > 0)mAcceleY += 1;
	}
}

/*投げる*/
void Ein::DoThrow(Player& another) {

	if (mCounter == 39)PlaySoundMem(mSoundPlayerAtack[1], DX_PLAYTYPE_BACK);

	if (mCounter == 20) {
		if (mRight)another.setAcceleX(mThrowDirection ? 20.0 : -20.0);
		else another.setAcceleX(mThrowDirection ? -20.0 : 20.0);
		another.setAcceleY(40.0);
		another.setGround(false);
		another.setState(Parameter::S_PLAYER_DAMAGE_AIR);
		another.setDamageCounter(0);
		another.setCounter(30);

		SSEffectController::getInstance().Play("mye1/mye1", mRight? mPositionX+100:mPositionX-100, 300, 0.9f, 1.0f, 0.6f, GetRand(359), 200);
	}
}