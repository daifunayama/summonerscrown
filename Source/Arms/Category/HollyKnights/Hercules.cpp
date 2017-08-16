#include "Hercules.h"
#include "../../../Application.h"
#include "../../../Effekseer/AnimationController.h"

Arms::Profile Hercules::getProfile() {
	Arms::Profile p;
	p.category = Parameter::HK;
	p.id = 6;
	p.type = 4;
	p.size = 0.3f;
	p.speed = 0.6f;
	return p;
}

/*�O���t�B�b�N�̃��[�h*/
void Hercules::LoadArmsGraphic() {
	//�v���C���[�̍쐬
	mSprite = ss::Player::create();

	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite->setData("Hercules");// ssbp�t�@�C�����i�g���q�s�v�j

	mIcon = LoadGraph("Data/arms/HollyKnights/Hercules/icon.png");

	mDistX = 300;
	mDistY = -800;
}

/*�T�E���h�̃��[�h*/
void Hercules::LoadArmsSound() {
	mSoundAtack[1] = LoadSoundMem("Data/arms/HollyKnights/Hercules/se1.mp3");
}

/*�A�j���[�V�����̍X�V*/
void Hercules::UpdateArmsAnimation() {
	
	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
		Parameter::WINDOW_HEIGHT - mPositionY + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	mSprite->update((float)30 / 1000);

}

/*�U�����n�߂�*/
void Hercules::StartAtack() {

	mState = Parameter::S_ARMS_SUMMON;
	if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
	else mPositionX = mPlayer->getPositionX() - mDistX;

	mPositionY = mPlayer->getPositionY() + mDistY;
	mCounter = 0;

	mAtack.InitAtack();
	mRight = mPlayer->getRight();
	
	mSprite->play("arms/summon");
	mSprite->setStep(0.8f);

	mSprite->setScale(mRight ? 0.5f:-0.5f, 0.5f);
}

/*�����\���ǂ����̃`�F�b�N*/
void Hercules::CheckCanSummon() {

}

/*����ŗL�̏���*/
void Hercules::Process() {
	if (mCounter == 1) {

		AnimationController::getInstance().Create(mGraphSummonEffect1, 1, mPositionX-30, mPositionY+400, 400, 400, 1.5, 360, 4, 1, 40, 0, true, false);
		AnimationController::getInstance().Create(mGraphSummonEffect2, 2, mPositionX-30, mPositionY+400, 400, 400, 1.5, 360, 4, 1, 40, 0, true, false);

	}
}

/*�U����̌ŗL����*/
void Hercules::ProcessAfterAtack() {

}
