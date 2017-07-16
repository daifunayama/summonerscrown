#pragma once
#include "../Player/Player.h"

/*
EXゲージの制御を行うクラス
*/
class EXGauge {
public:
	void setPlayerId(int id) { mPlayerId = id; }
	void Load();
	void Process(Player&);
	void Draw();

private:
	int mPlayerId;		//プレイヤーID
	int mGraphGauge;	//ゲージのグラフィックハンドル
	int mGraphBar;		//メータのグラフィックハンドル
	int mEX;			//EX値(0~100)
};