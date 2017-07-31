#include "EyecatchScene.h"
#include "../Application.h"
#include "../Input/Input.h"
#include "../Effekseer/AnimationController.h"
#include "../Player/Character/Ein.h"
#include "../Player/Character/Remnant.h"

/*リソースのロードと初期化*/
void EyecatchScene::Load() {

	mController.SetPlayerId(0);

	mPlayer[0] = new Ein();
	mPlayer[1] = new Remnant();

	mCounter = 0;

	mCharaGraph[0].positionX = 0;
	mCharaGraph[0].positionY = 500;
	mCharaGraph[1].positionX = Parameter::WINDOW_WIDTH;
	mCharaGraph[1].positionY = 500;

	mGraphBackground = LoadGraph("Data/graphic/charaselect/background.png");

	mCharaGraph[0].graph = LoadGraph("Data/graphic/game/ein.png");
	mCharaGraph[1].graph = LoadGraph("Data/graphic/game/remnant.png");

	mBGM = LoadSoundMem("Data/bgm/eyecatch.mp3");
}

/*更新*/
void EyecatchScene::Process() {
	mController.ConvertInput();

	if (CheckHitKey(KEY_INPUT_R) == 1)mCounter = 0;

	if (mController.getKey(9) == 1) {
		Application::mNextSceneId = Parameter::SCENE_BATTLE;
		PlaySoundMem(mSoundEnter, DX_PLAYTYPE_BACK);
	}

	if (mCounter == 0) {
		StopSoundMem(mBGM);
		mCharaGraph[0].positionX = -500;
		mCharaGraph[0].positionY = 500;
		mCharaGraph[1].positionX = Parameter::WINDOW_WIDTH + 500;
		mCharaGraph[1].positionY = 500;
		mNameX[0] = Parameter::WINDOW_WIDTH +200;
		mNameX[1] = -500;
		mBright = 0;
	}

	mCounter++;

	if (mCounter == 15)PlaySoundMem(mBGM, DX_PLAYTYPE_BACK, true);

	if (mCounter < 20) {
		mCharaGraph[0].positionX += 55;
		mCharaGraph[0].positionY -= 5;
		mNameX[0] -= 55;
	}
	else if (mCounter < 40) {
		mCharaGraph[0].positionX += 5;
		mCharaGraph[0].positionY -= 1;
		mNameX[0] -= 5;
	}
	else if (mCounter < 60) {
		mCharaGraph[0].positionX += 55;
		mCharaGraph[0].positionY -= 5;
		mNameX[0] -= 55;
	}
	else if (mCounter < 80) {
		mCharaGraph[1].positionX -= 55;
		mCharaGraph[1].positionY -= 5;
		mNameX[1] += 55;
	}
	else if (mCounter < 100) {
		mCharaGraph[1].positionX -= 5;
		mCharaGraph[1].positionY -= 1;
		mNameX[1] += 5;
	}
	else if (mCounter < 120) {
		mCharaGraph[1].positionX -= 55;
		mCharaGraph[1].positionY -= 5;
		mNameX[1] += 55;
	}
	else if (mCounter < 180) {
		mCharaGraph[0].positionX -= 23;
		mCharaGraph[1].positionX += 23;
	}
	else if (mCounter < 300) {
		mCharaGraph[0].positionX -= 1;
		mCharaGraph[1].positionX += 1;
	}

	if (mCounter == 120) {
		mCharaGraph[1].positionX = -500;
		mCharaGraph[0].positionX = Parameter::WINDOW_WIDTH + 500;
		mCharaGraph[0].positionY = 400;
		mCharaGraph[1].positionY = 400;
	}

	if (mCounter == 180) {
		mNameX[0] = 100;
		mNameX[1] = Parameter::WINDOW_WIDTH - 500;
	}

	if (mCounter > 140 && mCounter < 180) {
		mBright = (mBright > 255) ? 255 : mBright + 8;
	}
	else if (mCounter >= 180) {
		mBright = (mBright < 0) ? 0 : mBright - 3;
	}


	//アニメーションのプロセス
	AnimationController::getInstance().Process();
}

/*描画*/
void EyecatchScene::Drawing() {
	DrawGraph(0, 0, mGraphBackground, false);

	//アニメーションの描画
	AnimationController::getInstance().DrawLayer1();

	if (mCounter < 120) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		SetDrawBright(0, 0, 0);
		DrawRotaGraph(mCharaGraph[0].positionX + 30, mCharaGraph[0].positionY - 30, 0.9, 0,  mCharaGraph[0].graph, true, false);
		DrawRotaGraph(mCharaGraph[1].positionX - 30, mCharaGraph[1].positionY - 30, 0.9, 0,  mCharaGraph[1].graph, true, true);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

		DrawRotaGraph(mCharaGraph[0].positionX, mCharaGraph[0].positionY, 0.9, 0, mCharaGraph[0].graph, true, false);
		DrawRotaGraph(mCharaGraph[1].positionX, mCharaGraph[1].positionY, 0.9, 0,  mCharaGraph[1].graph, true, true);
	}
	else if (mCounter < 180) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		SetDrawBright(0, 0, 0);
		DrawRotaGraph(mCharaGraph[0].positionX, mCharaGraph[0].positionY, 0.9, 0, mCharaGraph[0].graph, true, false);
		DrawRotaGraph(mCharaGraph[1].positionX, mCharaGraph[1].positionY, 0.9, 0, mCharaGraph[1].graph, true, true);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		SetDrawBright(0, 0, 0);
		DrawRotaGraph(mCharaGraph[0].positionX + 30, mCharaGraph[0].positionY - 30, 0.9, 0, mCharaGraph[0].graph, true, false);
		DrawRotaGraph(mCharaGraph[1].positionX - 30, mCharaGraph[1].positionY - 30, 0.9, 0, mCharaGraph[1].graph, true, true);
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawRotaGraph(mCharaGraph[0].positionX, mCharaGraph[0].positionY, 0.9, 0, mCharaGraph[0].graph, true, false);
		DrawRotaGraph(mCharaGraph[1].positionX, mCharaGraph[1].positionY, 0.9, 0, mCharaGraph[1].graph, true, true);
	}

	DrawFormatStringToHandle(mNameX[0],550, Parameter::COLOR_WHITE, Parameter::FONT_120_FERRUM,
		"%s", mPlayer[0]->getProfile().eName.c_str());

	DrawFormatStringToHandle(mNameX[1], 550, Parameter::COLOR_WHITE, Parameter::FONT_120_FERRUM,
		"%s", mPlayer[1]->getProfile().eName.c_str());

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mBright);
	DrawBox(0, 0, Parameter::WINDOW_WIDTH, Parameter::WINDOW_HEIGHT, Parameter::COLOR_WHITE, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
