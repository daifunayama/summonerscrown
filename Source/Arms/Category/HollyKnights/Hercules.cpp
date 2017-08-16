#include "Hercules.h"
#include "../../../Application.h"
#include "../../../Effekseer/AnimationController.h"

Arms::Profile Hercules::getProfile() {
	Arms::Profile p;
	p.category = Parameter::HK;
	p.id = 6;
	p.type = 4;
	p.size = 0.3f;
	p.speed = 0.6f;
	return p;
}

/*グラフィックのロード*/
void Hercules::LoadArmsGraphic() {
	//プレイヤーの作成
	mSprite = ss::Player::create();

	//プレイヤーにリソースを割り当て
	mSprite->setData("Hercules");// ssbpファイル名（拡張子不要）

	mIcon = LoadGraph("Data/arms/HollyKnights/Hercules/icon.png");

	mDistX = 300;
	mDistY = -800;
}

/*サウンドのロード*/
void Hercules::LoadArmsSound() {
	mSoundAtack[1] = LoadSoundMem("Data/arms/HollyKnights/Hercules/se1.mp3");
}

/*アニメーションの更新*/
void Hercules::UpdateArmsAnimation() {
	
	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite->update((float)30 / 1000);

}

/*攻撃を始める*/
void Hercules::StartAtack() {

	mState = Parameter::S_ARMS_SUMMON;
	if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
	else mPositionX = mPlayer->getPositionX() - mDistX;

	mPositionY = mPlayer->getPositionY() + mDistY;
	mCounter = 0;

	mAtack.InitAtack();
	mRight = mPlayer->getRight();
	
	mSprite->play("arms/summon");
	mSprite->setStep(0.8f);

	mSprite->setScale(mRight ? 0.5f:-0.5f, 0.5f);
}

/*召喚可能かどうかのチェック*/
void Hercules::CheckCanSummon() {

}

/*魔具固有の処理*/
void Hercules::Process() {
	if (mCounter == 1) {

		AnimationController::getInstance().Create(mGraphSummonEffect1, 1, mPositionX-30, mPositionY+400, 400, 400, 1.5, 360, 4, 1, 40, 0, true, false);
		AnimationController::getInstance().Create(mGraphSummonEffect2, 2, mPositionX-30, mPositionY+400, 400, 400, 1.5, 360, 4, 1, 40, 0, true, false);

	}
}

/*攻撃後の固有処理*/
void Hercules::ProcessAfterAtack() {

}
