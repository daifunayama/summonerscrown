#pragma once
#include "../Player/Player.h"

/*
HP�Q�[�W�̐�����s���N���X
*/

class HPGauge {
public:
	void setPlayerId(int id) { mPlayerId = id; }
	void Load();
	void Process(Player&, Player&);
	void Draw();
	void DrawDegitNumber(int x, int y, int value);

private:
	int mPlayerId;			//�v���C���[ID
	string mName;			//�L������
	int mGraphGauge;		//�Q�[�W�̃O���t�B�b�N�n���h��
	int mGraphFace;			//�L�����t�F�C�X�̃O���t�B�b�N�n���h��	
	int mGraphBar[3];		//���[�^�̃O���t�B�b�N�n���h��
	int mGraphNumber[10];	//���l�̃O���t�B�b�N�n���h��
	int mHP;				//HP(0~1000)
	int mRedzone;			//���b�h�]�[��
	bool mKeepRedzone;		//���b�h�]�[���ۗ̕��t���O
};