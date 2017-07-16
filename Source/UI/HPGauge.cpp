#include "HPGauge.h"
#include "../Parameter.h"
#include "DxLib.h"

/*ロード*/
void HPGauge::Load() {
	mGraphGauge = LoadGraph("Data/graphic/ui/hpgauge.png");

	mGraphNumber[0] = LoadGraph("Data/graphic/ui/hpnumber/0.png");
	mGraphNumber[1] = LoadGraph("Data/graphic/ui/hpnumber/1.png");
	mGraphNumber[2] = LoadGraph("Data/graphic/ui/hpnumber/2.png");
	mGraphNumber[3] = LoadGraph("Data/graphic/ui/hpnumber/3.png");
	mGraphNumber[4] = LoadGraph("Data/graphic/ui/hpnumber/4.png");
	mGraphNumber[5] = LoadGraph("Data/graphic/ui/hpnumber/5.png");
	mGraphNumber[6] = LoadGraph("Data/graphic/ui/hpnumber/6.png");
	mGraphNumber[7] = LoadGraph("Data/graphic/ui/hpnumber/7.png");
	mGraphNumber[8] = LoadGraph("Data/graphic/ui/hpnumber/8.png");
	mGraphNumber[9] = LoadGraph("Data/graphic/ui/hpnumber/9.png");

	if (mPlayerId == 0) {
		mGraphFace = LoadGraph("Data/graphic/ui/face_ein.png");
		mGraphBar[0] = LoadGraph("Data/graphic/ui/bar1-1.png");
		mGraphBar[1] = LoadGraph("Data/graphic/ui/bar2-1.png");
		mGraphBar[2] = LoadGraph("Data/graphic/ui/bar3-1.png");
	}
	else {
		//mGraphFace = LoadGraph("Data/graphic/ui/face_ria.png");
		mGraphBar[0] = LoadGraph("Data/graphic/ui/bar1-2.png");
		mGraphBar[1] = LoadGraph("Data/graphic/ui/bar2-2.png");
		mGraphBar[2] = LoadGraph("Data/graphic/ui/bar3-2.png");
	}
}

/*更新*/
void HPGauge::Process(Player& player, Player& another) {
	if (another.getChain() == 1) {
		if(!mKeepRedzone)mRedzone = mHP;
		mKeepRedzone = true;
	}
	else if (another.getChain() == 0) {
		if (mKeepRedzone)mKeepRedzone = false;
		if (mHP < mRedzone)mRedzone -= 2;
	}
	mName = player.getName();
	mHP = player.getHP();
}

/*描画*/
void HPGauge::Draw() {
	double pos;

	if (mPlayerId == 0) {
		pos = (double)mRedzone / 1000 * 393;
		DrawRectGraph(154, 58, 0, 0,(int)pos, 40, mGraphBar[2], true, false);

		pos = (double)mHP / 1000 * 393;
		if(mHP == 1000)DrawRectGraph(154, 58, 0, 0, (int)pos, 40, mGraphBar[0], true, false);
		else DrawRectGraph(154, 58, 0, 0, (int)pos, 40, mGraphBar[1], true, false);
		DrawGraph(0, 0, mGraphGauge, true);
		DrawGraph(0, 0, mGraphFace, true);

		DrawFormatStringToHandle(150, 5, Parameter::COLOR_WHITE, Parameter::FONT_20_FERRUM, "%s", mName.c_str());

		DrawDegitNumber(210, 113, mHP);

	}
	else {
		pos = (double)mRedzone / 1000 * 393;
		DrawRectGraph(Parameter::WINDOW_WIDTH - 153 - (int)pos, 58, 393 - (int)pos, 0, 393, 40, mGraphBar[2], true, false);

		pos = (double)mHP / 1000 * 393;
		if (mHP == 1000)DrawRectGraph(Parameter::WINDOW_WIDTH - 153 - (int)pos, 58, 393 - (int)pos, 0, 393, 40, mGraphBar[0], true, false);
		else DrawRectGraph(Parameter::WINDOW_WIDTH - 153 - (int)pos, 58, 393 - (int)pos, 0, 393, 40, mGraphBar[1], true, false);

		DrawTurnGraph(Parameter::WINDOW_WIDTH - 600, 0, mGraphGauge, true);
		DrawTurnGraph(Parameter::WINDOW_WIDTH - 200, 0, mGraphFace, true);

		DrawFormatStringToHandle(1010, 5, Parameter::COLOR_WHITE, Parameter::FONT_20_FERRUM, "%s", mName.c_str());

		DrawDegitNumber(1000, 113, mHP);
	}
}

/*数値の描画*/
void HPGauge::DrawDegitNumber(int x, int y, int value) {
	if (value >= 1000) {
		DrawGraph(x, y, mGraphNumber[1], true);
		DrawGraph(x + 16, y, mGraphNumber[0], true);
		DrawGraph(x + 32, y, mGraphNumber[0], true);
		DrawGraph(x + 48, y, mGraphNumber[0], true);
	}
	else if (value >= 100) {
		DrawGraph(x, y, mGraphNumber[10], true);
		DrawGraph(x + 16, y, mGraphNumber[value / 100], true);
		DrawGraph(x + 32, y, mGraphNumber[value % 100 / 10], true);
		DrawGraph(x + 48, y, mGraphNumber[value % 10], true);
	}
	else if (value >= 10) {
		DrawGraph(x, y, mGraphNumber[10], true);
		DrawGraph(x + 16, y, mGraphNumber[10], true);
		DrawGraph(x + 32, y, mGraphNumber[value / 10], true);
		DrawGraph(x + 48, y, mGraphNumber[value % 10], true);
	}
	else if (value > 0) {
		DrawGraph(x, y, mGraphNumber[10], true);
		DrawGraph(x + 16, y, mGraphNumber[10], true);
		DrawGraph(x + 32, y, mGraphNumber[10], true);
		DrawGraph(x + 64, y, mGraphNumber[value], true);
	}
	else DrawGraph(x + 42, y, mGraphNumber[0], true);
}