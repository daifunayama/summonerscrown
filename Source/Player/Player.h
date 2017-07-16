#pragma once
#include "../SSPlayer/SS5Player.h"
#include "../HitBox/HitBox.h"
#include "../Atack/PlayerAtack.h"
#include "../Arms/Arms.h"
#include "../Input/Controller.h"
#include "../Camera/Camera.h"
#include "Profile.h"

class Arms;
class Camera;

/*
�o�g�����̃v���C���[�𐧌䂷��N���X
�e�L�����N�^�[�͂��̃N���X���p�����Ǝ��̏�����ǉ�����
*/
class Player {
public:
	inline Controller getController() { return mController; }
	inline int getPlayerId() { return mPlayerId; }
	inline int getColor() { return mColor; }
	inline string getName() { return mName; }
	inline int getState() { return mState; }
	inline int getCounter() { return mCounter; }
	inline int getHitStop() { return mHitStop; }
	inline int getHP() { return mHP; }
	inline int getEX() { return mEXP; }
	inline int getChain() { return mChain; }
	inline int getPositionX() { return mPositionX; }
	inline int getPositionY() { return mPositionY; }
	inline bool getRight() { return mRight; }
	inline bool getOpenCircle() { return mOpenCircle; }
	inline Arms* getArms(int n) { return mArms[n]; }
	inline bool getArmsExist(int n) { return mArmsExist[n]; }
	inline int getArmsId() { return mArmsId; }
	inline int getCircleCursor() { return mCircleCursor; }
	inline HitBox getDamageBox(int n1, int n2) { return mDamageBox[n1][n2]; }

	inline void setPlayerId(int playerId) { mPlayerId = playerId; }
	inline void setChain(int chain) { mChain = chain; }
	inline void setArmsExist(int n,bool t) { mArmsExist[n] = t; }

	void Init(int);
	virtual Profile getProfile() = 0;
	virtual void LoadGraphic();
	void LoadCommonSound();
	virtual void LoadSound() = 0;
	virtual void LoadVoice() = 0;
	virtual void LoadData() = 0;
	virtual void LoadAtack() = 0;
	void LoadArms(int);

	void Move(Player&);
	void DoJump();
	void StartSummon();
	void DoSummon();
	virtual void StartAtack();
	void DoAtack();
	virtual void ProcessAtack(){}
	virtual void StartDash();
	void DoDash();
	virtual void StartStep();
	void DoStep();
	void DoDamaged();
	void DecrementCounter(Player&);
	void DecrementHitStop();
	void ChangeDirection(Player&);
	void EatAtack(bool,BoxData);
	void EatDamage(Player&);
	void IncleaseChain() { mChain++ ; }

	void MoveArms();
	void DrawArms();
	void DrawArmsBack();
	void MoveCircleCursor();

	void CheckPlayersHit(Player&);
	void CheckWallHit();
	void CheckVirtualWallHit(Player &);
	void CheckPlayersAtackHit(Player&);

	virtual void UpdateAnimation() = 0;
	void Draw();
	void DrawShadow();
	void DrawHitBox();
	void DrawDamageBox();
	void DrawAtackBox();

	bool isAcceledState();
	bool isAtackState();
	bool isDamageState();
	bool isCanArmsAtackState();
	bool isCanCancelTiming(int atackId);

protected:
	Controller mController;			//�R���g���[���[

	int mPlayerId;					//�v���C���[ID
	int mCharaID;					//�L����ID
	int mColor;						//�J���[ID
	string mName;					//�L�����̖��O
	int mState;						//��ԕϐ�
	int mCounter;					//�ėp�J�E���^
	int mDamageCounter;				//�_���[�W�J�E���^
	int mHitStop;
	int mPositionX;					//X���W
	int mPositionY;					//Y���W
	double mPositionDX;				//X���W(double)
	double mPositionDY;				//Y���W(double)
	double mAcceleX;				//X�����x
	double mAcceleY;				//Y�����x
	bool mBarrier;					//�o���A��W�J���Ă��邩�̃t���O
	bool mOpenCircle;				//�_��w���J���Ă��邩�ǂ����̃t���O
	int mRightCounter;				//�E�L�[�̃J�E���^�[
	int mLeftCounter;				//���L�[�̃J�E���^�[
	int mHeight;					//�v���C���[�̍���
	int mSquatY;					//���Ⴊ�ݎ�Y���W�␳
	int mDownY;						//�_�E����Y���W�␳
	int mHP;						//�q�b�g�|�C���g
	int mEXP;						//EX�|�C���g
	bool mRight;					//�v���C���[�̌���
	bool mGround;					//�v���C���[�̐ڒn�t���O
	PlayerAtack mPlayerAtack[15];	//�v���C���[�̍U���f�[�^
	HitBox mHitBox[15];				//�v���C���[�̓����蔻��p�q�b�g�{�b�N�X
	HitBox mDamageBox[15][10];		//�v���C���[�̃_���[�W�H�炢����p�̃q�b�g�{�b�N�X
	bool mEatAtackFlag;				//�U����H��������ǂ����̃t���O
	bool mEatAtackRight;			//�U����H���������
	BoxData mEatAtackData;			//�H������U����ۑ����Ă����{�b�N�X�f�[�^
	ss::Player *mSprite;			//�v���C���[�̃X�v���C�g
	Arms* mArms[8];					//����8��
	bool mArmsExist[8];				//����̑��݃t���O
	int mArmsId;					//����������
	int mCircleCursor;				//�_��w�̃J�[�\���ʒu
	int mChain;						//�`�F�[��
	int mBarrierId;					//�o���A�̃A�j��ID

	int mGraphShadow;				//�e�̃O���t�B�b�N�n���h��
	int mGraphSummonEffect1;		//�����w�̃O���t�B�b�N�n���h��1
	int mGraphSummonEffect2;		//�����w�̃O���t�B�b�N�n���h��2
	int mGraphDamage;				//�_���[�W�G�t�F�N�g�̃O���t�B�b�N�n���h��
	int mAnimeBarrier;				//�o���A�̃O���t�B�b�N�n���h��

	int mSoundOpenCircle;			//�_��w���J��SE
	int mSoundSummon;				//����SE
	int mSoundDamage;				//�_���[�WSE
	int mSoundGuard;				//�K�[�hSE
	int mSoundPlayerAtack[10];		//�U���pSE
};