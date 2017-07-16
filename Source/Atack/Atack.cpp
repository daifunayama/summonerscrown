#include "Atack.h"

/*攻撃用の初期化*/
void Atack::InitAtack() {
	mCounter = 0;
	mAtackHit = false;
}

/*カウンターを進める*/
void Atack::IncreaseCounter() {
	mCounter++;
}

/*攻撃の終わりをチェック*/
bool Atack::CheckAtackEnd() {
	if (mCounter >= mFrameData.size()){
		return true;
	}
	return false;
}

/*フレームデータをプッシュする*/
void Atack::PushFrameData(FrameData frameData) {
	mFrameData.push_back(frameData);
}

/*フレームデータをクリアする*/
void Atack::ClearFrameData() {
	mFrameData.clear();
}