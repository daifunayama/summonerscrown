#include <fstream>
#include "../../Application.h"
#include "../../SSPlayer/SS5Player.h"
#include "../../Utility.h"
#include "../../Atack/FrameData.h"
#include "Remnant.h"

Profile Remnant::getProfile() {
	Profile p;
	p.name = "�����i���g";
	p.eName = "Remnant";
	p.pass = "remnant";

	p.size = 0.32f;
	p.speed = 0.4f;
	p.distX = 0;
	p.distY = -30;

	p.cAtack = 4;
	p.lAtack = 4;
	p.aut = 2;
	p.pAtack = 4;
	p.sAtack = 3;
	return p;
}


/*�T�E���h�̃��[�h*/
void Remnant::LoadSound() {
	mSoundDash = LoadSoundMem("Data/se/highspeed-movement1.mp3");
	mSoundStep = mSoundDash;

	mSoundPlayerAtack[1] = LoadSoundMem("Data/se/Cyber06-1.mp3");
	mSoundPlayerAtack[2] = LoadSoundMem("Data/se/���{�b�g�E����A�R��02.mp3");
	mSoundPlayerAtack[3] = mSoundDash;

	ChangeVolumeSoundMem(128, mSoundDash);
	ChangeVolumeSoundMem(128, mSoundStep);
	ChangeVolumeSoundMem(128, mSoundPlayerAtack[2]);
}

/*�{�C�X�̃��[�h*/
void Remnant::LoadVoice() {
}

/*�v���C���[�f�[�^�����[�h*/
void Remnant::LoadData() {
	ifstream ifs;
	string tmp;

	string statebox[15] =
	{ "normal","walk","back","squat","jump",
		"damage_u","damage_d","damage_air","damage_air2",
		"damage_squat","summon","dash","step","guard","guar_squat" };

	//�{�b�N�X�̏�����
	for (int i = 0; i<15; i++) {
		mHitBox[i].setExist(0);

		for (int j = 0; j < 10; j++) {
			mDamageBox[i][j].setExist(0);
		}
	}

	//�_���[�W�{�b�N�X�̓ǂݍ���

	ifs.clear();
	ifs.open("Data/character/remnant/DamageBoxData.txt");

	if (ifs) {
		ifs >> mHeight;//����
		ifs >> mSquatY;//���Ⴊ�ݎ�Y���W�␳
		ifs >> mDownY;//�_�E����Y���W�␳

		ifs >> tmp;

		for (int i = 1; i < 15; i++) {
			for (int j = 0; j < 10; j++) {
				ifs >> tmp;
				if (tmp == statebox[i])break;
				mDamageBox[i][j].setPositionX(Utility::StringToInt(tmp));
				ifs >> tmp;
				mDamageBox[i][j].setPositionY(Utility::StringToInt(tmp));
				ifs >> tmp;
				mDamageBox[i][j].setWidth(Utility::StringToInt(tmp));
				ifs >> tmp;
				mDamageBox[i][j].setHeight(Utility::StringToInt(tmp));

				mDamageBox[i][j].setExist(1);
			}
		}
	}
	ifs.close();

	//�v���C���[�̓����蔻��̓ǂݍ���

	ifs.clear();
	ifs.open("Data/character/remnant/HitBoxData.txt");

	if (ifs) {
		for (int i = 1; i < 15; i++) {
			ifs >> tmp;
			ifs >> tmp;
			mHitBox[i].setPositionX(Utility::StringToInt(tmp));
			ifs >> tmp;
			mHitBox[i].setPositionY(Utility::StringToInt(tmp));
			ifs >> tmp;
			mHitBox[i].setWidth(Utility::StringToInt(tmp));
			ifs >> tmp;
			mHitBox[i].setHeight(Utility::StringToInt(tmp));

			mHitBox[i].setExist(1);
		}
	}
	ifs.close();
}

/*�U���f�[�^�̃��[�h*/
void Remnant::LoadAtack() {
	ifstream ifs;
	int n;
	int boxId;
	int frameCounter;
	int boxCounter = 0;
	string tmp;

	FrameData frameData;
	BoxData boxData;
	HitBox hitBox;

	for (int a = 0; a < 6; a++) {

		if (a == 0)mPlayerAtack[Parameter::P_ATACK_A].ClearFrameData();
		if (a == 1)mPlayerAtack[Parameter::P_ATACK_B].ClearFrameData();
		if (a == 2)mPlayerAtack[Parameter::P_ATACK_2A].ClearFrameData();
		if (a == 3)mPlayerAtack[Parameter::P_ATACK_2B].ClearFrameData();
		if (a == 4)mPlayerAtack[Parameter::P_ATACK_3B].ClearFrameData();
		if (a == 5)mPlayerAtack[Parameter::P_ATACK_6B].ClearFrameData();

		hitBox.setExist(false);
		for (int i = 0; i < 20; i++) {
			frameData.setAtackBox(i, hitBox);
		}

		ifs.clear();

		if (a == 0)ifs.open("Data/character/remnant/a.txt");
		if (a == 1)ifs.open("Data/character/remnant/b.txt");
		if (a == 2)ifs.open("Data/character/remnant/2a.txt");
		if (a == 3)ifs.open("Data/character/remnant/2b.txt");
		if (a == 4)ifs.open("Data/character/remnant/3b.txt");
		if (a == 5)ifs.open("Data/character/remnant/6b.txt");


		if (ifs) {

			for (int i = 0; i < 9; i++) {
				ifs >> tmp;
				if (a == 0)mPlayerAtack[Parameter::P_ATACK_A].setAllowCancel(i, Utility::StringToInt(tmp));
				if (a == 1)mPlayerAtack[Parameter::P_ATACK_B].setAllowCancel(i, Utility::StringToInt(tmp));
				if (a == 2)mPlayerAtack[Parameter::P_ATACK_2A].setAllowCancel(i, Utility::StringToInt(tmp));
				if (a == 3)mPlayerAtack[Parameter::P_ATACK_2B].setAllowCancel(i, Utility::StringToInt(tmp));
				if (a == 4)mPlayerAtack[Parameter::P_ATACK_3B].setAllowCancel(i, Utility::StringToInt(tmp));
				if (a == 5)mPlayerAtack[Parameter::P_ATACK_6B].setAllowCancel(i, Utility::StringToInt(tmp));
			}


			//�{�b�N�X�f�[�^�̓ǂݍ���
			for (int i = 0; i < 5; i++) {
				ifs >> tmp;
				boxData.setAtackType(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setEffectType(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setSEType(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setGuardType(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setAllowMultHit(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setHitStop(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setDecHitStop(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setBindTime(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setContinueAtackAfterOffset(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setForceDown(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setFloorBound(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setWallBound(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setShakeWindow(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setVectorX(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setVectorY(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setAirVectorX(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setAirVectorY(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setPower(Utility::StringToInt(tmp));
				ifs >> tmp;
				boxData.setEXGain(Utility::StringToInt(tmp));

				frameData.setAtackBoxData(i, boxData);
			}

			while (!ifs.eof()) {
				ifs >> n;

				//�t���[���؂�ւ�
				if (n == 0) {
					if (a == 0)mPlayerAtack[Parameter::P_ATACK_A].PushFrameData(frameData);
					if (a == 1)mPlayerAtack[Parameter::P_ATACK_B].PushFrameData(frameData);
					if (a == 2)mPlayerAtack[Parameter::P_ATACK_2A].PushFrameData(frameData);
					if (a == 3)mPlayerAtack[Parameter::P_ATACK_2B].PushFrameData(frameData);
					if (a == 4)mPlayerAtack[Parameter::P_ATACK_3B].PushFrameData(frameData);
					if (a == 5)mPlayerAtack[Parameter::P_ATACK_6B].PushFrameData(frameData);

					boxCounter = 0;

					hitBox.setExist(false);
					for (int i = 0; i < 20; i++) {
						frameData.setAtackBox(i, hitBox);
					}

					//�L�����Z���\�t���O
					ifs >> tmp;
					frameData.setAllowCancel(Utility::StringToInt(tmp));

					//�f�t�H���g�ł̓T�E���h�͂Ȃ�
					frameData.setSoundId(0);
				}

				//�q�b�g�{�b�N�X
				if (n == 50) {
					ifs >> boxId;

					hitBox.setBoxId(boxId);
					hitBox.setExist(true);
					ifs >> tmp;
					hitBox.setPositionX(Utility::StringToInt(tmp));
					ifs >> tmp;
					hitBox.setPositionY(Utility::StringToInt(tmp));
					ifs >> tmp;
					hitBox.setWidth(Utility::StringToInt(tmp));
					ifs >> tmp;
					hitBox.setHeight(Utility::StringToInt(tmp));

					frameData.setAtackBox(boxCounter, hitBox);

					boxCounter++;
				}

				//�T�E���hID
				if (n == 30) {
					ifs >> tmp;
					frameData.setSoundId(Utility::StringToInt(tmp));
				}


			}

		}
		ifs.close();
	}
}

/*�A�j���[�V�����̍X�V*/
void Remnant::UpdateAnimation() {

	//�U�����
	if (mRight)mSprite->setScale(0.26, 0.26);
	else mSprite->setScale(-0.26, 0.26);

	//�ʏ펞�i�ҋ@�E�O�i�E��ށE�W�����v�j
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//�v���C���[���n�ʂɂ���
		if (mGround) {

			//�v���C���[���Î~���Ă���
			if (mAcceleX == 0) {
				if (mSprite->getPlayAnimeName() != "idle") {
					mSprite->play("remnant/idle");
				}
			}
			//�v���C���[���E�ɐi��ł���
			else if (mAcceleX > 0) {
				//�v���C���[���E����
				if (mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play("remnant/walk");
					}
				}
				//�v���C���[��������
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play("remnant/back");
				}
			}
			//�v���C���[�����ɐi��ł���
			else {
				//�v���C���[��������
				if (!mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play("remnant/walk");
					}
				}
				//�v���C���[���E����
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play("remnant/back");
				}
			}
		}
		//�v���C���[���󒆂ɂ���
		else {
			if (mSprite->getPlayAnimeName() != "jump") {
				mSprite->play("remnant/jump");
			}
		}

	}
	//�_�b�V��
	else if (mState == Parameter::S_PLAYER_DASH) {
		if (mSprite->getPlayAnimeName() != "dash") {
			mSprite->play("remnant/dash");
		}
	}
	//�o�b�N�X�e�b�v
	else if (mState == Parameter::S_PLAYER_STEP) {
		if (mSprite->getPlayAnimeName() != "backstep") {
			mSprite->play("remnant/backstep");
		}
	}
	//�v���C���[�����Ⴊ��ł���
	else if (mState == Parameter::S_PLAYER_SQUAT) {
		if (mSprite->getPlayAnimeName() != "squat") {
			mSprite->play("remnant/squat");
		}
	}
	//��i�_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_U && mDamageCounter == 1) {
		mSprite->play("remnant/damage_u");
		mSprite->setStep(0.9f);

	}
	//���i�_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_D && mDamageCounter == 1) {
		mSprite->play("remnant/damage_d");
		mSprite->setStep(0.9f);
	}
	//���Ⴊ�݃_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_S && mDamageCounter == 1) {
		mSprite->play("remnant/damage_squat");
	}
	//�����K�[�h���
	else if (mState == Parameter::S_PLAYER_GUARD) {
		if (mSprite->getPlayAnimeName() != "guard_u") {
			mSprite->play("remnant/guard_u");
		}
	}
	//���Ⴊ�݃K�[�h���
	else if (mState == Parameter::S_PLAYER_GUARD_S) {
		if (mSprite->getPlayAnimeName() != "guard_d") {
			mSprite->play("remnant/guard_d");
		}
	}
	//A�U��
	else if (mState == Parameter::S_PLAYER_ATACK_A &&
		mPlayerAtack[Parameter::P_ATACK_A].getCounter() == 1)
	{
		mSprite->play("remnant/a");
	}
	//A���U��
	else if (mState == Parameter::S_PLAYER_ATACK_2A &&
		mPlayerAtack[Parameter::P_ATACK_2A].getCounter() == 1)
	{
		mSprite->play("remnant/2a");
	}
	//B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_B &&
		mPlayerAtack[Parameter::P_ATACK_B].getCounter() == 1)
	{
		mSprite->play("remnant/b");
	}
	//6B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_6B &&
		mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 1)
	{
		mSprite->play("remnant/6b");
	}
	//B���U��
	else if (mState == Parameter::S_PLAYER_ATACK_2B &&
		mPlayerAtack[Parameter::P_ATACK_2B].getCounter() == 1)
	{
		mSprite->play("remnant/2b");
		mSprite->setStep(0.6);
	}
	//3B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_3B &&
		mPlayerAtack[Parameter::P_ATACK_3B].getCounter() == 1)
	{
		mSprite->play("remnant/3b");
		mSprite->setStep(0.8);
	}
	//6B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_6B &&
		mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 1)
	{
		mSprite->play("remnant/6b");
		mSprite->setStep(0.6);
	}

	//�\���ʒu�̍X�V
	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), Parameter::GROUND_LINE - mPositionY + 20);
	//�v���C���[�̍X�V�A�����͑O��̍X�V��������o�߂�������
	mSprite->update((float)30 / 1000);
}


//�I�[�o�[���[�h

/*�U�����n�߂�*/
void Remnant::StartAtack() {
	//A�U��
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		!mController.getDown() && mGround && isCanCancelTiming(Parameter::P_ATACK_A))
	{
		mState = Parameter::S_PLAYER_ATACK_A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_A].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
	//A���U��
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		mController.getDown() && mGround && isCanCancelTiming(Parameter::P_ATACK_2A))
	{
		mState = Parameter::S_PLAYER_ATACK_2A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2A].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
	//B�U��
	if (mController.getKey(2) == 1 && !mController.getUp() && !mController.getDown() && !mController.getRight() && !mController.getLeft()
		&& mGround && isCanCancelTiming(Parameter::P_ATACK_B))
	{
		mState = Parameter::S_PLAYER_ATACK_B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_B].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_B].PlayVoice();
	}
	//B���U��
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && !mController.getRight() && !mController.getLeft() && mGround &&
		isCanCancelTiming(Parameter::P_ATACK_2B))
	{
		mState = Parameter::S_PLAYER_ATACK_2B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2B].InitAtack();
		//mPlayerAtack[Parameter::P_ATACK_A].PlayVoice();
	}
	//3B�U��
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && (mRight && mController.getRight() || !mRight && mController.getLeft()) && mGround &&
		isCanCancelTiming(Parameter::P_ATACK_3B))
	{
		mState = Parameter::S_PLAYER_ATACK_3B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_3B].InitAtack();
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

/*�_�b�V�����n�߂�*/
void Remnant::StartDash() {
	mState = Parameter::S_PLAYER_DASH;
	mCounter = 15;
	PlaySoundMem(mSoundDash, DX_PLAYTYPE_BACK);
}

/*�X�e�b�v���n�߂�*/
void Remnant::StartStep() {
	mState = Parameter::S_PLAYER_STEP;
	mCounter = 15;
	PlaySoundMem(mSoundStep, DX_PLAYTYPE_BACK);
}

void Remnant::ProcessAtack() {
	if (mState == Parameter::S_PLAYER_ATACK_6B) {
		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() >= 2 && mPlayerAtack[Parameter::P_ATACK_6B].getCounter() < 20) {
			if (mRight)mAcceleX = 25;
			else mAcceleX = -25;
		}
		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() >= 20) {
			if (mRight) {
				mAcceleX -= 5;
				if (mAcceleX < 0)mAcceleX = 0;
			}
			else {
				mAcceleX += 5;
				if (mAcceleX > 0)mAcceleX = 0;
			}
		}
	}
}