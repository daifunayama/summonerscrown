#include "AtackEditScene.h"
#include "../Utility.h"
#include "../Player/Character/Ein.h"
#include "../Player/Character/Ria.h"
#include "../Player/Character/Kureha.h"
#include "../Player/Character/Remnant.h"
#include "../Player/Character/Carol.h"
#include "../Atack/PlayerAtack.h"

void AtackEditScene::Load() {
	mController.SetPlayerId(0);

	mTab = 0;
	mFrame = 0;
	mSpeed = 1.00;
	mArrowY = 0;
	selectedBox = 0;
	mCursorX = 500;
	mCursorY = 300;
	mMaxFrame = 50;
	mCharaId = 0;
	mMotionId = 0;

	boxNumber = 0;
	atackBoxVisible = 1;
	hitBoxVisible = 1;
	damageBoxVisible = 1;

	//プレイヤーの作成
	mSprite = ss::Player::create();

	mPlayer = new Ein();
	mPositionX = 350;
	mPositionY = 500;

	//プレイヤーにリソースを割り当て
	mSprite->setData(mPlayer->getProfile().pass);// ssbpファイル名

	ChangePlayerSprite(0);

	mSprite->play(mPlayer->getProfile().pass + "1/idle");
}

void AtackEditScene::Process() {
	static bool holdKey3 = 0;

	mController.ConvertInput();

	if (mController.getKey(5) == 1) {
		if (mTab == 4) {
			mPlayFrame = 0;
			mSprite->setFrameNo(0);
		}
		
		if (mTab == 1 || mTab == 2 || mTab == 3) {
			boxNumber = 0;
			mSprite->setFrameNo(0);
			for (int i = 0; i <= mFrame; i++)mSprite->update((float)30 / 1000);
		}

		mTab++;
	
	}
	if (mController.getKey(7) == 1) {
		if (mTab == 0) {
			mPlayFrame = 0;
			mSprite->setFrameNo(0);
		}

		if (mTab == 3 || mTab == 4 || mTab == 5) {
			boxNumber = 0;
			mSprite->setFrameNo(0);
			for (int i = 0; i <= mFrame; i++)mSprite->update((float)30 / 1000);
		}

		mTab--;
	}

	if (mTab == 6)mTab = 0;
	if (mTab == -1)mTab = 5;



	switch (mTab) {
	case 0:
		if (mController.getKey(8) == 1 && mCharaId > 0) {
			mCharaId--;
			ChangePlayerSprite(mCharaId);
		}
		if (mController.getKey(6) == 1 && mCharaId < 10) {
			mCharaId++;
			ChangePlayerSprite(mCharaId);
		}

		if (mController.getUp() == 1 && mMotionId > 0) {
			mMotionId--;
			if(mPlayer->getPlayerAtack(mMotionId).getExist())
				mSprite->play(mPlayer->getProfile().pass + "1/" + Utility::GetPAtackName(mMotionId));
			mSprite->setStep(0.7);
		}
		if (mController.getDown() == 1 && mMotionId < 17) {
			mMotionId++;
			if (mPlayer->getPlayerAtack(mMotionId).getExist())
				mSprite->play(mPlayer->getProfile().pass + "1/" + Utility::GetPAtackName(mMotionId));
			mSprite->setStep(0.7);
		}

		mSprite->update((float)30 / 1000);
		break;

	case 1:
		if ((mController.getUp() == 1 || mController.getUp() % 3 == 0 && mController.getUp() > 10) && mArrowY > 0) {
			mArrowY--;
		}

		if ((mController.getDown() == 1 || mController.getDown() % 3 == 0 && mController.getDown() > 10) && mArrowY < 17) {
			mArrowY++;
		}

	case 2:
		if (mController.getLeft() == 1) {
			mCursorX--;
		}
		if (mController.getLeft() > 10) {
			mCursorX -= 3;
		}
		if (mController.getRight() == 1) {
			mCursorX++;
		}
		if (mController.getRight() > 10) {
			mCursorX += 3;
		}
		if (mController.getUp() == 1) {
			mCursorY--;
		}
		if (mController.getUp() > 10) {
			mCursorY -= 3;
		}
		if (mController.getDown() == 1) {
			mCursorY++;
		}
		if (mController.getDown() > 10) {
			mCursorY += 3;
		}

		if ((mController.getKey(8) == 1 || mController.getKey(8) % 3 == 0 && mController.getKey(8) > 10) && mFrame > 0) {
			mFrame--;
			boxNumber = 0;
			mSprite->setFrameNo(0);
			for (int i = 0; i < mFrame; i++)mSprite->update((float)30 / 1000);
		}
		if ((mController.getKey(6) == 1 || mController.getKey(6) % 3 == 0 && mController.getKey(6) > 10) && mFrame < 100) {
			mFrame++;
			boxNumber = 0;
			mSprite->setFrameNo(0);
			for (int i = 0; i < mFrame; i++)mSprite->update((float)30 / 1000);
		}

		if (mController.getKey(3) == 1) {
			mAtackBox.setPositionX(mCursorX);
			mAtackBox.setPositionY(mCursorY);
		
			holdKey3 = 1;
		}
		if (!mController.getKey(3) && holdKey3) {
			holdKey3 = 0;

			mAtackBox.setExist(1);
			mAtackBox.setWidth(mCursorX - mAtackBox.getPositionX()); 
			mAtackBox.setHeight(mCursorY - mAtackBox.getPositionY()); 
			mAtackBox.setBoxId(selectedBox);
			mFrameArray[mFrame].setAtackBox(boxNumber, mAtackBox);

			boxNumber++;
		}

		break;

	case 3:
		if ((mController.getKey(8) == 1 || mController.getKey(8) % 3 == 0 && mController.getKey(8) > 10) && mFrame > 0) {
			mFrame--;
			mSprite->setFrameNo(0);
			for (int i = 0; i < mFrame; i++)mSprite->update((float)30 / 1000);
		}
		if ((mController.getKey(6) == 1 || mController.getKey(6) % 3 == 0 && mController.getKey(6) > 10) && mFrame < 100) {
			mFrame++;
			mSprite->setFrameNo(0);
			for (int i = 0; i < mFrame; i++)mSprite->update((float)30 / 1000);
		}
		break;

	case 4:
		if ((mController.getKey(8) == 1 || mController.getKey(8) % 3 == 0 && mController.getKey(8) > 10) && mFrame > 0) {
			mFrame--;
			mSprite->setFrameNo(0);
			for (int i = 0; i < mFrame; i++)mSprite->update((float)30 / 1000);
		}
		if ((mController.getKey(6) == 1 || mController.getKey(6) % 3 == 0 && mController.getKey(6) > 10) && mFrame < 100) {
			mFrame++;
			mSprite->setFrameNo(0);
			for (int i = 0; i < mFrame; i++)mSprite->update((float)30 / 1000);
		}
		break;

	case 5:
		if ((mController.getKey(8) == 1 || mController.getKey(8) > 10) && mSpeed > 0) {
			mSpeed -= 0.01;
			mSprite->setStep(mSpeed);
		}
		if ((mController.getKey(6) == 1 || mController.getKey(6) > 10) && mSpeed < 5) {
			mSpeed += 0.01;
			mSprite->setStep(mSpeed);
		}

		if (mController.getLeft() == 1 || (mController.getLeft() % 3 == 0 && mController.getLeft() > 10) && mMaxFrame > 1)mMaxFrame--;
		if (mController.getRight() == 1 || (mController.getRight() % 3 == 0 && mController.getRight() > 10) && mMaxFrame < 300)mMaxFrame++;
		
		mPlayFrame++;

		if (mPlayFrame == mMaxFrame) {
			mPlayFrame = 0;
			mSprite->setFrameNo(0);
		}
		mSprite->update((float)30 / 1000);
	}
}

void AtackEditScene::ChangePlayerSprite(int id) {
	if (id == 0 || id == 1 || id == 2 || id == 8 || id == 9) {

		//プレイヤーの再作成
		switch (id) {
		case 0:
			mPlayer = new Ein();
			break;
		case 1:
			mPlayer = new Ria();
			break;
		case 2:
			mPlayer = new Kureha();
			break;
		case 8:
			mPlayer = new Remnant();
			break;
		case 9:
			mPlayer = new Carol();
			break;
		default:
			mPlayer = new Ein();
			break;
		}

		if (id != 5) {
			mSprite->setData(mPlayer->getProfile().pass);
			mSprite->play(mPlayer->getProfile().pass + "1/idle");

			Profile pf = mPlayer->getProfile();
			mSprite->setStep(pf.speed);
			
			mSprite->setPosition(mPositionX,Parameter::WINDOW_HEIGHT-mPositionY);
			mSprite->setScale(pf.size, pf.size);
		
		}

		mPlayer->LoadAtack();
	}
}


void AtackEditScene::Drawing() {

	DrawBox(0, 0, 200, 25, Parameter::COLOR_GRAY, 1);
	DrawStringToHandle(5, 5, "モーション選択", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

	DrawBox(210, 0, 410, 25, Parameter::COLOR_GRAY, 1);
	DrawStringToHandle(215, 5, "攻撃ボックス登録", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

	DrawBox(420, 0, 620, 25, Parameter::COLOR_GRAY, 1);
	DrawStringToHandle(425, 5, "攻撃ボックス設置", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

	DrawBox(630, 0, 830, 25, Parameter::COLOR_GRAY, 1);
	DrawStringToHandle(635, 5, "ヒットボックス設置", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

	DrawBox(840, 0, 1040, 25, Parameter::COLOR_GRAY, 1);
	DrawStringToHandle(845, 5, "ダメージボックス設置", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

	DrawBox(1050, 0, 1250, 25, Parameter::COLOR_GRAY, 1);
	DrawStringToHandle(1055, 5, "プレイ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

	switch (mTab) {
	case 0:
		if (mPlayer->getPlayerAtack(mMotionId).getExist())mSprite->draw();
		else DrawStringToHandle(200, 400, "モーションがありません", Parameter::COLOR_WHITE, Parameter::FONT_30);

		DrawFormatStringToHandle(30, 100, Parameter::COLOR_WHITE, Parameter::FONT_15, "%s", mPlayer->getProfile().eName.c_str());

		DrawStringToHandle(10, 140 + 20 * mMotionId, "→", Parameter::COLOR_WHITE, Parameter::FONT_15);

		DrawStringToHandle(30, 140, "A", mPlayer->getPlayerAtack(Parameter::P_ATACK_A).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY,Parameter::FONT_15);
		DrawStringToHandle(30, 160, "2A", mPlayer->getPlayerAtack(Parameter::P_ATACK_2A).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 180, "8A", mPlayer->getPlayerAtack(Parameter::P_ATACK_8A).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 200, "JA", mPlayer->getPlayerAtack(Parameter::P_ATACK_JA).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 220, "B", mPlayer->getPlayerAtack(Parameter::P_ATACK_B).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 240, "2B", mPlayer->getPlayerAtack(Parameter::P_ATACK_2B).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 260, "3B", mPlayer->getPlayerAtack(Parameter::P_ATACK_3B).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 280, "4B", mPlayer->getPlayerAtack(Parameter::P_ATACK_4B).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 300, "6B", mPlayer->getPlayerAtack(Parameter::P_ATACK_6B).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 320, "8B", mPlayer->getPlayerAtack(Parameter::P_ATACK_8B).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 340, "JB", mPlayer->getPlayerAtack(Parameter::P_ATACK_JB).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);
		DrawStringToHandle(30, 360, "J2B", mPlayer->getPlayerAtack(Parameter::P_ATACK_J2B).getExist() ? Parameter::COLOR_WHITE : Parameter::COLOR_GRAY, Parameter::FONT_15);

		DrawBox(0, 0, 200, 25, Parameter::COLOR_RED, 1);
		DrawStringToHandle(5, 5, "モーション選択", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		break;

	case 1:
		
		DrawFormatStringToHandle(30, 100, Parameter::COLOR_WHITE, Parameter::FONT_15, "ボックスID：　　　　　%d", selectedBox);

		DrawBox(225 + selectedBox * 30, 95, 250 + selectedBox * 30, 120, Parameter::COLOR_WHITE, 1);

		DrawBox(230, 100, 245, 115, GetColor(255, 0, 0), 1);
		DrawBox(260, 100, 275, 115, GetColor(255, 64, 0), 1);
		DrawBox(290, 100, 305, 115, GetColor(255, 128, 0), 1);
		DrawBox(320, 100, 335, 115, GetColor(255, 192, 0), 1);
		DrawBox(350, 100, 365, 115, GetColor(255, 255, 0), 1);

		DrawStringToHandle(10, 100 + 20 * mArrowY, "→", Parameter::COLOR_WHITE, Parameter::FONT_15);

		if (mFrameData.getAtackBoxData(selectedBox).getAtackType() == 0)DrawStringToHandle(30, 120, "攻撃タイプ:  　　　　上段", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (mFrameData.getAtackBoxData(selectedBox).getAtackType() == 1)DrawStringToHandle(30, 120, "攻撃タイプ:  　　　　下段", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (mFrameData.getAtackBoxData(selectedBox).getAtackType() == 2)DrawStringToHandle(30, 120, "攻撃タイプ:  　　　　中段", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		DrawFormatStringToHandle(30, 140, Parameter::COLOR_WHITE, Parameter::FONT_15, "エフェクトタイプ：　%3d", mFrameData.getAtackBoxData(selectedBox).getEffectType());
		DrawFormatStringToHandle(30, 160, Parameter::COLOR_WHITE, Parameter::FONT_15, "SEタイプ：　　　　　%3d", mFrameData.getAtackBoxData(selectedBox).getSEType());
		if (mFrameData.getAtackBoxData(selectedBox).getGuardType() == 0)DrawStringToHandle(30, 180, "ガードタイプ:  　　　通常", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (mFrameData.getAtackBoxData(selectedBox).getGuardType() == 1)DrawStringToHandle(30, 180, "ガードタイプ:  　　　ガー不", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (mFrameData.getAtackBoxData(selectedBox).getGuardType() == 2)DrawStringToHandle(30, 180, "ガードタイプ:  　　　空ガー不", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		DrawFormatStringToHandle(30, 200, Parameter::COLOR_WHITE, Parameter::FONT_15, "多段ヒット：　　　　%3d", mFrameData.getAtackBoxData(selectedBox).getAllowMultHit());
		DrawFormatStringToHandle(30, 220, Parameter::COLOR_WHITE, Parameter::FONT_15, "受け身不能時間：　　%3d", mFrameData.getAtackBoxData(selectedBox).getHitStop());
		DrawFormatStringToHandle(30, 240, Parameter::COLOR_WHITE, Parameter::FONT_15, "減衰補正：　　　　　%3d", mFrameData.getAtackBoxData(selectedBox).getdecHitStop());
		DrawFormatStringToHandle(30, 260, Parameter::COLOR_WHITE, Parameter::FONT_15, "拘束補正：　　　　　%3d", mFrameData.getAtackBoxData(selectedBox).getBindTime());
		DrawFormatStringToHandle(30, 280, Parameter::COLOR_WHITE, Parameter::FONT_15, "相殺後継続フラグ：　%3d", mFrameData.getAtackBoxData(selectedBox).getContinueAtackAfterOffset());
		DrawFormatStringToHandle(30, 300, Parameter::COLOR_WHITE, Parameter::FONT_15, "ダウン誘発：　　　　%3d", mFrameData.getAtackBoxData(selectedBox).getForceDown());
		DrawFormatStringToHandle(30, 320, Parameter::COLOR_WHITE, Parameter::FONT_15, "床バウンド誘発：　　%3d", mFrameData.getAtackBoxData(selectedBox).getFloorBound());
		DrawFormatStringToHandle(30, 340, Parameter::COLOR_WHITE, Parameter::FONT_15, "壁叩きつけ誘発：　　%3d", mFrameData.getAtackBoxData(selectedBox).getWallBound());
		DrawFormatStringToHandle(30, 360, Parameter::COLOR_WHITE, Parameter::FONT_15, "多段ヒット：　　　　%3d", mFrameData.getAtackBoxData(selectedBox).getAllowMultHit());
		if (mFrameData.getAtackBoxData(selectedBox).getShakeWindow() == 0)DrawStringToHandle(30, 380, "画面揺らし:  　　　　なし", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (mFrameData.getAtackBoxData(selectedBox).getShakeWindow() == 1)DrawStringToHandle(30, 380, "画面揺らし:  　　　　弱", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (mFrameData.getAtackBoxData(selectedBox).getShakeWindow() == 2)DrawStringToHandle(30, 380, "画面揺らし:  　　　　中", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (mFrameData.getAtackBoxData(selectedBox).getShakeWindow() == 3)DrawStringToHandle(30, 380, "画面揺らし:  　　　　強", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		DrawFormatStringToHandle(30, 400, Parameter::COLOR_WHITE, Parameter::FONT_15, "吹き飛ばしⅩ成分：　%3d", mFrameData.getAtackBoxData(selectedBox).getVectorX());
		DrawFormatStringToHandle(30, 420, Parameter::COLOR_WHITE, Parameter::FONT_15, "吹き飛ばしＹ成分：　%3d", mFrameData.getAtackBoxData(selectedBox).getVectorY());
		DrawFormatStringToHandle(30, 440, Parameter::COLOR_WHITE, Parameter::FONT_15, "空吹き飛ばしⅩ成分：%3d", mFrameData.getAtackBoxData(selectedBox).getAirVectorX());
		DrawFormatStringToHandle(30, 460, Parameter::COLOR_WHITE, Parameter::FONT_15, "空吹き飛ばしＹ成分：%3d", mFrameData.getAtackBoxData(selectedBox).getAirVectorY());
		DrawFormatStringToHandle(30, 480, Parameter::COLOR_WHITE, Parameter::FONT_15, "威力：　　　　　　　%3d", mFrameData.getAtackBoxData(selectedBox).getPower());
		DrawFormatStringToHandle(30, 500, Parameter::COLOR_WHITE, Parameter::FONT_15, "EX回復：　　　　　　%3d", mFrameData.getAtackBoxData(selectedBox).getEXGain());


		DrawBox(210, 0, 410, 25, Parameter::COLOR_RED, 1);
		DrawStringToHandle(215, 5, "攻撃ボックス登録", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		break;

	case 2:
		mSprite->draw();
		DrawCircle(mPositionX, mPositionY, 3, Parameter::COLOR_YELLOW, 1, 1);

		for (int i = 0; i < 20; i++) {
			if (!mFrameArray[mFrame].getAtackBox(i).getExist())break;
			
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(mFrameArray[mFrame].getAtackBox(i).getPositionX(), mFrameArray[mFrame].getAtackBox(i).getPositionY(),
				mFrameArray[mFrame].getAtackBox(i).getPositionX() + mFrameArray[mFrame].getAtackBox(i).getWidth(),
				mFrameArray[mFrame].getAtackBox(i).getPositionY() + mFrameArray[mFrame].getAtackBox(i).getHeight(),
				GetColor(255, selectedBox * mFrameArray[mFrame].getAtackBox(i).getBoxId(), 0), 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		}

		if (mController.getKey(3)) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(mAtackBox.getPositionX(), mAtackBox.getPositionY(), mCursorX, mCursorY, GetColor(255, selectedBox * 64, 0), 1);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		DrawCircle(mCursorX, mCursorY, 3, Parameter::COLOR_RED, 1, 1);

		DrawFormatStringToHandle(10, 100, Parameter::COLOR_WHITE, Parameter::FONT_15, "フレーム：　　　%3d", mFrame);
		DrawFormatStringToHandle(10, 120, Parameter::COLOR_WHITE, Parameter::FONT_15, "再生フレーム：　%3d", mSprite->getFrameNo());
		DrawFormatStringToHandle(10, 140, Parameter::COLOR_WHITE, Parameter::FONT_15, "再生速度：　　　%1.2f", mSprite->getStep());
		DrawFormatStringToHandle(10, 160, Parameter::COLOR_WHITE, Parameter::FONT_15, "ボックスID：　　%3d", selectedBox);
		DrawBox(100, 160, 115, 175, GetColor(255, selectedBox * 64, 0), 1);
		DrawFormatStringToHandle(10, 180, Parameter::COLOR_WHITE, Parameter::FONT_15, "ボックス番号：　%3d", boxNumber);

		DrawFormatStringToHandle(200, 100, Parameter::COLOR_WHITE, Parameter::FONT_15, "カーソル位置(相対)：(%3d, %3d)", mCursorX-mPositionX,mCursorY-mPositionY);

		if (atackBoxVisible)DrawStringToHandle(10, 200, "攻撃ボックス：　　オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			    DrawStringToHandle(10, 200, "攻撃ボックス：　　オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (hitBoxVisible)DrawStringToHandle(10, 220, "ヒットボックス：　オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			  DrawStringToHandle(10, 220, "ヒットボックス：　オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (damageBoxVisible)DrawStringToHandle(10, 240, "ダメージボックス：オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			     DrawStringToHandle(10, 240, "ダメージボックス：オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

		DrawBox(420, 0, 620, 25, Parameter::COLOR_RED, 1);
		DrawStringToHandle(425, 5, "攻撃ボックス設置", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		break;


	case 3:
		mSprite->draw();
		DrawCircle(mPositionX, mPositionY, 3, Parameter::COLOR_YELLOW, 1, 1);

		DrawCircle(mCursorX, mCursorY, 3, Parameter::COLOR_RED, 1, 1);

		DrawFormatStringToHandle(10, 100, Parameter::COLOR_WHITE, Parameter::FONT_15, "フレーム：　　　%3d", mFrame);
		DrawFormatStringToHandle(10, 120, Parameter::COLOR_WHITE, Parameter::FONT_15, "再生フレーム：　%3d", mSprite->getFrameNo());
		DrawFormatStringToHandle(10, 140, Parameter::COLOR_WHITE, Parameter::FONT_15, "再生速度：　　　%1.2f", mSprite->getStep());

		if (atackBoxVisible)DrawStringToHandle(10, 200, "攻撃ボックス：　　オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			    DrawStringToHandle(10, 200, "攻撃ボックス：　　オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (hitBoxVisible)DrawStringToHandle(10, 220, "ヒットボックス：　オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			  DrawStringToHandle(10, 220, "ヒットボックス：　オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (damageBoxVisible)DrawStringToHandle(10, 240, "ダメージボックス：オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			     DrawStringToHandle(10, 240, "ダメージボックス：オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

		DrawBox(630, 0, 830, 25, Parameter::COLOR_RED, 1);
		DrawStringToHandle(635, 5, "ヒットボックス設置", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		break;

	case 4:
		mSprite->draw();
		DrawCircle(mPositionX, mPositionY, 3, Parameter::COLOR_YELLOW, 1, 1);

		DrawCircle(mCursorX, mCursorY, 3, Parameter::COLOR_RED, 1, 1);

		DrawFormatStringToHandle(10, 100, Parameter::COLOR_WHITE, Parameter::FONT_15, "フレーム：　　　%3d", mFrame);
		DrawFormatStringToHandle(10, 120, Parameter::COLOR_WHITE, Parameter::FONT_15, "再生フレーム：　%3d", mSprite->getFrameNo());
		DrawFormatStringToHandle(10, 140, Parameter::COLOR_WHITE, Parameter::FONT_15, "再生速度：　　　%1.2f", mSprite->getStep());

		if (atackBoxVisible)DrawStringToHandle(10, 200, "攻撃ボックス：　　オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			    DrawStringToHandle(10, 200, "攻撃ボックス：　　オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (hitBoxVisible)DrawStringToHandle(10, 220, "ヒットボックス：　オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			  DrawStringToHandle(10, 220, "ヒットボックス：　オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (damageBoxVisible)DrawStringToHandle(10, 240, "ダメージボックス：オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			     DrawStringToHandle(10, 240, "ダメージボックス：オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

		DrawBox(840, 0, 1040, 25, Parameter::COLOR_RED, 1);
		DrawStringToHandle(845, 5, "ダメージボックス設置", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		break;

	case 5:
		mSprite->draw();

		for (int i = 0; i < 20; i++) {
			if (mFrameArray[mPlayFrame+1].getAtackBox(i).getExist()) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
				DrawBox(mFrameArray[mPlayFrame+1].getAtackBox(i).getPositionX(), mFrameArray[mPlayFrame+1].getAtackBox(i).getPositionY(),
					mFrameArray[mPlayFrame+1].getAtackBox(i).getPositionX() + mFrameArray[mPlayFrame+1].getAtackBox(i).getWidth(),
					mFrameArray[mPlayFrame+1].getAtackBox(i).getPositionY() + mFrameArray[mPlayFrame+1].getAtackBox(i).getHeight(),
					GetColor(255, selectedBox * mFrameArray[mPlayFrame+1].getAtackBox(i).getBoxId(), 0), 1);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}

		DrawFormatStringToHandle(10, 100, Parameter::COLOR_WHITE, Parameter::FONT_15, "フレーム：　　　%3d", mPlayFrame);
		DrawFormatStringToHandle(10, 120, Parameter::COLOR_WHITE, Parameter::FONT_15, "再生フレーム：　%3d", mSprite->getFrameNo());
		DrawFormatStringToHandle(10, 140, Parameter::COLOR_WHITE, Parameter::FONT_15, "再生速度：　　　%1.2f", mSprite->getStep());
		DrawFormatStringToHandle(10, 160, Parameter::COLOR_WHITE, Parameter::FONT_15, "総フレーム数：　%3d", mMaxFrame);



		if (atackBoxVisible)DrawStringToHandle(10, 200, "攻撃ボックス：　　オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			    DrawStringToHandle(10, 200, "攻撃ボックス：　　オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (hitBoxVisible)DrawStringToHandle(10, 220, "ヒットボックス：　オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			  DrawStringToHandle(10, 220, "ヒットボックス：　オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		if (damageBoxVisible)DrawStringToHandle(10, 240, "ダメージボックス：オン", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		else			     DrawStringToHandle(10, 240, "ダメージボックス：オフ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);

		DrawBox(1050, 0, 1250, 25, Parameter::COLOR_RED, 1);
		DrawStringToHandle(1055, 5, "プレイ", Parameter::COLOR_WHITE, Parameter::FONT_15, 0, 0);
		break;
	}
}