#include "Arms.h"

/*武器クラスにプレイヤーと入力をわたす*/
void Arms::ReceivePlayer(Player *player, Controller controller) {
	mPlayer = player;
	mController = controller;
}