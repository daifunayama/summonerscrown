#include "Southern.h"
#include "../../../Application.h"

Arms::Profile Southern::getProfile() {
	Arms::Profile p;
	p.category = Parameter::HK;
	p.id = 3;
	p.size = 0.3f;
	p.speed = 0.6f;
	return p;
}

/*�O���t�B�b�N�̃��[�h*/
void Southern::LoadArmsGraphic() {
	//�v���C���[�̍쐬
	mSprite = ss::Player::create();

	//�A�j���f�[�^�����\�[�X�ɒǉ�
	//Application::resman->addData("Data/arms/HollyKnights/vein/vein.ssbp");
	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite->setData("Southern");// ssbp�t�@�C�����i�g���q�s�v�j
	
	//�v���C���[�̍쐬
	mSprite2 = ss::Player::create();

	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite2->setData("Southern");// ssbp�t�@�C�����i�g���q�s�v�j

	mIcon = LoadGraph("Data/arms/HollyKnights/vein/icon.png");

	mDistX = -100;
	mDistY = 30;
}

/*�T�E���h�̃��[�h*/
void Southern::LoadArmsSound() {
}

/*�A�j���[�V�����̍X�V*/
void Southern::UpdateArmsAnimation() {
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mSprite->getPlayAnimeName() != "wait_1") {
			mSprite->play("arms/wait_1");
			mSprite->setStep(0.6f);

			mSprite2->play("arms/wait_back");
			mSprite2->setStep(0.6f);
		}
	}
	if (mState == Parameter::S_ARMS_SUMMON) {
		if (mSprite->getPlayAnimeName() != "summon") {
			mSprite->play("arms/summon");
			mSprite->setStep(0.6f);

			mSprite2->stop();
		}
	}

	//�U�����
	if (mRight) {
		mSprite->setScale(0.3f, 0.25f);
		mSprite2->setScale(0.3f, 0.25f);
	}
	else {
		mSprite->setScale(-0.3f, 0.25f);
		mSprite2->setScale(-0.3f, 0.25f);
	}

	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite->update((float)30 / 1000);

	mSprite2->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite2->update((float)30 / 1000);
}

/*�U�����n�߂�*/
void Southern::StartAtack() {
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
void Southern::CheckCanSummon() {

}

/*����ŗL�̏���*/
void Southern::Process() {

}

/*�U����̌ŗL����*/
void Southern::ProcessAfterAtack() {

}

/*�ŗLUI�̕`��*/
void Southern::DrawUI() {

}

//�I�[�o�[���C�h


/*�v���C���[��Ǐ]����*/
void Southern::FollowPlayer(int pX, int pY) {
	double distX, distY, distAngle, moveX, moveY, speedX, speedY;

	distX = (double)(pX - mPositionX);
	distY = (double)(pY - mPositionY);


	distAngle = atan2(distY, distX);

	if (distX > 70 || distX < -70) {
		speedX = 10;
	}
	else speedX = abs(distX / 10);

	if (distY > 70 || distY < -70) {
		speedY = 10;
	}
	else speedY = abs(distY / 10);

	moveX = (double)cos(distAngle) * speedX;
	moveY = (double)sin(distAngle) * speedY;

	if (distX == 0)moveX = 0;
	if (distY == 0)moveY = 0;

	if(mRight)mPositionX = pX - mDistX;
	else mPositionX = pX + mDistX;

	mPositionY += (int)moveY;
}


void Southern::Draw() {
	mSprite->draw();
	
}

void Southern::DrawBack() {
	if(mState == Parameter::S_ARMS_NORMAL)mSprite2->draw();
}