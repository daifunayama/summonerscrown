#include <fstream>
#include "Player.h"
#include "../Parameter.h"
#include "../Input/Input.h"
#include "../Arms/FollowerArms.h"
#include "../Arms/Category/HollyKnights/Aries.h"
#include "../Arms/Category/HollyKnights/Southern.h"
#include "../Arms/Category/ArticArts/Alpha.h"
#include "../Arms/Category/EvilAnima/Enikuma.h"
#include "../Arms/Category/Comander/Cavalier.h"
#include "../Arms/Category/PrimalSpheres/Cyanos.h"
#include "../Utility.h"
#include "../Effekseer/AnimationController.h"
#include "../SSEffect/SSEffectController.h"
#include "DxLib.h"

Styles Player::getStyles() {
	string pass,tmp;
	ifstream ifs;
	Styles s;

	pass = "Data/character/";
	pass += getProfile().pass;
	pass += "/chara.txt";

	ifs.open(pass.c_str());
	if (ifs) {
		ifs >> tmp;
		ifs >> s.style;
		ifs >> s.str_style;
		ifs >> tmp;
		ifs >> s.ability;
		ifs >> s.str_ability;
		ifs >> tmp;
		ifs >> s.ultimate;
		ifs >> s.str_ultimate;
	}
	return s;
}

/*�v���C���[�f�[�^�̏�����*/
void Player::Init(int p) {
	mController.SetPlayerId(p);

	mState = Parameter::S_PLAYER_NORMAL;
	if (p == 0) {
		mPositionDX = 300.0;
		mRight = true;
	}
	else {
		mPositionDX = 500.0;
		mRight = false;
	}
	mPositionDY = Parameter::GROUND_LINE - mHeight;
	mPositionX = (int)mPositionDX;
	mPositionY = (int)mPositionDY;
	mAcceleX = 0;
	mAcceleY = 0;
	mHP = 1000;
	mEXP = 50;
	mChain = 0;
	mCircleCursor = 0;
	mGround = true;

	mArmsId = 0;
}

/*���ʂ̏�����*/
void Player::InitVolume() {
	ChangeVolumeSoundMem(128, mSoundBurst);
	ChangeVolumeSoundMem(128, mSoundDamage);
}

/*�O���t�B�b�N�̃��[�h*/
void Player::LoadGraphic() {

	mColor = 1;

	//�v���C���[�̍쐬
	mSprite = ss::Player::create();

	//�v���C���[�Ƀ��\�[�X�����蓖��
	mSprite->setData(getProfile().pass);// ssbp�t�@�C����

	mSprite->play(getProfile().pass + Utility::IntToString(getColor()) + "/idle");// �A�j���[�V���������w��

	//�\���ʒu��ݒ�
	mSprite->setPosition(400, 300);
	//�X�P�[���ݒ�
	mSprite->setScale(getProfile().size, getProfile().size);

	mSprite->setStep(getProfile().speed);

	mGraphShadow = LoadGraph("Data/graphic/game/shadow.png");
	mGraphDamage = LoadGraph("Data/graphic/animation/slash3.png");

	mGraphSummonEffect1 = LoadGraph("Data/graphic/animation/summon_effect1.png");
	mGraphSummonEffect2 = LoadGraph("Data/graphic/animation/summon_effect2.png");
	mAnimeBarrier = LoadGraph("Data/graphic/animation/barrier.png");
	mAnimeBurst1 = LoadGraph("Data/graphic/animation/burst1.png");
	mAnimeBurst2 = LoadGraph("Data/graphic/animation/burst2.png");
}

/*����f�[�^�̃��[�h*/
void Player::LoadArms(int p) {
	for(int i=0;i<8;i++)mArmsExist[i] = false;

	if (p == 0) {
		mArms[0] = new Cyanos();
		mArms[1] = new Cavalier();
		mArms[2] = new Southern();
		mArms[4] = new Aries();
		mArms[7] = new Alpha();
		mArmsExist[0] = true;
		mArmsExist[1] = true;
		mArmsExist[2] = true;
		mArmsExist[4] = true;
		mArmsExist[7] = true;
	}
	else {
		mArms[0] = new Enikuma();
		mArms[1] = new Cyanos();
		mArms[2] = new Cavalier();
		mArmsExist[0] = true;
		mArmsExist[1] = true;
		mArmsExist[2] = true;
	}
	
	for (int i = 0; i < 8; i++) {
		if (mArmsExist[i]) {
			mArms[i]->ReceivePlayer(this, mController);
			mArms[i]->InitArms();
			mArms[i]->LoadArmsData();
			mArms[i]->LoadArmsGraphic();
			mArms[i]->LoadArmsSound();
		}
	}
}

/*���ʃT�E���h�̃��[�h*/
void Player::LoadCommonSound() {
	mSoundOpenCircle = LoadSoundMem("Data/se/sen_ge_pis_kamaeru02.mp3");
	mSoundDamage = LoadSoundMem("Data/se/�葫�E����A�R��10.mp3");
	mSoundSummon = LoadSoundMem("Data/se/decision11.mp3");
	mSoundGuard = LoadSoundMem("Data/se/sen_ka_katana_04.mp3");
	mSoundCatch = LoadSoundMem("Data/se/���ށE�K�V�b01.mp3");
	mSoundEscape = LoadSoundMem("Data/se/setup1.mp3");
	mSoundBurst = LoadSoundMem("Data/se/burst.mp3");

	//ChangeVolumeSoundMem(128, mSoundBurst);
	//ChangeVolumeSoundMem(128, mSoundDamage);
}

/*�v���C���[�𓮂���*/
void Player::Move(Player& another) {
	//�R���g���[���[�̐ڑ�
	mController.ConvertInput();

	//�_��w���J��
	if (mController.getKey(5) > 0) {
		if (mController.getKey(5) == 1)PlaySoundMem(mSoundOpenCircle, DX_PLAYTYPE_BACK);
		mOpenCircle = true;
	}
	else {
		mOpenCircle = false;
		mCircleCursor = 0;
	}

	//�o���A���͂�E��������
	DoBarrier();

	//�R�l�N�V�����u���C�N
	if (mController.getKey(5) > 0 && mController.getKey(4) == 1)DoBurst();

	//�Î~�E���s��Ԃ̂Ƃ�
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//�E�����ւ̈ړ�
		if (mController.getRight() > 0) {
		
				if (mGround)mAcceleX = 8;

				//�_�b�V���E�X�e�b�v���n�߂�
				if (mController.getRight() == 1 && mRightCounter > 0) {
					mRight ? StartDash() : StartStep();
				}

				//�������10F�ȓ��Ȃ�΃_�b�V�����p�̃J�E���^�[��10�ɂ���
				mRightCounter = mController.getRight() < 10 ? 10 : 0;
			
		}
		else if (mRightCounter > 0)mRightCounter--;

		//�������ւ̈ړ�
		if (mController.getLeft() > 0) {
		
			
				if (mGround)mAcceleX = -8;

				//�_�b�V���E�X�e�b�v���n�߂�
				if (mController.getLeft() == 1 && mLeftCounter > 0) {
					mRight ? StartStep() : StartDash();
				}

				//�������10F�ȓ��Ȃ�΃_�b�V�����p�̃J�E���^�[��10�ɂ���
				mLeftCounter = mController.getLeft() < 10 ? 10 : 0;
			
		}
		else if (mLeftCounter > 0)mLeftCounter--;

		//���Ⴊ��
		if (mController.getDown() > 0 && mGround && mState == Parameter::S_PLAYER_NORMAL) {
			mState = Parameter::S_PLAYER_SQUAT;
			mAcceleX = 0;
		}
	}

	if (mState == Parameter::S_PLAYER_NORMAL || isAtackState()) {
		//�W�����v����
		if (mController.getUp() == 2 && !mOpenCircle &&
			!mController.getKey(1) && !mController.getKey(2) && !mController.getKey(3) && !mController.getKey(4)) {
			
			if (mGround) {
				mState = Parameter::S_PLAYER_NORMAL;
				DoJump();
			}
			else if (!mAirJumped) {
				mState = Parameter::S_PLAYER_NORMAL;
				DoAirJump();
			}
		}
	}

	//���Ⴊ��
	else if (mState == Parameter::S_PLAYER_SQUAT) {
		//����������Ă��Ȃ���Η���
		mAcceleX = 0;
		if (!mController.getDown())mState = Parameter::S_PLAYER_NORMAL;
	}

	//�_�b�V��
	else if (mState == Parameter::S_PLAYER_DASH) {
		DoDash();
	}

	//�K�[�h
	else if (mState == Parameter::S_PLAYER_GUARD || mState == Parameter::S_PLAYER_GUARD_S) {
		mAcceleX = mRight ? -2 : 2;
	}

	//�X�e�b�v
	else if (mState == Parameter::S_PLAYER_STEP) {
		DoStep();
	}

	//�o�[�X�g
	else if (mState == Parameter::S_PLAYER_BURST) {
		mAcceleX = 0;
		mAcceleY = 0;
	}

	//�_���[�W��
	else if (isDamageState())DoDamaged();

	//��������
	if (mState == Parameter::S_PLAYER_NORMAL || mState == Parameter::S_PLAYER_SQUAT) {
		if (mOpenCircle && mGround) {
			if (mController.getKey(6) == 1) {
				StartSummon();
			}
		}
	}

	//�U�����n�߂�
	if(!mBarrier && mState == Parameter::S_PLAYER_NORMAL || mState == Parameter::S_PLAYER_SQUAT ||
		isAtackState())StartAtack();

	//�������n�߂�
	if(mState == Parameter::S_PLAYER_NORMAL || isAtackState())StartThrow(another);

	//�����ʂ�
	if (mState == Parameter::S_PLAYER_CAUGHT) {
		if (mController.getKey(1) == 1 &&
			(mController.getRight() > 0 && mController.getRight() < 3 || mController.getLeft() > 0 && mController.getLeft() < 3)) {

			mState = Parameter::S_PLAYER_ESCAPE;
			another.mState = Parameter::S_PLAYER_ESCAPE;
			another.mAcceleX = mRight ? 20 : -20;
			mAcceleX = 0;
			mCounter = 15;
			another.mCounter = 15;

			PlaySoundMem(mSoundEscape, DX_PLAYTYPE_BACK);
		}
	}

	//�U���̃v���Z�X
	if (isAtackState())DoAtack();

	//�����̃v���Z�X
	if (mState == Parameter::S_PLAYER_THROW)DoThrow(another);

	//�_��w�̃J�[�\��
	if (mOpenCircle) {
		MoveCircleCursor();
	}

	//�����x��0�ɂ���
	if ((!mController.getRight() && !mController.getLeft() || mOpenCircle)
		&& mGround && mState == Parameter::S_PLAYER_NORMAL ||
		(mBarrier && mGround))
	{
		mAcceleX = 0;
	}

	//�J�E���^�[�����炵�A0�̂Ƃ�����Ԃ֑J��
	DecrementCounter(another);

	//�d�͂̏���
	if (!mGround && mState != Parameter::S_PLAYER_BURST)mAcceleY -= 2;

	//�v���C���[�̈ړ�
	mPositionDX += mAcceleX;
	mPositionDY -= mAcceleY;

	mPositionX = (int)mPositionDX;
	mPositionY = (int)mPositionDY;

	//�ǂƏ��̐ڐG����
	CheckWallHit();
}

/*�W�����v����*/
void Player::DoJump() {
	//�E����
	if (mController.getRight())mAcceleX = 8;
	//������
	else if (mController.getLeft())mAcceleX = -8;
	//����
	else mAcceleX = 0;

	//Y�������x
	mAcceleY = 38;

	//�ڒn�t���O��false��
	mGround = false;
}

/*�󒆃W�����v����*/
void Player::DoAirJump() {
	//�E����
	if (mController.getRight())mAcceleX = 8;
	//������
	else if (mController.getLeft())mAcceleX = -8;
	//����
	else mAcceleX = 0;

	//Y�������x
	mAcceleY = 30;

	mAirJumped = true;
}

/*�o���A���͂�*/
void Player::DoBarrier() {
	static int mBarrierCounter;
	//�o���A���͂�
	if ((mRight && mController.getLeft() > 0 || !mRight && mController.getRight() > 0)
		&& (mController.getKey(1) > 0 && mController.getKey(2) > 0 || mController.getKey(7) > 0) && mEXP > 0 &&
		(mState == Parameter::S_PLAYER_NORMAL || mState == Parameter::S_PLAYER_SQUAT ||
			mState == Parameter::S_PLAYER_GUARD || mState == Parameter::S_PLAYER_GUARD_S)) {

		if (!mBarrier)mBarrierId = AnimationController::getInstance().Create(mAnimeBarrier, 1, 0, 0, 200, 300, 1.2, 0, 4, 2, 144, 144, mRight, false);
		mBarrier = true;
		AnimationController::getInstance().SetPosition(mBarrierId, mPositionX + (mRight ? +50 : -50),
			(mState == Parameter::S_PLAYER_NORMAL || mState == Parameter::S_PLAYER_GUARD) ? mPositionY : mPositionY + 50);
	}
	//�o���A����������
	else if (mBarrier) {
		mBarrier = false;
		mBarrierCounter = 0;
		AnimationController::getInstance().Remove(mBarrierId);
	}

	if (mBarrier) {
		mBarrierCounter++;
		if(mBarrierCounter % 10 == 0)mEXP--;
	}
}

/*�R�l�N�V�����u���C�N*/
void Player::DoBurst() {
	mState = Parameter::S_PLAYER_BURST;
	mCounter = 60;
	AnimationController::getInstance().Create(mAnimeBurst1, 1, mPositionX, mPositionY, 500, 500, 1.5, 0, 4, 1, 63, -1, mRight, false);
	AnimationController::getInstance().Create(mAnimeBurst2, 3, mPositionX, mPositionY, 500, 500, 1.5, 0, 4, 1, 63, -1, mRight, false);
	PlaySoundMem(mSoundBurst, DX_PLAYTYPE_BACK, true);
}

/*�������n�߂�*/
void Player::StartSummon() {
	int pX;

	//�_��w�ɖ�����݂���Ƃ�
	if (mArmsExist[mCircleCursor] && mArmsId != mCircleCursor && mArms[mArmsId]->getState() == Parameter::S_ARMS_NORMAL) {
		pX = mRight ? mPositionX - 100 : mPositionX + 100;

		mArmsId = mCircleCursor;
		mArms[mArmsId]->StartSummon();

		AnimationController::getInstance().Create(mGraphSummonEffect1, 1, pX, 500, 400, 400, 1.2, 0, 4, 1, 40, 0, true, false);
		AnimationController::getInstance().Create(mGraphSummonEffect2, 2, pX, 500, 400, 400, 1.2, 0, 4, 1, 40, 0, true, false);

		PlaySoundMem(mSoundSummon, DX_PLAYTYPE_BACK);
	}
}

/*��������*/
void Player::DoSummon() {
	
}

/*�������n�߂�*/
void Player::StartThrow(Player& another) {
	if (mController.getKey(1) == 1 && mController.getRight() > 0 && mController.getRight() < 3) {
		if (mRight && mGround && another.mGround &&
			mPositionX + 50 > another.mPositionX - another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth() &&
			mPositionX + 50 <= another.mPositionX - another.mHitBox[another.mState].getPositionX()) {
			mAcceleX = 0;
			mThrowDirection = true;
			mState = Parameter::S_PLAYER_CATCH;
			another.mState = Parameter::S_PLAYER_CAUGHT;
			mCounter = 30;
			PlaySoundMem(mSoundCatch, DX_PLAYTYPE_BACK);
		}
	}
	if (mController.getKey(1) == 1 && mController.getLeft() > 0 && mController.getLeft() < 3) {
		if (!mRight && mGround && another.mGround &&
			mPositionX - 50 <= another.mPositionX + another.mHitBox[another.mState].getPositionX() + another.mHitBox[another.mState].getWidth() &&
			mPositionX - 50 > another.mPositionX + another.mHitBox[another.mState].getPositionX()) {
			mAcceleX = 0;
			mThrowDirection = true;
			mState = Parameter::S_PLAYER_CATCH;
			another.mState = Parameter::S_PLAYER_CAUGHT;
			mCounter = 30;
			PlaySoundMem(mSoundCatch, DX_PLAYTYPE_BACK);
		}
	}
}

/*������*/
void Player::DoThrow(Player& another) {
	if (mCounter == 25) {
		if (mRight) another.mAcceleX = mThrowDirection ? 40 : -40;
		else another.mAcceleX = mThrowDirection ? -40 : 40;
		another.mAcceleY = 40;
		another.mGround = false;
		another.mState = Parameter::S_PLAYER_DAMAGE_AIR;
		another.mDamageCounter = 0;
		another.mCounter = 30;
	}
}

/*�U�����n�߂�*/
void Player::StartAtack() {

	//A�U��
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		!mController.getDown() && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_A].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
	//A���U��
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		mController.getDown() && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_2A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2A].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
	//B�U��
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		!mController.getDown() && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_B].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_B].PlayVoice();
	}
	//B���U��
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_2B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2B].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
	//6B�U��
	if (mController.getKey(2) == 1 && !mController.getUp() && !mController.getDown() && (mRight && mController.getRight() || !mRight && mController.getLeft()) && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_6B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_6B].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
}

/*�U��*/
void Player::DoAtack() {
	int sId = 0;

	//A�U��
	if (mState == Parameter::S_PLAYER_ATACK_A) {

		//SE������ꍇ�Đ�
		sId = mPlayerAtack[Parameter::P_ATACK_A].getFrameData(mPlayerAtack[Parameter::P_ATACK_A].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_A].IncreaseCounter();

		//�U���I�����̏���
		if (mPlayerAtack[Parameter::P_ATACK_A].CheckAtackEnd()) {
			mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//A���U��
	if (mState == Parameter::S_PLAYER_ATACK_2A) {

		//SE������ꍇ�Đ�
		sId = mPlayerAtack[Parameter::P_ATACK_2A].getFrameData(mPlayerAtack[Parameter::P_ATACK_2A].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_2A].IncreaseCounter();

		//�U���I�����̏���
		if (mPlayerAtack[Parameter::P_ATACK_2A].CheckAtackEnd()) {
			//����������Ă����炵�Ⴊ�񂾂܂�
			if(mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//B�U��
	if (mState == Parameter::S_PLAYER_ATACK_B) {

		//SE������ꍇ�Đ�
		sId = mPlayerAtack[Parameter::P_ATACK_B].getFrameData(mPlayerAtack[Parameter::P_ATACK_B].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_B].IncreaseCounter();

		//�U���I�����̏���
		if (mPlayerAtack[Parameter::P_ATACK_B].CheckAtackEnd()) {
			mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//B���U��
	if (mState == Parameter::S_PLAYER_ATACK_2B) {

		//SE������ꍇ�Đ�
		sId = mPlayerAtack[Parameter::P_ATACK_2B].getFrameData(mPlayerAtack[Parameter::P_ATACK_2B].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_2B].IncreaseCounter();

		//�U���I�����̏���
		if (mPlayerAtack[Parameter::P_ATACK_2B].CheckAtackEnd()) {
			//����������Ă����炵�Ⴊ�񂾂܂�
			if (mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//3B�U��
	if (mState == Parameter::S_PLAYER_ATACK_3B) {

		//SE������ꍇ�Đ�
		sId = mPlayerAtack[Parameter::P_ATACK_3B].getFrameData(mPlayerAtack[Parameter::P_ATACK_3B].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_3B].IncreaseCounter();

		//�U���I�����̏���
		if (mPlayerAtack[Parameter::P_ATACK_3B].CheckAtackEnd()) {
			//����������Ă����炵�Ⴊ�񂾂܂�
			if (mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//6B�U��
	if (mState == Parameter::S_PLAYER_ATACK_6B) {

		//SE������ꍇ�Đ�
		sId = mPlayerAtack[Parameter::P_ATACK_6B].getFrameData(mPlayerAtack[Parameter::P_ATACK_6B].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_6B].IncreaseCounter();

		//�U���I�����̏���
		if (mPlayerAtack[Parameter::P_ATACK_6B].CheckAtackEnd()) {
			//����������Ă����炵�Ⴊ�񂾂܂�
			if (mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//JA�U��
	if (mState == Parameter::S_PLAYER_ATACK_JA) {

		//SE������ꍇ�Đ�
		sId = mPlayerAtack[Parameter::P_ATACK_JA].getFrameData(mPlayerAtack[Parameter::P_ATACK_JA].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_JA].IncreaseCounter();

		//�U���I�����̏���
		if (mPlayerAtack[Parameter::P_ATACK_JA].CheckAtackEnd()) {
			//����������Ă����炵�Ⴊ�񂾂܂�
			if (mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//JB�U��
	if (mState == Parameter::S_PLAYER_ATACK_JB) {

		//SE������ꍇ�Đ�
		sId = mPlayerAtack[Parameter::P_ATACK_JB].getFrameData(mPlayerAtack[Parameter::P_ATACK_JB].getCounter()).getSoundId();
		if (sId > 0 && sId < 10)PlaySoundMem(mSoundPlayerAtack[sId], DX_PLAYTYPE_BACK);

		mPlayerAtack[Parameter::P_ATACK_JB].IncreaseCounter();

		//�U���I�����̏���
		if (mPlayerAtack[Parameter::P_ATACK_JB].CheckAtackEnd()) {
			//����������Ă����炵�Ⴊ�񂾂܂�
			if (mController.getDown())mState = Parameter::S_PLAYER_SQUAT;
			else mState = Parameter::S_PLAYER_NORMAL;
		}
	}

	//�e�U���Ǝ��̏���
	ProcessAtack();
}

/*�_�b�V�����n�߂�*/
void Player::StartDash() {
	mState = Parameter::S_PLAYER_DASH;
	mCounter = 15;
}

/*�_�b�V��*/
void Player::DoDash() {
	mAcceleX = mRight ? 20 : -20;
	mAcceleY = 0;
}

/*�X�e�b�v���n�߂�*/
void Player::StartStep() {
	mState = Parameter::S_PLAYER_STEP;
	mCounter = 15;
}

/*�X�e�b�v*/
void Player::DoStep() {
	mAcceleX = mRight ? -20 : 20;
	mAcceleY = 0;
}

/*�_���[�W���̏���*/
void Player::DoDamaged() {
	mDamageCounter++;
	
	if (mAcceleX > 0)mAcceleX--;
	if (mAcceleX < 0)mAcceleX++;
}

/*�J�E���^�[�����炵0�̂Ƃ�����Ԃ�*/
void Player::DecrementCounter(Player &another) {
	if (mCounter > 0) {
		mCounter--;

		if (mCounter == 0) {
			//�_�b�V�����ʏ�
			if (mState == Parameter::S_PLAYER_DASH)mState = Parameter::S_PLAYER_NORMAL;

			//�X�e�b�v���ʏ�
			else if (mState == Parameter::S_PLAYER_STEP)mState = Parameter::S_PLAYER_NORMAL;

			//�_���[�W���ʏ�
			else if (isDamageState() && mState != Parameter::S_PLAYER_DAMAGE_AIR2) {
				if(!mController.getDown())mState = Parameter::S_PLAYER_NORMAL;
				else mState = Parameter::S_PLAYER_SQUAT;
				another.setChain(0);
			}

			//�_�E�����ʏ�
			else if (mState == Parameter::S_PLAYER_DOWN) {
				another.setChain(0);
				mState = Parameter::S_PLAYER_NORMAL;
			}
			//�����K�[�h
			else if (mState == Parameter::S_PLAYER_GUARD) {
				mState = Parameter::S_PLAYER_NORMAL;
				mAcceleX = 0;
			}
			//���Ⴊ�݃K�[�h
			else if (mState == Parameter::S_PLAYER_GUARD_S) {
				mState = Parameter::S_PLAYER_SQUAT;
				mAcceleX = 0;
			}
			else if (mState == Parameter::S_PLAYER_BURST) {
				mState = Parameter::S_PLAYER_NORMAL;
			}
			else if (mState == Parameter::S_PLAYER_CATCH) {
				mState = Parameter::S_PLAYER_THROW;
				mCounter = 30;
				if (mRight && mController.getLeft() || !mRight && mController.getRight())mThrowDirection = false;
			}
			else if (mState == Parameter::S_PLAYER_THROW) {
				mState = Parameter::S_PLAYER_NORMAL;
			}
			else if (mState == Parameter::S_PLAYER_ESCAPE) {
				mState = Parameter::S_PLAYER_NORMAL;
			}
		}
	}
}

void Player::DecrementHitStop() {
	if (mHitStop > 0)mHitStop--;
}

/*�U�����*/
void Player::ChangeDirection(Player& another) {
	if (mRight) {
		if (mGround && mPositionX > another.mPositionX
			&& mState == Parameter::S_PLAYER_NORMAL)mRight = false;
	}
	else {
		if (mGround && mPositionX < another.mPositionX
			&& mState == Parameter::S_PLAYER_NORMAL)mRight = true;
	}
	mArms[mArmsId]->setRight(mRight);
}

/*�U����H�炤*/
void Player::EatAtack(int atackType,bool right,BoxData boxdata) {
	mEatAtackData = boxdata;
	if (atackType == 1)mEatAtackFlag = 1;
	if (atackType == 2)mEatAtackFlag = 2;
	if (atackType == 3)mEatAtackFlag = 3;
	mEatAtackRight = right;
}

/*�_���[�W��H�炤*/
void Player::EatDamage(Player& another) {
	int effectY;
	/*
	atackType  ��E���E���i(0,1,2)
	guardType  �ʏ�E�K�[�s�E��K�[�s(0,1,2)
	*/
	
	//���̃t���[�����_���[�W��H�����
	if (mEatAtackFlag) {

		//�o���A�K�[�h
		if (mBarrier && mEatAtackFlag == 1 && (mController.getRight() && !mRight || mController.getLeft() && mRight)) {
			if (mController.getDown())mState = Parameter::S_PLAYER_GUARD_S;
			else mState = Parameter::S_PLAYER_GUARD;
			mCounter = 10;

			PlaySoundMem(mSoundGuard, DX_PLAYTYPE_BACK);
		}

		//��i�K�[�h����
		else if (mGround && mEatAtackData.getAtackType() == 0 &&
			(mController.getRight() && !mRight || mController.getLeft() && mRight)) {

			if (mController.getDown())mState = Parameter::S_PLAYER_GUARD_S;
			else mState = Parameter::S_PLAYER_GUARD;
			mCounter = 10;

			PlaySoundMem(mSoundGuard, DX_PLAYTYPE_BACK);
		}

		//���i�K�[�h����
		else if (mGround && mEatAtackData.getAtackType() == 1 && mController.getDown() &&
			(mController.getRight() && !mRight || mController.getLeft() && mRight)) {

			mState = Parameter::S_PLAYER_GUARD_S;
			mCounter = 10;

			PlaySoundMem(mSoundGuard, DX_PLAYTYPE_BACK);
		}

		//���i�K�[�h����
		else if (mGround && mEatAtackData.getAtackType() == 2 && !mController.getDown() &&
			(mController.getRight() && !mRight || mController.getLeft() && mRight)) {

			mState = Parameter::S_PLAYER_GUARD;
			mCounter = 10;

			PlaySoundMem(mSoundGuard, DX_PLAYTYPE_BACK);
		}

		//�󒆃K�[�h
		else if (!mGround && (mController.getRight() && !mRight || mController.getLeft() && mRight)) {
			mState = Parameter::S_PLAYER_GUARD;
			mCounter = 10;

			PlaySoundMem(mSoundGuard, DX_PLAYTYPE_BACK);
		}

		//�K�[�h���s
		else {

			if (mGround) {
				if (mState == Parameter::S_PLAYER_SQUAT || mState == Parameter::S_PLAYER_DAMAGE_S)
					mState = Parameter::S_PLAYER_DAMAGE_S;
				else {
					if (mEatAtackData.getAtackType() == 1)mState = Parameter::S_PLAYER_DAMAGE_D;
					else mState = Parameter::S_PLAYER_DAMAGE_U;
				}
				mCounter = mEatAtackData.getHitStop();
				mHP -= mEatAtackData.getPower();
				another.mEXP += mEatAtackData.getEXGain();
				if (another.mEXP > 100)another.mEXP = 100;
				mDamageCounter = 0;

				mAcceleX = mEatAtackRight ? mEatAtackData.getVectorX() : -mEatAtackData.getVectorX();

				mAcceleY = mEatAtackData.getVectorY();

				if (mAcceleY > 0) {
					mState = Parameter::S_PLAYER_DAMAGE_AIR;
					mGround = false;
				}
			}
			else {
				mState = Parameter::S_PLAYER_DAMAGE_AIR;

				mCounter = mEatAtackData.getHitStop();
				mHP -= mEatAtackData.getPower();
				mDamageCounter = 0;

				mAcceleX = mEatAtackRight ? mEatAtackData.getAirVectorX() : -mEatAtackData.getAirVectorX();

				mAcceleY = mEatAtackData.getAirVectorY();
			}

			if (mEatAtackData.getForceDown())mState = Parameter::S_PLAYER_DAMAGE_AIR2;

			//�`�F�[���𑝉�������
			another.IncleaseChain();

			PlaySoundMem(mSoundDamage, DX_PLAYTYPE_BACK);

			if (mEatAtackData.getEffectType() == 0) {
				if (mEatAtackData.getAtackType() == 0)effectY = mPositionY;
				else effectY = mPositionY + 80;
				AnimationController::getInstance().Create(mGraphDamage, 1, mPositionX, effectY, 600, 400, 1.2, GetRand(359), 4, 2, 48, 0, true, true);
			}
			if (mEatAtackData.getEffectType() == 1) {
				if (mEatAtackData.getAtackType() == 0)effectY = mPositionY;
				else effectY = mPositionY + 80;
				AnimationController::getInstance().Create(mGraphDamage, 1, mPositionX, effectY, 600, 400, 2, GetRand(359), 4, 2, 48, 0, true, true);
			}
			if (mEatAtackData.getEffectType() == 2) {
				if (mEatAtackData.getAtackType() == 0)effectY = mPositionY - 150;
				else effectY = mPositionY - 250;
				SSEffectController::getInstance().Play("mye1/mye1", mPositionX, effectY, 0.9f, 1.0f, 0.6f, GetRand(359), 200);
			}

			mHitStop = 0;
			another.mHitStop = 0;
		}
		
	}

	mEatAtackFlag = 0;
}

/*����𓮂���*/
void Player::MoveArms() {
	mArms[mArmsId]->ReceivePlayer(this, mController);
	mArms[mArmsId]->Move();
	mArms[mArmsId]->UpdateArmsAnimation();
}

/*�����`�悷��*/
void Player::DrawArms() {
	mArms[mArmsId]->Draw();
}

/*��������g�̌��ɕ`�悷��*/
void Player::DrawArmsBack() {
	mArms[mArmsId]->DrawBack();
}

/*�_��w�̃J�[�\���ړ�*/
void Player::MoveCircleCursor() {
	if (mController.getUp() && !mController.getRight() && !mController.getLeft())mCircleCursor = 0;
	if (mController.getUp() && mController.getRight())mCircleCursor = 1;
	if (!mController.getUp() && mController.getRight() && !mController.getDown())mCircleCursor = 2;
	if (mController.getRight() && mController.getDown())mCircleCursor = 3;
	if (!mController.getRight() && mController.getDown() && !mController.getLeft())mCircleCursor = 4;
	if (mController.getDown() && mController.getLeft())mCircleCursor = 5;
	if (!mController.getDown() && mController.getLeft() && !mController.getUp())mCircleCursor = 6;
	if (mController.getLeft() && mController.getUp())mCircleCursor = 7;

	//if (!mController.getUp() && !mController.getRight() && !mController.getDown() && !mController.getLeft())mCircleCursor = 0;
}

/*�v���C���[���m�̓����蔻��*/
void Player::CheckPlayersHit(Player& another) {
	Box box1, box2;
	int centerX;

	//���@��
	if (mRight && !another.mRight) {
		//P1�̃{�b�N�X
		box1.x = mPositionX + mHitBox[mState].getPositionX();
		box1.y = mPositionY + mHitBox[mState].getPositionY();
		box1.width = mHitBox[mState].getWidth();
		box1.height = mHitBox[mState].getHeight();

		//P2�̃{�b�N�X
		box2.x = another.mPositionX -
			another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth();
		box2.y = another.mPositionY + another.mHitBox[another.mState].getPositionY();
		box2.width = another.mHitBox[another.mState].getWidth();
		box2.height = mHitBox[another.mState].getHeight();

		if (Utility::CheckBoxHit(box1, box2)) {

			//�������n�ʂɂ���
			if (mGround && another.mGround) {

				//1P��2P�ɋ߂Â��Ă���
				if (mAcceleX > 0 && another.mAcceleX == 0) {
					another.mPositionDX = mPositionX + mHitBox[mState].getPositionX() + mHitBox[mState].getWidth()
						+ another.mHitBox[another.mState].getPositionX() + another.mHitBox[another.mState].getWidth();
					another.mPositionX = (int)another.mPositionDX;
				}
				//2P��1P�ɋ߂Â��Ă���
				else if (mAcceleX == 0 && another.mAcceleX < 0) {
					mPositionDX = (another.mPositionX - another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth())
						- mHitBox[mState].getPositionX() - mHitBox[mState].getWidth();
					mPositionX = (int)mPositionDX;
				}
				//�������ߕt��
				else {
					centerX = (mPositionX + another.mPositionX) / 2;

					mPositionDX = centerX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth();
					mPositionX = (int)mPositionDX;
					another.mPositionDX = centerX + (another.mHitBox[another.mState].getWidth() + another.mHitBox[another.mState].getPositionX());
					another.mPositionX = (int)another.mPositionDX;
				}
				//�ǂɖ��܂�ꍇ�̏���
				//1P���ǂɖ��܂�
				if (mPositionX + mHitBox[mState].getPositionX() < 0) {
					mPositionDX = -mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
					another.mPositionDX = mHitBox[mState].getWidth()
						+ (another.mHitBox[another.mState].getWidth() + another.mHitBox[another.mState].getPositionX());
					another.mPositionX = (int)another.mPositionDX;
				}
				//2P���ǂɖ��܂�
				if (another.mPositionX - another.mHitBox[another.mState].getPositionX() > Parameter::FIELD_WIDTH) {
					another.mPositionDX = Parameter::FIELD_WIDTH + another.mHitBox[another.mState].getPositionX();
					another.mPositionX = (int)another.mPositionDX;
					mPositionDX = Parameter::FIELD_WIDTH
						- another.mHitBox[another.mState].getWidth() - mHitBox[mState].getWidth() - mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
				}
			}


			//2P�������n�ʂɂ���
			if (!mGround && another.mGround) {
			
				if (mAcceleY < 0) {
					mAcceleX = 0;
					if (mPositionX >= another.mPositionX)mPositionDX += 5;
					else mPositionDX -= 5;
					mPositionX = (int)mPositionDX;
				}

				//�ǂɖ��܂�ꍇ�̏���
				//1P���ǂɖ��܂�
				if (mPositionX + mHitBox[mState].getPositionX() < 0) {
					mPositionDX = -mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
					another.mPositionDX = mHitBox[mState].getWidth()
						+ (another.mHitBox[another.mState].getWidth() + another.mHitBox[another.mState].getPositionX());
					another.mPositionX = (int)another.mPositionDX;
				}
				//2P���ǂɖ��܂�
				if (another.mPositionX - another.mHitBox[another.mState].getPositionX() > Parameter::FIELD_WIDTH) {
					another.mPositionDX = Parameter::FIELD_WIDTH + another.mHitBox[another.mState].getPositionX();
					another.mPositionX = (int)another.mPositionDX;
					mPositionDX = Parameter::FIELD_WIDTH
						- another.mHitBox[another.mState].getWidth() - mHitBox[mState].getWidth() - mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
				}
			}
		}
	}

	//���@��
	if (!mRight && another.mRight) {
		//P1�̃{�b�N�X
		box1.x = another.mPositionX + another.mHitBox[mState].getPositionX();
		box1.y = another.mPositionY + another.mHitBox[another.mState].getPositionY();
		box1.width = another.mHitBox[mState].getWidth();
		box1.height = another.mHitBox[mState].getHeight();

		//P2�̃{�b�N�X
		box2.x = mPositionX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth();
		box2.y = mPositionY + mHitBox[mState].getPositionY();
		box2.width = mHitBox[mState].getWidth();
		box2.height = mHitBox[mState].getHeight();

		if (Utility::CheckBoxHit(box1, box2)) {

			if (mGround && another.mGround) {
				//1P��2P�ɋ߂Â��Ă���
				if (another.mAcceleX > 0 && mAcceleX == 0) {
					mPositionDX = another.mPositionX + another.mHitBox[another.mState].getPositionX() + another.mHitBox[another.mState].getWidth()
						+ mHitBox[mState].getPositionX() + mHitBox[mState].getWidth();
					mPositionX = (int)mPositionDX;
				}
				//2P��1P�ɋ߂Â��Ă���
				else if (another.mAcceleX == 0 && mAcceleX < 0) {
					another.mPositionDX = (mPositionX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth())
						- another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth();
					another.mPositionX = (int)another.mPositionDX;
				}
				//�������ߕt��
				else {
					centerX = (mPositionX + another.mPositionX) / 2;

					another.mPositionDX = centerX - another.mHitBox[another.mState].getPositionX() - another.mHitBox[another.mState].getWidth();
					another.mPositionX = (int)another.mPositionDX;
					mPositionDX = centerX + (mHitBox[mState].getWidth() + mHitBox[mState].getPositionX());
					mPositionX = (int)mPositionDX;
				}
				//�ǂɖ��܂�ꍇ�̏���
				//�PP���ǂɖ��܂�
				if (another.mPositionX + mHitBox[another.mState].getPositionX() < 0) {
					another.mPositionDX = -another.mHitBox[another.mState].getPositionX();
					another.mPositionX = (int)another.mPositionDX;
					mPositionDX = another.mHitBox[another.mState].getWidth()
						+ (mHitBox[mState].getWidth() + mHitBox[mState].getPositionX());
					mPositionX = (int)mPositionDX;
				}
				//�QP���ǂɖ��܂�
				if (mPositionX - mHitBox[mState].getPositionX() > Parameter::FIELD_WIDTH) {
					mPositionDX = Parameter::FIELD_WIDTH + mHitBox[mState].getPositionX();
					mPositionX = (int)mPositionDX;
					another.mPositionDX = Parameter::FIELD_WIDTH
						- mHitBox[mState].getWidth() - another.mHitBox[another.mState].getWidth() - another.mHitBox[another.mState].getPositionX();
					another.mPositionX = (int)another.mPositionDX;
				}
			}
		}
	}


}

/*�ǁE���Ƃ̃q�b�g�`�F�b�N*/
void Player::CheckWallHit() {

	//�E�����̂Ƃ�
	if (mRight) {
		//����
		if (mPositionX + mHitBox[mState].getPositionX() < 0) {
			mPositionDX = -mHitBox[mState].getPositionX();
		}
		//�E��
		if (mPositionX + mHitBox[mState].getPositionX() + mHitBox[mState].getWidth() > Parameter::FIELD_WIDTH) {
			mPositionDX = Parameter::FIELD_WIDTH - mHitBox[mState].getWidth() - mHitBox[mState].getPositionX();
		}
	}

	//�������̂Ƃ�
	else {
		//����
		if (mPositionX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth() < 0) {
			mPositionDX = mHitBox[mState].getPositionX() + mHitBox[mState].getWidth();
		}
		//�E��
		if (mPositionX - mHitBox[mState].getPositionX() > Parameter::FIELD_WIDTH) {
			mPositionDX = Parameter::FIELD_WIDTH + mHitBox[mState].getPositionX();
		}
	}

	//��
	if (mPositionDY > Parameter::GROUND_LINE - mHeight) {
		mPositionDY = Parameter::GROUND_LINE - mHeight;
		mAcceleY = 0;
		mAcceleX = 0;
		mGround = true;
		mAirJumped = false;
		if (mState == Parameter::S_PLAYER_DAMAGE_AIR2) {
			mState = Parameter::S_PLAYER_DOWN;
			mCounter = 40;
		}
	}

	mPositionX = (int)mPositionDX;
	mPositionY = (int)mPositionDY;
}

/*���z���ǂƂ̐ڐG����*/
void Player::CheckVirtualWallHit(Player &another) {
	
	//1P����
	if (mPositionX < another.mPositionX) {
		if (mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) < - mHitBox[mState].getPositionX()
			&& another.mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) > Parameter::WINDOW_WIDTH + another.mHitBox[another.mState].getPositionX()) 
		{
			//1P�������Ă���
			if (mAcceleX != 0 && another.mAcceleX == 0) {
				mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) - mHitBox[mState].getPositionX();
			}
			//2P�������Ă���
			else if(mAcceleX == 0 && another.mAcceleX != 0) {
				another.mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) + Parameter::WINDOW_WIDTH + another.mHitBox[another.mState].getPositionX()+1;
			}

			else {
				mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) - mHitBox[mState].getPositionX();
				another.mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) + Parameter::WINDOW_WIDTH + another.mHitBox[another.mState].getPositionX();
			}

			mPositionX = (int)mPositionDX;
			another.mPositionX = (int)another.mPositionDX;

			Camera::getInstance().setCenterX((mPositionX + another.mPositionX) / 2);
		}
	}
	//2P����
	else {
		if (another.mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) < -another.mHitBox[another.mState].getPositionX()
			&& mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) > Parameter::WINDOW_WIDTH + mHitBox[mState].getPositionX())
		{
			//2P�������Ă���
			if (another.mAcceleX != 0 && mAcceleX == 0) {
				another.mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) - another.mHitBox[another.mState].getPositionX();
			}
			//1P�������Ă���
			else if (another.mAcceleX == 0 && mAcceleX != 0) {
				mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) + Parameter::WINDOW_WIDTH + mHitBox[mState].getPositionX() + 1;
			}

			else {
				another.mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) - another.mHitBox[another.mState].getPositionX();
				mPositionDX = (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2) + Parameter::WINDOW_WIDTH + mHitBox[mState].getPositionX();
			}

			mPositionX = (int)mPositionDX;
			another.mPositionX = (int)another.mPositionDX;

			Camera::getInstance().setCenterX((mPositionX + another.mPositionX) / 2);
		}
	}
}

/*�v���C���[�̍U���̓����蔻��*/
void Player::CheckPlayersAtackHit(Player& another) {
	int atackId, counter;
	Box box1, box2;
	bool atackHit = false;

	atackId = mState - 18;
	counter = mPlayerAtack[atackId].getCounter();

	if (isAtackState()) {
		for (int i = 0; i < 20 && !atackHit; i++) {
			//�Y���t���[���ɍU���p�{�b�N�X�����݂���Ƃ�
			if (mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				if (!mPlayerAtack[atackId].getAtackHit()) {

					//����̃q�b�g�{�b�N�X�Ɣ�r
					for (int j = 0; j < 10 && !atackHit; j++) {

						//����̃_���[�W�{�b�N�X�����݂���Ƃ�
						if (another.mDamageBox[another.mState][j].getExist()) {

							//���g���E����
							if (mRight) {
								box1.x = mPositionX + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX();
							}
							//���g��������
							else
								box1.x = mPositionX - mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
								- mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth();

							box1.y = mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY();
							box1.width = mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth();
							box1.height = mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight();

							//���肪�E����
							if (another.mRight) {
								box2.x = another.mPositionX + another.mDamageBox[another.mState][j].getPositionX();
							}
							//���肪������
							else {
								box2.x = another.mPositionX
									- another.mDamageBox[another.mState][j].getPositionX() - another.mDamageBox[another.mState][j].getWidth();
							}
							box2.y = another.mPositionY + another.mDamageBox[another.mState][j].getPositionY();
							box2.width = another.mDamageBox[another.mState][j].getWidth();
							box2.height = another.mDamageBox[another.mState][j].getHeight();

							//�U��������Ƀq�b�g
							if (Utility::CheckBoxHit(box1, box2)) {
							
								//�{�b�N�XID���擾
								int boxId = mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getBoxId();
								
								//����ɍU����^����
								another.EatAtack(1,mRight,mPlayerAtack[atackId].getFrameData(counter).getAtackBoxData(boxId));
								atackHit = true;

								//�U�������ɓ��������t���O�����Ă�
								if(!mPlayerAtack[atackId].getFrameData(counter).getAtackBoxData(boxId).getAllowMultHit())mPlayerAtack[atackId].setAtackHit(true);

								break;
							}
						}
					}
				}
			}
		}
	}

	if (mState == Parameter::S_PLAYER_BURST && mCounter == 50) {
		//����̃q�b�g�{�b�N�X�Ɣ�r
		for (int j = 0; j < 10 && !atackHit; j++) {

			//����̃_���[�W�{�b�N�X�����݂���Ƃ�
			if (another.mDamageBox[another.mState][j].getExist()) {

				//���g���E����
				if (mRight) {
					box1.x = mPositionX - 250;
				}
				//���g��������
				else
					box1.x = mPositionX + 250;

				box1.y = mPositionY - 250;
				box1.width = 500;
				box1.height = 500;

				//���肪�E����
				if (another.mRight) {
					box2.x = another.mPositionX + another.mDamageBox[another.mState][j].getPositionX();
				}
				//���肪������
				else {
					box2.x = another.mPositionX
						- another.mDamageBox[another.mState][j].getPositionX() - another.mDamageBox[another.mState][j].getWidth();
				}
				box2.y = another.mPositionY + another.mDamageBox[another.mState][j].getPositionY();
				box2.width = another.mDamageBox[another.mState][j].getWidth();
				box2.height = another.mDamageBox[another.mState][j].getHeight();

				//�U��������Ƀq�b�g
				if (Utility::CheckBoxHit(box1, box2)) {
					BoxData boxData;
					boxData.setAtackType(0);
					boxData.setEffectType(-1);
					boxData.setSEType(0);
					boxData.setGuardType(0);
					boxData.setAllowMultHit(0);
					boxData.setHitStop(20);
					boxData.setDecHitStop(0);
					boxData.setBindTime(0);
					boxData.setContinueAtackAfterOffset(0);
					boxData.setForceDown(0);
					boxData.setFloorBound(0);
					boxData.setWallBound(0);
					boxData.setShakeWindow(0);
					boxData.setVectorX(40);
					boxData.setVectorY(40);
					boxData.setAirVectorX(30);
					boxData.setAirVectorY(5);
					boxData.setPower(0);
					boxData.setEXGain(0);
				
					//����ɍU����^����
					another.EatAtack(3,mRight, boxData);
					atackHit = true;


					break;
				}
			}
		}
	}
}

/*�O���t�B�b�N�̕`��*/
void Player::Draw() {
	DrawShadow();
	mSprite->draw();\
}

/*�e��`��*/
void Player::DrawShadow() {
	DrawGraph(mPositionX - 60 - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), 
		Parameter::GROUND_LINE - 70 - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2), mGraphShadow, true);
}

/*�q�b�g�{�b�N�X�̕`��*/
void Player::DrawHitBox() {

	//�v���C���[�̃q�b�g�{�b�N�X
	if (!isAtackState()) {

		//���ߐݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

		//�{�b�N�X�����݂���Ƃ�
		if (mHitBox[mState].getExist()) {
			//�v���C���[���E�����̂Ƃ�
			if (mRight) {
				DrawBox(
					mPositionX + mHitBox[mState].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mHitBox[mState].getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					mPositionX + mHitBox[mState].getPositionX() + mHitBox[mState].getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mHitBox[mState].getPositionY() + mHitBox[mState].getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					Parameter::COLOR_GREEN, true);
			}
			//�v���C���[���������̂Ƃ�
			else {
				DrawBox(
					mPositionX - mHitBox[mState].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mHitBox[mState].getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					mPositionX - mHitBox[mState].getPositionX() - mHitBox[mState].getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mHitBox[mState].getPositionY() + mHitBox[mState].getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					Parameter::COLOR_GREEN, true);
			}
		}

		//���ߐݒ�����ǂ�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

/*�_���[�W�{�b�N�X�̕`��*/
void Player::DrawDamageBox() {

	//�v���C���[�̃q�b�g�{�b�N�X
	if (!isAtackState()) {

		//���ߐݒ�
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

		//�v���C���[�̃_���[�W�{�b�N�X

		for (int i = 0; i < 10; i++) {
			//�{�b�N�X�����݂���Ƃ�
			if (mDamageBox[mState][i].getExist()) {
				//�v���C���[���E�����̂Ƃ�
				if (mRight) {
					DrawBox(
						mPositionX + mDamageBox[mState][i].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
						mPositionY + mDamageBox[mState][i].getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
						mPositionX + mDamageBox[mState][i].getPositionX() + mDamageBox[mState][i].getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
						mPositionY + mDamageBox[mState][i].getPositionY() + mDamageBox[mState][i].getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
						Parameter::COLOR_BLUE, true);
				}
				//�v���C���[���������̂Ƃ�
				else {
					DrawBox(
						mPositionX - mDamageBox[mState][i].getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
						mPositionY + mDamageBox[mState][i].getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
						mPositionX - mDamageBox[mState][i].getPositionX() - mDamageBox[mState][i].getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
						mPositionY + mDamageBox[mState][i].getPositionY() + mDamageBox[mState][i].getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
						Parameter::COLOR_BLUE, true);
				}
			}
		}

		//���ߐݒ�����ǂ�
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

/*�U���{�b�N�X�̕`��*/
void Player::DrawAtackBox() {
	int atackId, counter;

	atackId = mState - 18;
	counter = mPlayerAtack[atackId].getCounter();

	//���ߐݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

	//�E�����̂Ƃ�
	if (mRight) {
		for (int i = 0; i < 20; i++) {
			if (mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					mPositionX + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
					+ mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY()
					+ mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					Parameter::COLOR_RED, true);
			}
			else break;
		}
	}

	//�������̂Ƃ�
	else {
		for (int i = 0; i < 20; i++) {
			if (mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX - mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					mPositionX - mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
					- mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY()
					+ mPlayerAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					Parameter::COLOR_RED, true);
			}
			else break;
		}
	}

	//���ߐݒ�����ǂ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/*�����x�̉e�����󂯂��Ԃ��ǂ���*/
bool Player::isAcceledState() {
	if (mState == Parameter::S_PLAYER_DASH
		|| mState == Parameter::S_PLAYER_STEP
		|| mState == Parameter::S_PLAYER_DAMAGE_U
		|| mState == Parameter::S_PLAYER_DAMAGE_D
		|| mState == Parameter::S_PLAYER_DAMAGE_S
		|| mState == Parameter::S_PLAYER_DAMAGE_AIR
		|| mState == Parameter::S_PLAYER_DAMAGE_AIR2)
	{
		return true;
	}
	else return false;
}

/*�U����Ԃ��ǂ���*/
bool Player::isAtackState() {
	if (mState == Parameter::S_PLAYER_ATACK_A
		|| mState == Parameter::S_PLAYER_ATACK_8A
		|| mState == Parameter::S_PLAYER_ATACK_2A
		|| mState == Parameter::S_PLAYER_ATACK_JA
		|| mState == Parameter::S_PLAYER_ATACK_B
		|| mState == Parameter::S_PLAYER_ATACK_8B
		|| mState == Parameter::S_PLAYER_ATACK_2B
		|| mState == Parameter::S_PLAYER_ATACK_3B
		|| mState == Parameter::S_PLAYER_ATACK_6B
		|| mState == Parameter::S_PLAYER_ATACK_JB)
	{
		return true;
	}
	else return false;
}

/*�_���[�W��Ԃ��ǂ���*/
bool Player::isDamageState() {
	if (mState == Parameter::S_PLAYER_DAMAGE_U
		|| mState == Parameter::S_PLAYER_DAMAGE_D
		|| mState == Parameter::S_PLAYER_DAMAGE_S
		|| mState == Parameter::S_PLAYER_DAMAGE_AIR
		|| mState == Parameter::S_PLAYER_DAMAGE_AIR2)
	{
		return true;
	}
	else return false;
}

/*�K�[�h��Ԃ��ǂ���*/
bool Player::isGuardState() {
	if (mState == Parameter::S_PLAYER_GUARD
		|| mState == Parameter::S_PLAYER_GUARD_S)
	{
		return true;
	}
	else return false;
}

/*����U���\���ǂ���*/
bool Player::isCanArmsAtackState() {
	if (
		mState == Parameter::S_ARMS_NORMAL ||
		mState == Parameter::S_PLAYER_SQUAT ||
		isAtackState()
		)
	{
		return true;
	}
	return false;
}

/*�L�����Z���\�ȃ^�C�~���O���ǂ���*/
bool Player::isCanCancelTiming(int atackId) {
	int counter;

	if (mState == Parameter::S_ARMS_NORMAL || mState == Parameter::S_PLAYER_SQUAT)return true;

	if (isAtackState()) {
		counter = mPlayerAtack[mState - 18].getCounter();

		if (mPlayerAtack[mState - 18].getFrameData(counter).getAllowCancel()) {
			if (mPlayerAtack[mState - 18].getAllowCancel(atackId)) {
				return true;
			}
		}
	}
	return false;
}