#pragma once
#include <map>

/*
�v���C���[����̓��͂̐�����s���V���O���g���p�^�[���N���X
*/
class Input {
public:
	static Input& getInstance(void) {
		static Input input;
		return input;
	}
	Input(const Input&) = delete;
	Input& operator = (const Input&) = delete;
	Input(Input&&) = delete;
	Input operator = (Input&&) = delete;

	void Update();
	int GetKey(int key);

private:
	std::map<int,int> mKey;		//�e�L�[�ւ̃}�b�s���O�p�z��

private:
	Input(){}
	~Input(){}
};