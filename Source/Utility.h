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

	static string GetPAtackPass(string pass, int atack) {
		string atackName;

		if (atack == Parameter::P_ATACK_A)atackName = "a";
		if(atack == Parameter::P_ATACK_2A)atackName = "2a";
		if(atack == Parameter::P_ATACK_8A)atackName = "8a";
		if(atack == Parameter::P_ATACK_JA)atackName = "ja";
		if(atack == Parameter::P_ATACK_B)atackName = "b";
		if(atack == Parameter::P_ATACK_2B)atackName = "2b";
		if(atack == Parameter::P_ATACK_3B)atackName = "3b";
		if(atack == Parameter::P_ATACK_4B)atackName = "4b";
		if(atack == Parameter::P_ATACK_6B)atackName = "6b";
		if(atack == Parameter::P_ATACK_8B)atackName = "8b";
		if(atack == Parameter::P_ATACK_JB)atackName = "jb";
		if(atack == Parameter::P_ATACK_J2B)atackName = "j2b";
		if(atack == Parameter::P_ATACK_D1)atackName = "d1";
		if(atack == Parameter::P_ATACK_D2)atackName = "d2";
		if(atack == Parameter::P_ATACK_D3)atackName = "d3";
		if(atack == Parameter::P_ATACK_D4)atackName = "d4";
		if(atack == Parameter::P_ATACK_D5)atackName = "d5";

		return "Data/character/" + pass + "/AtackData/" + atackName + ".txt";
	}

	static string GetPAtackName(int atack) {
		string atackName;

		if (atack == Parameter::P_ATACK_A)atackName = "a";
		if (atack == Parameter::P_ATACK_2A)atackName = "2a";
		if (atack == Parameter::P_ATACK_8A)atackName = "8a";
		if (atack == Parameter::P_ATACK_JA)atackName = "ja";
		if (atack == Parameter::P_ATACK_B)atackName = "b";
		if (atack == Parameter::P_ATACK_2B)atackName = "2b";
		if (atack == Parameter::P_ATACK_3B)atackName = "3b";
		if (atack == Parameter::P_ATACK_4B)atackName = "4b";
		if (atack == Parameter::P_ATACK_6B)atackName = "6b";
		if (atack == Parameter::P_ATACK_8B)atackName = "8b";
		if (atack == Parameter::P_ATACK_JB)atackName = "jb";
		if (atack == Parameter::P_ATACK_J2B)atackName = "j2b";
		if (atack == Parameter::P_ATACK_D1)atackName = "d1";
		if (atack == Parameter::P_ATACK_D2)atackName = "d2";
		if (atack == Parameter::P_ATACK_D3)atackName = "d3";
		if (atack == Parameter::P_ATACK_D4)atackName = "d4";
		if (atack == Parameter::P_ATACK_D5)atackName = "d5";

		return atackName;
	}
};