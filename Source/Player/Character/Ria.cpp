#include <fstream>
#include "../../Application.h"
#include "../../SSPlayer/SS5Player.h"
#include "../../Utility.h"
#include "../../Atack/FrameData.h"
#include "Ria.h"

Profile Ria::getProfile() {
	Profile p;
	p.name = "リア = アーヴェルシュタイン";
	p.eName = "Ria Arverstein";
	p.pass = "ria";

	p.size = 0.39f;
	p.speed = 1.0f;
	p.distX = -10;
	p.distY = 0;

	p.cAtack = 2;
	p.lAtack = 5;
	p.aut = 3;
	p.pAtack = 5;
	p.sAtack = 2;
	return p;
}

/*サウンドのロード*/
void Ria::LoadSound() {
	
}

/*ボイスのロード*/
void Ria::LoadVoice() {

}

/*プレイヤーデータをロード*/
void Ria::LoadData() {
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
	ifs.open("Data/character/ria/DamageBoxData.txt");

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
	ifs.open("Data/character/ria/HitBoxData.txt");

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

/*攻撃データのロード*/
void Ria::LoadAtack() {
	ifstream ifs;
	int n;
	int boxId;
	int frameCounter;
	int boxCounter = 0;
	string tmp;

	FrameData frameData;
	BoxData boxData;
	HitBox hitBox;

	for (int a = 0; a < 4; a++) {

		if (a == 0)mPlayerAtack[Parameter::P_ATACK_A].ClearFrameData();
		if (a == 1)mPlayerAtack[Parameter::P_ATACK_B].ClearFrameData();
		if (a == 2)mPlayerAtack[Parameter::P_ATACK_2A].ClearFrameData();
		if (a == 3)mPlayerAtack[Parameter::P_ATACK_2B].ClearFrameData();

		hitBox.setExist(false);
		for (int i = 0; i < 20; i++) {
			frameData.setAtackBox(i, hitBox);
		}

		ifs.clear();

		if (a == 0)ifs.open("Data/character/ria/a.txt");
		if (a == 1)ifs.open("Data/character/ria/b.txt");
		if (a == 2)ifs.open("Data/character/ria/ad.txt");
		if (a == 3)ifs.open("Data/character/ria/bd.txt");

		if (ifs) {
			//ボックスデータの読み込み
			for (int i = 0; i < 5; i++) {
				ifs >> tmp;
				boxData.setAtackType(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setEffectType(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setSEType(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setGuardType(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setHitStop(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setDecHitStop(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setBindTime(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setContinueAtackAfterOffset(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setForceDown(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setFloorBound(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setWallBound(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setShakeWindow(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setVectorX(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setVectorY(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setAirVectorX(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setAirVectorY(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setPower(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setEXGain(Utility::StringToInt(tmp));

				frameData.setAtackBoxData(i, boxData);
			}

			while (!ifs.eof()) {
				ifs >> n;

				//フレーム切り替え
				if (n == 0) {
					if (a == 0)mPlayerAtack[Parameter::P_ATACK_A].PushFrameData(frameData);
					if (a == 1)mPlayerAtack[Parameter::P_ATACK_B].PushFrameData(frameData);
					if (a == 2)mPlayerAtack[Parameter::P_ATACK_2A].PushFrameData(frameData);
					if (a == 3)mPlayerAtack[Parameter::P_ATACK_2B].PushFrameData(frameData);

					boxCounter = 0;

					hitBox.setExist(false);
					for (int i = 0; i < 20; i++) {
						frameData.setAtackBox(i, hitBox);
					}

					//デフォルトではサウンドはなし
					frameData.setSoundId(0);
				}

				//ヒットボックス
				if (n == 50) {
					ifs >> boxId;

					hitBox.setBoxId(boxId);
					hitBox.setExist(true);
					ifs >> tmp;
					hitBox.setPositionX(Utility::StringToInt(tmp));
					ifs >> tmp;
					hitBox.setPositionY(Utility::StringToInt(tmp));
					ifs >> tmp;
					hitBox.setWidth(Utility::StringToInt(tmp));
					ifs >> tmp;
					hitBox.setHeight(Utility::StringToInt(tmp));

					frameData.setAtackBox(boxCounter, hitBox);

					boxCounter++;
				}

				//サウンドID
				if (n == 30) {
					ifs >> tmp;
					frameData.setSoundId(Utility::StringToInt(tmp));
				}


			}

		}
		ifs.close();
	}
}

/*アニメーションの更新*/
void Ria::UpdateAnimation() {

	//振り向き
	if (mRight)mSprite->setScale(0.39, 0.39);
	else mSprite->setScale(-0.39, 0.39);

	//通常時（待機・前進・後退・ジャンプ）
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//プレイヤーが地面にいる
		if (mGround) {

			//プレイヤーが静止している
			if (mAcceleX == 0) {
				if (mSprite->getPlayAnimeName() != "idle") {
					mSprite->play("ria/idle");
				}
			}
			//プレイヤーが右に進んでいる
			else if (mAcceleX > 0) {
				//プレイヤーが右向き
				if (mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play("ria/walk");
					}
				}
				//プレイヤーが左向き
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play("ria/back");
				}
			}
			//プレイヤーが左に進んでいる
			else {
				//プレイヤーが左向き
				if (!mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play("ria/walk");
					}
				}
				//プレイヤーが右向き
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play("ria/back");
				}
			}
		}
		//プレイヤーが空中にいる
		//else {
		//	if (mSprite->getPlayAnimeName() != "jump") {
		//		mSprite->play("ria/jump");
		//	}
		//}

	}
	//ダッシュ
	else if (mState == Parameter::S_PLAYER_DASH) {
		if (mSprite->getPlayAnimeName() != "dash") {
			//mSprite->play("ria/dash");
		}
	}
	//バックステップ
	else if (mState == Parameter::S_PLAYER_STEP) {
		if (mSprite->getPlayAnimeName() != "backstep") {
			//mSprite->play("ria/backstep");
		}
	}
	//プレイヤーがしゃがんでいる
	else if (mState == Parameter::S_PLAYER_SQUAT) {
		if (mSprite->getPlayAnimeName() != "squat") {
			//mSprite->play("ria/squat");
		}
	}
	//上段ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_U && mDamageCounter == 1) {
		mSprite->play("ria/damage_u");
		mSprite->setStep(0.9f);

	}
	//下段ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_D && mDamageCounter == 1) {
		mSprite->play("ria/damage_d");
		mSprite->setStep(0.9f);
	}
	//しゃがみダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_S && mDamageCounter == 1) {
		mSprite->play("ria/damage_squat");
	}
	//A攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_A &&
		mPlayerAtack[Parameter::P_ATACK_A].getCounter() == 1)
	{
		mSprite->play("ria/a");
	}
	//A下攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_2A &&
		mPlayerAtack[Parameter::P_ATACK_2A].getCounter() == 1)
	{
		mSprite->play("ria/2a");
	}
	//B攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_B &&
		mPlayerAtack[Parameter::P_ATACK_B].getCounter() == 1)
	{
		mSprite->play("ria/b");
	}
	//B下攻撃
	else if (mState == Parameter::S_PLAYER_ATACK_2B &&
		mPlayerAtack[Parameter::P_ATACK_2B].getCounter() == 1)
	{
		mSprite->play("ria/2b");
	}

	//表示位置の更新
	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), Parameter::GROUND_LINE - mPositionY);
	//プレイヤーの更新、引数は前回の更新処理から経過した時間
	mSprite->update((float)30 / 1000);
}


//オーバーロード

