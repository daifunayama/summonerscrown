#pragma once
#include "../Player/Player.h"
#include "../Input/Controller.h"

/*
�_��w�̐�����s���N���X
*/
class ContractCircle {
public:
	void setPlayerId(int id) { mPlayerId = id; }
	void Load(Player&);
	void Process(Player&);
	void Draw();

	void ProcessInContract(int cursor);
	void DrawInContract();

private:
	int mPlayerId;				//�v���C���[ID
	int mGraphCircle;			//�_�񎞂̃O���t�B�b�N�n���h��
	int mGraphCursor;			//�J�[�\���̃O���t�B�b�N�n���h��
	int mGraphNameBar1;			//����A���[�g�̃O���t�B�b�N�n���h��1
	int mGraphNameBar2;			//����A���[�g�̃O���t�B�b�N�n���h��2
	int mGraphConditionBar1;	//����A���[�g�̃O���t�B�b�N�n���h��1
	int mGraphConditionBar2;	//����A���[�g�̃O���t�B�b�N�n���h��2
	int mIcon;					//����A�C�R��
	int mIconlist[8];			//����̃A�C�R�����X�g
	int mAngle;					//�_��w�̉�]�p
	bool mOpenCircle;			//�_��w���J���Ă��邩�̃t���O
	int mCursor;				//�J�[�\���ʒu
	string mName;				//���
	string mCondition;			//����
	Controller mController;		//���͐���p�R���g���[���[
};