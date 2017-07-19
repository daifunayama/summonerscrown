#include "AnimationController.h"
#include "../Parameter.h"
#include "../Camera/Camera.h"
#include "DxLib.h"

/*�A�j���[�V�����̍쐬*/
int AnimationController::Create(
	int gHandle, int layer, int x, int y, int width, int height, float exRate, int angle,
	int devided, int speed, int endFrame, int loopFrame, bool right,bool addFrag) {
	EffAnimation animation;

	animation.setState(1);
	animation.setCounter(0);

	animation.setGraph(gHandle);
	animation.setLayer(layer);
	animation.setPositionX(x);
	animation.setPositionY(y);
	animation.setWidth(width);
	animation.setHeight(height);
	animation.setExRate(exRate);
	animation.setAngle(angle);
	animation.setDevided(devided);
	animation.setSpeed(speed);
	animation.setEndFrame(endFrame);
	animation.setLoopFrame(loopFrame);
	animation.setRight(right);
	animation.setAddFlag(addFrag);

	mKey++;
	if (mKey > 100)mKey = 1;
	animation.setKey(mKey);

	mEffAnimation.push_back(animation);

	return mKey;
}

void AnimationController::SetPosition(int key, int x, int y) {
	for (int i = 0; i < mEffAnimation.size(); i++) {
		if (mEffAnimation[i].getKey() == key) {
			mEffAnimation[i].setPositionX(x);
			mEffAnimation[i].setPositionY(y);
			break;
		}
	}
}

/*�A�j���[�V�����̍폜*/
void AnimationController::Remove(int key) {
	for (int i = 0; i < mEffAnimation.size(); i++) {
		if (mEffAnimation[i].getKey() == key) {
			mEffAnimation[i].setState(0);
			mEffAnimation[i].setCounter(0);
			mEffAnimation.erase(mEffAnimation.begin() + i);
			mEffAnimation.shrink_to_fit();
			break;
		}
	}
}

/*�A�j���[�V�����̍X�V*/
void AnimationController::Process() {
	for (int i = 0; i < mEffAnimation.size(); i++) {
		if (mEffAnimation[i].getState() == 1) {
			mEffAnimation[i].IncrementCounter();

			if (mEffAnimation[i].getLoopFrame() > 0 && mEffAnimation[i].getCounter() >= mEffAnimation[i].getLoopFrame()) {
				mEffAnimation[i].setCounter(0);
			}
			
			else if (mEffAnimation[i].getCounter() >= mEffAnimation[i].getEndFrame()) {
				mEffAnimation[i].setState(0);
				mEffAnimation[i].setCounter(0);
				mEffAnimation.erase(mEffAnimation.begin()+i);
				mEffAnimation.shrink_to_fit();
			}
		}
	}
}

/*�A�j���[�V�����̏�����*/
void AnimationController::Reset() {
	mEffAnimation.clear();
}

/*�A�j���[�V���������C���[1�ɕ`��*/
void AnimationController::DrawLayer1() {
	int tmp;

	for (int i = 0; i < mEffAnimation.size(); i++) {
		if (mEffAnimation[i].getLayer() == 1) {
			//�Đ����̂Ƃ�
			if (mEffAnimation[i].getState() == 1) {

				//���Z�^�C�v�̏ꍇ�̓u�����h�ݒ�ύX
				if (mEffAnimation[i].getAddFlag())SetDrawBlendMode(DX_BLENDMODE_ADD, 255);


				tmp = DerivationGraph(
					(mEffAnimation[i].getCounter() / mEffAnimation[i].getSpeed()) % mEffAnimation[i].getDevided() * mEffAnimation[i].getWidth(),
					(mEffAnimation[i].getCounter() / mEffAnimation[i].getSpeed()) / mEffAnimation[i].getDevided() * mEffAnimation[i].getHeight(),
					mEffAnimation[i].getWidth(), mEffAnimation[i].getHeight(), mEffAnimation[i].getGraph());

				DrawRotaGraph2(
					mEffAnimation[i].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), mEffAnimation[i].getPositionY(),
					mEffAnimation[i].getWidth() / 2, mEffAnimation[i].getHeight() / 2, mEffAnimation[i].getExRate(), (Parameter::PI / 360)*mEffAnimation[i].getAngle(),
					tmp, true, !mEffAnimation[i].getRight());


				//�u�����h�^�C�v�����Ƃɂ��ǂ�
				if (mEffAnimation[i].getAddFlag())SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

/*�A�j���[�V���������C���[2�ɕ`��*/
void AnimationController::DrawLayer2() {
	int tmp;

	for (int i = 0; i < mEffAnimation.size(); i++) {
		if (mEffAnimation[i].getLayer() == 2) {
			//�Đ����̂Ƃ�
			if (mEffAnimation[i].getState() == 1) {

				//���Z�^�C�v�̏ꍇ�̓u�����h�ݒ�ύX
				if (mEffAnimation[i].getAddFlag())SetDrawBlendMode(DX_BLENDMODE_ADD, 255);


				tmp = DerivationGraph(
					(mEffAnimation[i].getCounter() / mEffAnimation[i].getSpeed()) % mEffAnimation[i].getDevided() * mEffAnimation[i].getWidth(),
					(mEffAnimation[i].getCounter() / mEffAnimation[i].getSpeed()) / mEffAnimation[i].getDevided() * mEffAnimation[i].getHeight(),
					mEffAnimation[i].getWidth(), mEffAnimation[i].getHeight(), mEffAnimation[i].getGraph());

				DrawRotaGraph2(
					mEffAnimation[i].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), mEffAnimation[i].getPositionY(),
					mEffAnimation[i].getWidth() / 2, mEffAnimation[i].getHeight() / 2, mEffAnimation[i].getExRate(), (Parameter::PI / 360)*mEffAnimation[i].getAngle(),
					tmp, true, !mEffAnimation[i].getRight());


				//�u�����h�^�C�v�����Ƃɂ��ǂ�
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}

/*�A�j���[�V���������C���[3�ɕ`��*/
void AnimationController::DrawLayer3() {
	int tmp;

	for (int i = 0; i < mEffAnimation.size(); i++) {
		if (mEffAnimation[i].getLayer() == 3) {
			//�Đ����̂Ƃ�
			if (mEffAnimation[i].getState() == 1) {

				//���Z�^�C�v�̏ꍇ�̓u�����h�ݒ�ύX
				if (mEffAnimation[i].getAddFlag())SetDrawBlendMode(DX_BLENDMODE_ADD, 255);


				tmp = DerivationGraph(
					(mEffAnimation[i].getCounter() / mEffAnimation[i].getSpeed()) % mEffAnimation[i].getDevided() * mEffAnimation[i].getWidth(),
					(mEffAnimation[i].getCounter() / mEffAnimation[i].getSpeed()) / mEffAnimation[i].getDevided() * mEffAnimation[i].getHeight(),
					mEffAnimation[i].getWidth(), mEffAnimation[i].getHeight(), mEffAnimation[i].getGraph());

				DrawRotaGraph2(
					mEffAnimation[i].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), mEffAnimation[i].getPositionY(),
					mEffAnimation[i].getWidth() / 2, mEffAnimation[i].getHeight() / 2, mEffAnimation[i].getExRate(), (Parameter::PI / 360)*mEffAnimation[i].getAngle(),
					tmp, true, !mEffAnimation[i].getRight());


				//�u�����h�^�C�v�����Ƃɂ��ǂ�
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}
	}
}