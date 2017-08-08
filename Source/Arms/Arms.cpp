#include <fstream>
#include "Arms.h"
#include "ArmsList.h"

/*����N���X�Ƀv���C���[�Ɠ��͂��킽��*/
void Arms::ReceivePlayer(Player *player, Controller controller) {
	mPlayer = player;
	mController = controller;
}

void Arms::LoadArmsName() {
	ifstream ifs;
	string pass,tmp;

	pass = ArmsList::get().getArmsPass(getProfile().category, getProfile().id) + "profile.txt";

	ifs.open(pass.c_str());
	if (ifs) {
		ifs >> tmp;
		ifs >> mName;
		ifs >> tmp;
		ifs >> tmp;
		ifs >> mCondition;
	}
	ifs.close();
}