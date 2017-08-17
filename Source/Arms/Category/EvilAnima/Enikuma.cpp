#include "Enikuma.h"
#include "../../../Application.h"

Arms::Profile Enikuma::getProfile() {
	Arms::Profile p;
	p.category = Parameter::EA;
	p.id = 2;
	p.size = 0.25f;
	p.speed = 0.6f;
	return p;
}

/*�O���t�B�b�N�̃��[�h*/
void Enikuma::LoadArmsGraphic() {
	//�v���C���[�̍쐬
	mSprite = ss::Player::create();

	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite->setData("Enikuma");// ssbp�t�@�C�����i�g���q�s�v�j

	mIcon = LoadGraph("Data/arms/EvilAnima/Enikuma/icon.png");

	mDistX = -100;
	mDistY = 0;
}

/*�T�E���h�̃��[�h*/
void Enikuma::LoadArmsSound() {
}

/*�A�j���[�V�����̍X�V*/
void Enikuma::UpdateArmsAnimation() {
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
void Enikuma::StartAtack() {
	if (mPlayer->isCanArmsAtackState() && mState == Parameter::S_ARMS_NORMAL) {

		if (mController.getKey(4) == 1) {
			mState = Parameter::S_ARMS_ATACK_D;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_D].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/d");
			mSprite->setStep(0.7);
		}

		if (mController.getKey(3) == 1) {
			mState = Parameter::S_ARMS_ATACK_C;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_C].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/c");
			mSprite->setStep(0.7);
		}
	}
}

/*�����\���ǂ����̃`�F�b�N*/
void Enikuma::CheckCanSummon() {

}

/*����ŗL�̏���*/
void Enikuma::Process() {

}

/*�U����̌ŗL����*/
void Enikuma::ProcessAfterAtack() {

}
