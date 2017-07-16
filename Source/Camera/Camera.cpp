#include "Camera.h"

void Camera::Init() {
	mPositionX = 0;
	mPositionY = -250;
}

void Camera::Update(Player& p1, Player& p2) {
	//�v���C���[���m�̒��Ԃ̍��W�𓾂�
	mCenterX = (p1.getPositionX() + p2.getPositionX()) / 2;

	//�J�������ړ�������
	if (mCenterX < Parameter::WINDOW_WIDTH / 2)mCenterX = Parameter::WINDOW_WIDTH / 2;
	if (mCenterX > Parameter::FIELD_WIDTH - Parameter::WINDOW_WIDTH / 2)mCenterX = Parameter::FIELD_WIDTH - Parameter::WINDOW_WIDTH / 2;

	mPositionX = Parameter::WINDOW_WIDTH / 2 - mCenterX;

	//mCenterX = Parameter::WINDOW_WIDTH / 2;
	//mPositionX = -400;
}