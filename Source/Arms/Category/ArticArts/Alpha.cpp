#include "Alpha.h"
#include "../../../Application.h"

Arms::Profile Alpha::getProfile() {
	Arms::Profile p;
	p.category = Parameter::AA;
	p.id = 0;
	p.type = 1;
	p.size = 0.25f;
	p.speed = 0.5f;
	return p;
}


/*グラフィックのロード*/
void Alpha::LoadArmsGraphic() {
	//プレイヤーの作成
	mSprite = ss::Player::create();

	//アニメデータをリソースに追加
	//Application::resman->addData("Data/arms/ArticArts/Alpha/alpha.ssbp");
	//プレイヤーにリソースを割り当て
	mSprite->setData("alpha");// ssbpファイル名（拡張子不要）
								 //再生するモーションを設定
	mSprite->play("arms/wait");// アニメーション名を指定(ssae名/アニメーション名も可能、詳しくは後述)

	//スケール設定
	mSprite->setScale(0.25f, 0.25f);

	mSprite->setStep(0.5f);

	mIcon = LoadGraph("Data/arms/ArticArts/Alpha/icon.png");

	mDistX = -100;
	mDistY = 50;
}

/*サウンドのロード*/
void Alpha::LoadArmsSound() {
}

/*アニメーションの更新*/
void Alpha::UpdateArmsAnimation() {
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mSprite->getPlayAnimeName() != "wait") {
			mSprite->play("arms/wait");
			mSprite->setStep(0.5f);
		}
	}
	if (mState == Parameter::S_ARMS_SUMMON) {
		if (mSprite->getPlayAnimeName() != "summon") {
			mSprite->play("arms/summon");
			mSprite->setStep(0.8f);
		}
	}

	//振り向き
	if (mRight)mSprite->setScale(0.25f, 0.25f);
	else mSprite->setScale(-0.25f, 0.25f);


	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite->update((float)30 / 1000);
}

/*攻撃を始める*/
void Alpha::StartAtack() {
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
void Alpha::CheckCanSummon() {

}

/*魔具固有の処理*/
void Alpha::Process() {

}

/*攻撃後の固有処理*/
void Alpha::ProcessAfterAtack() {

}

/*固有UIの描画*/
void Alpha::DrawUI() {
	
}