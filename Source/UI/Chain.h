#pragma once
#include "../Player/Player.h"

/*
チェーンの管理・制御を行うクラス
*/
class Chain {
public:
	void setPlayerId(int id) { mPlayerId = id; }
	void Load();
	void Process(Player&);
	void Draw();

private:
	int mPlayerId;				//プレイヤーID
	int mGraphNumber[10];		//数字のグラフィックハンドル
	int mChain;					//チェーン数
	int mChainCounter;			//チェーンの描画用カウンター
};