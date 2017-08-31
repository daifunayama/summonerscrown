#include <fstream>
#include "../../Application.h"
#include "../../SSPlayer/SS5Player.h"
#include "../../Utility.h"
#include "../../Atack/FrameData.h"
#include "../../Effekseer/AnimationController.h"
#include "Carol.h"
#include "../../Voice/Character/VoiceCarol.h"

Profile Carol::getProfile() {
	Profile p;
	p.name = "�L������ = �u���b�N�t�H�[�h";
	p.eName = "Carol Blackford";
	p.pass = "carol";

	p.size = 0.34f;
	p.speed = 0.5f;
	p.distX = 0;
	p.distY = 0;

	p.cAtack = 5;
	p.lAtack = 1;
	p.aut = 1;
	p.pAtack = 5;
	p.sAtack = 1;
	return p;
}

/*�T�E���h�̃��[�h*/
void Carol::LoadSound() {
	mAnimeDrill = LoadGraph("Data/graphic/animation/dorill2.png");

	mSoundDash = LoadSoundMem("Data/se/highspeed-movement1.mp3");
	mSoundStep = mSoundDash;

	mSoundPlayerAtack[1] = LoadSoundMem("Data/se/�葫�E��U��04.mp3");
	mSoundPlayerAtack[2] = LoadSoundMem("Data/se/���{�b�g�E����A�R��02.mp3");
	mSoundPlayerAtack[3] = mSoundDash;

	ChangeVolumeSoundMem(128, mSoundDash);
	ChangeVolumeSoundMem(128, mSoundStep);
	ChangeVolumeSoundMem(128, mSoundPlayerAtack[2]);
}

/*�{�C�X�̃��[�h*/
void Carol::LoadVoice() {
	mVoice = new VoiceCarol();
	mVoice->Load();
}

/*�v���C���[�f�[�^�����[�h*/
void Carol::LoadData() {
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
	ifs.open("Data/character/carol/DamageBoxData.txt");

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
	ifs.open("Data/character/carol/HitBoxData.txt");

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

	for (int i = 15; i < 40; i++) {
		mHitBox[i].setPositionX(mHitBox[0].getPositionX());
		mHitBox[i].setPositionY(mHitBox[0].getPositionY());
		mHitBox[i].setWidth(mHitBox[0].getWidth());
		mHitBox[i].setHeight(mHitBox[0].getHeight());
		mHitBox[i].setExist(1);
	}
}

/*�A�j���[�V�����̍X�V*/
void Carol::UpdateAnimation() {
	string name;
	name = getProfile().pass + Utility::IntToString(getColor()) + "/";

	//�U�����
	if (mRight)mSprite->setScale(0.34, 0.34);
	else mSprite->setScale(-0.34, 0.34);

	//�ʏ펞�i�ҋ@�E�O�i�E��ށE�W�����v�j
	if (mState == Parameter::S_PLAYER_NORMAL) {

		//�v���C���[���n�ʂɂ���
		if (mGround) {

			//�v���C���[���Î~���Ă���
			if (mAcceleX == 0) {
				if (mSprite->getPlayAnimeName() != "idle" && mSprite->getPlayAnimeName() != "wait") {
					mSprite->play(name + "idle");
					mSprite->setStep(0.8f);
				}
				if (mIdleCounter == 300 && mPlayerId == 0) {
					//mSprite->play(name + "wait");
					//mSprite->setStep(0.5f);
				}
				if (mIdleCounter == 400 && mPlayerId == 0)mSprite->play(name + "idle");
			}
			//�v���C���[���E�ɐi��ł���
			else if (mAcceleX > 0) {
				//�v���C���[���E����
				if (mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play(name + "walk");
						mSprite->setStep(0.6f);
					}
				}
				//�v���C���[��������
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play(name + "back");
					mSprite->setStep(0.6f);
				}
			}
			//�v���C���[�����ɐi��ł���
			else {
				//�v���C���[��������
				if (!mRight) {
					if (mSprite->getPlayAnimeName() != "walk") {
						mSprite->play(name + "walk");
						mSprite->setStep(0.6f);
					}
				}
				//�v���C���[���E����
				else if (mSprite->getPlayAnimeName() != "back") {
					mSprite->play(name + "back");
					mSprite->setStep(0.6f);
				}
			}
		}
		//�v���C���[���󒆂ɂ���
		else {
			if (mAcceleY == 36 || mAcceleY == 28) {
				mSprite->play(name + "jump");
				mSprite->setStep(0.6f);
			}
		}

	}
	//�_�b�V��
	else if (mState == Parameter::S_PLAYER_DASH) {
		if (mSprite->getPlayAnimeName() != "dash") {
			mSprite->play(name + "dash");
			mSprite->setStep(1.2f);
		}
	}
	//�o�b�N�X�e�b�v
	else if (mState == Parameter::S_PLAYER_STEP) {
		if (mSprite->getPlayAnimeName() != "backstep") {
			mSprite->play(name + "backstep");
			mSprite->setStep(1.2f);
		}
	}
	//�v���C���[�����Ⴊ��ł���
	else if (mState == Parameter::S_PLAYER_SQUAT) {
		if (mSprite->getPlayAnimeName() != "squat") {
			mSprite->play(name + "squat");
			mSprite->setStep(0.4f);
		}
	}
	//��i�_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_U && mDamageCounter == 1) {
		mSprite->play(name + "damage_u");
		mSprite->setStep(0.7f);
	}
	//���i�_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_D && mDamageCounter == 1) {
		mSprite->play(name + "damage_d");
		mSprite->setStep(0.7f);
	}
	//�󒆃_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_AIR2 && mDamageCounter == 1) {
		mSprite->play(name + "damage_air");
		mSprite->setStep(1.0f);
	}
	//�󒆃_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_AIR && mDamageCounter == 1) {
		mSprite->play(name + "damage_air");
		mSprite->setStep(1.0f);
		mSprite->setLoop(1);
	}
	//�_�E�����
	else if (mState == Parameter::S_PLAYER_DOWN && mCounter == 59) {
		mSprite->play(name + "down");
		mSprite->setStep(0.9f);
	}
	//���Ⴊ�݃_���[�W���
	else if (mState == Parameter::S_PLAYER_DAMAGE_S && mDamageCounter == 1) {
		mSprite->play(name + "damage_s");
	}
	//�󂯐g���
	else if (mState == Parameter::S_PLAYER_REVERSAL) {
		if (mSprite->getPlayAnimeName() != "reversal") {
			mSprite->play(name + "reversal");
			mSprite->setStep(0.7f);
		}
	}
	//���܂���
	else if (mState == Parameter::S_PLAYER_CAUGHT) {
		if (mSprite->getPlayAnimeName() != "caught") {
			mSprite->play(name + "caught");
			mSprite->setStep(0.5f);
		}
	}
	//�����ʂ����
	else if (mState == Parameter::S_PLAYER_ESCAPE) {
		if (mSprite->getPlayAnimeName() != "escape") {
			mSprite->play(name + "escape");
			mSprite->setStep(1.2f);
		}
	}
	//�����K�[�h���
	else if (mState == Parameter::S_PLAYER_GUARD) {
		if (mSprite->getPlayAnimeName() != "guard_u") {
			mSprite->play(name + "guard_u");
		}
	}
	//���Ⴊ�݃K�[�h���
	else if (mState == Parameter::S_PLAYER_GUARD_S) {
		if (mSprite->getPlayAnimeName() != "guard_d") {
			mSprite->play(name + "guard_d");
		}
	}
	//�o�[�X�g
	else if (mState == Parameter::S_PLAYER_BURST) {
		if (mSprite->getPlayAnimeName() != "burst") {
			mSprite->play(name + "burst");
			mSprite->setStep(0.5f);
		}
	}
	//A�U��
	else if (mState == Parameter::S_PLAYER_ATACK_A &&
		mPlayerAtack[Parameter::P_ATACK_A].getCounter() == 1)
	{
		mSprite->play(name + "a");
		//mSprite->setStep(0.7f);
	}
	//A���U��
	else if (mState == Parameter::S_PLAYER_ATACK_2A &&
		mPlayerAtack[Parameter::P_ATACK_2A].getCounter() == 1)
	{
		mSprite->play(name + "2a");
		//mSprite->setStep(0.7f);
	}
	//B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_B &&
		mPlayerAtack[Parameter::P_ATACK_B].getCounter() == 1)
	{
		mSprite->play(name + "b");
		mSprite->setStep(0.7f);
	}
	
	//6B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_6B &&
		mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 1)
	{
		mSprite->play(name + "6b");
		mSprite->setStep(0.8f);
	}
	/*
	//B���U��
	else if (mState == Parameter::S_PLAYER_ATACK_2B &&
		mPlayerAtack[Parameter::P_ATACK_2B].getCounter() == 1)
	{
		mSprite->play(name + "2b");
		mSprite->setStep(0.6);
	}
	//3B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_3B &&
		mPlayerAtack[Parameter::P_ATACK_3B].getCounter() == 1)
	{
		mSprite->play(name + "3b");
		mSprite->setStep(0.8);
	}
	//6B�U��
	else if (mState == Parameter::S_PLAYER_ATACK_6B &&
		mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 1)
	{
		mSprite->play(name + "6b");
		mSprite->setStep(0.6);
	}
	//JB�U��
	else if (mState == Parameter::S_PLAYER_ATACK_JA &&
		mPlayerAtack[Parameter::P_ATACK_JA].getCounter() == 1)
	{
		mSprite->play(name + "ja");
		mSprite->setStep(1.0);
	}
	//JB�U��
	else if (mState == Parameter::S_PLAYER_ATACK_JB &&
		mPlayerAtack[Parameter::P_ATACK_JB].getCounter() == 1)
	{
		mSprite->play(name + "jb");
		mSprite->setStep(1.2);
	}
	*/
	//����
	else if (mState == Parameter::S_PLAYER_CATCH) {
		if (mSprite->getPlayAnimeName() != "catch") {
			mSprite->play(name + "catch");
		}
	}
	//����
	else if (mState == Parameter::S_PLAYER_THROW) {
		if (mSprite->getPlayAnimeName() != "throw") {
			mSprite->play(name + "throw");
			mSprite->setStep(0.6f);
		}
	}

	//�\���ʒu�̍X�V
	mSprite->setPosition(mPositionX - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
		Parameter::GROUND_LINE - mPositionY + 10 + (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2));
	//�v���C���[�̍X�V�A�����͑O��̍X�V��������o�߂�������
	mSprite->update((float)30 / 1000);
}


//�I�[�o�[���[�h

/*�U�����n�߂�*/
void Carol::StartAtack() {
	//A�U��
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		!mController.getDown() && mGround && isCanCancelTiming(Parameter::P_ATACK_A))
	{
		mState = Parameter::S_PLAYER_ATACK_A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_A].InitAtack();
	}
	//A���U��
	if (mController.getKey(1) == 1 && !mController.getUp() &&
		mController.getDown() && mGround && isCanCancelTiming(Parameter::P_ATACK_2A))
	{
		mState = Parameter::S_PLAYER_ATACK_2A;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2A].InitAtack();
	}
	//B�U��
	if (mController.getKey(2) == 1 && !mController.getUp() && !mController.getDown() && !mController.getRight() && !mController.getLeft()
		&& mGround && isCanCancelTiming(Parameter::P_ATACK_B))
	{
		mState = Parameter::S_PLAYER_ATACK_B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_B].InitAtack();
	}
	//B���U��
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && !mController.getRight() && !mController.getLeft() && mGround &&
		isCanCancelTiming(Parameter::P_ATACK_2B))
	{
		mState = Parameter::S_PLAYER_ATACK_2B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_2B].InitAtack();
	}
	//3B�U��
	if (mController.getKey(2) == 1 && !mController.getUp() &&
		mController.getDown() && (mRight && mController.getRight() || !mRight && mController.getLeft()) && mGround &&
		isCanCancelTiming(Parameter::P_ATACK_3B))
	{
		mState = Parameter::S_PLAYER_ATACK_3B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_3B].InitAtack();
	}
	//6B�U��
	if (mController.getKey(2) == 1 && !mController.getUp() && !mController.getDown() && (mRight && mController.getRight() || !mRight && mController.getLeft()) && mGround)
	{
		mState = Parameter::S_PLAYER_ATACK_6B;
		mAcceleX = 0;
		mPlayerAtack[Parameter::P_ATACK_6B].InitAtack();
	}
}

/*�_�b�V�����n�߂�*/
void Carol::StartDash() {
	mState = Parameter::S_PLAYER_DASH;
	mCounter = 15;
	PlaySoundMem(mSoundDash, DX_PLAYTYPE_BACK);
}

/*�X�e�b�v���n�߂�*/
void Carol::StartStep() {
	mState = Parameter::S_PLAYER_STEP;
	mCounter = 15;
	PlaySoundMem(mSoundStep, DX_PLAYTYPE_BACK);
}

void Carol::ProcessAtack() {
	static int animeKey;

	if (mState == Parameter::S_PLAYER_ATACK_6B) {
		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() == 10) {
			animeKey = AnimationController::getInstance().Create(mAnimeDrill, 2, 0, 0, 500, 300, 2.5, 0, 4, 1, 30, -1, mRight, true);
		}

		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() >= 10 && mPlayerAtack[Parameter::P_ATACK_6B].getCounter() < 30) {
			if (mRight)mAcceleX = 30;
			else mAcceleX = -30;
		}
		if (mPlayerAtack[Parameter::P_ATACK_6B].getCounter() >= 25) {
			if (mRight) {
				mAcceleX -= 4;
				if (mAcceleX < 0)mAcceleX = 0;
			}
			else {
				mAcceleX += 4;
				if (mAcceleX > 0)mAcceleX = 0;
			}
		}
		AnimationController::getInstance().SetPosition(animeKey, mPositionX + (mRight ? -200 : 200), mPositionY - 20);
	}
}

/*������*/
void Carol::DoThrow(Player& another) {

	if (mCounter == 39 || mCounter == 34 || mCounter == 29 || mCounter == 24 || mCounter == 19)PlaySoundMem(mSoundPlayerAtack[1], DX_PLAYTYPE_BACK);

	if (mCounter == 15) {
		if (mRight)another.setAcceleX(mThrowDirection ? 5.0 : -5.0);
		else another.setAcceleX(mThrowDirection ? -5.0 : 5.0);
		another.setAcceleY(50.0);
		another.setGround(false);
		another.setState(Parameter::S_PLAYER_DAMAGE_AIR);
		another.setDamageCounter(0);
		another.setCounter(30);

		PlaySoundMem(mSoundPlayerAtack[2], DX_PLAYTYPE_BACK);
		AnimationController::getInstance().Create(mGraphDamage, 1, mRight?mPositionX+100:mPositionX-100, mPositionY, 600, 400, 2, GetRand(359), 4, 2, 48, 0, true, true);
	}
}