#pragma once
#include <string>

/*
各キャラクターのプロファイル定義
*/
struct Profile {
public:
	std::string name;	//名前
	std::string eName;	//名前(英語)
	std::string pass;	//スプライト用パス
	float size;			//スプライトのサイズ
	float speed;		//待機モーションの再生速度
	int distX;			//X座標補正
	int distY;			//X座標補正
	int cAtack;			//パラメータ：近接攻撃
	int lAtack;			//パラメータ：遠距離攻撃
	int pAtack;			//パラメータ：物理攻撃
	int sAtack;			//パラメータ：特殊攻撃
	int aut;			//パラメータ：オートマタ
};