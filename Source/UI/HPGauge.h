#pragma once
#include "../Player/Player.h"

/*
HPゲージの制御を行うクラス
*/

class HPGauge {
public:
	void setPlayerId(int id) { mPlayerId = id; }
	void Load(Player&);
	void Process(Player&, Player&);
	void Draw();
	void DrawDegitNumber(int x, int y, int value);

private:
	int mPlayerId;			//プレイヤーID
	string mName;			//キャラ名
	int mGraphGauge;		//ゲージのグラフィックハンドル
	int mGraphFace;			//キャラフェイスのグラフィックハンドル	
	int mGraphBar[3];		//メータのグラフィックハンドル
	int mGraphNumber[10];	//数値のグラフィックハンドル
	int mHP;				//HP(0~1000)
	int mRedzone;			//レッドゾーン
	bool mKeepRedzone;		//レッドゾーンの保留フラグ
};