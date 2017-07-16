#pragma once
#include "../Player/Player.h"
#include "../Input/Controller.h"

/*
契約陣の制御を行うクラス
*/
class ContractCircle {
public:
	void setPlayerId(int id) { mPlayerId = id; }
	void Load(Player&);
	void Process(Player&);
	void Draw();

private:
	int mPlayerId;				//プレイヤーID
	int mGraphCircle;			//契約時のグラフィックハンドル
	int mGraphCursor;			//カーソルのグラフィックハンドル
	int mGraphNameBar1;			//魔具名アラートのグラフィックハンドル1
	int mGraphNameBar2;			//魔具名アラートのグラフィックハンドル2
	int mGraphConditionBar1;	//誓約アラートのグラフィックハンドル1
	int mGraphConditionBar2;	//誓約アラートのグラフィックハンドル2
	int mIcon;					//魔具アイコン
	int mIconlist[8];			//魔具のアイコンリスト
	int mAngle;					//契約陣の回転角
	bool mOpenCircle;			//契約陣を開いているかのフラグ
	int mCursor;				//カーソル位置
	string mName;				//魔具名
	string mCondition;			//誓約
	Controller mController;		//入力制御用コントローラー
};