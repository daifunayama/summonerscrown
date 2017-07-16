#include "ContractCircle.h"
#include "../Input/Controller.h"
#include "../Parameter.h"

/*ロード*/
void ContractCircle::Load(Player& player) {
	mGraphCircle = LoadGraph("Data/graphic/ui/contract_circle.png");
	mGraphCursor = LoadGraph("Data/graphic/ui/cursor.png");
	mGraphNameBar1 = LoadGraph("Data/graphic/ui/namebar1.png");
	mGraphNameBar2 = LoadGraph("Data/graphic/ui/namebar2.png");
	mGraphConditionBar1 = LoadGraph("Data/graphic/ui/conditionbar1.png");
	mGraphConditionBar2 = LoadGraph("Data/graphic/ui/conditionbar2.png");
	mAngle = 0;

	for (int i = 0; i < 8; i++) {
		if (player.getArmsExist(i)) {
			mIconlist[i] = player.getArms(i)->getIcon();
		}
	}
}

/*更新*/
void ContractCircle::Process(Player& player) {
	mController = player.getController();
	mOpenCircle = player.getOpenCircle();
	mCursor = player.getCircleCursor();
	mIcon = player.getArms(player.getArmsId())->getIcon();

	if (player.getArmsExist(mCursor)) {
		mName = player.getArms(mCursor)->getName();
		mCondition = player.getArms(mCursor)->getCondition();
	}
	else {
		mName = "";
		mCondition = "";
	}

	mAngle++;
	if (mAngle >= 1440)mAngle = 0;
}

/*描画*/
void ContractCircle::Draw() {
	int centerX,centerY;

	if (mPlayerId == 0) {
		centerX = 136;
		centerY = 149;

		DrawGraph(centerX-30, centerY-30, mIcon, true);
		if (mOpenCircle) {
			DrawRotaGraph(centerX, centerY, 1, Parameter::PI / 360 * (double)mAngle*0.5, mGraphCircle, true, false);
			DrawGraph(centerX-30, centerY-115-30, mIconlist[0], true);
			DrawGraph(centerX+81-30, centerY-81-30, mIconlist[1], true);
			DrawGraph(centerX + -81 - 30, centerY - 81 - 30, mIconlist[7], true);
			
			if (mCursor == 0)DrawRotaGraph(centerX, centerY - 115, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 1)DrawRotaGraph(centerX+81, centerY-81, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 2)DrawRotaGraph(centerX +115, centerY, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 3)DrawRotaGraph(centerX + 81, centerY + 81, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 4)DrawRotaGraph(centerX, centerY + 115, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 5)DrawRotaGraph(centerX - 81, centerY + 81, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 6)DrawRotaGraph(centerX -115, centerY, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 7)DrawRotaGraph(centerX - 81, centerY - 81, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
	
			if (mController.getKey(5) > 50 && mController.getKey(5) <= 75) {
				for (int i = 0; i < mName.length() / 2; i++)DrawGraph(i * 20 - 500 + (mController.getKey(5)-50)*20, 0, mGraphNameBar1, true);
				DrawGraph(mName.length() / 2 * 20 - 500 + (mController.getKey(5) - 50) * 20, 0, mGraphNameBar2, true);
				for (int i = 0; i < mCondition.length() / 2; i++)DrawGraph(i * 15 - 500 + (mController.getKey(5) - 50) * 20, 27, mGraphConditionBar1, true);
				DrawGraph(mCondition.length() / 2 * 15 - 500 + (mController.getKey(5) - 50) * 20, 27, mGraphConditionBar2, true);

				DrawFormatStringFToHandle(-500 + (mController.getKey(5) - 50) * 20, 4, Parameter::COLOR_WHITE, Parameter::FONT_20, "%s", mName.c_str());
				DrawFormatStringFToHandle(-500 + (mController.getKey(5) - 50) * 20, 31, GetColor(100, 100, 100), Parameter::FONT_15, "%s", mCondition.c_str());
			}
			else if (mController.getKey(5) > 75) {
				for (int i = 0; i < mName.length() / 2; i++)DrawGraph(i * 20, 0, mGraphNameBar1, true);
				DrawGraph(mName.length() / 2 * 20, 0, mGraphNameBar2, true);
				for (int i = 0; i < mCondition.length() / 2; i++)DrawGraph(i * 15, 27, mGraphConditionBar1, true);
				DrawGraph(mCondition.length() / 2 * 15, 27, mGraphConditionBar2, true);

				DrawFormatStringFToHandle(0, 4, Parameter::COLOR_WHITE, Parameter::FONT_20, "%s", mName.c_str());
				DrawFormatStringFToHandle(0, 31, GetColor(100,100,100), Parameter::FONT_15, "%s", mCondition.c_str());
			}
		}
	}
	else {
		centerX = Parameter::WINDOW_WIDTH - 136;
		centerY = 149;

		DrawGraph(centerX - 30, centerY - 30, mIcon, true);
		if (mOpenCircle) {
			DrawRotaGraph(centerX, centerY, 1, Parameter::PI / 360 * (double)mAngle*0.5, mGraphCircle, true, false);
			DrawGraph(centerX - 30, centerY - 115 - 30, mIconlist[0], true);
			DrawGraph(centerX + 81 - 30, centerY - 81 - 30, mIconlist[1], true);

			if (mCursor == 0)DrawRotaGraph(centerX, centerY - 115, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 1)DrawRotaGraph(centerX + 81, centerY - 81, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 2)DrawRotaGraph(centerX + 115, centerY, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 3)DrawRotaGraph(centerX + 81, centerY + 81, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 4)DrawRotaGraph(centerX, centerY + 115, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 5)DrawRotaGraph(centerX - 81, centerY + 81, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 6)DrawRotaGraph(centerX - 115, centerY, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
			if (mCursor == 7)DrawRotaGraph(centerX - 81, centerY - 81, 1, Parameter::PI / 360 * (double)mAngle, mGraphCursor, true, false);
		}
	}
}