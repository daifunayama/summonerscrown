#include "BackGround.h"
#include "../Parameter.h"
#include "../Camera/Camera.h"
#include "DxLib.h"

/*ロード*/
void BackGround::LoadGraphic() {
	mGraphHandle = LoadGraph("Data/graphic/background/background1.png");

	mGraphEmblem[Parameter::HK] = LoadGraph("Data/graphic/emblem/HollyKnights.png");
	mGraphEmblem[Parameter::CM] = LoadGraph("Data/graphic/emblem/Comander.png");
	mGraphEmblem[Parameter::AA] = LoadGraph("Data/graphic/emblem/ArticArts.png");
	mGraphEmblem[Parameter::PS] = LoadGraph("Data/graphic/emblem/PrimalSpheres.png");
}

/*プレイヤー情報の取得*/
void BackGround::GetPlayer(Player& player1, Player& player2) {

	if (player1.getArms(player1.getArmsId())->getState() == Parameter::S_ARMS_SUMMON) {
		if (player1.getArms(player1.getArmsId())->getCounter() == 1) {
			mBlackoutCounter[0] = 40;
			mEmblemId[0] = player1.getArms(player1.getArmsId())->getCategoryId();
			if(player1.getRight())mX[0] = player1.getPositionX() - 100;
			else mX[0] = player1.getPositionX() + 100;
		}
	}
	if (player2.getArms(player2.getArmsId())->getState() == Parameter::S_ARMS_SUMMON) {
		if (player2.getArms(player2.getArmsId())->getCounter() == 1) {
			mBlackoutCounter[1] = 40;
			mEmblemId[1] = player2.getArms(player2.getArmsId())->getCategoryId();
			if (player2.getRight())mX[1] = player2.getPositionX() - 100;
			else mX[1] = player2.getPositionX() + 100;
		}
	}
	if (mBlackoutCounter[0] > 0)mBlackoutCounter[0]--;
	if (mBlackoutCounter[1] > 0)mBlackoutCounter[1]--;
}

/*描画*/
void BackGround::Draw() {
	int counter;

	if (mBlackoutCounter[0] > mBlackoutCounter[1])counter = mBlackoutCounter[0];
	else counter = mBlackoutCounter[1];

	SetDrawBright(200, 200, 200);
	if(counter > 10)SetDrawBright(60,60,60);
	else if (counter > 0)SetDrawBright(200 - counter * 14, 200 - counter * 14, 200 - counter * 14);

	DrawGraph(Camera::getInstance().getPositonX(), Camera::getInstance().getPositonY(), mGraphHandle, false);
	//DrawGraph(-400,-250, mGraphHandle, false);
	SetDrawBright(255,255,255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	if (mBlackoutCounter[0] > 0) {
		DrawRotaGraph(mX[0] - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 300,0.75,0, mGraphEmblem[mEmblemId[0]], true,false);
	}
	if (mBlackoutCounter[1] > 0) {
		DrawRotaGraph(mX[1] - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 300, 0.75, 0, mGraphEmblem[mEmblemId[1]], true, false);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}