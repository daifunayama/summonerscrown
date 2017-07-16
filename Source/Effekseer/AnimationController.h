#pragma once
#include "EffAnimation.h"
#include <vector>

/*
Effekseer�A�j���[�V�����̐�����s���V���O���g���p�^�[���N���X
*/
class AnimationController {
public:
	static AnimationController& getInstance(void) {
		static AnimationController animationController;
		return animationController;
	}
	AnimationController(const AnimationController&) = delete;
	AnimationController& operator = (const AnimationController&) = delete;
	AnimationController(AnimationController&&) = delete;
	AnimationController operator = (AnimationController&&) = delete;

	int Create(int gHandle, int layer, int x, int y, int width, int height, float exRate, int angle,
		int devided, int speed, int endFrame, int loopFrame, bool right, bool addFrag);
	void Process();
	void SetPosition(int id, int x, int y);
	void Remove(int id);
	void Reset();
	void DrawLayer1();
	void DrawLayer2();

private:
	AnimationController() {}
	~AnimationController() {}

private:
	std::vector<EffAnimation> mEffAnimation;	//�A�j���[�V��������z��
	int mKey;									//�A�j���[�V�����ɂ킽���L�[
};