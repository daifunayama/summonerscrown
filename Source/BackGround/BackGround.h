#pragma once
#include "../Player/Player.h"

/*
�w�i�̕`�������N���X
*/
class BackGround {
public:
	void LoadGraphic();
	void GetPlayer(Player&, Player&);
	void Draw();

	BackGround() { mBlackoutCounter[0] = 0; mBlackoutCounter[1] = 0; }
	~BackGround(){}

private: 
	int mGraphHandle;			//�w�i�̃O���t�B�b�N�n���h��
	int mGraphEmblem[10];		//�������G���u����
	int mBlackoutCounter[2];	//�Ó]�J�E���^�[
	int mEmblemId[2];			//�G���u����ID
	int mX[2];					//�v���C���[��X���W
};