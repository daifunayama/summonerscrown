#pragma once
#include "../Player/Player.h"

/*
�`�F�[���̊Ǘ��E������s���N���X
*/
class Chain {
public:
	void setPlayerId(int id) { mPlayerId = id; }
	void Load();
	void Process(Player&);
	void Draw();

private:
	int mPlayerId;				//�v���C���[ID
	int mGraphNumber[10];		//�����̃O���t�B�b�N�n���h��
	int mChain;					//�`�F�[����
	int mChainCounter;			//�`�F�[���̕`��p�J�E���^�[
};