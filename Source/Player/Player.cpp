#include "Player.h"
#include "../Parameter.h"
#include "../Input/Input.h"
#include "../Arms/FollowerArms.h"
#include "../Arms/Category/HollyKnights/Southern.h"
#include "../Arms/Category/ArticArts/Alpha.h"
#include "../Arms/Category/Comander/Cavalier.h"
#include "../Arms/Category/PrimalSpheres/Cyanos.h"
#include "../Utility.h"
#include "../Effekseer/AnimationController.h"
#include "../SSEffect/SSEffectController.h"
#include "DxLib.h"

/*プレイヤーデータの初期化*/
void Player::Init(int p) {
	mController.SetPlayerId(p);

	mState = Parameter::S_PLAYER_NORMAL;
	if (p == 0) {
		mPositionDX = 300.0;
		mRight = true;
		mName = "Ein";
	}
	else {
		mPositionDX = 500.0;
		mRight = false;
		mName = "Dammy";
	}
	mPositionDY = Parameter::GROUND_LINE - mHeight;
	mPositionX = (int)mPositionDX;
	mPositionY = (int)mPositionDY;
	mAcceleX = 0;
	mAcceleY = 0;
	mHP = 1000;
	mEXP = 50;
	mChain = 0;
	mCircleCursor = 0;
	mGround = true;

	mArmsId = 0;
}

/*グラフィックのロード*/
void Player::LoadGraphic() {

	mColor = 1;

	//プレイヤーの作成
	mSprite = ss::Player::create();

	//プレイヤーにリソースを割り当て
	mSprite->setData(getProfile().pass);// ssbpファイル名

	mSprite->play(getProfile().pass + Utility::IntToString(getColor()) + "/idle");// アニメーション名を指定

	//表示位置を設定
	mSprite->setPosition(400, 300);
	//スケール設定
	mSprite->setScale(getProfile().size, getProfile().size);

	mGraphShadow = LoadGraph("Data/graphic/game/shadow.png");
	mGraphDamage = LoadGraph("Data/graphic/animation/slash3.png");

	mGraphSummonEffect1 = LoadGraph("Data/graphic/animation/summon_effect1.png");
	mGraphSummonEffect2 = LoadGraph("Data/graphic/animation/summon_effect2.png");
	mAnimeBarrier = LoadGraph("Data/graphic/animation/barrier.png");
}

/*武器データのロード*/
void Player::LoadArms(int p) {
	for(int i=0;i<8;i++)mArmsExist[i] = false;

	if (p == 0) {
		mArms[0] = new Cyanos();
		mArms[1] = new Cavalier();
		mArms[2] = new Southern();
		mArms[7] = new Alpha();
		mArmsExist[0] = true;
		mArmsExist[1] = true;
		mArmsExist[2] = true;
		mArmsExist[7] = true;
	}
	else {
		mArms[0] = new Cavalier();
		mArms[1] = new Cyanos();
		mArmsExist[0] = true;
		mArmsExist[1] = true;
	}
	
	for (int i = 0; i < 8; i++) {
		if (mArmsExist[i]) {
			mArms[i]->ReceivePlayer(this, mController);
			mArms[i]->InitArms();
			mArms[i]->LoadArmsData();
			mArms[i]->LoadArmsGraphic();
			mArms[i]->LoadArmsSound();
		}
	}
}

/*共通サウンドのロード*/
void Player::LoadCommonSound() {
	mSoundOpenCircle = LoadSoundMem("Data/se/sen_ge_pis_kamaeru02.mp3");
	mSoundDamage = LoadSoundMem("Data/se/手足・殴る、蹴る10.mp3");
	mSoundSummon = LoadSoundMem("Data/se/decision11.mp3");
	mSoundGuard = LoadSoundMem("Data/se/sen_ka_katana_04.mp3");

	ChangeVolumeSoundMem(128, mSoundDamage);
}

/*プレイヤーを動かす*/
void Player::Move(Player& another) {
	//コントローラーの接続
	mController.ConvertInput();

	//契約陣を開く
	if (mController.getKey(5) > 0) {
		if (mController.getKey(5) == 1)PlaySoundMem(mSoundOpenCircle, DX_PLAYTYPE_BACK);
		mOpenCircle = true;
	}
	else mOpenCircle = false;

	//バリアをはる
	if ((mRight && mController.getLeft() > 0 || !mRight && mController.getRight() > 0)
		&& mController.getKey(1) > 0 && mController.getKey(2) > 0 && mEXP > 0 &&
		(mState == Parameter::S_PLAYER_NORMAL || mState == Parameter::S_PLAYER_SQUAT)) {
		if(!mBarrier)mBarrierId = AnimationController::getInstance().Create(mAnimeBarrier, 1,0,0,200, 300, 1.2, 0, 4, 2, 144, 144, mRight, false);
		mBarrier = true;
		AnimationController::getInstance().SetPosition(mBarrierId, mPositionX + (mRight ? +50 : -50), 
			mState == Parameter::S_PLAYER_NORMAL ? mPositionY : mPositionY+50);
	}
	//バリアを解除する
	else if (mBarrier) {
		mBarrier = false;
		AnimationController::getInstance().Remove(mBarrierId);
	}

	//静止・歩行状態のとき
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//右方向への移動
		if (mController.getRight() > 0) {
		
				if (mGround)mAcceleX = 8;

				//ダッシュ・ステップを始める
				if (mController.getRight() == 1 && mRightCounter > 0) {
					mRight ? StartDash() : StartStep();
				}

				//押されて10F以内ならばダッシュ許可用のカウンターを10にする
				mRightCounter = mController.getRight() < 10 ? 10 : 0;
			
		}
		else if (mRightCounter > 0)mRightCounter--;

		//左方向への移動
		if (mController.getLeft() > 0) {
		
			
				if (mGround)mAcceleX = -8;

				//ダッシュ・ステップを始める
				if (mController.getLeft() == 1 && mLeftCounter > 0) {
					mRight ? StartStep() : StartDash();
				}

				//押されて10F以内ならばダッシュ許可用のカウンターを10にする
				mLeftCounter = mController.getLeft() < 10 ? 10 : 0;
			
		}
		else if (mLeftCounter > 0)mLeftCounter--;

		//しゃがむ
		if (mController.getDown() > 0 && mGround && mState == Parameter::S_PLAYER_NORMAL) {
			mState = Parameter::S_PLAYER_SQUAT;
			mAcceleX = 0;
		}
	}

	if (mState == Parameter::S_PLAYER_NORMAL || isAtackState()) {
		//ジャンプする
		if (mController.getUp() == 2 && mGround && !mOpenCircle && 
			!mController.getKey(1) && !mController.getKey(2) && !mController.getKey(3) && !mController.getKey(4)) {
			mState = Parameter::S_ARMS_NORMAL;
			DoJump();
		}
	}

	//しゃがみ
	else if (mState == Parameter::S_PLAYER_SQUAT) {
		//下が押されていなければ立つ
		mAcceleX = 0;
		if (!mController.getDown())mState = Parameter::S_PLAYER_NORMAL;
	}

	//ダッシュ
	else if (mState == Parameter::S_PLAYER_DASH) {
		DoDash();
	}

	//ガード
	else if (mState == Parameter::S_PLAYER_GUARD || mState == Parameter::S_PLAYER_GUARD_S) {
		mAcceleX = mRight ? -2 : 2;
	}

	//ステップ
	else if (mState == Parameter::S_PLAYER_STEP) {
		DoStep();
	}

	//ダメージ中
	else if (isDamageState())DoDamaged();

	//召喚する
	if (mState == Parameter::S_PLAYER_NORMAL || mState == Parameter::S_PLAYER_SQUAT) {
		if (mOpenCircle && mGround) {
			if (mController.getKey(6) == 1) {
				StartSummon();
			}
		}
	}

	//攻撃を始める
	if(!mBarrier)StartAtack();

	//攻撃のプロセス
	if (isAtackState())DoAtack();

	//契約陣のカーソル
	if (mOpenCircle) {
		MoveCircleCursor();
	}

	//加速度を0にする
	if ((!mController.getRight() && !mController.getLeft() || mOpenCircle)
		&& mGround && mState == Parameter::S_PLAYER_NORMAL ||
		(mBarrier && mGround))
	{
		mAcceleX = 0;
	}

	//カウンターを減らし、0のとき次状態へ遷移
	DecrementCounter(another);

	//重力の処理
	if (!mGround)mAcceleY -= 2;

	//プレイヤーの移動
	mPositionDX += mAcceleX;
	mPositionDY -= mAcceleY;

	mPositionX = (int)mPositionDX;
	mPositionY = (int)mPositionDY;

	//壁と床の接触判定
	CheckWallHit();
}

/*ジャンプする*/
void Player::DoJump() {
	//右向き
	if (mController.getRight())mAcceleX = 8;
	//左向き
	else if (mController.getLeft())mAcceleX = -8;
	//垂直
	else mAcceleX = 0;

	//Y軸加速度
	mAcceleY = 38;

	//接地フラグをfalseに
	mGround = false;
}

/*召喚を始める*/
void Player::StartSummon() {
	int pX;

	//契約陣に魔具が存在するとき
	if (mArmsExist[mCircleCursor] && mArmsId != mCircleCursor && mArms[mArmsId]->getState() == Parameter::S_ARMS_NORMAL) {
		pX = mRight ? mPositionX - 100 : mPositionX + 100;

		mArmsId = mCircleCursor;
		mArms[mArmsId]->StartSummon();

		AnimationController::getInstance().Create(mGraphSummonEffect1, 1, pX, 500, 400, 400, 1.2, 0, 4, 1, 40, 0, true, false);
		AnimationController::getInstance().Create(mGraphSummonEffect2, 2, pX, 500, 400, 400, 1.2, 0, 4, 1, 40, 0, true, false);

		PlaySoundMem(mSoundSummon, DX_PLAYTYPE_BACK);
	}
}

/*召喚する*/
void Player::DoSummon() {
	
}

/*攻撃を始める*/
void Player::StartAtack() {
	//A攻撃
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		!mController.getDown() && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_A].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
	//A下攻撃
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		mController.getDown() && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_2A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2A].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
	//B攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		!mController.getDown() && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_B].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_B].PlayVoice();
	}
	//B下攻撃
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_2B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2B].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
}

/*攻撃*/
void Player::DoAtack() {
	int sId = 0;

	//A攻撃
	if (mState == Parameter::S_PLAYER_ATACK_A) {

		//SEがある場合再生
		sId = mPlayerAtack[Parameter::P_ATACK_A].getFrameData(mPlayerAtack[Parameter::P_ATACK_A].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_A].IncreaseCounter();

		//攻撃終了時の処理
		if (mPlayerAtack[Parameter::P_ATACK_A].CheckAtackEnd()) {
			mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//A下攻撃
	if (mState == Parameter::S_PLAYER_ATACK_2A) {

		//SEがある場合再生
		sId = mPlayerAtack[Parameter::P_ATACK_2A].getFrameData(mPlayerAtack[Parameter::P_ATACK_2A].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_2A].IncreaseCounter();

		//攻撃終了時の処理
		if (mPlayerAtack[Parameter::P_ATACK_2A].CheckAtackEnd()) {
			//下が押されていたらしゃがんだまま
			if(mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//B攻撃
	if (mState == Parameter::S_PLAYER_ATACK_B) {

		//SEがある場合再生
		sId = mPlayerAtack[Parameter::P_ATACK_B].getFrameData(mPlayerAtack[Parameter::P_ATACK_B].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_B].IncreaseCounter();

		//攻撃終了時の処理
		if (mPlayerAtack[Parameter::P_ATACK_B].CheckAtackEnd()) {
			mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//B下攻撃
	if (mState == Parameter::S_PLAYER_ATACK_2B) {

		//SEがある場合再生
		sId = mPlayerAtack[Parameter::P_ATACK_2B].getFrameData(mPlayerAtack[Parameter::P_ATACK_2B].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_2B].IncreaseCounter();

		//攻撃終了時の処理
		if (mPlayerAtack[Parameter::P_ATACK_2B].CheckAtackEnd()) {
			//下が押されていたらしゃがんだまま
			if (mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//3B攻撃
	if (mState == Parameter::S_PLAYER_ATACK_3B) {

		//SEがある場合再生
		sId = mPlayerAtack[Parameter::P_ATACK_3B].getFrameData(mPlayerAtack[Parameter::P_ATACK_3B].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_3B].IncreaseCounter();

		//攻撃終了時の処理
		if (mPlayerAtack[Parameter::P_ATACK_3B].CheckAtackEnd()) {
			//下が押されていたらしゃがんだまま
			if (mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//6B攻撃
	if (mState == Parameter::S_PLAYER_ATACK_6B) {

		//SEがある場合再生
		sId = mPlayerAtack[Parameter::P_ATACK_6B].getFrameData(mPlayerAtack[Parameter::P_ATACK_6B].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_6B].IncreaseCounter();

		//攻撃終了時の処理
		if (mPlayerAtack[Parameter::P_ATACK_6B].CheckAtackEnd()) {
			//下が押されていたらしゃがんだまま
			if (mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//各攻撃独自の処理
	ProcessAtack();
}

/*ダッシュを始める*/
void Player::StartDash() {
	mState = Parameter::S_PLAYER_DASH;
	mCounter = 15;
}

/*ダッシュ*/
void Player::DoDash() {
	mAcceleX = mRight ? 20 : -20;
	mAcceleY = 0;
}

/*ステップを始める*/
void Player::StartStep() {
	mState = Parameter::S_PLAYER_STEP;
	mCounter = 15;
}

/*ステップ*/
void Player::DoStep() {
	mAcceleX = mRight ? -20 : 20;
	mAcceleY = 0;
}

/*ダメージ中の処理*/
void Player::DoDamaged() {
	mDamageCounter++;
	
	if (mAcceleX > 0)mAcceleX--;
	if (mAcceleX < 0)mAcceleX++;
}

/*カウンターを減らし0のとき次状態へ*/
void Player::DecrementCounter(Player &another) {
	if (mCounter > 0) {
		mCounter--;

		if (mCounter == 0) {
			//ダッシュ→通常
			if (mState == Parameter::S_PLAYER_DASH)mState = Parameter::S_PLAYER_NORMAL;

			//ステップ→通常
			if (mState == Parameter::S_PLAYER_STEP)mState = Parameter::S_PLAYER_NORMAL;

			//ダメージ→通常
			if (isDamageState() && mState != Parameter::S_PLAYER_DAMAGE_AIR2) {
				mState = Parameter::S_PLAYER_NORMAL;
				another.setChain(0);
			}

			//ダウン→通常
			if (mState == Parameter::S_PLAYER_DOWN) {
				another.setChain(0);
				mState = Parameter::S_PLAYER_NORMAL;
			}
			//立ちガード
			if (mState == Parameter::S_PLAYER_GUARD) {
				mState = Parameter::S_PLAYER_NORMAL;
				mAcceleX = 0;
			}
			//しゃがみガード
			if (mState == Parameter::S_PLAYER_GUARD_S) {
				mState = Parameter::S_PLAYER_SQUAT;
				mAcceleX = 0;
			}
		}
	}
}

void Player::DecrementHitStop() {
	if (mHitStop > 0)mHitStop--;
}

/*振り向き*/
void Player::ChangeDirection(Player& another) {
	if (mRight) {
		if (mGround && mPositionX > another.mPositionX
			&& mState == Parameter::S_PLAYER_NORMAL)mRight = false;
	}
	else {
		if (mGround && mPositionX < another.mPositionX
			&& mState == Parameter::S_PLAYER_NORMAL)mRight = true;
	}
	mArms[mArmsId]->setRight(mRight);
}

/*攻撃を食らう*/
void Player::EatAtack(bool right,BoxData boxdata) {
	mEatAtackData = boxdata;
	mEatAtackFlag = true;
	mEatAtackRight = right;
}

/*ダメージを食らう*/
void Player::EatDamage(Player& another) {
	int effectY;
	/*
	atackType  上・下・中段(0,1,2)
	guardType  通常・ガー不・空ガー不(0,1,2)
	*/
	
	//このフレーム中ダメージを食らった
	if (mEatAtackFlag) {

		//上段ガード成功
		if (mGround && mEatAtackData.getAtackType() == 0 &&
			(mController.getRight() && !mRight || mController.getLeft() && mRight)) {
		
			if (mController.getDown())mState = Parameter::S_PLAYER_GUARD_S;
			else mState = Parameter::S_PLAYER_GUARD;
			mCounter = 10;

			PlaySoundMem(mSoundGuard, DX_PLAYTYPE_BACK);
		}

		//下段ガード成功
		else if (mGround && mEatAtackData.getAtackType() == 1 && mController.getDown() &&
			(mController.getRight() && !mRight || mController.getLeft() && mRight)) {

			mState = Parameter::S_PLAYER_GUARD_S;
			mCounter = 10;

			PlaySoundMem(mSoundGuard, DX_PLAYTYPE_BACK);
		}

		//中段ガード成功
		else if (mGround && mEatAtackData.getAtackType() == 2 && !mController.getDown() &&
			(mController.getRight() && !mRight || mController.getLeft() && mRight)) {

			mState = Parameter::S_PLAYER_GUARD;
			mCounter = 10;

			PlaySoundMem(mSoundGuard, DX_PLAYTYPE_BACK);
		}

		//ガード失敗
		else {

			if (mGround) {
				if (mEatAtackData.getAtackType() == 1)mState = Parameter::S_PLAYER_DAMAGE_D;
				else mState = Parameter::S_PLAYER_DAMAGE_U;

				mCounter = mEatAtackData.getHitStop();
				mHP -= mEatAtackData.getPower();
				another.mEXP += mEatAtackData.getEXGain();
				if (another.mEXP > 100)another.mEXP = 100;
				mDamageCounter = 0;

				mAcceleX = mEatAtackRight? mEatAtackData.getVectorX() : -mEatAtackData.getVectorX();

				mAcceleY = mEatAtackData.getVectorY();

				if (mAcceleY > 0) {
					mState = Parameter::S_PLAYER_DAMAGE_AIR;
					mGround = false;
				}
			}
			else {
				mState = Parameter::S_PLAYER_DAMAGE_AIR;

				mCounter = mEatAtackData.getHitStop();
				mHP -= mEatAtackData.getPower();
				mDamageCounter = 0;

				mAcceleX = mEatAtackRight ? mEatAtackData.getAirVectorX() : -mEatAtackData.getAirVectorX();

				mAcceleY = mEatAtackData.getAirVectorY();
			}

			if (mEatAtackData.getForceDown())mState = Parameter::S_PLAYER_DAMAGE_AIR2;

			//チェーンを増加させる
			another.IncleaseChain();

			PlaySoundMem(mSoundDamage, DX_PLAYTYPE_BACK);

			if (mEatAtackData.getEffectType() == 0) {
				if (mEatAtackData.getAtackType() == 0)effectY = mPositionY;
				else effectY = mPositionY + 80;
				AnimationController::getInstance().Create(mGraphDamage, 1, mPositionX, effectY, 600, 400, 1.2, GetRand(359), 4, 2, 48, 0, true, true);
			}
			if (mEatAtackData.getEffectType() == 1) {
				if (mEatAtackData.getAtackType() == 0)effectY = mPositionY;
				else effectY = mPositionY + 80;
				AnimationController::getInstance().Create(mGraphDamage, 1, mPositionX, effectY, 600, 400, 2, GetRand(359), 4, 2, 48, 0, true, true);
			}
			if (mEatAtackData.getEffectType() == 2) {
				if (mEatAtackData.getAtackType() == 0)effectY = mPositionY - 150;
				else effectY = mPositionY - 250;
				SSEffectController::getInstance().Play("mye1/mye1", mPositionX, effectY, 0.9f, 1.0f, 0.6f, GetRand(359), 200);
			}

			mHitStop = 0;
			another.mHitStop = 0;
		}
	}

	mEatAtackFlag = false;
}

/*魔具を動かす*/
void Player::MoveArms() {
	mArms[mArmsId]->ReceivePlayer(this, mController);
	mArms[mArmsId]->Move();
	mArms[mArmsId]->UpdateArmsAnimation();
}

/*魔具を描画する*/
void Player::DrawArms() {
	mArms[mArmsId]->Draw();
}

/*魔具を自身の後ろに描画する*/
void Player::DrawArmsBack() {
	mArms[mArmsId]->DrawBack();
}


/*契約陣のカーソル移動*/
void Player::MoveCircleCursor() {
	if (mController.getUp() && !mController.getRight() && !mController.getLeft())mCircleCursor = 0;
	if (mController.getUp() && mController.getRight())mCircleCursor = 1;
	if (!mController.getUp() && mController.getRight() && !mController.getDown())mCircleCursor = 2;
	if (mController.getRight() && mController.getDown())mCircleCursor = 3;
	if (!mController.getRight() && mController.getDown() && !mController.getLeft())mCircleCursor = 4;
	if (mController.getDown() && mController.getLeft())mCircleCursor = 5;
	if (!mController.getDown() && mController.getLeft() && !mController.getUp())mCircleCursor = 6;
	if (mController.getLeft() && mController.getUp())mCircleCursor = 7;

	if (!mController.getUp() && !mController.getRight() && !mController.getDown() && !mController.getLeft())mCircleCursor = 0;
}

/*プレイヤー同士の当たり判定*/
void Player::CheckPlayersHit(Player& another) {
	Box box1, box2;
	int centerX;

	//→　←
	if (mRight && !another.mRight) {
		//P1のボックス
		box1.x = mPositionX + mHitBox[mState].getPositionX();
		box1.y = mPositionY + mHitBox[mState].getPositionY();
		box1.width = mHitBox[mState].getWidth();
		box1.height = mHitBox[mState].getHeight();

		//P2のボックス
		box2.x = another.mPositionX -
			another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth();
		box2.y = another.mPositionY + another.mHitBox[another.mState].getPositionY();
		box2.width = another.mHitBox[another.mState].getWidth();
		box2.height = mHitBox[another.mState].getHeight();

		if (Utility::CheckBoxHit(box1, box2)) {

			//両方が地面にいる
			if (mGround && another.mGround) {

				//1Pが2Pに近づいている
				if (mAcceleX > 0 && another.mAcceleX == 0) {
					another.mPositionDX = mPositionX + mHitBox[mState].getPositionX() + mHitBox[mState].getWidth()
						+ another.mHitBox[another.mState].getPositionX() + another.mHitBox[another.mState].getWidth();
					another.mPositionX = (int)another.mPositionDX;
				}
				//2Pが1Pに近づいてくる
				else if (mAcceleX == 0 && another.mAcceleX < 0) {
					mPositionDX = (another.mPositionX - another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth())
						- mHitBox[mState].getPositionX() - mHitBox[mState].getWidth();
					mPositionX = (int)mPositionDX;
				}
				//両方が近付く
				else {
					centerX = (mPositionX + another.mPositionX) / 2;

					mPositionDX = centerX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth();
					mPositionX = (int)mPositionDX;
					another.mPositionDX = centerX + (another.mHitBox[another.mState].getWidth() + another.mHitBox[another.mState].getPositionX());
					another.mPositionX = (int)another.mPositionDX;
				}
				//壁に埋まる場合の処理
				//1Pが壁に埋まる
				if (mPositionX + mHitBox[mState].getPositionX() < 0) {
					mPositionDX = -mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
					another.mPositionDX = mHitBox[mState].getWidth()
						+ (another.mHitBox[another.mState].getWidth() + another.mHitBox[another.mState].getPositionX());
					another.mPositionX = (int)another.mPositionDX;
				}
				//2Pが壁に埋まる
				if (another.mPositionX - another.mHitBox[another.mState].getPositionX() > Parameter::FIELD_WIDTH) {
					another.mPositionDX = Parameter::FIELD_WIDTH + another.mHitBox[another.mState].getPositionX();
					another.mPositionX = (int)another.mPositionDX;
					mPositionDX = Parameter::FIELD_WIDTH
						- another.mHitBox[another.mState].getWidth() - mHitBox[mState].getWidth() - mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
				}
			}


			//2Pだけが地面にいる
			if (!mGround && another.mGround) {
			
				if (mAcceleY < 0) {
					mAcceleX = 0;
					if (mPositionX >= another.mPositionX)mPositionDX += 5;
					else mPositionDX -= 5;
					mPositionX = (int)mPositionDX;
				}

				//壁に埋まる場合の処理
				//1Pが壁に埋まる
				if (mPositionX + mHitBox[mState].getPositionX() < 0) {
					mPositionDX = -mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
					another.mPositionDX = mHitBox[mState].getWidth()
						+ (another.mHitBox[another.mState].getWidth() + another.mHitBox[another.mState].getPositionX());
					another.mPositionX = (int)another.mPositionDX;
				}
				//2Pが壁に埋まる
				if (another.mPositionX - another.mHitBox[another.mState].getPositionX() > Parameter::FIELD_WIDTH) {
					another.mPositionDX = Parameter::FIELD_WIDTH + another.mHitBox[another.mState].getPositionX();
					another.mPositionX = (int)another.mPositionDX;
					mPositionDX = Parameter::FIELD_WIDTH
						- another.mHitBox[another.mState].getWidth() - mHitBox[mState].getWidth() - mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
				}
			}
		}
	}

	//←　→
	if (!mRight && another.mRight) {
		//P1のボックス
		box1.x = another.mPositionX + another.mHitBox[mState].getPositionX();
		box1.y = another.mPositionY + another.mHitBox[another.mState].getPositionY();
		box1.width = another.mHitBox[mState].getWidth();
		box1.height = another.mHitBox[mState].getHeight();

		//P2のボックス
		box2.x = mPositionX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth();
		box2.y = mPositionY + mHitBox[mState].getPositionY();
		box2.width = mHitBox[mState].getWidth();
		box2.height = mHitBox[mState].getHeight();

		if (Utility::CheckBoxHit(box1, box2)) {

			if (mGround && another.mGround) {
				//1Pが2Pに近づいている
				if (another.mAcceleX > 0 && mAcceleX == 0) {
					mPositionDX = another.mPositionX + another.mHitBox[another.mState].getPositionX() + another.mHitBox[another.mState].getWidth()
						+ mHitBox[mState].getPositionX() + mHitBox[mState].getWidth();
					mPositionX = (int)mPositionDX;
				}
				//2Pが1Pに近づいてくる
				else if (another.mAcceleX == 0 && mAcceleX < 0) {
					another.mPositionDX = (mPositionX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth())
						- another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth();
					another.mPositionX = (int)another.mPositionDX;
				}
				//両方が近付く
				else {
					centerX = (mPositionX + another.mPositionX) / 2;

					another.mPositionDX = centerX - another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth();
					another.mPositionX = (int)another.mPositionDX;
					mPositionDX = centerX + (mHitBox[mState].getWidth() + mHitBox[mState].getPositionX());
					mPositionX = (int)mPositionDX;
				}
				//壁に埋まる場合の処理
				//１Pが壁に埋まる
				if (another.mPositionX + mHitBox[another.mState].getPositionX() < 0) {
					another.mPositionDX = -another.mHitBox[another.mState].getPositionX();
					another.mPositionX = (int)another.mPositionDX;
					mPositionDX = another.mHitBox[another.mState].getWidth()
						+ (mHitBox[mState].getWidth() + mHitBox[mState].getPositionX());
					mPositionX = (int)mPositionDX;
				}
				//２Pが壁に埋まる
				if (mPositionX - mHitBox[mState].getPositionX() > Parameter::FIELD_WIDTH) {
					mPositionDX = Parameter::FIELD_WIDTH + mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
					another.mPositionDX = Parameter::FIELD_WIDTH
						- mHitBox[mState].getWidth() - another.mHitBox[another.mState].getWidth() - another.mHitBox[another.mState].getPositionX();
					another.mPositionX = (int)another.mPositionDX;
				}
			}
		}
	}


}

/*壁・床とのヒットチェック*/
void Player::CheckWallHit() {

	//右向きのとき
	if (mRight) {
		//左側
		if (mPositionX + mHitBox[mState].getPositionX() < 0) {
			mPositionDX = -mHitBox[mState].getPositionX();
		}
		//右側
		if (mPositionX + mHitBox[mState].getPositionX() + mHitBox[mState].getWidth() > Parameter::FIELD_WIDTH) {
			mPositionDX = Parameter::FIELD_WIDTH - mHitBox[mState].getWidth() - mHitBox[mState].getPositionX();
		}
	}

	//左向きのとき
	else {
		//左側
		if (mPositionX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth() < 0) {
			mPositionDX = mHitBox[mState].getPositionX() + mHitBox[mState].getWidth();
		}
		//右側
		if (mPositionX - mHitBox[mState].getPositionX() > Parameter::FIELD_WIDTH) {
			mPositionDX = Parameter::FIELD_WIDTH + mHitBox[mState].getPositionX();
		}
	}

	//床
	if (mPositionDY > Parameter::GROUND_LINE - mHeight) {
		mPositionDY = Parameter::GROUND_LINE - mHeight;
		mAcceleY = 0;
		mAcceleX = 0;
		mGround = true;
		if (mState == Parameter::S_PLAYER_DAMAGE_AIR2) {
			mState = Parameter::S_PLAYER_DOWN;
			mCounter = 40;
		}
	}

	mPositionX = (int)mPositionDX;
	mPositionY = (int)mPositionDY;
}

/*仮想化壁との接触判定*/
void Player::CheckVirtualWallHit(Player &another) {
	
	//1Pが左
	if (mPositionX < another.mPositionX) {
		if (mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) < - mHitBox[mState].getPositionX()
			&& another.mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) > Parameter::WINDOW_WIDTH + another.mHitBox[another.mState].getPositionX()) 
		{
			//1Pが動いている
			if (mAcceleX != 0 && another.mAcceleX == 0) {
				mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) - mHitBox[mState].getPositionX();
			}
			//2Pが動いている
			else if(mAcceleX == 0 && another.mAcceleX != 0) {
				another.mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) + Parameter::WINDOW_WIDTH + another.mHitBox[another.mState].getPositionX()+1;
			}

			else {
				mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) - mHitBox[mState].getPositionX();
				another.mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) + Parameter::WINDOW_WIDTH + another.mHitBox[another.mState].getPositionX();
			}

			mPositionX = (int)mPositionDX;
			another.mPositionX = (int)another.mPositionDX;

			Camera::getInstance().setCenterX((mPositionX + another.mPositionX) / 2);
		}
	}
	//2Pが左
	else {
		if (another.mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) < -another.mHitBox[another.mState].getPositionX()
			&& mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) > Parameter::WINDOW_WIDTH + mHitBox[mState].getPositionX())
		{
			//2Pが動いている
			if (another.mAcceleX != 0 && mAcceleX == 0) {
				another.mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) - another.mHitBox[another.mState].getPositionX();
			}
			//1Pが動いている
			else if (another.mAcceleX == 0 && mAcceleX != 0) {
				mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) + Parameter::WINDOW_WIDTH + mHitBox[mState].getPositionX() + 1;
			}

			else {
				another.mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) - another.mHitBox[another.mState].getPositionX();
				mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) + Parameter::WINDOW_WIDTH + mHitBox[mState].getPositionX();
			}

			mPositionX = (int)mPositionDX;
			another.mPositionX = (int)another.mPositionDX;

			Camera::getInstance().setCenterX((mPositionX + another.mPositionX) / 2);
		}
	}
}

/*プレイヤーの攻撃の当たり判定*/
void Player::CheckPlayersAtackHit(Player& another) {
	int atackId, counter;
	Box box1, box2;
	bool atackHit = false;

	atackId = mState - 18;
	counter = mPlayerAtack[atackId].getCounter();

	if (isAtackState()) {
		for (int i = 0; i < 20 && !atackHit; i++) {
			//該当フレームに攻撃用ボックスが存在するとき
			if (mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				if (!mPlayerAtack[atackId].getAtackHit()) {

					//相手のヒットボックスと比較
					for (int j = 0; j < 10 && !atackHit; j++) {

						//相手のダメージボックスが存在するとき
						if (another.mDamageBox[another.mState][j].getExist()) {

							//自身が右向き
							if (mRight) {
								box1.x = mPositionX + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX();
							}
							//自身が左向き
							else
								box1.x = mPositionX - mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
								- mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth();

							box1.y = mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY();
							box1.width = mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth();
							box1.height = mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight();

							//相手が右向き
							if (another.mRight) {
								box2.x = another.mPositionX + another.mDamageBox[another.mState][j].getPositionX();
							}
							//相手が左向き
							else {
								box2.x = another.mPositionX
									- another.mDamageBox[another.mState][j].getPositionX() - another.mDamageBox[another.mState][j].getWidth();
							}
							box2.y = another.mPositionY + another.mDamageBox[another.mState][j].getPositionY();
							box2.width = another.mDamageBox[another.mState][j].getWidth();
							box2.height = another.mDamageBox[another.mState][j].getHeight();

							//攻撃が相手にヒット
							if (Utility::CheckBoxHit(box1, box2)) {
							
								//ボックスIDを取得
								int boxId = mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getBoxId();
								
								//相手に攻撃を与える
								another.EatAtack(mRight,mPlayerAtack[atackId].getFrameData(counter).getAtackBoxData(boxId));
								atackHit = true;

								//攻撃が既に当たったフラグをたてる
								if(!mPlayerAtack[atackId].getFrameData(counter).getAtackBoxData(boxId).getAllowMultHit())mPlayerAtack[atackId].setAtackHit(true);

								break;
							}
						}
					}
				}
			}
		}
	}
}

/*グラフィックの描画*/
void Player::Draw() {
	DrawShadow();
	mSprite->draw();
	//if(mPlayerId == 1)DrawFormatString(0, 0, Parameter::COLOR_RED, "%2d %2d", mState,mCounter);
}

/*影を描画*/
void Player::DrawShadow() {
	DrawGraph(mPositionX - 60 - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), Parameter::GROUND_LINE - 70, mGraphShadow, true);
}

/*ヒットボックスの描画*/
void Player::DrawHitBox() {

	//プレイヤーのヒットボックス
	if (!isAtackState()) {

		//透過設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

		//ボックスが存在するとき
		if (mHitBox[mState].getExist()) {
			//プレイヤーが右向きのとき
			if (mRight) {
				DrawBox(
					mPositionX + mHitBox[mState].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mHitBox[mState].getPositionY(),
					mPositionX + mHitBox[mState].getPositionX() + mHitBox[mState].getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mHitBox[mState].getPositionY() + mHitBox[mState].getHeight(),
					Parameter::COLOR_GREEN, true);
			}
			//プレイヤーが左向きのとき
			else {
				DrawBox(
					mPositionX - mHitBox[mState].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mHitBox[mState].getPositionY(),
					mPositionX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mHitBox[mState].getPositionY() + mHitBox[mState].getHeight(),
					Parameter::COLOR_GREEN, true);
			}
		}

		//透過設定をもどす
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

/*ダメージボックスの描画*/
void Player::DrawDamageBox() {

	//プレイヤーのヒットボックス
	if (!isAtackState()) {

		//透過設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

		//プレイヤーのダメージボックス

		for (int i = 0; i < 10; i++) {
			//ボックスが存在するとき
			if (mDamageBox[mState][i].getExist()) {
				//プレイヤーが右向きのとき
				if (mRight) {
					DrawBox(
						mPositionX + mDamageBox[mState][i].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
						mPositionY + mDamageBox[mState][i].getPositionY(),
						mPositionX + mDamageBox[mState][i].getPositionX() + mDamageBox[mState][i].getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
						mPositionY + mDamageBox[mState][i].getPositionY() + mDamageBox[mState][i].getHeight(),
						Parameter::COLOR_BLUE, true);
				}
				//プレイヤーが左向きのとき
				else {
					DrawBox(
						mPositionX - mDamageBox[mState][i].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
						mPositionY + mDamageBox[mState][i].getPositionY(),
						mPositionX - mDamageBox[mState][i].getPositionX() - mDamageBox[mState][i].getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
						mPositionY + mDamageBox[mState][i].getPositionY() + mDamageBox[mState][i].getHeight(),
						Parameter::COLOR_BLUE, true);
				}
			}
		}

		//透過設定をもどす
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

/*攻撃ボックスの描画*/
void Player::DrawAtackBox() {
	int atackId, counter;

	atackId = mState - 18;
	counter = mPlayerAtack[atackId].getCounter();

	//透過設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

	//右向きのとき
	if (mRight) {
		for (int i = 0; i < 20; i++) {
			if (mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY(),
					mPositionX + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
					+ mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY()
					+ mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight(),
					Parameter::COLOR_RED, true);
			}
			else break;
		}
	}

	//左向きのとき
	else {
		for (int i = 0; i < 20; i++) {
			if (mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX - mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY(),
					mPositionX - mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
					- mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY()
					+ mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight(),
					Parameter::COLOR_RED, true);
			}
			else break;
		}
	}

	//透過設定をもどす
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/*加速度の影響を受ける状態かどうか*/
bool Player::isAcceledState() {
	if (mState == Parameter::S_PLAYER_DASH
		|| mState == Parameter::S_PLAYER_STEP
		|| mState == Parameter::S_PLAYER_DAMAGE_U
		|| mState == Parameter::S_PLAYER_DAMAGE_D
		|| mState == Parameter::S_PLAYER_DAMAGE_S
		|| mState == Parameter::S_PLAYER_DAMAGE_AIR
		|| mState == Parameter::S_PLAYER_DAMAGE_AIR2)
	{
		return true;
	}
	else return false;
}

/*攻撃状態かどうか*/
bool Player::isAtackState() {
	if (mState == Parameter::S_PLAYER_ATACK_A
		|| mState == Parameter::S_PLAYER_ATACK_8A
		|| mState == Parameter::S_PLAYER_ATACK_2A
		|| mState == Parameter::S_PLAYER_ATACK_JA
		|| mState == Parameter::S_PLAYER_ATACK_B
		|| mState == Parameter::S_PLAYER_ATACK_8B
		|| mState == Parameter::S_PLAYER_ATACK_2B
		|| mState == Parameter::S_PLAYER_ATACK_3B
		|| mState == Parameter::S_PLAYER_ATACK_6B
		|| mState == Parameter::S_PLAYER_ATACK_JB)
	{
		return true;
	}
	else return false;
}

/*ダメージ状態かどうか*/
bool Player::isDamageState() {
	if (mState == Parameter::S_PLAYER_DAMAGE_U
		|| mState == Parameter::S_PLAYER_DAMAGE_D
		|| mState == Parameter::S_PLAYER_DAMAGE_S
		|| mState == Parameter::S_PLAYER_DAMAGE_AIR
		|| mState == Parameter::S_PLAYER_DAMAGE_AIR2)
	{
		return true;
	}
	else return false;
}

/*魔具攻撃可能かどうか*/
bool Player::isCanArmsAtackState() {
	if (
		mState == Parameter::S_ARMS_NORMAL ||
		mState == Parameter::S_PLAYER_SQUAT ||
		isAtackState()
		)
	{
		return true;
	}
	return false;
}

/*キャンセル可能なタイミングかどうか*/
bool Player::isCanCancelTiming(int atackId) {
	int counter;

	if (mState == Parameter::S_ARMS_NORMAL || mState == Parameter::S_PLAYER_SQUAT)return true;

	if (isAtackState()) {
		counter = mPlayerAtack[mState - 18].getCounter();

		if (mPlayerAtack[mState - 18].getFrameData(counter).getAllowCancel()) {
			if (mPlayerAtack[mState - 18].getAllowCancel(atackId)) {
				return true;
			}
		}
	}
	return false;
}