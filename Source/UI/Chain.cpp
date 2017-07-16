#include "Chain.h"
#include "../Parameter.h"
#include "DxLib.h"

/*ロード*/
void Chain::Load() {
	mGraphNumber[0] = LoadGraph("Data/graphic/ui/number/0.png");
	mGraphNumber[1] = LoadGraph("Data/graphic/ui/number/1.png");
	mGraphNumber[2] = LoadGraph("Data/graphic/ui/number/2.png");
	mGraphNumber[3] = LoadGraph("Data/graphic/ui/number/3.png");
	mGraphNumber[4] = LoadGraph("Data/graphic/ui/number/4.png");
	mGraphNumber[5] = LoadGraph("Data/graphic/ui/number/5.png");
	mGraphNumber[6] = LoadGraph("Data/graphic/ui/number/6.png");
	mGraphNumber[7] = LoadGraph("Data/graphic/ui/number/7.png");
	mGraphNumber[8] = LoadGraph("Data/graphic/ui/number/8.png");
	mGraphNumber[9] = LoadGraph("Data/graphic/ui/number/9.png");
}

/*更新*/
void Chain::Process(Player& player) {
	//チェーンが増加していたとき
	if (mChain != player.getChain()) {
		mChain = player.getChain();
		mChainCounter = 15;
	}
	else if(mChain > 0) mChainCounter--;
}

/*描画*/
void Chain::Draw() {
	if (mChainCounter > 0 && mChain > 0) {
		//プレイヤー1
		if (mPlayerId == 0) {
			if (mChain < 10) {
				DrawGraph(90, 100, mGraphNumber[mChain], true);
			}
			else {
				DrawGraph(90, 100, mGraphNumber[mChain % 10], true);
				DrawGraph(20, 100, mGraphNumber[mChain / 10], true);
			}
		}
		//プレイヤー2
		else {
			if (mChain < 10) {
				DrawGraph(950, 100, mGraphNumber[mChain], true);
			}
			else {
				DrawGraph(950, 100, mGraphNumber[mChain % 10], true);
				DrawGraph(880, 100, mGraphNumber[mChain / 10], true);
			}
		}
	}
}