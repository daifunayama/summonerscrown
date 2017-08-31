#pragma once
#include "../SSPlayer/SS5Player.h"
#include "../HitBox/HitBox.h"
#include "../Atack/PlayerAtack.h"
#include "../Arms/Arms.h"
#include "../Voice/BattleVoice.h"
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
	inline Arms* getBlaze() { return mBlaze; }
	inline BattleVoice* getVoice() { return mVoice; }
	inline bool getArmsExist(int n) { return mArmsExist[n]; }
	inline int getArmsId() { return mArmsId; }
	inline int getCircleCursor() { return mCircleCursor; }
	inline PlayerAtack getPlayerAtack(int id) { return mPlayerAtack[id]; }
	inline HitBox getDamageBox(int n1, int n2) { return mDamageBox[n1][n2]; }

	inline void setPlayerId(int playerId) { mPlayerId = playerId; }
	inline void setEX(int ex) { mEXP = ex; }
	inline void setChain(int chain) { mChain = chain; }
	inline void setArmsExist(int n,bool t) { mArmsExist[n] = t; }
	inline void setCounter(int counter) { mCounter = counter; }
	inline void setDamageCounter(int damageCounter) { mDamageCounter = damageCounter; }
	inline void setState(int state) { mState = state; }
	inline void setAcceleX(double acceleX) { mAcceleX = acceleX; }
	inline void setAcceleY(double acceleY) { mAcceleY = acceleY; }
	inline void setGround(bool ground) { mGround = ground; }

	void Init(int);
	void InitVolume();
	virtual Profile getProfile() = 0;
	virtual Styles getStyles();
	virtual void LoadGraphic();
	void LoadCommonSound();
	virtual void LoadSound() = 0;
	virtual void LoadVoice() = 0;
	virtual void LoadData() = 0;
	virtual void LoadAtack();
	void LoadArms(int);

	void Move(Player&);
	void DoJump();
	void DoAirJump();
	void DoBarrier();
	void DoBurst();
	void StartSummon();
	void DoSummon();
	virtual void StartThrow(Player &);
	virtual void DoThrow(Player&);
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
	void EatAtack(int atackType,bool,BoxData);
	void EatDamage(Player&);
	void IncleaseChain() { mChain++ ; }

	void MoveArms();
	void DrawArms();
	void DrawArmsBack();
	void DrawThrowEffect();
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
	bool isIdleState();
	bool isAcceledState();
	bool isAtackState();
	bool isDamageState();
	bool isCanGuardState();
	bool isGuardState();
	bool isCanArmsAtackState();
	bool isCanCancelTiming(int atackId);

protected:
	Controller mController;			//�R���g���[���[

	int mPlayerId;					//�v���C���[ID
	int mCharaID;					//�L����ID
	int mColor;						//�J���[ID
	int mState;						//��ԕϐ�
	int mCounter;					//�ėp�J�E���^
	int mDamageCounter;				//�_���[�W�J�E���^
	int mRightCounter;				//�E�L�[�̃J�E���^�[
	int mLeftCounter;				//���L�[�̃J�E���^�[
	int mIdleCounter;				//�ړ����Ă��Ȃ��J�E���^�[
	int mHitStop;
	int mPositionX;					//X���W
	int mPositionY;					//Y���W
	double mPositionDX;				//X���W(double)
	double mPositionDY;				//Y���W(double)
	double mAcceleX;				//X�����x
	double mAcceleY;				//Y�����x
	bool mBarrier;					//�o���A��W�J���Ă��邩�̃t���O
	bool mOpenCircle;				//�_��w���J���Ă��邩�ǂ����̃t���O
	int mHeight;					//�v���C���[�̍���
	int mSquatY;					//���Ⴊ�ݎ�Y���W�␳
	int mDownY;						//�_�E����Y���W�␳
	int mHP;						//�q�b�g�|�C���g
	int mEXP;						//EX�|�C���g
	bool mRight;					//�v���C���[�̌���
	bool mGround;					//�v���C���[�̐ڒn�t���O
	bool mAirJumped;				//�󒆃W�����v�t���O
	bool mThrowDirection;			//�����̂ނ�
	PlayerAtack mPlayerAtack[30];	//�v���C���[�̍U���f�[�^
	HitBox mHitBox[40];				//�v���C���[�̓����蔻��p�q�b�g�{�b�N�X
	HitBox mDamageBox[40][10];		//�v���C���[�̃_���[�W�H�炢����p�̃q�b�g�{�b�N�X
	int mEatAtackFlag;				//�U����H��������ǂ����̃t���O
	bool mEatAtackRight;			//�U����H���������
	BoxData mEatAtackData;			//�H������U����ۑ����Ă����{�b�N�X�f�[�^
	ss::Player *mSprite;			//�v���C���[�̃X�v���C�g
	Arms* mArms[8];					//����8��
	Arms* mBlaze;					//�u���C�Y
	BattleVoice* mVoice;			//�{�C�X
	bool mArmsExist[8];				//����̑��݃t���O
	int mArmsId;					//����������
	int mCircleCursor;				//�_��w�̃J�[�\���ʒu
	int mChain;						//�`�F�[��
	int mBarrierId;					//�o���A�̃A�j��ID

	int mGraphShadow;				//�e�̃O���t�B�b�N�n���h��
	int mGraphThrow;				//�����̐����o��
	int mGraphSummonEffect1;		//�����w�̃O���t�B�b�N�n���h��1
	int mGraphSummonEffect2;		//�����w�̃O���t�B�b�N�n���h��2
	int mGraphDamage;				//�_���[�W�G�t�F�N�g�̃O���t�B�b�N�n���h��
	int mGraphDamage2;
	int mGraphDamage3;
	int mGraphDamage4;
	int mAnimeBarrier;				//�o���A�̃O���t�B�b�N�n���h��
	int mAnimeCancel;
	int mAnimeBurst1;
	int mAnimeBurst2;
	int mAnimeReversal;

	int mSoundOpenCircle;			//�_��w���J��SE
	int mSoundSummon;				//����SE
	int mSoundDamage;				//�_���[�WSE
	int mSoundGuard;				//�K�[�hSE
	int mSoundCatch;				//����SE
	int mSoundEscape;
	int mSoundCancel;
	int mSoundBurst;				//�o�[�X�gSE
	int mSoundPlayerAtack[10];		//�U���pSE
};