#include <fstream>
#include "ContractScene.h"
#include "../Application.h"
#include "../Input/Input.h"
#include "../Effekseer/AnimationController.h"
#include "../Utility.h"
#include "../Arms/Category/HollyKnights/Aries.h"
#include "../Arms/ArmsList.h"
#include "../Arms/Category/HollyKnights/Southern.h"
#include "../Arms/Category/ArticArts/Alpha.h"
#include "../Arms/Category/Comander/Cavalier.h"
#include "../Arms/Category/EvilAnima/Enikuma.h"
#include "../Arms/Category/PrimalSpheres/Cyanos.h"
#include "../Player/Character/Ein.h"

/*ロード*/
void ContractScene::Load() {

	mGraphBackground = LoadGraph("Data/graphic/charaselect/background.png");
	mGraphAnime1 = LoadGraph("Data/graphic/charaselect/l.png");

	mGraphEmblem[0] = LoadGraph("Data/graphic/emblem/HollyKnights.png");
	mGraphEmblem[1] = LoadGraph("Data/graphic/emblem/Comander.png");
	mGraphEmblem[2] = LoadGraph("Data/graphic/emblem/MasouGakudan.png");
	mGraphEmblem[3] = LoadGraph("Data/graphic/emblem/Yoto.png");
	mGraphEmblem[4] = LoadGraph("Data/graphic/emblem/Totures.png");
	mGraphEmblem[5] = LoadGraph("Data/graphic/emblem/EvilAnima.png");
	mGraphEmblem[6] = LoadGraph("Data/graphic/emblem/ArticArts.png");
	mGraphEmblem[9] = LoadGraph("Data/graphic/emblem/PrimalSpheres.png");

	mSoundCursor = LoadSoundMem("Data/se/sen_ge_pis_kamaeru02.mp3");
	mSoundEnter = LoadSoundMem("Data/se/decision16.mp3");
	mSoundCancel = LoadSoundMem("Data/se/cancel5.mp3");
	mBGM = LoadSoundMem("Data/bgm/nobasita.mp3");
	ChangeVolumeSoundMem(128, mSoundCancel);
	ChangeVolumeSoundMem(128, mBGM);

	mController[0].SetPlayerId(0);
	mController[1].SetPlayerId(1);

	mCounter = 0;

	for (int p = 0; p < 2; p++) {
		mPlayer[p] = new Ein();
		mPlayer[p]->setPlayerId(p);

		mCursor[p] = 0;
		mArmsCursor[p] = 0;
		mCategoryCursor[p] = 0;
		mDecided[p] = 0;
		mSwitch[p] = 0;
		mSprite[p] = ss::Player::create();

		for (int i = 0; i < 8; i++)mPlayer[p]->setArmsExist(i, false);

		mCircle[p].setPlayerId(p);
		mCircle[p].Load(*mPlayer[p]);
	}

	PlaySoundMem(mBGM, DX_PLAYTYPE_LOOP);

	LoadCategoryList(0, 0);
	LoadArmsProfile(0, Parameter::HK, 0);
	
	ChangeArmsSprite(0);
	mSprite[0]->setPosition(400, 400);
	mSprite[0]->setScale(0.5f,0.5f);

	AnimationController::getInstance().Create(mGraphAnime1, 1, 640, 350, 1024, 620, 1.25, 0, 4, 4, 204, 204, 0, 0);
}

/*更新*/
void ContractScene::Process() {

	if (mController[0].getKey(9) == 1) {
		Application::mNextSceneId = Parameter::SCENE_EYECATCH;
		StopSoundMem(mBGM);
	}

	for (int p = 0; p < 2; p++) {

		mController[p].ConvertInput();

		//契約陣モード
		if (!mSwitch[p]) {
			MoveCircleCursor(p);

			if (mController[p].getKey(3) == 1) {
				mSwitch[p] = true;
				PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
			}

			mCircle[p].ProcessInContract(mCursor[p]);
		}

		//選択モード
		else {
			if (mController[p].getRight() == 1) {
				if (mCategoryCursor[p] < 10) {
					mCategoryCursor[p]++;
					mArmsCursor[p] = 0;
					LoadCategoryList(p, mCategoryCursor[p]);
					LoadArmsProfile(p, mCategoryCursor[p], mArmsCursor[p]);
					PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
				}
			}

			if (mController[p].getLeft() == 1) {
				if (mCategoryCursor[p] > 0) {
					mCategoryCursor[p]--;
					mArmsCursor[p] = 0;
					LoadCategoryList(p, mCategoryCursor[p]);
					LoadArmsProfile(p, mCategoryCursor[p], mArmsCursor[p]);
					PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
				}
			}


			if (mController[p].getUp() == 1) {
				if (mArmsCursor[p] > 0) {
					mArmsCursor[p]--;
					LoadArmsProfile(p,mCategoryCursor[p],mArmsCursor[p]);
					PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
				}
			}

			if (mController[p].getDown() == 1) {
				if (mArmsCursor[p] < 10) {
					mArmsCursor[p]++;
					LoadArmsProfile(p, mCategoryCursor[p], mArmsCursor[p]);
					PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
				}
			}


			if (mController[p].getKey(3) == 1) {
				mSwitch[p] = false;
				PlaySoundMem(mSoundEnter, DX_PLAYTYPE_BACK);
			}

			if (mController[p].getKey(4) == 1) {
				if (mDecided[p]) {
					mDecided[p] = false;
					PlaySoundMem(mSoundCancel, DX_PLAYTYPE_BACK);
				}
			}

			if (mController[p].getKey(1) == 1) {
				mSwitch[p] = !mSwitch[p];
				PlaySoundMem(mSoundCursor, DX_PLAYTYPE_BACK);
			}
		}
	}

	//アニメーションのプロセス
	AnimationController::getInstance().Process();

	mSprite[0]->update((float)30 / 1000);

	mCounter++;
}

/*カーソル移動*/
void ContractScene::MoveCircleCursor(int p) {
	if (mController[p].getUp() && !mController[p].getRight() && !mController[p].getLeft())mCursor[p] = 0;
	if (mController[p].getUp() && mController[p].getRight())mCursor[p] = 1;
	if (!mController[p].getUp() && mController[p].getRight() && !mController[p].getDown())mCursor[p] = 2;
	if (mController[p].getRight() && mController[p].getDown())mCursor[p] = 3;
	if (!mController[p].getRight() && mController[p].getDown() && !mController[p].getLeft())mCursor[p] = 4;
	if (mController[p].getDown() && mController[p].getLeft())mCursor[p] = 5;
	if (!mController[p].getDown() && mController[p].getLeft() && !mController[p].getUp())mCursor[p] = 6;
	if (mController[p].getLeft() && mController[p].getUp())mCursor[p] = 7;
}

/*カテゴリーリストのロード*/
void ContractScene::LoadCategoryList(int p, int category) {
	ifstream ifs,ifs2;
	string pass,pass2;

	pass = ArmsList::get().getCategoryPass(category) + "category.txt";
	ifs.open(pass.c_str());
	
	if (ifs) {
		ifs >> mCategorylist[p].sName;
		ifs >> mCategorylist[p].name;
	}
	ifs.close();

	for (int i = 0; i < 10; i++) {
		ifs2.clear();
		pass2.clear();

		mCategorylist[p].armslist[i].name.clear();

		pass2 = ArmsList::get().getArmsPass(category, i) + "profile.txt";
		ifs2.open(pass2.c_str());

		if (ifs2) {
			mCategorylist[p].armslist[i].exist = true;
			ifs2 >> mCategorylist[p].armslist[i].sName;
			ifs2 >> mCategorylist[p].armslist[i].name;
			ifs2 >> mCategorylist[p].armslist[i].type;
			ifs2 >> mCategorylist[p].armslist[i].rank;
		}
		else mCategorylist[p].armslist[i].exist = false;

		ifs2.close();
	}
}

/*魔具プロファイルのロード*/
void ContractScene::LoadArmsProfile(int p,int category, int id) {
	ifstream ifs;
	string pass;

	pass = ArmsList::get().getArmsPass(category, id) + "profile.txt";

	ifs.open(pass.c_str());
	if (ifs) {
		ifs >> mProfile[p].sName;
		ifs >> mProfile[p].name;
		ifs >> mProfile[p].type;
		ifs >> mProfile[p].rank;

		ifs >> mProfile[p].condition;

		for (int i = 0; i < 5; i++)mProfile[p].explain[i].clear();

		for (int i = 0; i < 5 && !ifs.eof(); i++) {
			ifs >> mProfile[p].explain[i];
		}

		mProfile[p].exist = true;
	}
	else mProfile[p].exist = false;

	ifs.close();

	ChangeArmsSprite(p);
}

/*魔具の表示スプライトの変更*/
void ContractScene::ChangeArmsSprite(int p) {
	switch (mCategoryCursor[p]) {
	case Parameter::HK:
		mArms[p] = new Aries();
		mSprite[p]->setData("Aries");
		break;

	case Parameter::PS:
		mArms[p] = new Cyanos();
		mSprite[p]->setData("Cyanos");
		break;
	
	case Parameter::CM:
		mArms[p] = new Cavalier();
		mSprite[p]->setData("cavalier");
		break;

	case Parameter::EA:
		mArms[p] = new Enikuma();
		mSprite[p]->setData("Enikuma");
		break;

	case Parameter::AA:
		mArms[p] = new Alpha();
		mSprite[p]->setData("alpha");
		break;

	default:
		mArms[p] = new Southern();
		mSprite[p]->setData("Southern");
		break;
	}

	mSprite[p]->play("arms/wait");
	mSprite[p]->setScale(mArms[p]->getProfile().size, mArms[p]->getProfile().size);
	mSprite[p]->setStep(mArms[p]->getProfile().speed);
}

/*描画*/
void ContractScene::Drawing() {
	DrawGraph(0, 0, mGraphBackground, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//アニメーションの描画
	AnimationController::getInstance().Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (CheckHitKey(KEY_INPUT_R) == 1)mCounter = 0;

	mSprite[0]->draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawRotaGraph(200, 600, 0.5, 0, mGraphEmblem[mCategoryCursor[0]], true, false);
	DrawRotaGraph(Parameter::WINDOW_WIDTH-200, 600, 0.5, 0, mGraphEmblem[mCategoryCursor[1]], true, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int p = 0; p < 2; p++) {
		if (mSwitch[p])SetDrawBright(100, 100, 100);
		mCircle[p].DrawInContract();
		if (mSwitch[p])SetDrawBright(255,255,255);

		if (p == 0) {
			DrawProfile(p, 50, 300);
			DrawCategoryList(p, 50, 450);
		}
	}

	DrawStringToHandle(460, 30, "Contract", Parameter::COLOR_YELLOW, Parameter::FONT_100_FERRUM, 0, 0);
	DrawStringToHandle(490, 130, "魔具と契約を交わしてください", Parameter::COLOR_YELLOW, Parameter::FONT_20, 0, 0);
}

/*カテゴリーリストの描画*/
void ContractScene::DrawCategoryList(int p, int x, int y) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(x - 10, y - 10, x + 300, y + 600, Parameter::COLOR_BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	if(mCategorylist[p].sName != "none")
		DrawFormatStringToHandle(x+20, y, Parameter::COLOR_WHITE, Parameter::FONT_10, "%s", mCategorylist[p].sName.c_str());
	DrawFormatStringToHandle(x, y + 10, Parameter::COLOR_WHITE, Parameter::FONT_20, "〔%s〕", mCategorylist[p].name.c_str());

	for (int i = 0; i < 10; i++) {
		if (mCategorylist[p].armslist[i].exist) {
			DrawFormatStringToHandle(x, y + 40 + i * 25, Parameter::COLOR_WHITE, Parameter::FONT_20, "%s", mCategorylist[p].armslist[i].name.c_str());
			DrawFormatStringToHandle(x + 300, y + 40 + i * 25, Parameter::COLOR_WHITE, Parameter::FONT_20, "%2d", mCategorylist[p].armslist[i].rank);
		}
	}
}

/*プロファイルの描画*/
void ContractScene::DrawProfile(int p, int x, int y) {
	if(mProfile[p].sName != "none")
		DrawFormatStringToHandle(x, y, Parameter::COLOR_WHITE, Parameter::FONT_10, "%s", mProfile[p].sName.c_str());
	DrawFormatStringToHandle(x, y+10, Parameter::COLOR_WHITE, Parameter::FONT_20, "%s", mProfile[p].name.c_str());

	DrawFormatStringToHandle(x, y+40, Parameter::COLOR_WHITE, Parameter::FONT_12, "誓約：%s", mProfile[p].condition.c_str());

	for (int i = 0; i < 5; i++) {
		DrawFormatStringToHandle(x, y+ 60 + i * 15, Parameter::COLOR_WHITE, Parameter::FONT_12, "%s", mProfile[p].explain[i].c_str());
	}
}