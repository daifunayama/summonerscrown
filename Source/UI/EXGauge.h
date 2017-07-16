#pragma once
#include "../Player/Player.h"

/*
EX�Q�[�W�̐�����s���N���X
*/
class EXGauge {
public:
	void setPlayerId(int id) { mPlayerId = id; }
	void Load();
	void Process(Player&);
	void Draw();

private:
	int mPlayerId;		//�v���C���[ID
	int mGraphGauge;	//�Q�[�W�̃O���t�B�b�N�n���h��
	int mGraphBar;		//���[�^�̃O���t�B�b�N�n���h��
	int mEX;			//EX�l(0~100)
};