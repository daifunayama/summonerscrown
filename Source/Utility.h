#pragma once
#include "HitBox/Box.h"
#include <string>
#include <sstream>

/*
汎用関数の定義クラス
*/
class Utility {
public:
	/*intをstringに変換*/
	static std::string IntToString(int n) {
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	/*stringをintに変換*/
	static int StringToInt(std::string str) {
		int n;
		std::stringstream ss;
		ss << str;
		ss >> n;
		return n;
	}

	/*2つのボックスの衝突判定*/
	static bool CheckBoxHit(Box box1, Box box2) {
		if (box1.x <= box2.x + box2.width && box2.x <= box1.x + box1.width &&
			box1.y <= box2.y + box2.height && box2.y <= box1.y + box1.height) {
			return true;
		}
		return false;
	}
};