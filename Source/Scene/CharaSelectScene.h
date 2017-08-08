#pragma once
#include "Scene.h"
#include "../Parameter.h"
#include "../SSPlayer/SS5Player.h"
#include "../Player/Player.h"

/*
キャラセレクトシーンクラス
*/
class CharaSelectScene : public Scene {
public:
	CharaSelectScene() :Scene(Parameter::SCENE_TITLE) {
		Load();
	}

	void Load();
	void Process();
	void ChangePlayerSprite(int p,int id);
	void Drawing();
	void DrawProfile(int p,Profile pf, int x, int y);
	void DrawStyles(int p, Styles st, int x, int y);
	void DrawRotaEmblem(int category, int x, int y);

private:
	Controller mController[2];		//入力制御用コントローラー

	int mAnimeCounter[2];			//各プレイヤーのアニメーション用カウンタ
	int mCounter;					//汎用カウンター
	int mCursor[2];					//カーソル位置
	int mColor[2];					//カラーID
	int mDecided[2];				//キャラ決定フラグ
	bool mSwitch[2];				//表示フラグ

	int mGraphBackground;			//背景のグラフィックハンドル
	int mGraphCursor[2];			//カーソルのグラフィックハンドル
	int mGraphCursor2[2];			//カーソルのグラフィックハンドル2
	int mGraphFace[11];				//キャラフェイスのグラフィックハンドル
	int mGraphStand[11];			//キャラ立ち絵のグラフィックハンドル
	int mGraphEmblem[11];			//エンブレムのグラフィックハンドル
	int mGraphAnime1;				//背景アニメのグラフィックハンドル
	int mGraphShadow;				//影のグラフィックハンドル
	Player* mPlayer[2];				//プレイヤー
	ss::Player* mSprite[2];			//プレイヤーのスプライト
	

	int mSoundCursor;				//カーソル移動のサウンドハンドル
	int mSoundMetal;				//ガチャン音
	int mSoundEnter;				//決定SE
	int mSoundCancel;				//キャンセルSE
	int mBGM;						//BGMのサウンドハンドル
};