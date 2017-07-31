#include "Cyanos.h"
#include "../../../Application.h"

/*�O���t�B�b�N�̃��[�h*/
void Cyanos::LoadArmsGraphic() {
	//�v���C���[�̍쐬
	mSprite = ss::Player::create();

	//�A�j���f�[�^�����\�[�X�ɒǉ�
	//Application::resman->addData("Data/arms/PrimalSpheres/Cyanos/cyanos.ssbp");
	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite->setData("cyanos");// ssbp�t�@�C�����i�g���q�s�v�j
	//�Đ����郂�[�V������ݒ�
	mSprite->play("arms/wait");// �A�j���[�V���������w��(ssae��/�A�j���[�V���������\�A�ڂ����͌�q)

	mIcon = LoadGraph("Data/arms/PrimalSpheres/Cyanos/icon.png");

	mAnimation[0].setGraph(LoadGraph("Data/arms/PrimalSpheres/Cyanos/anime1.png"));
	mAnimation[1].setGraph(LoadGraph("Data/arms/PrimalSpheres/Cyanos/anime2.png"));
	mGraphGauge1 = LoadGraph("Data/arms/PrimalSpheres/Cyanos/gauge1.png");
	mGraphGauge2 = LoadGraph("Data/arms/PrimalSpheres/Cyanos/gauge2.png");
}

/*�T�E���h�̃��[�h*/
void Cyanos::LoadArmsSound() {
	mSoundAtack[1] = LoadSoundMem("Data/arms/PrimalSpheres/Cyanos/se1.mp3");
	mSoundAtack[2] = LoadSoundMem("Data/arms/PrimalSpheres/Cyanos/se2.mp3");
	mSoundAtack[3] = LoadSoundMem("Data/arms/PrimalSpheres/Cyanos/se6.mp3");
	mSoundAtack[4] = LoadSoundMem("Data/arms/PrimalSpheres/Cyanos/se5.mp3");
	mSoundAtack[5] = LoadSoundMem("Data/arms/PrimalSpheres/Cyanos/se3.mp3");

	ChangeVolumeSoundMem(200, mSoundAtack[3]);
	ChangeVolumeSoundMem(200, mSoundAtack[5]);
}

/*�A�j���[�V�����̍X�V*/
void Cyanos::UpdateArmsAnimation() {
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mSprite->getPlayAnimeName() != "wait") {
			mSprite->play("arms/wait");
		}
	}
	if (mState == Parameter::S_ARMS_SUMMON) {
		if (mSprite->getPlayAnimeName() != "summon") {
			mSprite->play("arms/summon");
			mSprite->setStep(0.8f);
		}
	}

	//�U�����
	if (mRight)mSprite->setScale(0.32f, 0.32f);
	else mSprite->setScale(-0.32f, 0.32f);

	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite->update((float)30 / 1000);
}

/*�����\���ǂ����̃`�F�b�N*/
void Cyanos::CheckCanSummon() {

}

/*�U���O�̌ŗL����*/
void Cyanos::ProcessBeforeAtack() {

}

/*�U����̌ŗL����*/
void Cyanos::ProcessAfterAtack() {
	if (mState == Parameter::S_ARMS_ATACK_C) {
		mBullet += 2;
		if (mBullet > mMaxBullet)mBullet = mMaxBullet;
	}
}

/*�U�����n�߂�*/
void Cyanos::StartAtack() {
	if (mPlayer->isCanArmsAtackState()) {

		if (mController.getKey(3) == 2 && !mController.getDown() && !mController.getUp() && isCanCancelTiming(Parameter::ATACK_C)) {
			mState = Parameter::S_ARMS_ATACK_C;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_C].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/c");
			mSprite->setStep(0.65f);
		}

		if (mController.getKey(3) == 2 && mController.getDown() && isCanCancelTiming(Parameter::ATACK_2C)) {
			mState = Parameter::S_ARMS_ATACK_2C;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_2C].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/2c");
			mSprite->setStep(1.0f);
		}

		if (mController.getKey(3) == 2 && !mController.getDown() && mController.getUp() && isCanCancelTiming(Parameter::ATACK_8C)) {
			mState = Parameter::S_ARMS_ATACK_8C;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_8C].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/8c");
			mSprite->setStep(0.65f);
		}

		if (mController.getKey(4) == 2 && mBullet >= 2 && !mController.getDown() && !mController.getUp() && isCanCancelTiming(Parameter::ATACK_D)) {
			mState = Parameter::S_ARMS_ATACK_D;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_D].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/d");
			mBullet -= 2;
		}

		if (mController.getKey(4) == 2 && mBullet >= 1 && mController.getDown() && !mController.getUp() && isCanCancelTiming(Parameter::ATACK_2D)) {
			mState = Parameter::S_ARMS_ATACK_2D;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_2D].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/2d");
			mSprite->setStep(0.5f);
			mBullet -= 1;
		}
	}
}

/*�`��*/
void Cyanos::Draw() {
	int mask;
	if (mState == Parameter::S_ARMS_ATACK_2C) {
		CreateMaskScreen();
		mask = LoadMask("Data/arms/PrimalSpheres/Cyanos/mask.png");
		DrawMask(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) -200,
			-30 - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2), mask, DX_MASKTRANS_NONE);
	}
	mSprite->draw();
	if (mState == Parameter::S_ARMS_ATACK_2C) {
		DeleteMask(mask);
		DeleteMaskScreen();
	}
}

/*�ŗLUI�̕`��*/
void Cyanos::DrawUI() {
	if (mPlayer->getPlayerId() == 0) {
		for (int i = 0; i < mMaxBullet; i++) {
			DrawGraph(20 + i * 50, 620, mGraphGauge2, true);
		}
		for (int i = 0; i < mBullet; i++) {
			DrawGraph(20 + i * 50, 620, mGraphGauge1, true);
		}
	}
	else {
		for (int i = 0; i < mMaxBullet; i++) {
			DrawGraph(900 + i * 50, 620, mGraphGauge2, true);
		}
		for (int i = 0; i < mBullet; i++) {
			DrawGraph(900 + i * 50, 620, mGraphGauge1, true);
		}
	}
}

