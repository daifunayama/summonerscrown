#pragma once
#include <windows.h>
#include "Scene.h"
#include "../Player/Player.h"
#include "../BackGround/BackGround.h"
#include "../UI/HPGauge.h"
#include "../UI/EXGauge.h"
#include "../UI/Chain.h"
#include "../UI/ContractCircle.h"
#include "../Parameter.h"

/*
戦闘シーンクラス
戦闘時必要な処理をすべて管理する
*/
class BattleScene : public Scene {
public:
	BattleScene() :Scene(Parameter::SCENE_BATTLE) {
		Load();
	}

	void Load();
	virtual void Process();
	virtual void Drawing();
	virtual int CheckDrawPriority(Player& p1, Player& p2);

private:
	Player* mPlayer[2];						//戦闘プレイヤー
	HPGauge mHPGauge[2];					//HPゲージ
	EXGauge mEXGauge[2];					//EXゲージ
	Chain mChain[2];						//チェーン
	ContractCircle mContractCircle[2];		//契約陣
	BackGround mBackGround;					//背景

	int mBGM;								//BGMのサウンドハンドル
};