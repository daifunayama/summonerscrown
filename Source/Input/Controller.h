#pragma once

/*
�e�v���C���[�p�̓��̓L�[�̕ϊ��N���X
*/
class Controller {
public:
	void SetPlayerId(int id) { mPlayerId = id; }
	void ConvertInput();

	inline int getKey(int key) { return pushKey[key]; }
	inline int getUp() { return pushUp; }
	inline int getDown() { return pushDown; }
	inline int getRight() { return pushRight; }
	inline int getLeft() { return pushLeft; }

private:
	int mPlayerId;		//�v���C���[ID
	int pushKey[12];	//�e�{�^��
	int pushUp;			//��L�[
	int pushDown;		//���L�[
	int pushRight;		//�E�L�[
	int pushLeft;		//���L�[
};