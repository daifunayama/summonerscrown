#include "BattleScene.h"
#include "../Input/Input.h"
#include "../Effekseer/AnimationController.h"
#include "../Player/Character/Ein.h"
#include "../Player/Character/Ria.h"
#include "../Player/Character/Kare-meshi.h"
#include "../Arms/FollowerArms.h"
#include "../SSEffect/SSEffectController.h"
#include "../Camera/Camera.h"

/*���\�[�X�̃��[�h�Ə�����*/
void BattleScene::Load() {
	mPlayer[0] = new Ein();
	mPlayer[1] = new KareMeshi();

	for (int p= 0; p < 2; p++) {
		//�v���C���[�̃��[�h
		mPlayer[p]->setPlayerId(p);
		mPlayer[p]->LoadGraphic();//�O���t�B�b�N�̃��[�h
		mPlayer[p]->LoadCommonSound();//����SE�̃��[�h
		mPlayer[p]->LoadSound();//�ŗLSE�̃��[�h
		mPlayer[p]->LoadVoice();//�{�C�X�̃��[�h
		mPlayer[p]->LoadData();//�{�b�N�X�f�[�^�̃��[�h
		mPlayer[p]->LoadAtack();//�U���f�[�^�̃��[�h
		mPlayer[p]->Init(p);//�v���C���[�̏�����

		//����̃��[�h
		mPlayer[p]->LoadArms(p);

		//HP�Q�[�W�̐ݒ�
		mHPGauge[p].setPlayerId(p);
		mHPGauge[p].Load();

		//EX�Q�[�W�̐ݒ�
		mEXGauge[p].setPlayerId(p);
		mEXGauge[p].Load();

		//�`�F�[���̐ݒ�
		mChain[p].setPlayerId(p);
		mChain[p].Load();

		//�_��w�̐ݒ�
		mContractCircle[p].setPlayerId(p);
		mContractCircle[p].Load(*mPlayer[p]);
	}
	//�w�i�̃��[�h
	mBackGround.LoadGraphic();

	SSEffectController::getInstance().Load();

	//�J�����̏�����
	Camera::getInstance().Init();

	mBGM = LoadSoundMem("Data/bgm/night2.mp3");
	ChangeVolumeSoundMem(100, mBGM);
	PlaySoundMem(mBGM, DX_PLAYTYPE_LOOP);
}

/*�X�V*/
void BattleScene::Process() {
	if (Input::getInstance().GetKey(KEY_INPUT_F) == 1) {
		mPlayer[0]->LoadAtack();//�U���f�[�^�̃��[�h
		mPlayer[1]->LoadAtack();//�U���f�[�^�̃��[�h
		mPlayer[0]->LoadData();
		mPlayer[1]->LoadData();
		mPlayer[0]->LoadArms(0);
	}

	if (Input::getInstance().GetKey(KEY_INPUT_A) == 1) {
		mPlayer[0]->Init(0);
		mPlayer[1]->Init(1);
		mPlayer[0]->getArms(mPlayer[0]->getArmsId())->setPositionX(mPlayer[0]->getPositionX());
		mPlayer[0]->getArms(mPlayer[0]->getArmsId())->setPositionY(mPlayer[0]->getPositionY());
		mPlayer[1]->getArms(mPlayer[1]->getArmsId())->setPositionX(mPlayer[1]->getPositionX());
		mPlayer[1]->getArms(mPlayer[1]->getArmsId())->setPositionY(mPlayer[1]->getPositionY());
	}

	//�v���C���[�̓���
	mPlayer[0]->Move(*mPlayer[1]);
	mPlayer[1]->Move(*mPlayer[0]);

	//����̓���
	mPlayer[0]->MoveArms();
	mPlayer[1]->MoveArms();

	//�w�i�Ƀv���C���[����n��
	mBackGround.GetPlayer(*mPlayer[0], *mPlayer[1]);

	//�v���C���[���m�̓����蔻��
	mPlayer[0]->CheckPlayersHit(*mPlayer[1]);

	//���z�ǂƂ̐ڐG����
	mPlayer[0]->CheckVirtualWallHit(*mPlayer[1]);

	//����̍U���̓����蔻��
	mPlayer[0]->getArms(mPlayer[0]->getArmsId())->CheckArmsAtackHit(*mPlayer[1]);
	mPlayer[1]->getArms(mPlayer[1]->getArmsId())->CheckArmsAtackHit(*mPlayer[0]);

	//�v���C���[�̍U���̓����蔻��
	mPlayer[0]->CheckPlayersAtackHit(*mPlayer[1]);
	mPlayer[1]->CheckPlayersAtackHit(*mPlayer[0]);

	//�U�����
	mPlayer[0]->ChangeDirection(*mPlayer[1]);
	mPlayer[1]->ChangeDirection(*mPlayer[0]);

	//�v���C���[���U����H������Ƃ��̏���
	mPlayer[0]->EatDamage(*mPlayer[1]);
	mPlayer[1]->EatDamage(*mPlayer[0]);

	//�v���C���[�̃A�j���[�V�����̍X�V
	if (mPlayer[0]->getHitStop() == 0)mPlayer[0]->UpdateAnimation();
	if (mPlayer[1]->getHitStop() == 0)mPlayer[1]->UpdateAnimation();

	//HP�Q�[�W�֔��f
	mHPGauge[0].Process(*mPlayer[0], *mPlayer[1]);
	mHPGauge[1].Process(*mPlayer[1], *mPlayer[0]);

	//EX�Q�[�W�֔��f
	mEXGauge[0].Process(*mPlayer[0]);
	mEXGauge[1].Process(*mPlayer[1]);

	//�`�F�[���֔��f
	mChain[0].Process(*mPlayer[0]);
	mChain[1].Process(*mPlayer[1]);

	//�_��w�֔��f
	mContractCircle[0].Process(*mPlayer[0]);
	mContractCircle[1].Process(*mPlayer[1]);

	mPlayer[0]->DecrementHitStop();
	mPlayer[1]->DecrementHitStop();

	//�A�j���[�V�����̃v���Z�X
	AnimationController::getInstance().Process();

	SSEffectController::getInstance().Process();

	//�J�����̃A�b�v�f�[�g
	Camera::getInstance().Update(*mPlayer[0], *mPlayer[1]);
}

/*�`��*/
void BattleScene::Drawing() {
	static bool boxDrawFlag = false;

	if (Input::getInstance().GetKey(KEY_INPUT_G) == 1)boxDrawFlag = !boxDrawFlag;

	//�w�i�̕`��
	mBackGround.Draw();

	//HP�Q�[�W��`��
	mHPGauge[0].Draw();
	mHPGauge[1].Draw();

	//�_��w��`��
	mContractCircle[0].Draw();
	mContractCircle[1].Draw();

	AnimationController::getInstance().DrawLayer3();

	mPlayer[0]->DrawArmsBack();
	mPlayer[1]->DrawArmsBack();

	//�v���C���[�̕`��
	if(CheckDrawPriority(*mPlayer[0],*mPlayer[1]) == 0){
		mPlayer[1]->Draw();
		mPlayer[0]->Draw();
	}
	else {
		mPlayer[0]->Draw();
		mPlayer[1]->Draw();
	}

	AnimationController::getInstance().DrawLayer2();

	mPlayer[0]->DrawArms();
	mPlayer[1]->DrawArms();

	//�A�j���[�V�����̕`��
	AnimationController::getInstance().DrawLayer1();

	//�G�t�F�N�g�̕`��
	SSEffectController::getInstance().Draw();

	//�q�b�g�{�b�N�X��\������
	if (boxDrawFlag) {
		mPlayer[0]->DrawHitBox();
		mPlayer[0]->DrawDamageBox();
		mPlayer[1]->DrawHitBox();
		mPlayer[1]->DrawDamageBox();

		if (mPlayer[0]->isAtackState())mPlayer[0]->DrawAtackBox();
		if (mPlayer[1]->isAtackState())mPlayer[1]->DrawAtackBox();
		if (mPlayer[0]->getArms(mPlayer[0]->getArmsId())->isAtackState())mPlayer[0]->getArms(0)->DrawAtackBox();
		if (mPlayer[1]->getArms(mPlayer[1]->getArmsId())->isAtackState())mPlayer[1]->getArms(0)->DrawAtackBox();
	}

	mPlayer[0]->getArms(mPlayer[0]->getArmsId())->DrawUI();
	mPlayer[1]->getArms(mPlayer[1]->getArmsId())->DrawUI();

	//EX�Q�[�W��`��
	mEXGauge[0].Draw();
	mEXGauge[1].Draw();

	//�`�F�[����`��
	mChain[0].Draw();
	mChain[1].Draw();

	if (mPlayer[1]->isDamageState()) {
		DrawBox(100, 200, mPlayer[1]->getCounter() * 4 + 100, 250, Parameter::COLOR_RED, true);
	}
}

/*�`��̗D�揇�ʂ�Ԃ�*/
int BattleScene::CheckDrawPriority(Player& p1, Player& p2) {
	//�_���[�W���̃v���C���[������
	if (p1.isDamageState() && !p2.isDamageState())return 1;
	if (p2.isDamageState() && !p1.isDamageState())return 0;
	if (p1.isDamageState() && p2.isDamageState())return 0;

	//�K�[�h���̃v���C���[������
	if (p1.isGuardState() && !p2.isGuardState())return 1;
	if (p2.isGuardState() && !p1.isGuardState())return 0;
	if (p1.isGuardState() && p2.isGuardState())return 0;

	//�U�����̃v���C���[��O�Ɂ@�����̏ꍇ��o���̕���D��
	if (p1.isAtackState() && !p2.isAtackState())return 0;
	if (p2.isAtackState() && !p1.isAtackState())return 1;
	if (p1.isAtackState() && p2.isAtackState()) {
		return p1.getPlayerAtack(p1.getState() - 18).getCounter() <= p2.getPlayerAtack(p1.getState() - 18).getCounter() ?
			0 : 1;
	}

	return 0;
}