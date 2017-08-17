#include "TitleScene.h"
#include "../Application.h"
#include "../Input/Input.h"
#include "../Effekseer/AnimationController.h"

/*リソースのロードと初期化*/
void TitleScene::Load() {
	mGraphAnime1 = LoadGraph("Data/graphic/charaselect/l.png");

	//プレイヤーの作成
	mSprite = ss::Player::create();

	//アニメデータをリソースに追加
	Application::resman->addData("Data/sprite_logo/logo.ssbp");

	//プレイヤーにリソースを割り当て
	mSprite->setData("logo");// ssbpファイル名

	mSprite->play("logo/anime_1");// アニメーション名を指定

	//表示位置を設定
	mSprite->setPosition(640, 360);
	//スケール設定
	mSprite->setScale(0.6f, 0.6f);

	mSprite->setStep(0.6);

	mSoundEnter = LoadSoundMem("Data/se/decision16.mp3");

	mController.SetPlayerId(0);
}

/*更新*/
void TitleScene::Process() {
	mController.ConvertInput();

	if (mController.getKey(9) == 1) {
		Application::mNextSceneId = Parameter::SCENE_CHARASELECT;
		PlaySoundMem(mSoundEnter, DX_PLAYTYPE_BACK);
	}
	mSprite->update((float)30 / 1000);

	if (mSprite->getFrameNo() == 38)
		AnimationController::getInstance().Create(mGraphAnime1, 1, 640, 350, 1024, 620, 1.25, 0, 4, 4, 204, 204, 0, 0);

	if (mSprite->getFrameNo() == 119)mSprite->setFrameNo(78);

	//アニメーションのプロセス
	AnimationController::getInstance().Process();
}

/*描画*/
void TitleScene::Drawing() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//アニメーションの描画
	AnimationController::getInstance().Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	mSprite->draw();

	if (mSprite->getFrameNo() > 38)DrawStringToHandle(480, 600, "<Press Start>", Parameter::COLOR_WHITE, Parameter::FONT_80_FERRUM, 0, 0);
}
