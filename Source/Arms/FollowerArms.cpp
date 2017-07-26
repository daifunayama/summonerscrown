#include "FollowerArms.h"
#include "../Application.h"
#include "../Parameter.h"
#include "../Utility.h"
#include "../Effekseer/AnimationController.h"
#include <fstream>

/*����̏�����*/
void FollowerArms::InitArms() {
	mState = Parameter::S_ARMS_NORMAL;
	mDistX = -100;
	mDistY = 50;
	if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
	else mPositionX = mPlayer->getPositionX() - mDistX;
	
	mPositionY = mPlayer->getPositionY() + mDistY;
	
}

/*����̃��[�h*/
void FollowerArms::LoadArmsData() {
	ifstream ifs;
	int n;
	int boxId;
	int frameCounter;
	int boxCounter;
	string tmp;
	string pass;

	FrameData frameData;
	BoxData boxData;
	HitBox hitBox;

	//�A�j���[�V�����̏�����
	for (int i = 0; i < 10; i++)mAnimation[i].setExist(false);

	for (int a = 0; a < 8; a++) {

		mAtack[a].ClearFrameData();

		hitBox.setExist(false);
		for (int i = 0; i < 20; i++) {
			frameData.setAtackBox(i, hitBox);
		}

		ifs.clear();

		pass.clear();

		if (a == Parameter::ATACK_C)pass = mPass + "/c.txt";
		if (a == Parameter::ATACK_2C)pass = mPass + "/cd.txt";
		if (a == Parameter::ATACK_8C)pass = mPass + "/cu.txt";
		if (a == Parameter::ATACK_D)pass = mPass + "/d.txt";
		if (a == Parameter::ATACK_2D)pass = mPass + "/dd.txt";


		ifs.open(pass.c_str());

		if (ifs) {
			
			for (int i = 0; i < 8; i++) {
				ifs >> tmp;
				mAtack[a].setAllowCancel(i, Utility::StringToInt(tmp));
			}

			ifs >> tmp;
			mAtack[a].setContinueAtackAfterDamage(Utility::StringToInt(tmp));

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
					mAtack[a].PushFrameData(frameData);

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

				//�A�j���[�V����
				if (11 <= n && n <= 20) {
					mAnimation[n - 11].setExist(true);
					mAnimation[n - 11].setAtackId(a);

					ifs >> tmp;
					mAnimation[n - 11].setPositionX(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setPositionY(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setWidth(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setHeight(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setExRate(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setDevided(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setSpeed(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setStartFrame(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setEndFrame(Utility::StringToInt(tmp));
					ifs >> tmp;
					mAnimation[n - 11].setAddFlag(Utility::StringToInt(tmp));
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

/*����𓮂���*/
void FollowerArms::Move() {

	//�ҋ@��
	if (mState == Parameter::S_ARMS_NORMAL) {
		if (mPlayer->getRight())FollowPlayer(mPlayer->getPositionX() + mDistX, mPlayer->getPositionY() + mDistY);
		else FollowPlayer(mPlayer->getPositionX() - mDistX, mPlayer->getPositionY() + mDistY);
	}

	//������
	if (mState == Parameter::S_ARMS_SUMMON) {
		mCounter++;
		if (mCounter >= 45)mState = Parameter::S_ARMS_NORMAL;
	}

	//�U�����J�n����
	StartAtack();

	//�U����
	if (isAtackState()) {
		DoAtack();
	}
}

/*�v���C���[��Ǐ]����*/
void FollowerArms::FollowPlayer(int pX, int pY) {
	double distX, distY, distAngle, moveX, moveY, speedX, speedY;

	distX = (double)(pX - mPositionX);
	distY = (double)(pY - mPositionY);

	if (-5 < distX && distX < 5)distX = 0;
	if (-5 < distY && distY < 5)distY = 0;

	distAngle = atan2(distY, distX);

	if (distX > 70 || distX < -70) {
		speedX = 7;
	}
	else speedX = abs(distX / 10);

	if (distY > 70 || distY < -70) {
		speedY = 7;
	}
	else speedY = abs(distY / 10);

	moveX = (double)cos(distAngle) * speedX;
	moveY = (double)sin(distAngle) * speedY;

	if (distX == 0)moveX = 0;
	if (distY == 0)moveY = 0;

	mPositionX += (int)moveX;
	mPositionY += (int)moveY;
}

/*�������n�߂�*/
void FollowerArms::StartSummon() {
	mState = Parameter::S_ARMS_SUMMON;
	mCounter = 0;

	mRight = mPlayer->getRight();
	if (mRight)mPositionX = mPlayer->getPositionX() + mDistX;
	else mPositionX = mPlayer->getPositionX() - mDistX;

	mPositionY = mPlayer->getPositionY() + mDistY;
}

/*�U�����n�߂�*/
void FollowerArms::StartAtack() {
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
	}
}

/*�U��*/
void FollowerArms::DoAtack() {
	int sId = 0;

	for(int a=0;a<8;a++){
		if (mState == a+2) {

			//SE������ꍇ�Đ�
			sId = mAtack[a].getFrameData(mAtack[a].getCounter()).getSoundId();
			if (sId > 0 && sId <= 10)PlaySoundMem(mSoundAtack[sId], DX_PLAYTYPE_BACK);

			//�A�j���[�V����������ꍇ�Đ�
			for (int i = 0; i < 10; i++) {
				if (mAnimation[i].getExist() && mAnimation[i].getAtackId() == a) {
					if (mAnimation[i].getStartFrame() == mAtack[a].getCounter()) {
						if (mRight) {
							AnimationController::getInstance().Create(
								mAnimation[i].getGraph(), 1,
								mPositionX + mAnimation[i].getPositionX(),
								mPositionY + mAnimation[i].getPositionY(),
								mAnimation[i].getWidth(), mAnimation[i].getHeight(), mAnimation[i].getExRate(), 0, mAnimation[i].getDevided(),
								mAnimation[i].getSpeed(), mAnimation[i].getEndFrame(), -1, mRight, mAnimation[i].getAddFlag());
						}
						else {
							AnimationController::getInstance().Create(
								mAnimation[i].getGraph(), 1,
								mPositionX - mAnimation[i].getPositionX(),
								mPositionY + mAnimation[i].getPositionY(),
								mAnimation[i].getWidth(), mAnimation[i].getHeight(), mAnimation[i].getExRate(), 0, mAnimation[i].getDevided(),
								mAnimation[i].getSpeed(), mAnimation[i].getEndFrame(), -1, mRight, mAnimation[i].getAddFlag());
						}
					}
				}
			}

			mAtack[a].IncreaseCounter();

			//�U���I�����̏���
			if (mAtack[a].CheckAtackEnd()) {
				ProcessAfterAtack();
				mState = Parameter::S_ARMS_NORMAL;
			}
		}
	}
}

/*�`��*/
void FollowerArms::Draw() {
	mSprite->draw();
}

/*�U���{�b�N�X�̕`��*/
void FollowerArms::DrawAtackBox() {
	int atackId, counter;

	atackId = mState - 2;
	counter = mAtack[atackId].getCounter();

	//���ߐݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

	//�E�����̂Ƃ�
	if (mRight) {
		for (int i = 0; i < 20; i++) {
			if (mAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX(),
					mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY(),
					mPositionX + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
					+ mAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth(),
					mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY()
					+ mAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight(),
					Parameter::COLOR_RED, true);
			}
		}
	}

	//�������̂Ƃ�
	else {
		for (int i = 0; i < 20; i++) {
			if (mAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX - mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX(),
					mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY(),
					mPositionX - mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
					- mAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth(),
					mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY()
					+ mAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight(),
					Parameter::COLOR_RED, true);
			}
		}
	}

	//���ߐݒ�����ǂ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/*����̍U���̓����蔻��*/
void FollowerArms::CheckArmsAtackHit(Player& another) {
	int atackId, counter;
	Box box1, box2;

	atackId = mState - 2;
	counter = mAtack[atackId].getCounter();
	bool atackHit = false;

	if (isAtackState()) {
		for (int i = 0; i < 20 && !atackHit; i++) {
			//�Y���t���[���ɍU���p�{�b�N�X�����݂���Ƃ�
			if (mAtack[atackId].getFrameData(counter).getAtackBox(i).getExist()) {
				if (!mAtack[atackId].getAtackHit()) {

					//����̃q�b�g�{�b�N�X�Ɣ�r
					for (int j = 0; j < 10 && !atackHit; j++) {

						//����̃_���[�W�{�b�N�X�����݂���Ƃ�
						if (another.getDamageBox(another.getState(),j).getExist()) {

							//���g���E����
							if (mRight) {
								box1.x = mPositionX + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX();
							}
							//���g��������
							else
								box1.x = mPositionX - mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionX()
								- mAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth();

							box1.y = mPositionY + mAtack[atackId].getFrameData(counter).getAtackBox(i).getPositionY();
							box1.width = mAtack[atackId].getFrameData(counter).getAtackBox(i).getWidth();
							box1.height = mAtack[atackId].getFrameData(counter).getAtackBox(i).getHeight();

							//���肪�E����
							if (another.getRight()) {
								box2.x = another.getPositionX() + another.getDamageBox(another.getState(), j).getPositionX();
							}
							//���肪������
							else {
								box2.x = another.getPositionX()
									- another.getDamageBox(another.getState(), j).getPositionX()
									- another.getDamageBox(another.getState(), j).getWidth();
							}
							box2.y = another.getPositionY() + another.getDamageBox(another.getState(), j).getPositionY();
 							box2.width = another.getDamageBox(another.getState(), j).getWidth();
							box2.height = another.getDamageBox(another.getState(), j).getHeight();

							//�U��������Ƀq�b�g
							if (Utility::CheckBoxHit(box1, box2)) {

								//�{�b�N�XID���擾
								int boxId = mAtack[atackId].getFrameData(counter).getAtackBox(i).getBoxId();

								//����ɍU����^����
								another.EatAtack(2,mRight, mAtack[atackId].getFrameData(counter).getAtackBoxData(boxId));

								//�U�������i�q�b�g�������Ȃ��ꍇ���ɓ��������t���O�����Ă�
								if (!mAtack[atackId].getFrameData(counter).getAtackBoxData(boxId).getAllowMultHit())mAtack[atackId].setAtackHit(true);

								atackHit = true;
								break;
							}
						}
					}
				}
			}
		}
	}
}

/*�U����Ԃ��ǂ�����Ԃ�*/
bool FollowerArms::isAtackState() {
	if (mState == Parameter::S_ARMS_ATACK_C  ||
		mState == Parameter::S_ARMS_ATACK_8C ||
		mState == Parameter::S_ARMS_ATACK_2C ||
		mState == Parameter::S_ARMS_ATACK_JC ||
		mState == Parameter::S_ARMS_ATACK_D  ||
		mState == Parameter::S_ARMS_ATACK_8D ||
		mState == Parameter::S_ARMS_ATACK_2D ||
		mState == Parameter::S_ARMS_ATACK_JD) {
		return true;
	}
	return false;
}

/*�L�����Z���\�ȃ^�C�~���O���ǂ���*/
bool FollowerArms::isCanCancelTiming(int atackId) {
	int counter;

	return true;

	if (mState == Parameter::S_ARMS_NORMAL)return true;

	if (isAtackState()) {
		counter = mAtack[mState - 2].getCounter();

		if (mAtack[mState - 2].getFrameData(counter).getAllowCancel()) {
			if (mAtack[mState - 2].getAllowCancel(atackId)) {
				return true;
			}
		}
	}
	return false;
}