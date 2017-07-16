#include "EXGauge.h"
#include "../Parameter.h"
#include "DxLib.h"

/*ロード*/
void EXGauge::Load() {
	mGraphGauge = LoadGraph("Data/graphic/ui/exgauge.png");

	if (mPlayerId == 0) {
		mGraphBar = LoadGraph("Data/graphic/ui/exgauge2.png");
	
	}
	else {
		mGraphBar = LoadGraph("Data/graphic/ui/exgauge2-2.png");
	}
}

/*更新*/
void EXGauge::Process(Player& player) {
	mEX = player.getEX();
}

/*描画*/
void EXGauge::Draw() {
	double pos;

	if (mPlayerId == 0) {
		pos = (double)mEX * 4;

		DrawRectGraph(56, 686, 0, 0, (int)pos, 31, mGraphBar, true, false);
		DrawGraph(50, 680, mGraphGauge, true);
	}
	else {
		pos = (double)mEX * 4;

		DrawRectGraph(Parameter::WINDOW_WIDTH - 56 - (int)pos, 686, 400 - (int)pos, 0, 400, 31, mGraphBar, true, false);
		DrawTurnGraph(Parameter::WINDOW_WIDTH - 413 - 50, 680, mGraphGauge, true);
	}
}