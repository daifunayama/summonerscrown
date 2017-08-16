#include "Enikuma.h"
#include "../../../Application.h"

Arms::Profile Enikuma::getProfile() {
	Arms::Profile p;
	p.category = Parameter::EA;
	p.id = 2;
	p.type = 1;
	p.size = 0.25f;
	p.speed = 0.6f;
	return p;
}

/*グラフィックのロード*/
void Enikuma::LoadArmsGraphic() {
	//プレイヤーの作成
	mSprite = ss::Player::create();

	//プレイヤーにリソースを割り当て
	mSprite->setData("Enikuma");// ssbpファイル名（拡張子不要）

	mIcon = LoadGraph("Data/arms/EvilAnima/Enikuma/icon.png");

	mDistX = -100;
	mDistY = 0;
}

/*サウンドのロード*/
void Enikuma::LoadArmsSound() {
	mSoundAtack[1] = LoadSoundMem("Data/se/手足・空振り04.mp3");
	mSoundAtack[2] = LoadSoundMem("Data/se/ロボット・殴る、蹴る02.mp3");

}

/*アニメーションの更新*/
void Enikuma::UpdateArmsAnimation() {
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
void Enikuma::StartAtack() {
	if (mPlayer->isCanArmsAtackState() && mState == Parameter::S_ARMS_NORMAL) {

		if (mController.getKey(4) == 1) {
			mState = Parameter::S_ARMS_ATACK_D;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_D].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/d");
			mSprite->setStep(0.7);
		}

		if (mController.getKey(3) == 1) {
			mState = Parameter::S_ARMS_ATACK_C;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_C].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/c");
			mSprite->setStep(0.7);
		}
	}
}

void Enikuma::DoAssult() {
	ResetPosition();
	mState = Parameter::S_ARMS_ATACK_D;

	mAtack[Parameter::ATACK_D].InitAtack();
	mRight = mPlayer->getRight();

	mSprite->play("arms/d");
	mSprite->setStep(0.7);
	mPlayer->setEX(mPlayer->getEX() - 50);
}

/*召喚可能かどうかのチェック*/
void Enikuma::CheckCanSummon() {

}

/*魔具固有の処理*/
void Enikuma::Process() {

}

/*攻撃後の固有処理*/
void Enikuma::ProcessAfterAtack() {

}
