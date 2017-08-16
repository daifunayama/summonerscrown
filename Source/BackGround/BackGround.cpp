#include "BackGround.h"
#include "../Parameter.h"
#include "../Camera/Camera.h"
#include "DxLib.h"

/*ƒ[ƒh*/
void BackGround::LoadGraphic() {
	mEmblemId[0] = -1;
	mEmblemId[1] = -1;

	mGraphHandle[0] = LoadGraph("Data/graphic/background/background1-1.png");
	mGraphHandle[1] = LoadGraph("Data/graphic/background/background1-2.png");
	mGraphHandle[2] = LoadGraph("Data/graphic/background/background1-3.png");

	mGraphEmblem[Parameter::HK] = LoadGraph("Data/graphic/emblem/HollyKnights.png");
	mGraphEmblem[Parameter::CM] = LoadGraph("Data/graphic/emblem/Comander.png");
	mGraphEmblem[Parameter::AA] = LoadGraph("Data/graphic/emblem/ArticArts.png");
	mGraphEmblem[Parameter::EA] = LoadGraph("Data/graphic/emblem/EvilAnima.png");
	mGraphEmblem[Parameter::PS] = LoadGraph("Data/graphic/emblem/PrimalSpheres.png");
}

void BackGround::Process(Player& player1, Player& player2) {

	if (player1.getArms(player1.getArmsId())->getState() == Parameter::S_ARMS_SUMMON) {
		if (player1.getArms(player1.getArmsId())->getCounter() == 1) {
			mBlackoutCounter[0] = 40;
			mEmblemId[0] = player1.getArms(player1.getArmsId())->getProfile().category;
			mX[0] = player1.getRight() ? player1.getPositionX() - 100 : player1.getPositionX() + 100;
		}
	}
	if (player2.getArms(player2.getArmsId())->getState() == Parameter::S_ARMS_SUMMON) {
		if (player2.getArms(player2.getArmsId())->getCounter() == 1) {
			mBlackoutCounter[1] = 40;
			mEmblemId[1] = player2.getArms(player2.getArmsId())->getProfile().category;
			mX[1] = player1.getRight() ? player2.getPositionX() - 100 : player2.getPositionX() + 100;
		}
	}

	if (player1.getBlaze() != nullptr) {
		if (player1.getBlaze()->getState() == Parameter::S_ARMS_SUMMON) {
			if (mBlackoutCounter[0] == 60) {
				
				mEmblemId[0] = player1.getBlaze()->getProfile().category;
				mX[0] = player1.getRight() ? player1.getPositionX() - 100 : player1.getPositionX() + 100;
			}
		}
	}

	if (mBlackoutCounter[0] > 0)mBlackoutCounter[0]--;
	if (mBlackoutCounter[1] > 0)mBlackoutCounter[1]--;

	if (mBlackoutCounter[0] == 0)mEmblemId[0] = -1;
	if (mBlackoutCounter[1] == 0)mEmblemId[1] = -1;
}


/*•`‰æ*/
void BackGround::Draw() {
	int counter;

	if (mBlackoutCounter[0] > mBlackoutCounter[1])counter = mBlackoutCounter[0];
	else counter = mBlackoutCounter[1];

	SetDrawBright(200, 200, 200);
	if(counter > 10)SetDrawBright(30,30,30);
	else if (counter > 0)SetDrawBright(200 - counter * 14, 200 - counter * 14, 200 - counter * 14);
	

	DrawGraph(Camera::getInstance().getPositonX() - 500, Camera::getInstance().getPositonY()+50, mGraphHandle[2], true);
	DrawGraph(Camera::getInstance().getPositonX() - 500, Camera::getInstance().getPositonY()+50, mGraphHandle[1], true);
	DrawGraph(Camera::getInstance().getPositonX() - 500, Camera::getInstance().getPositonY()+50, mGraphHandle[0], true);

	SetDrawBright(255,255,255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	if (mBlackoutCounter[0] > 0 && mEmblemId[0] != -1) {
		DrawRotaGraph(mX[0] - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 300,0.75,0, mGraphEmblem[mEmblemId[0]], true,false);
	}
	if (mBlackoutCounter[1] > 0 && mEmblemId[1] != -1) {
		DrawRotaGraph(mX[1] - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 300, 0.75, 0, mGraphEmblem[mEmblemId[1]], true, false);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}