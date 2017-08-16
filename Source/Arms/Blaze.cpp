#include "../Arms/Blaze.h"
#include "../Application.h"
#include "../Parameter.h"
#include "../Utility.h"
#include "../Effekseer/AnimationController.h"
#include <fstream>


/*����̏�����*/
void Blaze::InitArms() {
	mState = Parameter::S_ARMS_NORMAL;
	mDistX = -100;
	mDistY = 50;
	if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
	else mPositionX = mPlayer->getPositionX() - mDistX;

	mPositionY = mPlayer->getPositionY() + mDistY;
	mCounter = 0;

	mGraphSummonEffect1 = LoadGraph("Data/graphic/animation/summon_effect1.png");
	mGraphSummonEffect2 = LoadGraph("Data/graphic/animation/summon_effect2.png");
}

/*�T�E���h�̃��[�h*/
void Blaze::LoadArmsSound() {

}

/*����̃��[�h*/
void Blaze::LoadArmsData() {
	ifstream ifs;
	int n;
	int boxId;
	int boxCounter;
	string tmp;
	string pass;

	FrameData frameData;
	BoxData boxData;
	HitBox hitBox;

	//�A�j���[�V�����̏�����
	for (int i = 0; i < 10; i++)mAnimation[i].setExist(false);


		mAtack.ClearFrameData();

		hitBox.setExist(false);
		for (int i = 0; i < 20; i++) {
			frameData.setAtackBox(i, hitBox);
		}

		ifs.clear();
		pass.clear();
		pass = ArmsList::get().getArmsPass(getProfile().category, getProfile().id) + "/atack.txt";

		ifs.open(pass.c_str());

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
					mAtack.PushFrameData(frameData);

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
					mAnimation[n - 11].setAtackId(1);

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

/*����𓮂���*/
void Blaze::Move() {
	mCounter++; 
	Process();
	DoAtack();
}

/*�U�����n�߂�*/
void Blaze::StartAtack() {

	mState = Parameter::S_ARMS_SUMMON;
	if (mPlayer->getRight())mPositionX = mPlayer->getPositionX() + mDistX;
	else mPositionX = mPlayer->getPositionX() - mDistX;

	mPositionY = mPlayer->getPositionY() + mDistY;
	mCounter = 0;

	mAtack.InitAtack();
	mRight = mPlayer->getRight();

	mSprite->play("arms/summon");

}

/*�U��*/
void Blaze::DoAtack() {
	int sId = 0;

	//SE������ꍇ�Đ�
	sId = mAtack.getFrameData(mAtack.getCounter()).getSoundId();
	if (sId > 0 && sId <= 10)PlaySoundMem(mSoundAtack[sId], DX_PLAYTYPE_BACK);

	//�A�j���[�V����������ꍇ�Đ�
	for (int i = 0; i < 10; i++) {
		if (mAnimation[i].getExist() && mAnimation[i].getAtackId() == 1) {
			if (mAnimation[i].getStartFrame() == mAtack.getCounter()) {
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

	mAtack.IncreaseCounter();

	//�U���I�����̏���
	if (mAtack.CheckAtackEnd()) {
		//ProcessAfterAtack();
		mState = Parameter::S_ARMS_NORMAL;
	}
	
	
}

void Blaze::Draw() {
	mSprite->draw();
}

/*�U���{�b�N�X�̕`��*/
void Blaze::DrawAtackBox() {
	int atackId, counter;

	atackId = 1;
	counter = mAtack.getCounter();

	//���ߐݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);

	//�E�����̂Ƃ�
	if (mRight) {
		for (int i = 0; i < 20; i++) {
			if (mAtack.getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX + mAtack.getFrameData(counter).getAtackBox(i).getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mAtack.getFrameData(counter).getAtackBox(i).getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					mPositionX + mAtack.getFrameData(counter).getAtackBox(i).getPositionX()
					+ mAtack.getFrameData(counter).getAtackBox(i).getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mAtack.getFrameData(counter).getAtackBox(i).getPositionY()
					+ mAtack.getFrameData(counter).getAtackBox(i).getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					Parameter::COLOR_RED, true);
			}
		}
	}

	//�������̂Ƃ�
	else {
		for (int i = 0; i < 20; i++) {
			if (mAtack.getFrameData(counter).getAtackBox(i).getExist()) {
				DrawBox(
					mPositionX - mAtack.getFrameData(counter).getAtackBox(i).getPositionX() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mAtack.getFrameData(counter).getAtackBox(i).getPositionY() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					mPositionX - mAtack.getFrameData(counter).getAtackBox(i).getPositionX()
					- mAtack.getFrameData(counter).getAtackBox(i).getWidth() - (Camera::getInstance().getCenterX() - Parameter::WINDOW_WIDTH / 2),
					mPositionY + mAtack.getFrameData(counter).getAtackBox(i).getPositionY()
					+ mAtack.getFrameData(counter).getAtackBox(i).getHeight() - (Camera::getInstance().getCenterY() - Parameter::WINDOW_HEIGHT / 2),
					Parameter::COLOR_RED, true);
			}
		}
	}

	//���ߐݒ�����ǂ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

/*����̍U���̓����蔻��*/
void Blaze::CheckArmsAtackHit(Player& another) {
	int atackId, counter;
	Box box1, box2;

	atackId = 1;
	counter = mAtack.getCounter();
	bool atackHit = false;

	if (mState == Parameter::S_ARMS_SUMMON) {

		for (int i = 0; i < 20 && !atackHit; i++) {
			//�Y���t���[���ɍU���p�{�b�N�X�����݂���Ƃ�
			if (mAtack.getFrameData(counter).getAtackBox(i).getExist()) {
				if (!mAtack.getAtackHit()) {

					//����̃q�b�g�{�b�N�X�Ɣ�r
					for (int j = 0; j < 10 && !atackHit; j++) {

						//����̃_���[�W�{�b�N�X�����݂���Ƃ�
						if (another.getDamageBox(another.getState(), j).getExist()) {

							//���g���E����
							if (mRight) {
								box1.x = mPositionX + mAtack.getFrameData(counter).getAtackBox(i).getPositionX();
							}
							//���g��������
							else
								box1.x = mPositionX - mAtack.getFrameData(counter).getAtackBox(i).getPositionX()
								- mAtack.getFrameData(counter).getAtackBox(i).getWidth();

							box1.y = mPositionY + mAtack.getFrameData(counter).getAtackBox(i).getPositionY();
							box1.width = mAtack.getFrameData(counter).getAtackBox(i).getWidth();
							box1.height = mAtack.getFrameData(counter).getAtackBox(i).getHeight();

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
								int boxId = mAtack.getFrameData(counter).getAtackBox(i).getBoxId();

								//����ɍU����^����
								another.EatAtack(2, mRight, mAtack.getFrameData(counter).getAtackBoxData(boxId));

								//�U�������i�q�b�g�������Ȃ��ꍇ���ɓ��������t���O�����Ă�
								if (!mAtack.getFrameData(counter).getAtackBoxData(boxId).getAllowMultHit())mAtack.setAtackHit(true);

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