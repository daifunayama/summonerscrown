#pragma once
#include "HitBox/Box.h"
#include <string>
#include <sstream>

/*
�ėp�֐��̒�`�N���X
*/
class Utility {
public:
	/*int��string�ɕϊ�*/
	static std::string IntToString(int n) {
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	/*string��int�ɕϊ�*/
	static int StringToInt(std::string str) {
		int n;
		std::stringstream ss;
		ss << str;
		ss >> n;
		return n;
	}

	/*2�̃{�b�N�X�̏Փ˔���*/
	static bool CheckBoxHit(Box box1, Box box2) {
		if (box1.x <= box2.x + box2.width && box2.x <= box1.x + box1.width &&
			box1.y <= box2.y + box2.height && box2.y <= box1.y + box1.height) {
			return true;
		}
		return false;
	}
};