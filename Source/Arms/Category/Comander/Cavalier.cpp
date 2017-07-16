#include "Cavalier.h"
#include "../../../Application.h"

/*�O���t�B�b�N�̃��[�h*/
void Cavalier::LoadArmsGraphic() {
	//�v���C���[�̍쐬
	mSprite = ss::Player::create();

	//�A�j���f�[�^�����\�[�X�ɒǉ�
	Application::resman->addData("Data/arms/Comander/Cavalier/cavalier.ssbp");
	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite->setData("cavalier");// ssbp�t�@�C�����i�g���q�s�v�j
	//�Đ����郂�[�V������ݒ�
	mSprite->play("arms/wait");// �A�j���[�V���������w��(ssae��/�A�j���[�V���������\�A�ڂ����͌�q)

	//�\���ʒu��ݒ�
	mSprite->setPosition(400, 300);
	//�X�P�[���ݒ�
	mSprite->setScale(0.25f, 0.25f);
	//��]��ݒ�
	mSprite->setRotation(0.0f, 0.0f, 0.0f);
	//�����x��ݒ�
	mSprite->setAlpha(255);
	//���]��ݒ�
	mSprite->setFlip(false, false);

	mSprite->setStep(0.5f);

	mIcon = LoadGraph("Data/arms/Comander/Cavalier/icon.png");
	mGraphBullet = LoadGraph("Data/arms/Comander/bullet.png");

}

/*�T�E���h�̃��[�h*/
void Cavalier::LoadArmsSound() {
	mSoundAtack[1] = LoadSoundMem("Data/arms/Comander/Cavalier/se1.mp3");
	mSoundAtack[2] = LoadSoundMem("Data/arms/Comander/Cavalier/se2.mp3");
	mSoundAtack[3] = LoadSoundMem("Data/arms/Comander/Cavalier/gun-reload1.mp3");
	
	ChangeVolumeSoundMem(128, mSoundAtack[3]);
}

/*�A�j���[�V�����̍X�V*/
void Cavalier::UpdateArmsAnimation() {
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mSprite->getPlayAnimeName() != "wait") {
			mSprite->play("arms/wait");
			mSprite->setStep(0.5f);
		}
	}
	if (mState == Parameter::S_ARMS_SUMMON) {
		if (mSprite->getPlayAnimeName() != "summon") {
			mSprite->play("arms/summon");
			mSprite->setStep(0.8f);
		}
	}

	//�U�����
	if (mRight)mSprite->setScale(0.25f, 0.25f);
	else mSprite->setScale(-0.25f, 0.25f);


	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), Parameter::WINDOW_HEIGHT - mPositionY);
	mSprite->update((float)30 / 1000);
}

/*�U�����n�߂�*/
void Cavalier::StartAtack() {
	if (mPlayer->isCanArmsAtackState() && mState == Parameter::S_ARMS_NORMAL) {

		if (mController.getKey(4) == 1 && mBullet > 0) {
			mState = Parameter::S_ARMS_ATACK_D;
			if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
			else mPositionX = mPlayer->getPositionX() - mDistX;

			mPositionY = mPlayer->getPositionY() + mDistY;

			mAtack[Parameter::ATACK_D].InitAtack();
			mRight = mPlayer->getRight();

			mSprite->play("arms/d");
			mBullet--;
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
void Cavalier::CheckCanSummon() {

}

/*����ŗL�̏���*/
void Cavalier::Process() {

}

/*�U����̌ŗL����*/
void Cavalier::ProcessAfterAtack() {
	if (mState == Parameter::S_ARMS_ATACK_2C) {
		if (mBullet < mMaxBullet)mBullet++;
	}
}

/*�ŗLUI�̕`��*/
void Cavalier::DrawUI() {
	if (mPlayer->getPlayerId() == 0) {
		for (int i = 0; i < mBullet; i++) {
			DrawGraph(50 + i * 40, 620, mGraphBullet, true);
		}
	}
	else {
		for (int i = 0; i < mBullet; i++) {
			DrawGraph(1000 + i * 40, 620, mGraphBullet, true);
		}
	}
}