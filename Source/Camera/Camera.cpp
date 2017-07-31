#include "Camera.h"

void Camera::Init() {
	mPositionX = 0;
	mPositionY = -250;
}

void Camera::Update(Player& p1, Player& p2) {
	//プレイヤー同士の中間の座標を得る
	mCenterX = (p1.getPositionX() + p2.getPositionX()) / 2;
	mCenterY = (p1.getPositionY() + p2.getPositionY()) / 2;

	//カメラを移動させる
	if (mCenterX < Parameter::WINDOW_WIDTH / 2)mCenterX = Parameter::WINDOW_WIDTH / 2;
	if (mCenterX > Parameter::FIELD_WIDTH - Parameter::WINDOW_WIDTH / 2)mCenterX = Parameter::FIELD_WIDTH - Parameter::WINDOW_WIDTH / 2;

	if (mCenterY > Parameter::WINDOW_HEIGHT / 2)mCenterY = Parameter::WINDOW_HEIGHT / 2;
	if (mCenterY > Parameter::FIELD_HEIGHT - Parameter::WINDOW_HEIGHT / 2)mCenterY = Parameter::FIELD_HEIGHT - Parameter::WINDOW_HEIGHT / 2;

	mPositionX = Parameter::WINDOW_WIDTH / 2 - mCenterX;
	mPositionY = Parameter::WINDOW_HEIGHT / 2 - mCenterY-750;

	//mCenterX = Parameter::WINDOW_WIDTH / 2;
	//mPositionX = -400;
}