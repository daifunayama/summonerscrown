#include "FollowerArms.h"
#include "../Application.h"
#include "../Parameter.h"
#include "../Utility.h"
#include "../Effekseer/AnimationController.h"
#include <fstream>

/*武器の初期化*/
void FollowerArms::InitArms() {
	mState = Parameter::S_ARMS_NORMAL;
	mDistX = -100;
	mDistY = 50;
	if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
	else mPositionX = mPlayer->getPositionX() - mDistX;
	
	mPositionY = mPlayer->getPositionY() + mDistY;
	
}

/*武器のロード*/
void FollowerArms::LoadArmsData() {
	ifstream ifs;
	int n;
	int boxId;
	int frameCounter;
	int boxCounter;
	string tmp;
	string pass;

	FrameData frameData;
	BoxData boxData;
	HitBox hitBox;

	//アニメーションの初期化
	for (int i = 0; i < 10; i++)mAnimation[i].setExist(false);

	for (int a = 0; a < 8; a++) {

		mAtack[a].ClearFrameData();

		hitBox.setExist(false);
		for (int i = 0; i < 20; i++) {
			frameData.setAtackBox(i, hitBox);
		}

		ifs.clear();

		pass.clear();



		if (a == Parameter::ATACK_C)pass = ArmsList::get().getArmsPass(getProfile().category,getProfile().id) + "/c.txt";
		if (a == Parameter::ATACK_2C)pass = ArmsList::get().getArmsPass(getProfile().category, getProfile().id) + "/cd.txt";
		if (a == Parameter::ATACK_8C)pass = ArmsList::get().getArmsPass(getProfile().category, getProfile().id) + "/cu.txt";
		if (a == Parameter::ATACK_D)pass = ArmsList::get().getArmsPass(getProfile().category, getProfile().id) + "/d.txt";
		if (a == Parameter::ATACK_2D)pass = ArmsList::get().getArmsPass(getProfile().category, getProfile().id) + "/dd.txt";


		ifs.open(pass.c_str());

		if (ifs) {
			
			for (int i = 0; i < 8; i++) {
				ifs >> tmp;
				mAtack[a].setAllowCancel(i, Utility::StringToInt(tmp));
			}

			ifs >> tmp;
			mAtack[a].setContinueAtackAfterDamage(Utility::StringToInt(tmp));

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
				boxData.setAllowMultHit(Utility::StringToInt(tmp));
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
					mAtack[a].PushFrameData(frameData);

					boxCounter = 0;

					hitBox.setExist(false);
					for (int i = 0; i < 20; i++) {
						frameData.setAtackBox(i, hitBox);
					}

					//キャンセル可能フラグ
					ifs >> tmp;
					frameData.setAllowCancel(Utility::StringToInt(tmp));

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

				//アニメーション
				if (11 <= n && n <= 20) {
					mAnimation[n - 11].setExist(true);
					mAnimation[n - 11].setAtackId(a);

					ifs >> tmp;
					mAnimation[n - 11].setPositionX(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setPositionY(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setWidth(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setHeight(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setExRate(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setDevided(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setSpeed(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setStartFrame(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setEndFrame(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setAddFlag(Utility::StringToInt(tmp));
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

/*武器を動かす*/
void FollowerArms::Move() {

	//待機時
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mPlayer->getRight())FollowPlayer(mPlayer->getPositionX() + mDistX, mPlayer->getPositionY() + mDistY);
		else FollowPlayer(mPlayer->getPositionX() - mDistX, mPlayer->getPositionY() + mDistY);
	}

	//召喚時
	if (mState == Parameter::S_ARMS_SUMMON) {
		mCounter++;
		if (mCounter >= 45)mState = Parameter::S_ARMS_NORMAL;
	}

	//クイックキャンセル
	if (!mController.getKey(5) && mController.getKey(6) == 1 && mPlayer->getEX() >= 50)DoCancel();

	//クイックアサルト
	if (mController.getKey(5) && mController.getKey(3) == 1 && mPlayer->getEX() >= 50)DoAssult();

	//攻撃を開始する
	StartAtack();

	//攻撃時
	if (isAtackState()) {
		DoAtack();
	}

	
}

/*プレイヤーを追従する*/
void FollowerArms::FollowPlayer(int pX, int pY) {
	double distX, distY, distAngle, moveX, moveY, speedX, speedY;

	distX = (double)(pX - mPositionX);
	distY = (double)(pY - mPositionY);

	if (-5 < distX && distX < 5)distX = 0;
	if (-5 < distY && distY < 5)distY = 0;

	distAngle = atan2(distY, distX);

	if (distX > 70 || distX < -70) {
		speedX = 7;
	}
	else speedX = abs(distX / 10);

	if (distY > 70 || distY < -70) {
		speedY = 7;
	}
	else speedY = abs(distY / 10);

	moveX = (double)cos(distAngle) * speedX;
	moveY = (double)sin(distAngle) * speedY;

	if (distX == 0)moveX = 0;
	if (distY == 0)moveY = 0;

	mPositionX += (int)moveX;
	mPositionY += (int)moveY;
}

/*位置をリセットする*/
void FollowerArms::ResetPosition() {
	mPositionX = mPlayer->getPositionX() +(mPlayer->getRight() ? +mDistX : -mDistX);
	mPositionY = mPlayer->getPositionY() + mDistY;
}

/*召喚を始める*/
void FollowerArms::StartSummon() {
	mState = Parameter::S_ARMS_SUMMON;
	mCounter = 0;

	mRight = mPlayer->getRight();
	if (mRight)mPositionX = mPlayer->getPositionX() + mDistX;
	else mPositionX = mPlayer->getPositionX() - mDistX;

	mPositionY = mPlayer->getPositionY() + mDistY;
}

/*攻撃を始める*/
void FollowerArms::StartAtack() {
	if (mPlayer->isCanArmsAtackState() && mState == Parameter::S_ARMS_NORMAL) {

		if (mController.getKey(4) == 1) {
			mState = Parameter::S_ARMS_ATACK_D;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_D].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/d");
		}
	}
}

/*攻撃*/
void FollowerArms::DoAtack() {
	int sId = 0;

	for(int a=0;a<8;a++){
		if (mState == a+2) {

			//SEがある場合再生
			sId = mAtack[a].getFrameData(mAtack[a].getCounter()).getSoundId();
			if (sId > 0 && sId <= 10)PlaySoundMem(mSoundAtack[sId], DX_PLAYTYPE_BACK);

			//アニメーションがある場合再生
			for (int i = 0; i < 10; i++) {
				if (mAnimation[i].getExist() && mAnimation[i].getAtackId() == a) {
					if (mAnimation[i].getStartFrame() == mAtack[a].getCounter()) {
						if (mRight) {
							AnimationController::getInstance().Create(
								mAnimation[i].getGraph(), 1,
								mPositionX + mAnimation[i].getPositionX(),
								mPositionY + mAnimation[i].getPositionY(),
								mAnimation[i].getWidth(), mAnimation[i].getHeight(), mAnimation[i].getExRate(), 0, mAnimation[i].getDevided(),
								mAnimation[i].getSpeed(), mAnimation[i].getEndFrame(), -1, mRight, mAnimation[i].getAddFlag());
						}
						else {
							AnimationController::getInstance().Create(
								mAnimation[i].getGraph(), 1,
								mPositionX - mAnimation[i].getPositionX(),
								mPositionY + mAnimation[i].getPositionY(),
								mAnimation[i].getWidth(), mAnimation[i].getHeight(), mAnimation[i].getExRate(), 0, mAnimation[i].getDevided(),
								mAnimation[i].getSpeed(), mAnimation[i].getEndFrame(), -1, mRight, mAnimation[i].getAddFlag());
						}
					}
				}
			}

			if(mAtack[a].getCounter() == 1)mPlayer->getVoice()->PlayVoiceIf(Parameter::VOICE_MATACK, GetRand(4));

			mAtack[a].IncreaseCounter();

			//攻撃終了時の処理
			if (mAtack[a].CheckAtackEnd()) {
				ProcessAfterAtack();
				mState = Parameter::S_ARMS_NORMAL;
			}
		}
	}
}

/*クイックキャンセル*/
void FollowerArms::DoCancel() {
	mState = Parameter::S_ARMS_NORMAL;
	ResetPosition();
	mPlayer->setEX(mPlayer->getEX() - 25);
}

/*クイックアサルト*/
void FollowerArms::DoAssult() {
	ResetPosition();
	mCounter = 0;
	mState = Parameter::S_ARMS_ATACK_D;

	mAtack[Parameter::ATACK_D].InitAtack();
	mRight = mPlayer->getRight();

	mSprite->play("arms/d");

	mPlayer->setEX(mPlayer->getEX() - 50);
}

/*描画*/
void FollowerArms::Draw() {
	mSprite->draw();
}

/*攻撃ボックスの描画*/
void FollowerArms::DrawAtackBox() {
	int atackId, counter;

	atackId = mState - 2;
	counter = mAtack[atackId].getCounter();

	//透過設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

	//右向きのとき
	if (mRight) {
		for (int i = 0; i < 20; i++) {
			if (mAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					mPositionX + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
					+ mAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY()
					+ mAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					Parameter::COLOR_RED, true);
			}
		}
	}

	//左向きのとき
	else {
		for (int i = 0; i < 20; i++) {
			if (mAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX - mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					mPositionX - mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
					- mAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY()
					+ mAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					Parameter::COLOR_RED, true);
			}
		}
	}

	//透過設定をもどす
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/*魔具の攻撃の当たり判定*/
void FollowerArms::CheckArmsAtackHit(Player& another) {
	int atackId, counter;
	Box box1, box2;

	atackId = mState - 2;
	counter = mAtack[atackId].getCounter();
	bool atackHit = false;

	if (isAtackState()) {
		for (int i = 0; i < 20 && !atackHit; i++) {
			//該当フレームに攻撃用ボックスが存在するとき
			if (mAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				if (!mAtack[atackId].getAtackHit()) {

					//相手のヒットボックスと比較
					for (int j = 0; j < 10 && !atackHit; j++) {

						//相手のダメージボックスが存在するとき
						if (another.getDamageBox(another.getState(),j).getExist()) {

							//自身が右向き
							if (mRight) {
								box1.x = mPositionX + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX();
							}
							//自身が左向き
							else
								box1.x = mPositionX - mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
								- mAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth();

							box1.y = mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY();
							box1.width = mAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth();
							box1.height = mAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight();

							//相手が右向き
							if (another.getRight()) {
								box2.x = another.getPositionX() + another.getDamageBox(another.getState(), j).getPositionX();
							}
							//相手が左向き
							else {
								box2.x = another.getPositionX()
									- another.getDamageBox(another.getState(), j).getPositionX()
									- another.getDamageBox(another.getState(), j).getWidth();
							}
							box2.y = another.getPositionY() + another.getDamageBox(another.getState(), j).getPositionY();
 							box2.width = another.getDamageBox(another.getState(), j).getWidth();
							box2.height = another.getDamageBox(another.getState(), j).getHeight();

							//攻撃が相手にヒット
							if (Utility::CheckBoxHit(box1, box2)) {

								//ボックスIDを取得
								int boxId = mAtack[atackId].getFrameData(counter).getAtackBox(i).getBoxId();

								//相手に攻撃を与える
								another.EatAtack(2,mRight, mAtack[atackId].getFrameData(counter).getAtackBoxData(boxId));

								//攻撃が多段ヒットを許可しない場合既に当たったフラグをたてる
								if (!mAtack[atackId].getFrameData(counter).getAtackBoxData(boxId).getAllowMultHit())mAtack[atackId].setAtackHit(true);

								atackHit = true;
								break;
							}
						}
					}
				}
			}
		}
	}
}

/*攻撃状態かどうかを返す*/
bool FollowerArms::isAtackState() {
	if (mState == Parameter::S_ARMS_ATACK_C  ||
		mState == Parameter::S_ARMS_ATACK_8C ||
		mState == Parameter::S_ARMS_ATACK_2C ||
		mState == Parameter::S_ARMS_ATACK_JC ||
		mState == Parameter::S_ARMS_ATACK_D  ||
		mState == Parameter::S_ARMS_ATACK_8D ||
		mState == Parameter::S_ARMS_ATACK_2D ||
		mState == Parameter::S_ARMS_ATACK_JD) {
		return true;
	}
	return false;
}

/*キャンセル可能なタイミングかどうか*/
bool FollowerArms::isCanCancelTiming(int atackId) {
	int counter;

	return true;

	if (mState == Parameter::S_ARMS_NORMAL)return true;

	if (isAtackState()) {
		counter = mAtack[mState - 2].getCounter();

		if (mAtack[mState - 2].getFrameData(counter).getAllowCancel()) {
			if (mAtack[mState - 2].getAllowCancel(atackId)) {
				return true;
			}
		}
	}
	return false;
}