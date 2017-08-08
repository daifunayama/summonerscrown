#include "Aries.h"
#include "../../../Application.h"

Arms::Profile Aries::getProfile() {
	Arms::Profile p;
	p.category = Parameter::HK;
	p.id = 0;
	p.size = 0.3f;
	p.speed = 0.6f;
	return p;
}

/*�O���t�B�b�N�̃��[�h*/
void Aries::LoadArmsGraphic() {
	//�v���C���[�̍쐬
	mSprite = ss::Player::create();

	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite->setData("Aries");// ssbp�t�@�C�����i�g���q�s�v�j

	mIcon = LoadGraph("Data/arms/HollyKnights/Aries/icon.png");

	mDistX = -100;
	mDistY = 0;
}

/*�T�E���h�̃��[�h*/
void Aries::LoadArmsSound() {
}

/*�A�j���[�V�����̍X�V*/
void Aries::UpdateArmsAnimation() {
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mSprite->getPlayAnimeName() != "wait") {
			mSprite->play("arms/wait");
			mSprite->setStep(0.6f);
		}
	}
	if (mState == Parameter::S_ARMS_SUMMON) {
		if (mSprite->getPlayAnimeName() != "summon") {
			mSprite->play("arms/summon");
			mSprite->setStep(0.6f);
		}
	}

	//�U�����
	if (mRight) {
		mSprite->setScale(0.3f, 0.3f);
	}
	else {
		mSprite->setScale(-0.3f, 0.3f);
	}

	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite->update((float)30 / 1000);

}

/*�U�����n�߂�*/
void Aries::StartAtack() {
	if (mPlayer->isCanArmsAtackState() && mState == Parameter::S_ARMS_NORMAL) {

		if (mController.getKey(4) == 1) {
			mState = Parameter::S_ARMS_ATACK_D;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_D].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/d");
		}

		if (mController.getKey(3) == 1 && mController.getDown()) {
			mState = Parameter::S_ARMS_ATACK_2C;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_2C].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/2c");
			mSprite->setStep(0.7);
		}
	}
}

/*�����\���ǂ����̃`�F�b�N*/
void Aries::CheckCanSummon() {

}

/*����ŗL�̏���*/
void Aries::Process() {

}

/*�U����̌ŗL����*/
void Aries::ProcessAfterAtack() {

}
