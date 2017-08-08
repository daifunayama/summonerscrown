#include "ArmsList.h"
#include "../Parameter.h"

/*魔具の登録*/
void ArmsList::init() {
	category[Parameter::HK].name = "HollyKnights";
	category[Parameter::CM].name = "Comander";
	category[Parameter::MG].name = "MasouGakudan";
	category[Parameter::YT].name = "Yoto";
	category[Parameter::HC].name = "HellClockworks";
	category[Parameter::EA].name = "EvilAnima";
	category[Parameter::AA].name = "ArticArts";
	category[Parameter::HR].name = "Heros";
	category[Parameter::MJ].name = "Majogari";
	category[Parameter::PS].name = "PrimalSpheres";

	//聖夜騎装
	category[Parameter::HK].arms[0] = "Aries";
	category[Parameter::HK].arms[1] = "Lepus";
	category[Parameter::HK].arms[2] = "Orion";
	category[Parameter::HK].arms[3] = "Southern";
	category[Parameter::HK].arms[4] = "Sagittarius";
	category[Parameter::HK].arms[5] = "Sign";
	category[Parameter::HK].arms[6] = "Hercules";
	category[Parameter::HK].arms[7] = "Lightning";

	//コマンダー
	category[Parameter::CM].arms[0] = "Spoter";
	category[Parameter::CM].arms[1] = "Cavalier";
	category[Parameter::CM].arms[2] = "Tigger";
	category[Parameter::CM].arms[3] = "Centurion";
	category[Parameter::CM].arms[4] = "Tigger";
	category[Parameter::CM].arms[5] = "Reloader";
	category[Parameter::CM].arms[6] = "Gustavus";
	category[Parameter::CM].arms[7] = "SilentShot";

	//魔奏楽団
	category[Parameter::MG].arms[0] = "Metoron";
	category[Parameter::MG].arms[1] = "Trumpeta";
	category[Parameter::MG].arms[2] = "Druma";
	category[Parameter::MG].arms[3] = "Vioris";
	category[Parameter::MG].arms[4] = "Harpion";
	category[Parameter::MG].arms[5] = "Encore";
	category[Parameter::MG].arms[6] = "Fortessimo";
	category[Parameter::MG].arms[7] = "Cymbales";

	//妖刀

	//煉獄機巧
	category[Parameter::HC].arms[0] = "Chain";
	category[Parameter::HC].arms[1] = "Maiden";
	category[Parameter::HC].arms[2] = "Phalaris";
	category[Parameter::HC].arms[3] = "Wheel";
	category[Parameter::HC].arms[4] = "Pendulum";
	category[Parameter::HC].arms[5] = "Executer";

	//イービルアニマ
	category[Parameter::EA].arms[0] = "Medusagi";
	category[Parameter::EA].arms[1] = "Inurito";
	category[Parameter::EA].arms[2] = "Enikuma";
	category[Parameter::EA].arms[3] = "ChimeLio";
	category[Parameter::EA].arms[4] = "Deal";

	//アーティックアーツ
	category[Parameter::AA].arms[0] = "Alpha";
	category[Parameter::AA].arms[1] = "Beta";
	category[Parameter::AA].arms[2] = "Ganma";

	//ヒーローズ
	category[Parameter::HR].arms[0] = "Yusha";
	category[Parameter::HR].arms[1] = "Shoota";
	category[Parameter::HR].arms[2] = "Fighter";
	category[Parameter::HR].arms[3] = "Beat";
	category[Parameter::HR].arms[4] = "Puzzle";
	category[Parameter::HR].arms[5] = "LevelUp";
	category[Parameter::HR].arms[6] = "DeathMatch";
	category[Parameter::HR].arms[7] = "BlackEnemin";
	category[Parameter::HR].arms[8] = "MetalEnemin";

	//魔女狩り
	category[Parameter::MJ].arms[0] = "Kama";

	//源創魔球
	category[Parameter::PS].arms[0] = "core";
	category[Parameter::PS].arms[1] = "Cyanos";
	category[Parameter::PS].arms[2] = "Yellon";
	category[Parameter::PS].arms[3] = "Magesta";
	category[Parameter::PS].arms[4] = "Instant";
}

std::string ArmsList::getCategoryName(int id) {
	return category[id].name;
}

std::string ArmsList::getCategoryPass(int id) {
	std::string pass;

	pass = "Data/arms/";
	pass += getCategoryName(id) + "/";
	return pass;
}

std::string ArmsList::getArmsName(int c, int id) {
	return category[c].arms[id];
}

std::string ArmsList::getArmsPass(int c, int id) {
	std::string pass;

	pass = "Data/arms/";
	pass += getCategoryName(c) + "/" + getArmsName(c, id) + "/";
	return pass;
}