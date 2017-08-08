#include "Southern.h"
#include "../../../Application.h"

Arms::Profile Southern::getProfile() {
	Arms::Profile p;
	p.category = Parameter::HK;
	p.id = 3;
	p.size = 0.3f;
	p.speed = 0.6f;
	return p;
}

/*グラフィックのロード*/
void Southern::LoadArmsGraphic() {
	//プレイヤーの作成
	mSprite = ss::Player::create();

	//アニメデータをリソースに追加
	//Application::resman->addData("Data/arms/HollyKnights/vein/vein.ssbp");
	//プレイヤーにリソースを割り当て
	mSprite->setData("Southern");// ssbpファイル名（拡張子不要）
	
	//プレイヤーの作成
	mSprite2 = ss::Player::create();

	//プレイヤーにリソースを割り当て
	mSprite2->setData("Southern");// ssbpファイル名（拡張子不要）

	mIcon = LoadGraph("Data/arms/HollyKnights/vein/icon.png");

	mDistX = -100;
	mDistY = 30;
}

/*サウンドのロード*/
void Southern::LoadArmsSound() {
}

/*アニメーションの更新*/
void Southern::UpdateArmsAnimation() {
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mSprite->getPlayAnimeName() != "wait_1") {
			mSprite->play("arms/wait_1");
			mSprite->setStep(0.6f);

			mSprite2->play("arms/wait_back");
			mSprite2->setStep(0.6f);
		}
	}
	if (mState == Parameter::S_ARMS_SUMMON) {
		if (mSprite->getPlayAnimeName() != "summon") {
			mSprite->play("arms/summon");
			mSprite->setStep(0.6f);

			mSprite2->stop();
		}
	}

	//振り向き
	if (mRight) {
		mSprite->setScale(0.3f, 0.25f);
		mSprite2->setScale(0.3f, 0.25f);
	}
	else {
		mSprite->setScale(-0.3f, 0.25f);
		mSprite2->setScale(-0.3f, 0.25f);
	}

	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite->update((float)30 / 1000);

	mSprite2->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite2->update((float)30 / 1000);
}

/*攻撃を始める*/
void Southern::StartAtack() {
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
void Southern::CheckCanSummon() {

}

/*魔具固有の処理*/
void Southern::Process() {

}

/*攻撃後の固有処理*/
void Southern::ProcessAfterAtack() {

}

/*固有UIの描画*/
void Southern::DrawUI() {

}

//オーバーライド


/*プレイヤーを追従する*/
void Southern::FollowPlayer(int pX, int pY) {
	double distX, distY, distAngle, moveX, moveY, speedX, speedY;

	distX = (double)(pX - mPositionX);
	distY = (double)(pY - mPositionY);


	distAngle = atan2(distY, distX);

	if (distX > 70 || distX < -70) {
		speedX = 10;
	}
	else speedX = abs(distX / 10);

	if (distY > 70 || distY < -70) {
		speedY = 10;
	}
	else speedY = abs(distY / 10);

	moveX = (double)cos(distAngle) * speedX;
	moveY = (double)sin(distAngle) * speedY;

	if (distX == 0)moveX = 0;
	if (distY == 0)moveY = 0;

	if(mRight)mPositionX = pX - mDistX;
	else mPositionX = pX + mDistX;

	mPositionY += (int)moveY;
}


void Southern::Draw() {
	mSprite->draw();
	
}

void Southern::DrawBack() {
	if(mState == Parameter::S_ARMS_NORMAL)mSprite2->draw();
}