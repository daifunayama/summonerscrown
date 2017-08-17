#pragma once
#include "Scene.h"
#include "../Parameter.h"
#include "../SSPlayer/SS5Player.h"
#include "../Input/Controller.h"

/*
タイトル画面のシーンクラス
*/
class TitleScene : public Scene {
public:
	TitleScene():Scene(Parameter::SCENE_TITLE) {
		Load();
	}

	void Load();
	void Process();
	void Drawing();

private:
	Controller mController;
	int mCounter;
	ss::Player *mSprite;		//ロゴアニメーション用スプライト
	int mGraphAnime1;			//背景アニメ
	int mGraphBack;

	int mSoundEnter;			//決定SE
	int mSE1;
	int mSE2;
	int mSE3;
};