#include "SSEffectController.h"
#include "../Application.h"

/*���\�[�X�̃��[�h*/
void SSEffectController::Load() {

	//�A�j���f�[�^�����\�[�X�ɒǉ�
	Application::resman->addData("Data/sprite_effects/ParticleEffectSample.ssbp");

	for (int i = 0; i < 5; i++) {
		//�v���C���[�̍쐬
		mSSEffect[i] = ss::Player::create();

		//�v���C���[�Ƀ��\�[�X�����蓖��
		mSSEffect[i]->setData("ParticleEffectSample");// ssbp�t�@�C����
	}
	

}

/*�A�j���[�V�����̍Đ�*/
void SSEffectController::Play(string pass, int positionX, int positionY, float scaleX, float scaleY, float speed,float angle, int alpha) {
	mSSEffect[mActive]->play(pass.c_str());
	
	mSSEffect[mActive]->setPosition(positionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), positionY);
	//�X�P�[���ݒ�
	mSSEffect[mActive]->setScale(scaleX, scaleY);
	//��]��ݒ�
	mSSEffect[mActive]->setRotation(0.0f, 0.0f, angle);
	//�����x��ݒ�
	mSSEffect[mActive]->setAlpha(alpha);
	//���]��ݒ�
	mSSEffect[mActive]->setFlip(false, false);

	mSSEffect[mActive]->setLoop(1);
	mSSEffect[mActive]->setStep(speed);

	mActive++;
	if (mActive >= 5)mActive = 0;

}

/*�X�V*/
void SSEffectController::Process() {
	for(int i=0;i<5;i++)mSSEffect[i]->update((float)30 / 1000);
}

/*�`��*/
void SSEffectController::Draw() {
	for (int i = 0; i<5; i++)mSSEffect[i]->draw();
}