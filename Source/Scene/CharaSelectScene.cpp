#include "CharaSelectScene.h"
#include "../Application.h"
#include "../Input/Input.h"
#include "../Effekseer/AnimationController.h"
#include "../Utility.h"
#include "../Player/Character/Ein.h"
#include "../Player/Character/Ria.h"
#include "../Player/Character/Kureha.h"
#include "../Player/Character/Remnant.h"
#include "../Player/Character/Carol.h"
#include "../Player/Character/Random.h"

void CharaSelectScene::Load() {

	mGraphBackground = LoadGraph("Data/graphic/charaselect/background.png");
	mGraphAnime1 = LoadGraph("Data/graphic/charaselect/l.png");

	mGraphShadow = LoadGraph("Data/graphic/game/shadow.png");

	mGraphCursor[0] = LoadGraph("Data/graphic/charaselect/frame_1p.png");
	mGraphCursor[1] = LoadGraph("Data/graphic/charaselect/frame_2p.png");
	mGraphCursor2[0] = LoadGraph("Data/graphic/charaselect/frame_1p_2.png");
	mGraphCursor2[1] = LoadGraph("Data/graphic/charaselect/frame_2p_2.png");

	for (int i = 0; i < 11; i++) {
		mGraphFace[i] = LoadGraph("Data/graphic/charaselect/frame_new.png");
		mGraphStand[i] = LoadGraph("Data/graphic/charaselect/frame2.png");
	}

	mGraphFace[0] = LoadGraph("Data/graphic/charaselect/face_ein.png");
	mGraphFace[1] = LoadGraph("Data/graphic/charaselect/face_ria.png");
	mGraphFace[2] = LoadGraph("Data/graphic/charaselect/face_kureha.png");
	mGraphFace[3] = LoadGraph("Data/graphic/charaselect/face_annie.png");

	mGraphFace[5] = LoadGraph("Data/graphic/charaselect/face_random.png");

	mGraphFace[7] = LoadGraph("Data/graphic/charaselect/face_akane.png");
	mGraphFace[8] = LoadGraph("Data/graphic/charaselect/face_remnant.png");
	mGraphFace[9] = LoadGraph("Data/graphic/charaselect/face_carol.png");


	mGraphStand[0] = LoadGraph("Data/graphic/charaselect/frame_ein.png");
	mGraphStand[1] = LoadGraph("Data/graphic/charaselect/frame_ria.png");
	mGraphStand[2] = LoadGraph("Data/graphic/charaselect/frame_kureha.png");
	mGraphStand[3] = LoadGraph("Data/graphic/charaselect/frame_annie.png");

	mGraphStand[7] = LoadGraph("Data/graphic/charaselect/frame_akane.png");
	mGraphStand[8] = LoadGraph("Data/graphic/charaselect/frame_remnant.png");
	mGraphStand[9] = LoadGraph("Data/graphic/charaselect/frame_carol.png");

	mGraphEmblem[0] = LoadGraph("Data/graphic/emblem/PrimalSpheres.png");
	mGraphEmblem[1] = LoadGraph("Data/graphic/emblem/Comander.png");
	mGraphEmblem[2] = LoadGraph("Data/graphic/emblem/Yoto.png");
	mGraphEmblem[3] = LoadGraph("Data/graphic/emblem/MasouGakudan.png");

	mGraphEmblem[7] = LoadGraph("Data/graphic/emblem/ArticArts.png");
	//mGraphEmblem[8] = LoadGraph("Data/graphic/emblem/Comander.png");
	mGraphEmblem[9] = LoadGraph("Data/graphic/emblem/EvilAnima.png");

	mSoundCursor = LoadSoundMem("Data/se/sen_ge_pis_kamaeru02.mp3");
	mSoundMetal = LoadSoundMem("Data/se/gun-reload1.mp3");
	mSoundEnter = LoadSoundMem("Data/se/decision16.mp3");
	mSoundCancel = LoadSoundMem("Data/se/cancel5.mp3");
	mBGM = LoadSoundMem("Data/bgm/nobasita.mp3");
	ChangeVolumeSoundMem(128, mSoundCancel);
	ChangeVolumeSoundMem(128, mBGM);

	mController[0].SetPlayerId(0);
	mController[1].SetPlayerId(1);

	mCounter = 0;
	mAnimeCounter[0] = 0;
	mAnimeCounter[1] = 0;

	mCursor[0] = 2;
	mCursor[1] = 8;

	mDecided[0] = 0;
	mDecided[1] = 0;

	mColor[0] = 1;
	mColor[1] = 1;

	mSprite[0] = ss::Player::create();
	mSprite[1] = ss::Player::create();

	ChangePlayerSprite(0, mCursor[0]);
	ChangePlayerSprite(1, mCursor[1]);

	PlaySoundMem(mBGM, DX_PLAYTYPE_LOOP);

	AnimationController::getInstance().Create(mGraphAnime1, 1, 0, 350, 1024, 620, 1.25, 0, 4, 4, 204, 204, 0, 0);
}

void CharaSelectScene::Process() {

	if (mController[0].getKey(9) == 1) {
		Application::mNextSceneId = Parameter::SCENE_BATTLE;
		StopSoundMem(mBGM);
	}

	for (int p = 0; p < 2; p++) {
		mController[p].ConvertInput();

		if (mController[p].getRight() == 1 && !mDecided[p]) {
			if (mCursor[p] < 10) {
				mColor[p] = 1;
				mCursor[p]++;
				ChangePlayerSprite(p, mCursor[p]);
				mAnimeCounter[p] = 0;
				PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
			}
		}

		if(mController[p].getLeft() == 1 && !mDecided[p]) {
			if (mCursor[p] > 0) {
				mColor[p] = 1;
				mCursor[p]--;
				ChangePlayerSprite(p, mCursor[p]);
				mAnimeCounter[p] = 0;
				PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
			}
		}

		if (mCursor[p] == 0) {
			if (mController[p].getUp() == 1 && !mDecided[p]) {
				if (mColor[p] > 1) {
					mColor[p]--;
					ChangePlayerSprite(p, mCursor[p]);
					PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
				}
			}

			if (mController[p].getDown() == 1 && !mDecided[p]) {
				if (mColor[p] < 2) {
					mColor[p]++;
					ChangePlayerSprite(p, mCursor[p]);
					PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
				}
			}
		}

		if (mController[p].getKey(3) == 1) {
			if (!mDecided[p]) {
				mDecided[p] = true;
				PlaySoundMem(mSoundEnter, DX_PLAYTYPE_BACK);
			}
		}

		if (mController[p].getKey(4) == 1) {
			if (mDecided[p]) {
				mDecided[p] = false;
				PlaySoundMem(mSoundCancel, DX_PLAYTYPE_BACK);
			}
		}
	}

	mSprite[0]->update((float)30 / 1000);
	mSprite[1]->update((float)30 / 1000);

	//アニメーションのプロセス
	AnimationController::getInstance().Process();

	mCounter++;
	mAnimeCounter[0]++;
	mAnimeCounter[1]++;
}

void CharaSelectScene::ChangePlayerSprite(int p, int id) {
	if (id == 0 || id == 1 || id == 2 || id == 5 || id == 8 || id == 9) {

		//プレイヤーの再作成
		switch (id) {
		case 0: 
			mPlayer[p] = new Ein();
			break;
		case 1:
			mPlayer[p] = new Ria();
			break;
		case 2:
			mPlayer[p] = new Kureha();
			break;
		case 5:
			mPlayer[p] = new Random();
			break;
		case 8:
			mPlayer[p] = new Remnant();
			break;
		case 9:
			mPlayer[p] = new Carol();
			break;
		default:
			mPlayer[p] = new Ein();
			break;
		}

		if (id != 5) {
			mSprite[p]->setData(mPlayer[p]->getProfile().pass);
			mSprite[p]->play(mPlayer[p]->getProfile().pass + Utility::IntToString(mColor[p]) + "/idle");

			Profile pf = mPlayer[p]->getProfile();
			mSprite[p]->setStep(pf.speed);

			if (p == 0) {
				mSprite[p]->setPosition(150 + pf.distX, 230 + pf.distY);
				mSprite[p]->setScale(pf.size, pf.size);
			}
			else {
				mSprite[p]->setPosition(Parameter::WINDOW_WIDTH - 150 - pf.distX, 230 + pf.distY);
				mSprite[p]->setScale(-pf.size, pf.size);
			}
		}
	}
}

void CharaSelectScene::Drawing() {
	DrawGraph(0, 0, mGraphBackground, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//アニメーションの描画
	AnimationController::getInstance().DrawLayer1();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (CheckHitKey(KEY_INPUT_R) == 1)mCounter = 0;

	//立ち絵
	if (mCounter == 90) {
		mAnimeCounter[0] = 0;
		mAnimeCounter[1] = 0;
	}
	if (mCounter > 90) {
		mAnimeCounter[0] < 10 ?
			DrawGraph(-600 + mAnimeCounter[0] * 60, 0, mGraphStand[mCursor[0]], true):
			DrawGraph(0, 0, mGraphStand[mCursor[0]], true);

		mAnimeCounter[1] < 10 ?
			DrawTurnGraph(Parameter::WINDOW_WIDTH - 500 + 600 - mAnimeCounter[1] * 60, 0, mGraphStand[mCursor[1]], true):
			DrawTurnGraph(Parameter::WINDOW_WIDTH - 500, 0, mGraphStand[mCursor[1]], true);
	}

	//顔グラ
	if (mCounter < 90) {
		for (int i = 0; i < 11; i++) {
			if (i < 6)mCounter < (30 + i * 10) ?
				DrawGraph(340 + 55 * (5 - i) - (1200 + i * 400) + (mCounter * 40), 200, mGraphFace[5 - i], true) :
				DrawGraph(340 + 55 * (5 - i), 200, mGraphFace[5 - i], true);
			else mCounter < (35 + (i-6) * 10) ?
				DrawGraph(340 + 55 * i + 1400 + (i - 6) * 400 - (mCounter * 40), 200, mGraphFace[i], true) :
				DrawGraph(340 + 55 * i, 200, mGraphFace[i], true);
		}
		if (mCounter >= 30 && mCounter <= 65 && mCounter % 5 == 0)PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
	}
	else {
		if (mCounter == 90)PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
		for (int i = 0; i < 11; i++)DrawGraph(340 + i * 55, 180 + 40 * (i % 2), mGraphFace[i], true);
	}

	//カーソル
	if (mCounter > 65) {
		if (mCounter < 90) {
			DrawGraph(340 + mCursor[1] * 55, 180 + 1000 - (mCounter - 65) * 40, mGraphCursor[1], true);
			DrawGraph(340 + mCursor[0] * 55, 180 - 1000 + (mCounter - 65) * 40, mGraphCursor[0], true);
		}
		else {
			if (!mDecided[1])DrawGraph(340 + mCursor[1] * 55, 180 + 40 * (mCursor[1] % 2), mGraphCursor[1], true);
			else DrawGraph(340 + mCursor[1] * 55, 180 + 40 * (mCursor[1] % 2), mGraphCursor2[1], true);
			if (!mDecided[0])DrawGraph(340 + mCursor[0] * 55, 180 + 40 * (mCursor[0] % 2), mGraphCursor[0], true);
			else DrawGraph(340 + mCursor[0] * 55, 180 + 40 * (mCursor[0] % 2), mGraphCursor2[0], true);
		}
	}
	
	if (mCounter > 90) {
		//エンブレム
		DrawRotaEmblem(mCursor[0], -30, 350);
		DrawRotaEmblem(mCursor[1], Parameter::WINDOW_WIDTH - 300 + 30, 350);

		//キャラの影
		DrawGraph(90, 640, mGraphShadow, true);
		DrawGraph(Parameter::WINDOW_WIDTH - 210, 640, mGraphShadow, true);

		//キャラスプライト
		if (mCursor[0] != 5)mSprite[0]->draw();
		if (mCursor[1] != 5)mSprite[1]->draw();

		//P1キャラクター名
		Profile p = mPlayer[0]->getProfile();
		if (mAnimeCounter[0] < 10) {
			DrawFormatStringToHandle(50, 640 + 100 - mAnimeCounter[0] * 10, Parameter::COLOR_WHITE, Parameter::FONT_80_FERRUM,
				"%s", p.eName.c_str());
			DrawFormatStringToHandle(60, 700 + 100 - mAnimeCounter[0] * 10, Parameter::COLOR_WHITE, Parameter::FONT_20,
				"%s", p.name.c_str());
		}
		else {
			DrawFormatStringToHandle(50, 640, Parameter::COLOR_WHITE, Parameter::FONT_80_FERRUM,
				"%s", p.eName.c_str());
			DrawFormatStringToHandle(60, 700, Parameter::COLOR_WHITE, Parameter::FONT_20,
				"%s", p.name.c_str());
		}
		//キャラプロファイル
		DrawProfile(0,p, 230, 500);

		//P2キャラクター名
		p = mPlayer[1]->getProfile();

		if (mAnimeCounter[1] < 10) {
			DrawFormatStringToHandle(Parameter::WINDOW_WIDTH - p.eName.length() * 30 - 30, 640 + 100 - mAnimeCounter[1] * 10, Parameter::COLOR_WHITE,
				Parameter::FONT_80_FERRUM, "%s", p.eName.c_str());
			DrawFormatStringToHandle(Parameter::WINDOW_WIDTH - p.eName.length() * 30 - 20, 700 + 100- mAnimeCounter[1] * 10, Parameter::COLOR_WHITE,
				Parameter::FONT_20, "%s", p.name.c_str());
		}
		else {
			DrawFormatStringToHandle(Parameter::WINDOW_WIDTH - p.eName.length() * 30 - 30, 640, Parameter::COLOR_WHITE,
				Parameter::FONT_80_FERRUM, "%s", p.eName.c_str());
			DrawFormatStringToHandle(Parameter::WINDOW_WIDTH - p.eName.length() * 30 - 20, 700, Parameter::COLOR_WHITE,
				Parameter::FONT_20, "%s", p.name.c_str());
		}

		//キャラプロファイル
		DrawProfile(1,p, 800, 500);
	}

	DrawStringToHandle(330, 30, "Character Select", Parameter::COLOR_YELLOW, Parameter::FONT_100_CLOISTER, 0, 0);
	DrawStringToHandle(490, 130, "キャラクターを選択してください", Parameter::COLOR_YELLOW, Parameter::FONT_20, 0, 0);

	//DrawStringToHandle(500, 530, "←→　キャラクター選択", Parameter::COLOR_YELLOW, Parameter::FONT_20, 0, 0);
	//DrawStringToHandle(500, 560, "↑↓　カラー選択", Parameter::COLOR_YELLOW, Parameter::FONT_20, 0, 0);
}

void CharaSelectScene::DrawRotaEmblem(int category, int x, int y) {
	static int animationCounter = 150;

	animationCounter++;
	if (animationCounter > 300)animationCounter = 0;

	if (animationCounter < 150) {
		DrawModiGraph(x + animationCounter,y, x + 300 - animationCounter, y,
			x + 300 - animationCounter, y+300, x + animationCounter, y+300, mGraphEmblem[category], true);
	
	}
	else {
		DrawModiGraph(x + 300 - (animationCounter ), y, x + (animationCounter), y,
			x + (animationCounter), y+300, x + 300 - (animationCounter), y+300, mGraphEmblem[category], true);
	}
}

void CharaSelectScene::DrawProfile(int p, Profile pf, int x, int y) {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(x - 10, y - 10, x + 250, y + 150, Parameter::COLOR_BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawStringToHandle(x, y, "Close-Range", Parameter::COLOR_WHITE, Parameter::FONT_20, 0, 0);
	DrawStringToHandle(x, y + 30, "Long-Range", Parameter::COLOR_WHITE, Parameter::FONT_20, 0, 0);
	DrawStringToHandle(x, y + 60, "Automaton", Parameter::COLOR_WHITE, Parameter::FONT_20, 0, 0);
	DrawStringToHandle(x, y + 90, "Physical", Parameter::COLOR_WHITE, Parameter::FONT_20, 0, 0);
	DrawStringToHandle(x, y + 120, "Special", Parameter::COLOR_WHITE, Parameter::FONT_20, 0, 0);

	if (mAnimeCounter[p] < pf.cAtack * 5)DrawBox(x + 130, y, x + 130 + mAnimeCounter[p] * 4, y + 20, Parameter::COLOR_RED, true);
	else DrawBox(x + 130, y, x + 130 + pf.cAtack * 20, y + 20, Parameter::COLOR_RED, true);

	if (mAnimeCounter[p] < pf.lAtack * 5)DrawBox(x + 130, y+30, x + 130 + mAnimeCounter[p] * 4, y + 50, Parameter::COLOR_RED, true);
	else DrawBox(x + 130, y+30, x + 130 + pf.lAtack * 20, y + 50, Parameter::COLOR_RED, true);

	if (mAnimeCounter[p] < pf.aut * 5)DrawBox(x + 130, y+60, x + 130 + mAnimeCounter[p] * 4, y + 80, Parameter::COLOR_RED, true);
	else DrawBox(x + 130, y+60, x + 130 + pf.aut * 20, y + 80, Parameter::COLOR_RED, true);

	if (mAnimeCounter[p] < pf.pAtack * 5)DrawBox(x + 130, y+90, x + 130 + mAnimeCounter[p] * 4, y + 110, Parameter::COLOR_RED, true);
	else DrawBox(x + 130, y+90, x + 130 + pf.pAtack * 20, y + 110, Parameter::COLOR_RED, true);

	if (mAnimeCounter[p] < pf.sAtack * 5)DrawBox(x + 130, y+120, x + 130 + mAnimeCounter[p] * 4, y + 140, Parameter::COLOR_RED, true);
	else DrawBox(x + 130, y+120, x + 130 + pf.sAtack * 20, y + 140, Parameter::COLOR_RED, true);
}