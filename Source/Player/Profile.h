#pragma once
#include <string>

/*
�e�L�����N�^�[�̃v���t�@�C����`
*/
struct Profile {
public:
	std::string name;	//���O
	std::string eName;	//���O(�p��)
	std::string pass;	//�X�v���C�g�p�p�X
	float size;			//�X�v���C�g�̃T�C�Y
	float speed;		//�ҋ@���[�V�����̍Đ����x
	int distX;			//X���W�␳
	int distY;			//X���W�␳
	int cAtack;			//�p�����[�^�F�ߐڍU��
	int lAtack;			//�p�����[�^�F�������U��
	int pAtack;			//�p�����[�^�F�����U��
	int sAtack;			//�p�����[�^�F����U��
	int aut;			//�p�����[�^�F�I�[�g�}�^
};