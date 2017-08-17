#pragma once
#include "../Player/Player.h"

/*
背景の描画をするクラス
*/
class BackGround {
public:
	static  BackGround& get(void) {
		static BackGround background;
		return background;
	}
	BackGround(const  BackGround&) = delete;
	BackGround& operator = (const  BackGround&) = delete;
	BackGround(BackGround&&) = delete;
	BackGround operator = (BackGround&&) = delete;

	inline void setBlackCounter(int p, int n) { mBlackoutCounter[p] = n; }
	void LoadGraphic();
	void Process(Player& player1, Player& player2);
	void Draw();

private:
	BackGround() { mBlackoutCounter[0] = 0; mBlackoutCounter[1] = 0; }
	~BackGround(){}

private: 
	int mGraphHandle[3];		//背景のグラフィックハンドル
	int mGraphEmblem[10];		//召喚時エンブレム
	int mBlackoutCounter[2];	//暗転カウンター
	int mEmblemId[2];			//エンブレムID
	int mX[2];					//プレイヤーのX座標
};