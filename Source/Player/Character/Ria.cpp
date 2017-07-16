#include <fstream>
#include "../../Application.h"
#include "../../SSPlayer/SS5Player.h"
#include "../../Utility.h"
#include "../../Atack/FrameData.h"
#include "Ria.h"

Profile Ria::getProfile() {
	Profile p;
	p.name = "���A = �A�[���F���V���^�C��";
	p.eName = "Ria Arverstein";
	p.pass = "ria";

	p.size = 0.39f;
	p.speed = 1.0f;
	p.distX = -10;
	p.distY = 0;

	p.cAtack = 2;
	p.lAtack = 5;
	p.aut = 3;
	p.pAtack = 5;
	p.sAtack = 2;
	return p;
}

/*�T�E���h�̃��[�h*/
void Ria::LoadSound() {
	
}

/*�{�C�X�̃��[�h*/
void Ria::LoadVoice() {

}

/*�v���C���[�f�[�^�����[�h*/
void Ria::LoadData() {
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
	ifs.open("Data/character/ria/DamageBoxData.txt");

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
	ifs.open("Data/character/ria/HitBoxData.txt");

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
void Ria::LoadAtack() {
	ifstream ifs;
	int n;
	int boxId;
	int frameCounter;
	int boxCounter = 0;
	string tmp;

	FrameData frameData;
	BoxData boxData;
	HitBox hitBox;

	for (int a = 0; a < 4; a++) {

		if (a == 0)mPlayerAtack[Parameter::P_ATACK_A].ClearFrameData();
		if (a == 1)mPlayerAtack[Parameter::P_ATACK_B].ClearFrameData();
		if (a == 2)mPlayerAtack[Parameter::P_ATACK_2A].ClearFrameData();
		if (a == 3)mPlayerAtack[Parameter::P_ATACK_2B].ClearFrameData();

		hitBox.setExist(false);
		for (int i = 0; i < 20; i++) {
			frameData.setAtackBox(i, hitBox);
		}

		ifs.clear();

		if (a == 0)ifs.open("Data/character/ria/a.txt");
		if (a == 1)ifs.open("Data/character/ria/b.txt");
		if (a == 2)ifs.open("Data/character/ria/ad.txt");
		if (a == 3)ifs.open("Data/character/ria/bd.txt");

		if (ifs) {
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

					boxCounter = 0;

					hitBox.setExist(false);
					for (int i = 0; i < 20; i++) {
						frameData.setAtackBox(i, hitBox);
					}

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
void Ria::UpdateAnimation() {

	//�U�����
	if (mRight)mSprite->setScale(0.39, 0.39);
	else mSprite->setScale(-0.39, 0.39);

	//�ʏ펞�i�ҋ@�E�O�i�E��ށE�W�����v�j
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//�v���C���[���n�ʂɂ���
		if (mGround) {

			//�v���C���[���Î~���Ă���
			if (mAcceleX == 0) {
				if (mSprite->getPlayAnimeName() != "idle") {
					mSprite->play("ria/idle");
				}
			}
			//�v���C���[���E�ɐi��ł���
			else if (mAcceleX > 0) {
				//�v���C���[���E����
				if (mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play("ria/walk");
					}
				}
				//�v���C���[��������
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play("ria/back");
				}
			}
			//�v���C���[�����ɐi��ł���
			else {
				//�v���C���[��������
				if (!mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play("ria/walk");
					}
				}
				//�v���C���[���E����
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play("ria/back");
				}
			}
		}
		//�v���C���[���󒆂ɂ���
		//else {
		//	if (mSprite->getPlayAnimeName() != "jump") {
		//		mSprite->play("ria/jump");
		//	}
		//}

	}
	//�_�b�V��
	else if (mState == Parameter::S_PLAYER_DASH) {
		if (mSprite->getPlayAnimeName() != "dash") {
			//mSprite->play("ria/dash");
		}
	}
	//�o�b�N�X�e�b�v
	else if (mState == Parameter::S_PLAYER_STEP) {
		if (mSprite->getPlayAnimeName() != "backstep") {
			//mSprite->play("ria/backstep");
		}
	}
	//�v���C���[�����Ⴊ��ł���
	else if (mState == Parameter::S_PLAYER_SQUAT) {
		if (mSprite->getPlayAnimeName() != "squat") {
			//mSprite->play("ria/squat");
		}
	}
	//��i�_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_U && mDamageCounter == 1) {
		mSprite->play("ria/damage_u");
		mSprite->setStep(0.9f);

	}
	//���i�_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_D && mDamageCounter == 1) {
		mSprite->play("ria/damage_d");
		mSprite->setStep(0.9f);
	}
	//���Ⴊ�݃_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_S && mDamageCounter == 1) {
		mSprite->play("ria/damage_squat");
	}
	//A�U��
	else if (mState == Parameter::S_PLAYER_ATACK_A &&
		mPlayerAtack[Parameter::P_ATACK_A].getCounter() == 1)
	{
		mSprite->play("ria/a");
	}
	//A���U��
	else if (mState == Parameter::S_PLAYER_ATACK_2A &&
		mPlayerAtack[Parameter::P_ATACK_2A].getCounter() == 1)
	{
		mSprite->play("ria/2a");
	}
	//B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_B &&
		mPlayerAtack[Parameter::P_ATACK_B].getCounter() == 1)
	{
		mSprite->play("ria/b");
	}
	//B���U��
	else if (mState == Parameter::S_PLAYER_ATACK_2B &&
		mPlayerAtack[Parameter::P_ATACK_2B].getCounter() == 1)
	{
		mSprite->play("ria/2b");
	}

	//�\���ʒu�̍X�V
	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2), Parameter::GROUND_LINE - mPositionY);
	//�v���C���[�̍X�V�A�����͑O��̍X�V��������o�߂�������
	mSprite->update((float)30 / 1000);
}


//�I�[�o�[���[�h

