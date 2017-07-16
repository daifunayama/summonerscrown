#pragma once
#include "../Player/Player.h"

class Player;

/*
�J�����̐�����s���V���O���g���p�^�[���N���X
*/
class Camera {
public:
	static Camera& getInstance(void) {
		static Camera camera;
		return camera;
	}
	Camera(const Camera&) = delete;
	Camera& operator = (const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera operator = (Camera&&) = delete;

	inline int getPositonX() { return mPositionX; }
	inline int getPositonY() { return mPositionY; }
	inline int getCenterX() { return mCenterX; }
	inline int getCenterY() { return mCenterY; }

	inline void setPositonX(int positionX) { mPositionX = positionX; }
	inline void setPositonY(int positionY) { mPositionY = positionY; }
	inline void setCenterX(int centerX) { mCenterX = centerX; }
	inline void setCenterY(int centerY) { mCenterY = centerY; }
	void Init();
	void Update(Player& p1, Player& p2);

private:
	int mPositionX;		//�J������X���W
	int mPositionY;		//�J������Y���W
	int mCenterX;		//��ʒ�����X���W
	int mCenterY;		//��ʒ�����Y���W

private:
	Camera() {}
	~Camera() {}
};