#pragma once
#include "../Player/Player.h"

/*
�w�i�̕`�������N���X
*/
class BackGround {
public:
	static  BackGround& get(void) {
		static BackGround background;
		return background;
	}
	BackGround(const  BackGround&) = delete;
	BackGround& operator = (const  BackGround&) = delete;
	BackGround(BackGround&&) = delete;
	BackGround operator = (BackGround&&) = delete;

	inline void setBlackCounter(int p, int n) { mBlackoutCounter[p] = n; }
	void LoadGraphic();
	void Process(Player& player1, Player& player2);
	void Draw();

private:
	BackGround() { mBlackoutCounter[0] = 0; mBlackoutCounter[1] = 0; }
	~BackGround(){}

private: 
	int mGraphHandle[3];		//�w�i�̃O���t�B�b�N�n���h��
	int mGraphEmblem[10];		//�������G���u����
	int mBlackoutCounter[2];	//�Ó]�J�E���^�[
	int mEmblemId[2];			//�G���u����ID
	int mX[2];					//�v���C���[��X���W
};