#include "Aries.h"
#include "../../../Application.h"

Arms::Profile Aries::getProfile() {
	Arms::Profile p;
	p.category = Parameter::HK;
	p.id = 0;
	p.type = 1;
	p.size = 0.3f;
	p.speed = 0.6f;
	return p;
}

/*グラフィックのロード*/
void Aries::LoadArmsGraphic() {
	//プレイヤーの作成
	mSprite = ss::Player::create();

	//プレイヤーにリソースを割り当て
	mSprite->setData("Aries");// ssbpファイル名（拡張子不要）

	mIcon = LoadGraph("Data/arms/HollyKnights/Aries/icon.png");

	mDistX = -100;
	mDistY = 0;
}

/*サウンドのロード*/
void Aries::LoadArmsSound() {
}

/*アニメーションの更新*/
void Aries::UpdateArmsAnimation() {
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mSprite->getPlayAnimeName() != "wait") {
			mSprite->play("arms/wait");
			mSprite->setStep(0.6f);
		}
	}
	if (mState == Parameter::S_ARMS_SUMMON) {
		if (mSprite->getPlayAnimeName() != "summon") {
			mSprite->play("arms/summon");
			mSprite->setStep(0.6f);
		}
	}

	//振り向き
	if (mRight) {
		mSprite->setScale(0.3f, 0.3f);
	}
	else {
		mSprite->setScale(-0.3f, 0.3f);
	}

	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite->update((float)30 / 1000);

}

/*攻撃を始める*/
void Aries::StartAtack() {
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

		if (mController.getKey(3) == 1 && mController.getDown()) {
			mState = Parameter::S_ARMS_ATACK_2C;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_2C].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/2c");
			mSprite->setStep(0.7);
		}
	}
}

/*召喚可能かどうかのチェック*/
void Aries::CheckCanSummon() {

}

/*魔具固有の処理*/
void Aries::Process() {

}

/*攻撃後の固有処理*/
void Aries::ProcessAfterAtack() {

}
