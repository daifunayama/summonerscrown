#include <fstream>
#include "../../Application.h"
#include "../../SSPlayer/SS5Player.h"
#include "../../Utility.h"
#include "../../Atack/FrameData.h"
#include "Kare-meshi.h"

Profile KareMeshi::getProfile() {
	Profile p;
	p.name = "カレーメシ";
	p.eName = "Kare-meshi";
	p.cAtack = 3;
	p.lAtack = 5;
	p.aut = 2;
	p.pAtack = 3;
	p.sAtack = 3;
	return p;
}

/*グラフィックのロード*/
void KareMeshi::LoadGraphic() {
	//プレイヤーの作成
	mSprite = ss::Player::create();

	//プレイヤーにリソースを割り当て
	mSprite->setData("kare-messhi");// ssbpファイル名

	mSprite->play("kare-meshi/idle");// アニメーション名を指定

	//表示位置を設定
	mSprite->setPosition(400, 300);
	//スケール設定
	mSprite->setScale(0.25f, 0.25f);

	mGraphShadow = LoadGraph("Data/graphic/game/shadow.png");
	mGraphDamage = LoadGraph("Data/graphic/animation/slash3.png");

	mGraphSummonEffect1 = LoadGraph("Data/graphic/animation/summon_effect1.png");
	mGraphSummonEffect2 = LoadGraph("Data/graphic/animation/summon_effect2.png");
}

/*サウンドのロード*/
void KareMeshi::LoadSound() {

}

/*ボイスのロード*/
void KareMeshi::LoadVoice() {

}

/*プレイヤーデータをロード*/
void KareMeshi::LoadData() {
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
	ifs.open("Data/character/kare-meshi/DamageBoxData.txt");

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
	ifs.open("Data/character/kare-meshi/HitBoxData.txt");

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
void KareMeshi::LoadAtack() {
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

		if (a == 0)ifs.open("Data/character/kare-meshi/a.txt");
		if (a == 1)ifs.open("Data/character/kare-meshi/b.txt");
		if (a == 2)ifs.open("Data/character/kare-meshi/ad.txt");
		if (a == 3)ifs.open("Data/character/kare-meshi/bd.txt");

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
void KareMeshi::UpdateAnimation() {

	//振り向き
	if (mRight)mSprite->setScale(0.36, 0.36);
	else mSprite->setScale(-0.36, 0.36);

	//通常時（待機・前進・後退・ジャンプ）
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//プレイヤーが地面にいる
		if (mGround) {

			//プレイヤーが静止している
			if (mAcceleX == 0) {
				if (mSprite->getPlayAnimeName() != "idle") {
					mSprite->play("kare-meshi/idle");
				}
			}
			//プレイヤーが右に進んでいる
			else if (mAcceleX > 0) {
				//プレイヤーが右向き
				if (mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play("kare-meshi/walk");
					}
				}
				//プレイヤーが左向き
				else if (mSprite->getPlayAnimeName() != "walk") {
					mSprite->play("kare-meshi/walk");
				}
			}
			//プレイヤーが左に進んでいる
			else {
				//プレイヤーが左向き
				if (!mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play("kare-meshi/walk");
					}
				}
				//プレイヤーが右向き
				else if (mSprite->getPlayAnimeName() != "walk") {
					mSprite->play("kare-meshi/walk");
				}
			}
		}
		//プレイヤーが空中にいる
		//else {
		//	if (mSprite->getPlayAnimeName() != "jump") {
		//		mSprite->play("kare-meshi/jump");
		//	}
		//}

	}
	//上段ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_U && mDamageCounter == 1) {
		mSprite->play("kare-meshi/damage_u");
		mSprite->setStep(0.9f);

	}
	//下段ダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_D && mDamageCounter == 1) {
		mSprite->play("kare-meshi/damage_d");
		mSprite->setStep(0.9f);
	}
	//しゃがみダメージ状態
	else if (mState == Parameter::S_PLAYER_DAMAGE_S && mDamageCounter == 1) {
		//mSprite->play("kare-meshi/damage_squat");
	}
	else if (mState == Parameter::S_PLAYER_DAMAGE_AIR && mDamageCounter == 1) {
		mSprite->play("kare-meshi/damage_air");
		mSprite->setStep(0.7f);
	}
	else if (mState == Parameter::S_PLAYER_DAMAGE_AIR2 && mDamageCounter == 1) {
		mSprite->play("kare-meshi/damage_air");
		mSprite->setStep(0.7f);
	}
	else if (mState == Parameter::S_PLAYER_DOWN && mCounter == 39) {
		mSprite->play("kare-meshi/down");
		mSprite->setStep(0.8f);
	}
	

	//表示位置の更新
	if(mRight)mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), Parameter::GROUND_LINE - mPositionY-120);
	else mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) +25, Parameter::GROUND_LINE - mPositionY - 120);
	//プレイヤーの更新、引数は前回の更新処理から経過した時間
	mSprite->update((float)30 / 1000);
}


//オーバーロード

