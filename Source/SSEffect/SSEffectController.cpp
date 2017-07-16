#include "SSEffectController.h"
#include "../Application.h"

/*リソースのロード*/
void SSEffectController::Load() {

	//アニメデータをリソースに追加
	Application::resman->addData("Data/sprite_effects/ParticleEffectSample.ssbp");

	for (int i = 0; i < 5; i++) {
		//プレイヤーの作成
		mSSEffect[i] = ss::Player::create();

		//プレイヤーにリソースを割り当て
		mSSEffect[i]->setData("ParticleEffectSample");// ssbpファイル名
	}
	

}

/*アニメーションの再生*/
void SSEffectController::Play(string pass, int positionX, int positionY, float scaleX, float scaleY, float speed,float angle, int alpha) {
	mSSEffect[mActive]->play(pass.c_str());
	
	mSSEffect[mActive]->setPosition(positionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), positionY);
	//スケール設定
	mSSEffect[mActive]->setScale(scaleX, scaleY);
	//回転を設定
	mSSEffect[mActive]->setRotation(0.0f, 0.0f, angle);
	//透明度を設定
	mSSEffect[mActive]->setAlpha(alpha);
	//反転を設定
	mSSEffect[mActive]->setFlip(false, false);

	mSSEffect[mActive]->setLoop(1);
	mSSEffect[mActive]->setStep(speed);

	mActive++;
	if (mActive >= 5)mActive = 0;

}

/*更新*/
void SSEffectController::Process() {
	for(int i=0;i<5;i++)mSSEffect[i]->update((float)30 / 1000);
}

/*描画*/
void SSEffectController::Draw() {
	for (int i = 0; i<5; i++)mSSEffect[i]->draw();
}