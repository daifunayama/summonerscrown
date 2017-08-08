#pragma once
#include "Scene.h"
#include "../Parameter.h"
#include "../SSPlayer/SS5Player.h"
#include "../Player/Player.h"
#include "../UI/ContractCircle.h"

/*
契約シーンクラス
*/
class ContractScene : public Scene {
public:
	ContractScene() :Scene(Parameter::SCENE_CONTRACT) {
		Load();
	}

	void Load();
	void LoadCategoryList(int p, int category);
	void LoadArmsProfile(int p,int category, int id);
	void Process();
	void MoveCircleCursor(int p);
	void ChangeArmsSprite(int p);

	void Drawing();
	void DrawCategoryList(int p, int x, int y);
	void DrawProfile(int p, int x, int y);

private:
	struct ArmsProfile {
		bool exist;
		string name;
		string sName;
		string condition;
		string explain[5];
		int type;
		int rank;
	};

	struct CategoryList {
		string name;
		string sName;
		ArmsProfile armslist[10];
	};

private:
	Controller mController[2];		//入力制御用コントローラー

	int mCounter;					//汎用カウンター
	int mCursor[2];					//カーソル位置
	int mCategoryCursor[2];
	int mArmsCursor[2];
	int mDecided[2];				//決定フラグ
	bool mSwitch[2];				//表示フラグ

	int mGraphBackground;			//背景のグラフィックハンドル
	int mGraphCursor;				//カーソルのグラフィックハンドル
	int mGraphCursor2;				//カーソルのグラフィックハンドル2
	int mGraphEmblem[11];			//エンブレムのグラフィックハンドル
	int mGraphAnime1;				//背景アニメのグラフィックハンドル
	Player* mPlayer[2];				//プレイヤー
	ss::Player* mSprite[2];			//スプライト
	ArmsProfile mProfile[2];		//武器のプロファイル
	ContractCircle mCircle[2];		//契約陣
	CategoryList mCategorylist[2];
	Arms *mArms[2];

	int mSoundCursor;				//カーソル移動のサウンドハンドル
	int mSoundEnter;				//決定SE
	int mSoundCancel;				//キャンセルSE
	int mBGM;						//BGMのサウンドハンドル

};