#pragma once
#include "../Player/Player.h"
#include "../Input/Controller.h"
#include "../Effekseer/EffAnimation.h"
#include "../SSPlayer/SS5Player.h"
#include "../Parameter.h"

class Player;
class Controller;

/*
�S����̂��ƂƂȂ�N���X
Follower,Automata,Spell,Blaze�͂��̃N���X���p�����Ǝ��̏������s��
*/

class Arms {
protected:


	struct Profile {
		int category;
		int id;
		float size;
		float speed;
	};

public:
	inline int getState() { return mState; }
	inline int getCounter() { return mCounter; }
	inline int getPositionX() { return mPositionX; }
	inline int getPositionY() { return mPositionY; }
	inline int getDistX() { return mDistX; }
	inline int getDistY() { return mDistY; }
	inline bool getRight() { return mRight; }
	inline string getName() { return mName; }
	inline string getCondition() { return mCondition; }
	inline int getIcon() { return mIcon; }

	inline void setPositionX(int positionX) { mPositionX = positionX; }
	inline void setPositionY(int positionY) { mPositionY = positionY; }
	inline void setState(int state) { mState = state; }
	inline void setRight(bool right) { mRight = right; }
	inline void setCounter(int counter) { mCounter = counter; }

	void ReceivePlayer(Player*, Controller);
	void LoadArmsName();

	virtual Profile getProfile() = 0;
	virtual void InitArms() = 0;
	virtual void LoadArmsData() = 0;
	virtual void LoadArmsGraphic() = 0;
	virtual void LoadArmsSound() = 0;
	virtual void Move() = 0;
	virtual void StartSummon() = 0;
	virtual void UpdateArmsAnimation() = 0;
	virtual void Draw() = 0;
	virtual void DrawBack() {}
	virtual void DrawAtackBox() = 0;
	virtual void DrawUI(){}

	virtual void CheckArmsAtackHit(Player&) = 0;

	virtual bool isAtackState() = 0;

protected:
	Player* mPlayer;				//�v���C���[
	Controller mController;			//���쐧��p�R���g���[���[
	int mCategoryId;				//����̃J�e�S��ID
	int mArmsId;					//�����ID
	int mState;						//����̏�ԕϐ�
	int mCounter;					//�ėp�J�E���^
	int mPositionX;					//X���W
	int mPositionY;					//Y���W
	int mDistX;						//X���W�␳
	int mDistY;						//Y���W�␳
	bool mRight;					//����
	ss::Player *mSprite;			//�X�v���C�g
	int mIcon;						//����A�C�R���̃O���t�B�b�N�n���h��
	int mSoundAtack[10];			//SE�n���h��
	EffAnimation mAnimation[10];	//�A�j���[�V����
	//string mPass;					//����̃f�B���N�g���p�X
	string mName;					//����̖���
	string mCondition;				//����
};