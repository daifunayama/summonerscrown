#pragma once
#include "Scene.h"
#include "../Parameter.h"
#include "../SSPlayer/SS5Player.h"
#include "../Input/Controller.h"

/*
戦闘前アイキャッチのシーンクラス
*/
class Player;

class EyecatchScene : public Scene {
public:
	EyecatchScene() :Scene(Parameter::SCENE_TITLE) {
		Load();
	}

	void Load();
	void Process();
	void Drawing();

private:
	struct CharaGraph {
		int positionX;
		int positionY;
		int graph;
	};

	Controller mController;
	int mCounter;
	int mBright;
	CharaGraph mCharaGraph[2];
	Player *mPlayer[2];
	int mNameX[2];

	ss::Player *mSprite;		//ロゴアニメーション用スプライト
	int mGraphBackground;		//背景
	int mGraphAnime1;			//背景アニメ
	int mSoundEnter;			//決定SE
	int mBGM;					//BGM
};

