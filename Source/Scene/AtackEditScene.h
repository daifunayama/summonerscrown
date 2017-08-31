#pragma once
#include "../SSPlayer/SS5Player.h"
#include "../Player/Player.h"
#include "Scene.h"
#include "../Parameter.h"

class AtackEditScene : public Scene {
public:
	AtackEditScene() : Scene(Parameter::SCENE_ATACKEDIT) {
		Load();
	}

	void Load();
	void Process();
	void Drawing();

private:
	void ChangePlayerSprite(int id);

private:
	int mTab;
	int mFrame;
	int mCharaId;
	int mMotionId;
	int mCursorX;
	int mCursorY;
	int mArrowY;
	int selectedBox;
	int boxNumber;
	int mPositionX;
	int mPositionY;
	bool atackBoxVisible;
	bool hitBoxVisible;
	bool damageBoxVisible;
	float mSpeed;
	int mMaxFrame;
	int mPlayFrame;
	Controller mController;
	Player *mPlayer;
	FrameData mFrameData;
	FrameData mFrameArray[300];
	HitBox mAtackBox;

	ss::Player *mSprite;
};