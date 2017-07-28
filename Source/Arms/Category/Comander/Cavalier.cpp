#include "Cavalier.h"
#include "../../../Application.h"

/*グラフィックのロード*/
void Cavalier::LoadArmsGraphic() {
	//プレイヤーの作成
	mSprite = ss::Player::create();

	//アニメデータをリソースに追加
	//Application::resman->addData("Data/arms/Comander/Cavalier/cavalier.ssbp");
	//プレイヤーにリソースを割り当て
	mSprite->setData("cavalier");// ssbpファイル名（拡張子不要）
	//再生するモーションを設定
	mSprite->play("arms/wait");// アニメーション名を指定(ssae名/アニメーション名も可能、詳しくは後述)

	//表示位置を設定
	mSprite->setPosition(400, 300);
	//スケール設定
	mSprite->setScale(0.25f, 0.25f);
	//回転を設定
	mSprite->setRotation(0.0f, 0.0f, 0.0f);
	//透明度を設定
	mSprite->setAlpha(255);
	//反転を設定
	mSprite->setFlip(false, false);

	mSprite->setStep(0.5f);

	mIcon = LoadGraph("Data/arms/Comander/Cavalier/icon.png");
	mGraphBullet = LoadGraph("Data/arms/Comander/bullet.png");

}

/*サウンドのロード*/
void Cavalier::LoadArmsSound() {
	mSoundAtack[1] = LoadSoundMem("Data/arms/Comander/Cavalier/se1.mp3");
	mSoundAtack[2] = LoadSoundMem("Data/arms/Comander/Cavalier/se2.mp3");
	mSoundAtack[3] = LoadSoundMem("Data/arms/Comander/Cavalier/gun-reload1.mp3");
	
	ChangeVolumeSoundMem(128, mSoundAtack[3]);
}

/*アニメーションの更新*/
void Cavalier::UpdateArmsAnimation() {
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


	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), Parameter::WINDOW_HEIGHT - mPositionY);
	mSprite->update((float)30 / 1000);
}

/*攻撃を始める*/
void Cavalier::StartAtack() {
	if (mPlayer->isCanArmsAtackState() && mState == Parameter::S_ARMS_NORMAL) {

		if (mController.getKey(4) == 1 && mBullet > 0) {
			mState = Parameter::S_ARMS_ATACK_D;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_D].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/d");
			mBullet--;
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
void Cavalier::CheckCanSummon() {

}

/*魔具固有の処理*/
void Cavalier::Process() {

}

/*攻撃後の固有処理*/
void Cavalier::ProcessAfterAtack() {
	if (mState == Parameter::S_ARMS_ATACK_2C) {
		if (mBullet < mMaxBullet)mBullet++;
	}
}

/*固有UIの描画*/
void Cavalier::DrawUI() {
	if (mPlayer->getPlayerId() == 0) {
		for (int i = 0; i < mBullet; i++) {
			DrawGraph(50 + i * 40, 620, mGraphBullet, true);
		}
	}
	else {
		for (int i = 0; i < mBullet; i++) {
			DrawGraph(1000 + i * 40, 620, mGraphBullet, true);
		}
	}
}