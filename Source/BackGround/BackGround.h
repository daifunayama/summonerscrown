#pragma once
#include "../Player/Player.h"

/*
背景の描画をするクラス
*/
class BackGround {
public:
	inline void setBlackCounter(int p, int n) { mBlackoutCounter[p] = n; }
	void LoadGraphic();
	void GetPlayer(Player&, Player&);
	void Draw();

	BackGround() { mBlackoutCounter[0] = 0; mBlackoutCounter[1] = 0; }
	~BackGround(){}

private: 
	int mGraphHandle[3];		//背景のグラフィックハンドル
	int mGraphEmblem[10];		//召喚時エンブレム
	int mBlackoutCounter[2];	//暗転カウンター
	int mEmblemId[2];			//エンブレムID
	int mX[2];					//プレイヤーのX座標
};